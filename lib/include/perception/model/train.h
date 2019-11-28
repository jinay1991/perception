///
/// @file
///
#ifndef PERCEPTION_MODEL_TRAIN_H_
#define PERCEPTION_MODEL_TRAIN_H_

#include "perception/model/net.h"

namespace perception
{
class Runner
{
  public:
    Runner() = default;
    virtual ~Runner() = default;

    virtual void SetNetwork(const Net& net);
    virtual void SetDevice(const torch::Device& device);

    virtual void Train(std::int32_t epochs);
    virtual void Test();

  private:
    std::int32_t epochs_;
    Net net_;
    torch::Device device_;
};

}  // namespace perception
#endif  /// PERCEPTION_MODEL_TRAIN_H_
