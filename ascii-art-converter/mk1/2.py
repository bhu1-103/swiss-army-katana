from PIL import Image
import numpy as np

# Load the image
image_path = "pic.png"
image = Image.open(image_path).convert("RGB")
grayscaled = image.convert('L')

COLORS = "@%*=-:. "
width, height = grayscaled.size
aspect_ratio = float(height) / float(width)
resolution = 100
new_w = resolution
#new_h = int(aspect_ratio * resolution * 0.357)  # Height adjustment for ASCII aspect ratio
new_h = int(aspect_ratio * resolution * 11/25)
resized_gray = grayscaled.resize((new_w, new_h))
pixels_gray = np.array(resized_gray)

# Load the RGB values for colors
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

print(colored_ascii_art)
