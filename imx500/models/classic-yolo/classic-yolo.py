import pygame
import numpy as np
import sys
import os
from modlib.devices import AiCamera
from modlib.models import COLOR_FORMAT, MODEL_TYPE, Model
from modlib.models.post_processors import pp_od_yolo_ultralytics

BASE_PATH = "/home/bhu5/models/4-yolov8/yolo11n/yolo11n_imx_model"
ZIP_PATH = os.path.join(BASE_PATH, "packerOut.zip")
LABELS_PATH = os.path.join(BASE_PATH, "labels.txt")

CAMERA_FPS = 15
WINDOW_W = 640
WINDOW_H = 480

COLOR_BG = (0, 0, 0)
COLOR_HUD = (0, 255, 255)
COLOR_ACCENT = (255, 0, 255)
COLOR_TEXT = (255, 255, 255)
COLOR_DIM = (40, 40, 40)

class YOLO(Model):
    def __init__(self):
        super().__init__(
            model_file=ZIP_PATH,
            model_type=MODEL_TYPE.CONVERTED,
            color_format=COLOR_FORMAT.RGB,
            preserve_aspect_ratio=True,
        )
        if os.path.exists(LABELS_PATH):
            self.labels = np.genfromtxt(LABELS_PATH, dtype=str, delimiter="\n")
        else:
            self.labels = [f"Class {i}" for i in range(100)]

    def post_process(self, output_tensors):
        return pp_od_yolo_ultralytics(output_tensors)

def draw_tactical_corners(surface, color, rect, length=15, thickness=2):
    """Draws only the corners of a rectangle for a cleaner look."""
    x, y, w, h = rect
    
    pygame.draw.line(surface, color, (x, y), (x + length, y), thickness)
    pygame.draw.line(surface, color, (x, y), (x, y + length), thickness)
    pygame.draw.line(surface, color, (x + w, y), (x + w - length, y), thickness)
    pygame.draw.line(surface, color, (x + w, y), (x + w, y + length), thickness)
    pygame.draw.line(surface, color, (x, y + h), (x + length, y + h), thickness)
    pygame.draw.line(surface, color, (x, y + h), (x, y + h - length), thickness)
    pygame.draw.line(surface, color, (x + w, y + h), (x + w - length, y + h), thickness)
    pygame.draw.line(surface, color, (x + w, y + h), (x + w, y + h - length), thickness)

pygame.init()
screen = pygame.display.set_mode((WINDOW_W, WINDOW_H))
pygame.display.set_caption("TACTICAL FEED")
clock = pygame.time.Clock()

try:
    font_main = pygame.font.Font(None, 24)
    font_small = pygame.font.SysFont("monospace", 14)
except:
    font_main = pygame.font.SysFont("arial", 20)
    font_small = pygame.font.SysFont("monospace", 14)

device = AiCamera(frame_rate=CAMERA_FPS)
model = YOLO()
device.deploy(model, overwrite=False)

try:
    with device as stream:
        for frame in stream:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    raise KeyboardInterrupt
                if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                    raise KeyboardInterrupt

            screen.fill(COLOR_BG)
            
            cx, cy = WINDOW_W // 2, WINDOW_H // 2
            pygame.draw.line(screen, COLOR_DIM, (cx-20, cy), (cx+20, cy), 1)
            pygame.draw.line(screen, COLOR_DIM, (cx, cy-20), (cx, cy+20), 1)
            pygame.draw.rect(screen, COLOR_DIM, (10, 10, WINDOW_W-20, WINDOW_H-20), 1)

            detections = list(frame.detections)
            
            for det in detections:
                try:
                    bbox, score, class_id, _ = det
                except ValueError:
                    continue
                
                if score < 0.20: continue

                color = COLOR_HUD if int(class_id) % 2 == 0 else COLOR_ACCENT

                raw_x1, raw_y1, raw_x2, raw_y2 = bbox
                x1 = int(raw_x1 * WINDOW_W)
                y1 = int(raw_y1 * WINDOW_H)
                x2 = int(raw_x2 * WINDOW_W)
                y2 = int(raw_y2 * WINDOW_H)
                w = x2 - x1
                h = y2 - y1

                draw_tactical_corners(screen, color, (x1, y1, w, h), length=20, thickness=2)
                
                label_text = f"{model.labels[int(class_id)].upper()} [{int(score*100)}%]"
                text_surf = font_small.render(label_text, True, color)
                
                bg_rect = text_surf.get_rect(topleft=(x1 + 5, y1 + 5))
                pygame.draw.rect(screen, (0,0,0), bg_rect) 
                screen.blit(text_surf, bg_rect)

            fps_text = f"SYS: {int(clock.get_fps())} | NET: {len(detections)}"
            screen.blit(font_small.render(fps_text, True, COLOR_DIM), (20, WINDOW_H - 30))

            pygame.display.flip()
            clock.tick(30)

except KeyboardInterrupt:
    pass
finally:
    pygame.quit()
    sys.exit()
