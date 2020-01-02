///
/// @file
///
#include <gtest/gtest.h>

#include "perception/model/train.h"

namespace perception
{
namespace
{
class ModelSpecFixture : public ::testing::Test
{
  protected:
    Runner unit_;
};

TEST_F(ModelSpecFixture, DISABLED_GivenNeuralNetwork_ExpectTrainedModel)
{
    unit_.Train("/Users/jinay/workspace/git-repo/ad-platform/perception/data");
}
}  // namespace
}  // namespace perception