///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/object/node/object_node.h"

#include "middleware/communication/intra_process_pub_sub_factory.h"
#include "middleware/lifecycle/test/single_topic_publisher.h"
#include "middleware/lifecycle/test/single_topic_subscriber.h"
#include "perception/communication/topics.h"
#include "perception/sensor/camera/node/camera_node.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
class ObjectNodeTest : public ::testing::Test
{
  public:
    ObjectNodeTest() : factory_{}, unit_{factory_}, camera_{factory_}, test_subscriber_{"test_subscriber", factory_} {}

  protected:
    void SetUp() override
    {
        camera_.Init();
        unit_.Init();
        test_subscriber_.Init();
    }

    void RunOnce()
    {
        camera_.Step();
        unit_.Step();
        test_subscriber_.Step();
    }

    void TearDown() override
    {
        camera_.Shutdown();
        unit_.Shutdown();
        test_subscriber_.Shutdown();
    }

    middleware::IntraProcessPubSubFactory factory_;
    ObjectNode unit_;
    CameraNode camera_;
    middleware::SingleTopicSubscriber<ObjectListTopic> test_subscriber_;
};

TEST_F(ObjectNodeTest, ObjectNode_GivenTypicalInputs_ExpectDetectedObjects)
{
    // When
    RunOnce();

    // Then
    const auto actual = test_subscriber_.GetSample();
    EXPECT_LT(0, actual.size());
}

}  // namespace
}  // namespace perception
