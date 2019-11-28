///
/// @file
///
#include "perception/model/train.h"

namespace perception
{
void Runner::SetNetwork(const Net& net) { net_ = net; }
void Runner::SetDevice(const torch::Device& device) { device_ = device; }

void Runner::Train(std::int32_t epochs) {}
void Runner::Test() {}

}  // namespace perception