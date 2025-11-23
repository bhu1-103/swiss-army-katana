import os
import numpy as np
from PIL import Image

COLORS = "@%*=-:. "
char_to_idx = {c: i for i, c in enumerate(COLORS)}
idx_to_char = {i: c for c, i in char_to_idx.items()}

def encode_ascii(ascii_art, max_length):
    encoded = [char_to_idx[c] for c in ascii_art.replace("\n", "")]
    return np.pad(encoded, (0, max_length - len(encoded)), constant_values=0)

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

def load_data(image_folder, ascii_folder, resolution=50):
    images = []
    ascii_seqs = []
    max_length = resolution * resolution
    
    for i in range(len(os.listdir(image_folder))):
        image_path = os.path.join(image_folder, f"mnist_{i}.png")
        image = np.array(Image.open(image_path)) / 255.0
        
        ascii_path = os.path.join(ascii_folder, f"ascii_{i}.txt")
        with open(ascii_path, "r") as f:
            ascii_art = f.read()
        ascii_seq = encode_ascii(ascii_art, max_length)
        
        images.append(image)
        ascii_seqs.append(ascii_seq)

    return np.array(images), np.array(ascii_seqs)

X, y = load_data("mnist_images", "ascii_art")

np.save("X.npy", X)
np.save("y.npy", y)

print("Data prepared and saved as X.npy and y.npy.")
