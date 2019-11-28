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
    torch::Tensor forward(torch::Tensor tensor);

  private:
    torch::nn::Linear fc1_{nullptr};
    torch::nn::Linear fc2_{nullptr};
    torch::nn::Linear fc3_{nullptr};
};

}  // namespace perception
#endif  /// PERCEPTION_MODEL_NET_H_