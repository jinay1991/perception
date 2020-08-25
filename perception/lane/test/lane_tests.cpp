///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/lane/lane.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
class LaneTest : public ::testing::Test
{
  public:
    LaneTest() : unit_{} {}

  protected:
    void SetUp() override {}
    void TearDown() override {}

  private:
    Lane unit_;
};

TEST_F(LaneTest, GivenTypicalInputs_ExpectLaneDetection) {}

}  // namespace
}  // namespace perception
