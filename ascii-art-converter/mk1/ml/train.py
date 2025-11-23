import torch
import torch.nn as nn
import torch.optim as optim
import numpy as np
#from model import ImageToASCIIModel

X = np.load("X.npy")
y = np.load("y.npy")

vocab_size = len("@%*=-:. ")
max_length = y.shape[1]
batch_size = 32
epochs = 10
learning_rate = 0.001

X = torch.Tensor(X).unsqueeze(1)
y = torch.LongTensor(y)
dataset = torch.utils.data.TensorDataset(X, y)
dataloader = torch.utils.data.DataLoader(dataset, batch_size=batch_size, shuffle=True)

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model = ImageToASCIIModel(vocab_size, max_length).to(device)
criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=learning_rate)

for epoch in range(epochs):
    model.train()
    epoch_loss = 0
    batch_count = len(dataloader)

    for batch_idx, (images, labels) in enumerate(dataloader):
        images, labels = images.to(device), labels.to(device)
        outputs = model(images)
        outputs = outputs.view(-1, vocab_size)
        labels = labels.view(-1)
        loss = criterion(outputs, labels)
        epoch_loss += loss.item()
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        if batch_idx % 100 == 0:
            print(f"Epoch {epoch+1}/{epochs}, Batch {batch_idx}/{batch_count}, Loss: {loss.item():.4f}")

    print(f"Epoch {epoch+1}/{epochs} completed. Average Loss: {epoch_loss / batch_count:.4f}")

torch.save(model.state_dict(), "image_to_ascii_model.pth")
print("Model training complete and saved!")
