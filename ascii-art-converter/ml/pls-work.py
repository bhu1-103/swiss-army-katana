import torch
from PIL import Image
import numpy as np
#from model import ImageToASCIIModel

COLORS = "@%*=-:. "
idx_to_char = {i: c for i, c in enumerate(COLORS)}

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
vocab_size = len(COLORS)
max_length = 50 * 20
model = ImageToASCIIModel(vocab_size, max_length).to(device)
model.load_state_dict(torch.load("image_to_ascii_model.pth"))
model.eval()

def generate_ascii(model, image_path, resolution=50):
    image = Image.open(image_path).convert("L")

    image = image.resize((28, 28))

    image = np.array(image) / 255.0

    image = torch.Tensor(image).unsqueeze(0).unsqueeze(0).to(device)

    with torch.no_grad():
        outputs = model(image)

        outputs = outputs.argmax(dim=-1).squeeze().cpu().numpy()
        ascii_art = "".join(idx_to_char[idx] for idx in outputs)

        ascii_lines = [ascii_art[i:i+resolution] for i in range(0, len(ascii_art), resolution)]
        return "\n".join(ascii_lines)

result = generate_ascii(model, "input.jpg")
print(result)
