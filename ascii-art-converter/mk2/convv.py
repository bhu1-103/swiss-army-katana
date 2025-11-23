import os
from PIL import Image
import numpy as np

frames_folder = "frames"
output_folder = "frames-t"

if not os.path.exists(output_folder):
    os.makedirs(output_folder)

COLORS = "@%*=-:. "
resolution = 100

def image_to_ascii(image_path):
    image = Image.open(image_path).convert("RGB")
    grayscaled = image.convert('L')

    width, height = grayscaled.size
    aspect_ratio = float(height) / float(width)
    new_w = resolution
    new_h = int(aspect_ratio * resolution * 11/25)
    resized_gray = grayscaled.resize((new_w, new_h))
    pixels_gray = np.array(resized_gray)

    resized_color = image.resize((new_w, new_h))
    pixels_color = np.array(resized_color)

    limit = (pixels_gray / 255) * 7
    ascii_pixels = [COLORS[int(pixel)] for pixel in limit.flatten()]

    def rgb_to_ansi(r, g, b):
        return f"\033[38;2;{r};{g};{b}m"

    colored_ascii_art = ""
    for i in range(new_h):
        for j in range(new_w):
            gray_char = ascii_pixels[i * new_w + j]
            r, g, b = pixels_color[i, j][:3]
            ansi_code = rgb_to_ansi(r, g, b)
            colored_ascii_art += f"{ansi_code}{gray_char}\033[0m"
        colored_ascii_art += "\n"

    return colored_ascii_art

for frame_filename in os.listdir(frames_folder):
    if frame_filename.endswith(".png"):
        frame_path = os.path.join(frames_folder, frame_filename)
        ascii_art = image_to_ascii(frame_path)
        output_filename = frame_filename.replace(".png", ".txt")
        output_path = os.path.join(output_folder, output_filename)

        with open(output_path, "w") as output_file:
            output_file.write(ascii_art)

        print(f"Processed: {frame_filename} -> {output_filename}")
