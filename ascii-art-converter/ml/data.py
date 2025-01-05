from PIL import Image
import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt

(x_train, y_train), (_, _) = tf.keras.datasets.mnist.load_data()

example_image = x_train[0]
example_label = y_train[0]
print(f"Label: {example_label}")

COLORS = "@%*=-:. "

def image_to_ascii(image, resolution=50):
    grayscaled = Image.fromarray(image).convert('L')
    
    aspect_ratio = grayscaled.size[1] / grayscaled.size[0]
    new_w = resolution
    new_h = int(aspect_ratio * resolution * 11 / 25)
    resized = grayscaled.resize((new_w, new_h))

    pixels = np.array(resized)
    limit = (pixels / 255) * (len(COLORS) - 1)
    ascii_pixels = [COLORS[int(pixel)] for pixel in limit.flatten()]

    ascii_image = "\n".join(
        ["".join(row) for row in np.reshape(ascii_pixels, (new_h, new_w))]
    )
    return ascii_image

ascii_art = image_to_ascii(example_image, resolution=50)
print(ascii_art)

plt.imshow(example_image, cmap='gray')
plt.title(f"Original MNIST Image (Label: {example_label})")
plt.show()
