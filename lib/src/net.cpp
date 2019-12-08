///
/// @file
///

#include "perception/model/net.h"

namespace perception
{
Net::Net()
    : conv1_{torch::nn::Conv2dOptions{1, 6, 5}},
      pool1_{torch::nn::MaxPool2dOptions{2}},
      conv2_{torch::nn::Conv2dOptions{6, 16, 5}},
      pool2_{torch::nn::MaxPool2dOptions{2}},
      conv3_{torch::nn::Conv2dOptions{16, 120, 4}},
      fc1_{torch::nn::LinearOptions{120, 84}},
      fc2_{torch::nn::LinearOptions{84, 10}}
{
    register_module("c1", conv1_);
    register_module("s2", pool1_);
    register_module("c3", conv2_);
    register_module("s4", pool2_);
    register_module("c5", conv3_);
    register_module("f6", fc1_);
    register_module("f7", fc2_);
}

torch::Tensor Net::forward(torch::Tensor& tensor)
{
    const auto p = 0.5;
    const auto dim = 1;

    // c1 Input: [64x1x28x28] Output: [64x6x24x24]
    tensor = torch::relu(conv1_->forward(tensor));
    tensor = torch::dropout(tensor, p, is_training());

    // s2 Input: [64x5x24x24] Output: [64x6x12x12]
    tensor = pool1_->forward(tensor);

    // c3 Input: [64x6x12x12] Output: [64x16x8x8]
    tensor = torch::relu(conv2_->forward(tensor));
    tensor = torch::dropout(tensor, p, is_training());

    // s4 Input: [64x16x8x8] Output: [64x16x4x4]
    tensor = pool2_->forward(tensor);

    // c5 Input: [64x16x4x4] Output: [64x120]
    tensor = torch::relu(conv3_->forward(tensor));
    tensor = torch::dropout(tensor, p, is_training());
    tensor = tensor.view({tensor.size(0), -1});

    // f6 Input: [64x120] Output: [64x84]
    tensor = torch::relu(fc1_->forward(tensor));
    tensor = torch::dropout(tensor, p, is_training());

    // f7 Input: [64x84] Output: [64x10]
    tensor = torch::relu(fc2_->forward(tensor));
    tensor = torch::dropout(tensor, p, is_training());

    tensor = torch::log_softmax(tensor, dim);
    return tensor;
}
}  // namespace perception