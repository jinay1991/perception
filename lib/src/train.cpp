///
/// @file
///
#include "perception/model/train.h"

namespace perception
{
void Runner::SetNetwork(const Net& net) { net_ = net; }

void Runner::Train()
{
    const auto batch_size = 64;
    const auto learning_rate = 0.01;

    auto net = std::make_shared<Net>();

    auto data_loader = torch::data::make_data_loader(
        torch::data::datasets::MNIST("/Users/jinay/workspace/git-repo/ad-platform/perception/data")
            .map(torch::data::transforms::Stack<>()),
        batch_size);

    torch::optim::SGD optimizer(net->parameters(), learning_rate);

    for (size_t epoch = 1; epoch <= 1; ++epoch)
    {
        size_t batch_index = 0;
        for (auto& batch : *data_loader)
        {
            optimizer.zero_grad();

            torch::Tensor prediction = net->forward(batch.data);

            torch::Tensor loss = torch::nll_loss(prediction, batch.target);

            loss.backward();

            optimizer.step();

            if (++batch_index % 100 == 0)
            {
                std::cout << "Epoch: " << epoch << " | Batch: " << batch_index << " | Loss: " << loss.item<float>()
                          << std::endl;
                torch::save(net, "net.pt");
            }
        }
    }
}

void Runner::Test() {}

}  // namespace perception