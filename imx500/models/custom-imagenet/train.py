import torch
import torch.nn as nn
import torch.optim as optim
from torchvision import datasets, transforms, models
import model_compression_toolkit as mct
from model_compression_toolkit.exporter import pytorch_export_model
import os

DATASET_PATH = "my_dataset"
IMG_SIZE = 224
BATCH_SIZE = 8
EPOCHS = 3
DEVICE = torch.device("cuda" if torch.cuda.is_available() else "cpu")

print(f"Using device: {DEVICE}")

data_transforms = transforms.Compose([
    transforms.Resize((IMG_SIZE, IMG_SIZE)),
    transforms.ToTensor(),
])

print(f"Loading data from {DATASET_PATH}...")
train_dataset = datasets.ImageFolder(DATASET_PATH, transform=data_transforms)
train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=BATCH_SIZE, shuffle=True)

class_names = train_dataset.classes
print(f"CLASSES: {class_names}")

model = models.mobilenet_v2(weights=models.MobileNet_V2_Weights.DEFAULT)

num_ftrs = model.classifier[1].in_features
model.classifier[1] = nn.Linear(num_ftrs, len(class_names))

model = model.to(DEVICE)

criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)

print("\nStarting Training")
model.train()
for epoch in range(EPOCHS):
    running_loss = 0.0
    for inputs, labels in train_loader:
        inputs, labels = inputs.to(DEVICE), labels.to(DEVICE)

        optimizer.zero_grad()
        outputs = model(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        running_loss += loss.item()
    
    print(f"Epoch {epoch+1}/{EPOCHS}, Loss: {running_loss/len(train_loader):.4f}")

print("Training done")

print("\nStarting Sony IMX500 Quantization...")

model.eval()
model.cpu()

def rep_data_gen():
    calib_loader = torch.utils.data.DataLoader(train_dataset, batch_size=1, shuffle=True)
    for i, (image, _) in enumerate(calib_loader):
        if i >= 50: break
        yield [image]

tpc = mct.get_target_platform_capabilities("pytorch", "imx500")

quantized_model, _ = mct.ptq.pytorch_post_training_quantization(
    in_module=model,
    representative_data_gen=rep_data_gen,
    target_platform_capabilities=tpc
)

print("\nONNX exporting")

SAVE_PATH = "cat_dog_imx.onnx"

mct.exporter.pytorch_export_model(
    model=quantized_model,
    save_model_path=SAVE_PATH,
    repr_dataset=rep_data_gen,
)

print(f"\nModel saved to: {os.path.abspath(SAVE_PATH)}")
