import os
from tensorflow.keras.datasets import mnist
from PIL import Image
import numpy as np

os.makedirs("mnist_images", exist_ok=True)
os.makedirs("ascii_art", exist_ok=True)

COLORS = "@%*=-:. "

def image_to_ascii(image, resolution=50):
    aspect_ratio = image.shape[0] / image.shape[1]
    new_w = resolution
    new_h = int(aspect_ratio * resolution * 11 / 25)
    resized = Image.fromarray(image).resize((new_w, new_h)).convert("L")
    pixels = np.array(resized)
    
    limit = (pixels / 255) * (len(COLORS) - 1)
    ascii_pixels = [COLORS[int(pixel)] for pixel in limit.flatten()]
    
    ascii_image = "\n".join(
        ["".join(ascii_pixels[i * new_w:(i + 1) * new_w]) for i in range(new_h)]
    )
    return ascii_image

(x_train, y_train), _ = mnist.load_data()

for i, image in enumerate(x_train[:10000]):
    image_path = f"mnist_images/mnist_{i}.png"
    Image.fromarray(image).save(image_path)
    
    ascii_art = image_to_ascii(image, resolution=50)
    ascii_path = f"ascii_art/ascii_{i}.txt"
    with open(ascii_path, "w") as f:
        f.write(ascii_art)

    if i % 10 == 0:
        print(f"Processed {i+1}/10000 images.")

print("All files saved.")
