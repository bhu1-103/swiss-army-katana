from PIL import Image
import numpy as np

image_path = "pic.png"
image = Image.open(image_path)

grayscaled = image.convert('L')

COLORS = "@%*=-:. "

width, height = grayscaled.size
aspect_ratio = float(height)/float(width)
resolution = 50
new_w = resolution
new_h = int(aspect_ratio * resolution * 11/25) #used 11/25 because that's the ratio of height vs width for the font i am using right now, ShureTech Nerd Font
#new_h = int(aspect_ratio * resolution * 0.357)
resized = grayscaled.resize((new_w,new_h))
pixels = np.array(resized)

limit = (pixels/255) * 7
ascii_pixels = [COLORS[int(pixel)] for pixel in limit.flatten()]

image = "\n".join(["".join(row) for row in np.reshape(ascii_pixels, (new_h, new_w))])

print(image)
