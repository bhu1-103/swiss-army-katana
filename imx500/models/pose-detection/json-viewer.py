import pygame
import json
import sys
import os

JSON_FILE = "pose_data.json"
WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600
FPS = 15

COLOR_BG = (10, 10, 18)
COLOR_GRID = (30, 30, 40)
COLOR_HUD = (0, 255, 100)

COLOR_L_CORE = (255, 0, 150)
COLOR_L_GLOW = (255, 0, 150)

COLOR_R_CORE = (0, 200, 255)
COLOR_R_GLOW = (0, 200, 255)

COLOR_C_CORE = (200, 255, 200)
COLOR_C_GLOW = (0, 255, 100)

COLOR_JOINT = (255, 255, 255)

CYBER_BONES = [
    ("nose", "left_eye", 'C'), ("nose", "right_eye", 'C'),
    ("left_eye", "left_ear", 'L'), ("right_eye", "right_ear", 'R'),

    ("left_shoulder", "left_elbow", 'L'), ("left_elbow", "left_wrist", 'L'),
    ("right_shoulder", "right_elbow", 'R'), ("right_elbow", "right_wrist", 'R'),

    ("left_shoulder", "right_shoulder", 'C'),
    ("left_shoulder", "left_hip", 'L'), ("right_shoulder", "right_hip", 'R'),
    ("left_hip", "right_hip", 'C'),

    ("left_hip", "left_knee", 'L'), ("left_knee", "left_ankle", 'L'),
    ("right_hip", "right_knee", 'R'), ("right_knee", "right_ankle", 'R')
]

def load_data():
    if not os.path.exists(JSON_FILE):
        print(f"❌ Error: {JSON_FILE} not found!")
        sys.exit(1)
    with open(JSON_FILE, "r") as f:
        return json.load(f)

def draw_neon_line(surface, start_pos, end_pos, core_color, glow_color):
    pygame.draw.line(surface, [c//2 for c in glow_color], start_pos, end_pos, 8) 
    pygame.draw.line(surface, core_color, start_pos, end_pos, 2)

def main():
    pygame.init()
    screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
    pygame.display.set_caption("bhu5 - memory recollect mode")
    clock = pygame.time.Clock()
    
    try:
        font_large = pygame.font.Font(None, 40)
        font_small = pygame.font.Font(None, 24)
    except:
        font_large = pygame.font.SysFont("monospace", 30)
        font_small = pygame.font.SysFont("monospace", 18)

    data = load_data()
    total_frames = len(data)
    print(f"oaded {total_frames} frames from {JSON_FILE}")

    current_frame = 0
    paused = False
    running = True

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    paused = not paused
                elif event.key == pygame.K_RIGHT:
                    current_frame = (current_frame + 1) % total_frames
                elif event.key == pygame.K_LEFT:
                    current_frame = (current_frame - 1) % total_frames
                elif event.key == pygame.K_ESCAPE:
                    running = False

        screen.fill(COLOR_BG)
        
        for x in range(0, WINDOW_WIDTH, 50):
            pygame.draw.line(screen, COLOR_GRID, (x, 0), (x, WINDOW_HEIGHT), 1)
        for y in range(0, WINDOW_HEIGHT, 50):
            pygame.draw.line(screen, COLOR_GRID, (0, y), (WINDOW_WIDTH, y), 1)

        if total_frames > 0:
            frame_data = data[current_frame]
            people = frame_data["people"]

            for person in people:
                joints = person["joints"]

                for start_bone, end_bone, side in CYBER_BONES:
                    if start_bone in joints and end_bone in joints:
                        x1 = int(joints[start_bone]["x"] * WINDOW_WIDTH)
                        y1 = int(joints[start_bone]["y"] * WINDOW_HEIGHT)
                        x2 = int(joints[end_bone]["x"] * WINDOW_WIDTH)
                        y2 = int(joints[end_bone]["y"] * WINDOW_HEIGHT)

                        if x1 > 0 and x2 > 0:
                            if side == 'L':
                                c_core, c_glow = COLOR_L_CORE, COLOR_L_GLOW
                            elif side == 'R':
                                c_core, c_glow = COLOR_R_CORE, COLOR_R_GLOW
                            else:
                                c_core, c_glow = COLOR_C_CORE, COLOR_C_GLOW
                            
                            draw_neon_line(screen, (x1, y1), (x2, y2), c_core, c_glow)

                for joint_name, coords in joints.items():
                    x = int(coords["x"] * WINDOW_WIDTH)
                    y = int(coords["y"] * WINDOW_HEIGHT)
                    if x > 0:
                        pygame.draw.circle(screen, COLOR_JOINT, (x, y), 3)

        status_text = "PAUSED" if paused else "PLAYING"
        pygame.draw.rect(screen, (0, 40, 0), (10, 10, 200, 60))
        pygame.draw.rect(screen, COLOR_HUD, (10, 10, 200, 60), 1)
        
        lbl_status = font_large.render(status_text, True, COLOR_HUD)
        lbl_frame = font_small.render(f"FRM: {current_frame:04d} / {total_frames:04d}", True, COLOR_HUD)
        
        screen.blit(lbl_status, (20, 20))
        screen.blit(lbl_frame, (20, 50))

        lbl_controls = font_small.render("[SPACE] PAUSE  [ARROWS] SEEK  [ESC] EXIT", True, (100, 100, 100))
        screen.blit(lbl_controls, (10, WINDOW_HEIGHT - 30))

        pygame.display.flip()

        if not paused:
            current_frame += 1
            if current_frame >= total_frames:
                current_frame = 0
            clock.tick(FPS)
        else:
            clock.tick(10)

    pygame.quit()

if __name__ == "__main__":
    main()
