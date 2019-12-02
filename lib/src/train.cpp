///
/// @file
///
#include "perception/model/train.h"

namespace perception
{
void Runner::SetNetwork(const Net& net) { net_ = net; }

void Runner::Train()
{
    torch::Tensor tensor = torch::eye(3);

    std::cout << tensor << std::endl;
}

void Runner::Test() {}

}  // namespace perception