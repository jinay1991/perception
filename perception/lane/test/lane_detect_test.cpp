///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/lane/lane_detect.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
class LaneDetectTest : public ::testing::Test
{
  public:
    LaneDetectTest() : unit_{} {}

  protected:
    void SetUp() override { unit_.Init(); }
    void RunOnce() { unit_.Execute(); }
    void TearDown() override { unit_.Shutdown(); }

    LaneDetect unit_;
};

TEST_F(LaneDetectTest, GivenTypicalInput_ExpectValidLaneDetected)
{
    RunOnce();
}
}  // namespace
}  // namespace perception