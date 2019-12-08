///
/// @file
///
#ifndef PERCEPTION_MODEL_NET_H_
#define PERCEPTION_MODEL_NET_H_

#include <torch/torch.h>

namespace perception
{
class Net : public torch::nn::Module
{
  public:
    Net();
    torch::Tensor forward(torch::Tensor& tensor);

  private:
    torch::nn::Conv2d conv1_;
    torch::nn::MaxPool2d pool1_;
    torch::nn::Conv2d conv2_;
    torch::nn::MaxPool2d pool2_;
    torch::nn::Conv2d conv3_;
    torch::nn::Linear fc1_;
    torch::nn::Linear fc2_;
};

}  // namespace perception
#endif  /// PERCEPTION_MODEL_NET_H_