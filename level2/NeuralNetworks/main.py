import torch
import torch.nn as nn
import torch.nn.functional as F
from torchvision import datasets, transforms

device = torch.device("cuda" if torch.cuda.is_available() else "cpu") #如果可行，使用GPU

epoches = 100
learning_rate = 0.001
batch_size = 128

transform = transforms.Compose([transforms.ToTensor()]) #这里的compose作为一个容器将多种对图像的操作组合起来，尽管在此处只调用了一个将图像转为Tensor的操作

train_dataset = datasets.MNIST(root='./data', train=True, download=True, transform=transform)
test_dataset = datasets.MNIST(root='./data', train=False, download=True, transform=transform)

train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=64, shuffle=True) #batch_size 每次输入数据量
test_loader = torch.utils.data.DataLoader(test_dataset, batch_size=64, shuffle=False)


class NeuralNetwork(nn.Module):
    def __init__(self):
        super(NeuralNetwork, self).__init__()
        self.fc1 = nn.Linear(784, 100)
        self.fc2 = nn.Linear(100, 100)
        self.fc3 = nn.Linear(100, 10)
    def forward(self, x):
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = F.log_softmax(self.fc3(x), dim=1)
        return x

net = NeuralNetwork().to(device)
optimizer = torch.optim.Adam(net.parameters(), lr=learning_rate) #只有类才有parameters方法，其返回所有可训练参数

def evaluate(test_data):
    correct = 0
    total = 0
    with torch.no_grad(): #上下文管理器
        for data, target in test_data:
            data, target = data.to(device), target.to(device)
            output = net(data.view(-1, 28*28))
            _, predicted = torch.max(output.data, 1) #_, :忽略多余返回值
            correct += (predicted == target).sum().item()
            total += data.size(0)

    return correct / total


for epoch in range(epoches):
    net.train()
    for data, target in train_loader:
        data = data.view(-1, 28*28)
        data, target = data.to(device), target.to(device)
        optimizer.zero_grad()
        output = net(data)
        #这里不使用net.forward(data)的原因是NeuralNetwork类继承自nn.Module，而nn.Module类中定义了__call__方法，会自动调用forward函数
        #net(data) 等同于 net.__call__(data)
        loss = F.nll_loss(output, target)
        loss.backward()
        optimizer.step()
    print(evaluate(test_loader))