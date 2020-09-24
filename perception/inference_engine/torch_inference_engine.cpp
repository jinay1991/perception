///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/inference_engine/torch_inference_engine.h"

#include "perception/common/logging/logging.h"

#include <torch/torch.h>

namespace perception
{
namespace
{
class TestNet : public torch::nn::Module
{
  public:
    explicit TestNet(const std::int32_t n, const std::int32_t m)
    {
        weight = register_parameter("weight", torch::randn({n, m}));
        bias = register_parameter("bias", torch::randn(m));
    }
    torch::Tensor forward(const torch::Tensor& input) { return torch::addmm(bias, input, weight); }

  private:
    torch::Tensor weight;
    torch::Tensor bias;
};
}  // namespace

TorchInferenceEngine::TorchInferenceEngine(const InferenceEngineParameters& /* params */) : results_{} {}

void TorchInferenceEngine::Init()
{
    auto test_net = TestNet{4, 5};
    const torch::Tensor tensor = test_net.forward(torch::ones({2, 4}));
    std::cout << tensor << std::endl;
}

void TorchInferenceEngine::Execute(const Image& image) {}

void TorchInferenceEngine::Shutdown() {}

std::vector<cv::Mat> TorchInferenceEngine::GetResults() const
{
    return results_;
}

}  // namespace perception
