import torch
import torch.nn as nn
import torch.nn.functional as F

class ImageToASCIIModel(nn.Module):
    def __init__(self, vocab_size, max_length):
        super(ImageToASCIIModel, self).__init__()
        self.vocab_size = vocab_size
        self.max_length = max_length

        self.cnn = nn.Sequential(
            nn.Conv2d(1, 32, kernel_size=3, stride=1, padding=1),
            nn.ReLU(),
            nn.MaxPool2d(2, 2),
            nn.Conv2d(32, 64, kernel_size=3, stride=1, padding=1),
            nn.ReLU(),
            nn.MaxPool2d(2, 2)
        )

        self.lstm = nn.LSTM(input_size=64 * 7 * 7, hidden_size=128, num_layers=2, batch_first=True)

        self.fc = nn.Linear(128, vocab_size)

    def forward(self, x):
        batch_size = x.size(0)

        features = self.cnn(x)

        features = features.view(batch_size, -1)

        features = features.unsqueeze(1).repeat(1, self.max_length, 1)

        lstm_out, _ = self.lstm(features)

        outputs = self.fc(lstm_out)

        outputs = F.softmax(outputs, dim=-1)

        return outputs
