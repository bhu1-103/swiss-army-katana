import json
import time
import sys
import os
import pygame
from modlib.devices import AiCamera
from modlib.models import COLOR_FORMAT, MODEL_TYPE, Model
from modlib.models.post_processors import pp_yolo_pose_ultralytics

ZIP_PATH = "/home/bhu5/models/4-yolov8/yolo11n/yolo11n-pose_imx_model/packerOut.zip"
OUTPUT_FILE = "pose_data.json"
DURATION_SEC = 120
CAMERA_FPS = 20 

WINDOW_W = 640
WINDOW_H = 480
COLOR_BG = (20, 20, 20)
COLOR_BONE = (0, 255, 255)
COLOR_JOINT = (255, 255, 0)

KEYPOINT_NAMES = [
    "nose", "left_eye", "right_eye", "left_ear", "right_ear",
    "left_shoulder", "right_shoulder", "left_elbow", "right_elbow",
    "left_wrist", "right_wrist", "left_hip", "right_hip",
    "left_knee", "right_knee", "left_ankle", "right_ankle"
]

SKELETON_CONNECTIONS = [
    ("nose", "left_eye"), ("nose", "right_eye"),
    ("left_eye", "left_ear"), ("right_eye", "right_ear"),
    ("left_shoulder", "right_shoulder"),
    ("left_shoulder", "left_elbow"), ("left_elbow", "left_wrist"),
    ("right_shoulder", "right_elbow"), ("right_elbow", "right_wrist"),
    ("left_shoulder", "left_hip"), ("right_shoulder", "right_hip"),
    ("left_hip", "right_hip"),
    ("left_hip", "left_knee"), ("left_knee", "left_ankle"),
    ("right_hip", "right_knee"), ("right_knee", "right_ankle")
]

class YOLOPose(Model):
    def __init__(self):
        super().__init__(
            model_file=ZIP_PATH,
            model_type=MODEL_TYPE.CONVERTED,
            color_format=COLOR_FORMAT.RGB,
            preserve_aspect_ratio=True,
        )

    def post_process(self, output_tensors):
        return pp_yolo_pose_ultralytics(output_tensors)

pygame.init()
screen = pygame.display.set_mode((WINDOW_W, WINDOW_H))
pygame.display.set_caption("bhu5 vision activated")
clock = pygame.time.Clock()

device = AiCamera(frame_rate=CAMERA_FPS)
model = YOLOPose()
device.deploy(model, overwrite=False)

full_recording = []

print(f"{DURATION_SEC}")

try:
    with device as stream:
        start_time = time.time()
        frame_count = 0
        
        for frame in stream:
            for event in pygame.event.get():
                if event.type == pygame.QUIT or (event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE):
                    raise KeyboardInterrupt

            screen.fill(COLOR_BG)
            
            now = time.time()
            elapsed = now - start_time
            if elapsed > DURATION_SEC:
                print("\nstopping")
                break

            frame_data = {
                "frame_id": frame_count,
                "timestamp": round(elapsed, 4),
                "people": []
            }

            poses = frame.detections
            
            if hasattr(poses, 'confidence') and poses.confidence is not None:
                num_people = len(poses.confidence)
                
                for i in range(num_people):
                    score = float(poses.confidence[i])
                    if score > 0.40:
                        person_joints = {}
                        
                        person_data = {
                            "person_index": i,
                            "confidence": round(score, 3),
                            "joints": {}
                        }

                        if hasattr(poses, 'keypoints') and poses.keypoints is not None:
                            kpts = poses.keypoints[i]
                            
                            for k_idx, k_name in enumerate(KEYPOINT_NAMES):
                                x_norm = float(kpts[k_idx][0])
                                y_norm = float(kpts[k_idx][1])
                                
                                if x_norm > 0 or y_norm > 0:
                                    person_data["joints"][k_name] = {
                                        "x": round(x_norm, 4),
                                        "y": round(y_norm, 4)
                                    }
                                    
                                    px = int(x_norm * WINDOW_W)
                                    py = int(y_norm * WINDOW_H)
                                    person_joints[k_name] = (px, py)

                        frame_data["people"].append(person_data)

                        for start_b, end_b in SKELETON_CONNECTIONS:
                            if start_b in person_joints and end_b in person_joints:
                                pygame.draw.line(screen, COLOR_BONE, person_joints[start_b], person_joints[end_b], 2)
                        
                        for j_name, coord in person_joints.items():
                            pygame.draw.circle(screen, COLOR_JOINT, coord, 4)

            pygame.display.flip()
            full_recording.append(frame_data)
            
            frame_count += 1
            if frame_count % 10 == 0:
                print(f"frame: {frame_count} | {elapsed:.1f}s")

except KeyboardInterrupt:
    print("\nStopping...")

finally:
    pygame.quit()
    with open(OUTPUT_FILE, "w") as f:
        json.dump(full_recording, f, indent=2)
