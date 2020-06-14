///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/lane/lane_detect.h"

#include "middleware/communication/intra_process_pub_sub_factory.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
class LaneDetectTest : public ::testing::Test
{
  public:
    LaneDetectTest() : factory_{}, unit_{factory_} {}

  protected:
    void SetUp() override { unit_.Init(); }
    void RunOnce() { unit_.ExecuteStep(); }
    void TearDown() override { unit_.Shutdown(); }

  private:
    middleware::IntraProcessPubSubFactory factory_;
    LaneDetect unit_;
};

TEST_F(LaneDetectTest, GivenTypicalInput_ExpectValidLaneDetected)
{
    RunOnce();
}
}  // namespace
}  // namespace perception
