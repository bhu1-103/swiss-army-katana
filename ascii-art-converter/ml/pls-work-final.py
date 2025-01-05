import torch
from torchvision import datasets, transforms
import numpy as np
from torch.utils.data import DataLoader

COLORS = "@%*=-:. "
idx_to_char = {i: c for i, c in enumerate(COLORS)}

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
vocab_size = len(COLORS)
max_length = 50 * 20
model = ImageToASCIIModel(vocab_size, max_length).to(device)
model.load_state_dict(torch.load("image_to_ascii_model.pth"))
model.eval()

transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.5,), (0.5,))  
])

mnist_test = datasets.MNIST(root='./data', train=False, download=True, transform=transform)

test_loader = DataLoader(mnist_test, batch_size=1, shuffle=True)

def generate_ascii(model, image_tensor, resolution=50):
    image_tensor = image_tensor.to(device)

    with torch.no_grad():
        outputs = model(image_tensor)

        print(f"Raw Model Output: {outputs}")

        outputs = outputs.argmax(dim=-1).squeeze().cpu().numpy()
        ascii_art = "".join(idx_to_char[idx] for idx in outputs)

        ascii_lines = [ascii_art[i:i+resolution] for i in range(0, len(ascii_art), resolution)]
        return "\n".join(ascii_lines)

def normalize_and_map(image_array, colors):
    normalized = (image_array - image_array.min()) / (image_array.max() - image_array.min())
    
    num_colors = len(colors)
    indices = (normalized * (num_colors - 1)).astype(int)
    
    mapped_chars = np.vectorize(lambda x: colors[x])(indices)
    
    return mapped_chars

for i, (image, label) in enumerate(test_loader):
    print(f"Processing label: {label.item()}")
    
    scaled_image = (image + 2).squeeze().numpy()
    
    ascii_chars = normalize_and_map(scaled_image, COLORS)
    ascii_art = "\n".join(["".join(row) for row in ascii_chars])
    
    print(ascii_art)
    break
