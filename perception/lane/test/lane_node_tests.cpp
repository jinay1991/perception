///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License
///
#include "middleware/communication/intra_process_pub_sub_factory.h"
#include "perception/lane/node/lane_node.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
class LaneNodeTest : public ::testing::Test
{
  public:
    LaneNodeTest() : factory_{}, unit_{factory_} {}

  protected:
    void SetUp() override { unit_.Init(); }
    void RunOnce() { unit_.ExecuteStep(); }
    void TearDown() override { unit_.Shutdown(); }

  private:
    middleware::IntraProcessPubSubFactory factory_;
    LaneNode unit_;
};

TEST_F(LaneNodeTest, GivenTypicalInput_ExpectValidLaneDetected)
{
    RunOnce();
}
}  // namespace
}  // namespace perception
