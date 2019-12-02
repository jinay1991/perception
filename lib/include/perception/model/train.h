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
    Runner() {}
    virtual ~Runner() = default;

    virtual void SetNetwork(const Net& net);

    virtual void Train();
    virtual void Test();

  private:
    Net net_;
};

}  // namespace perception
#endif  /// PERCEPTION_MODEL_TRAIN_H_
