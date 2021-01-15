///
/// @file
/// @copyright Copyright (c) 2020-2021. All Rights Reserved.
///
#include "middleware/communication/intra_process_pub_sub_factory.h"
#include "middleware/lifecycle/test/support/single_topic_subscriber.h"
#include "perception/communication/topics.h"
#include "perception/sensor/vehicle_dynamics/node/vehicle_dynamics_node.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
class VehicleDynamicsNodeTest : public ::testing::Test
{
  public:
    VehicleDynamicsNodeTest() : factory_{}, unit_{factory_}, test_subscriber_{"test_subscriber", factory_} {}

  protected:
    void SetUp() override
    {
        unit_.Init();
        test_subscriber_.Init();
    }
    void RunOnce()
    {
        unit_.Step();
        test_subscriber_.Step();
    }
    void TearDown() override
    {
        unit_.Shutdown();
        test_subscriber_.Shutdown();
    }

    middleware::IntraProcessPubSubFactory factory_;
    VehicleDynamicsNode unit_;
    middleware::SingleTopicSubscriber<VehicleDynamicsTopic> test_subscriber_;
};

TEST_F(VehicleDynamicsNodeTest, VehicleDynamicsNode_GivenTypicalInputs_ExpectDynamics) {}

}  // namespace
}  // namespace perception
