///
/// @file
///

#include "perception/model/net.h"

namespace perception
{
Net::Net()
    : fc1_{register_module("fc1", torch::nn::Linear(784, 64))},
      fc2_{register_module("fc2", torch::nn::Linear(64, 32))},
      fc3_{register_module("fc3", torch::nn::Linear(32, 10))}
{
}

torch::Tensor Net::forward(torch::Tensor tensor)
{
    const auto p = 0.5;
    const auto dim = 1;
    tensor = torch::relu(fc1_->forward(tensor.reshape({tensor.size(0), 784})));
    tensor = torch::dropout(tensor, p, is_training());
    tensor = torch::relu(fc2_->forward(tensor));
    tensor = torch::log_softmax(fc3_->forward(tensor), dim);
    return tensor;
}
}  // namespace perception