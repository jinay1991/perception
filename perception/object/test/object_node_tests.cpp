///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "middleware/communication/intra_process_pub_sub_factory.h"
#include "middleware/lifecycle/test/single_topic_publisher.h"
#include "middleware/lifecycle/test/single_topic_subscriber.h"
#include "perception/communication/topics.h"
#include "perception/object/node/object_node.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <opencv4/opencv2/calib3d.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>

#include <string>

namespace perception
{
namespace
{
class ObjectNodeTest : public ::testing::Test
{
  public:
    ObjectNodeTest()
        : factory_{},
          test_image_path_{"data/messi5.jpg"},
          camera_message_{},
          unit_{factory_},
          test_publisher_{"test_publisher", factory_},
          test_subscriber_{"test_subscriber", factory_}
    {
        camera_message_.image = cv::imread(test_image_path_, cv::IMREAD_UNCHANGED);
        cv::undistort(camera_message_.image,
                      camera_message_.undistorted_image,
                      camera_message_.calibration_params.intrinsic,
                      camera_message_.calibration_params.extrinsic);
    }

  protected:
    void SetUp() override
    {
        test_publisher_.Init();
        unit_.Init();
        test_subscriber_.Init();
    }

    void RunOnce()
    {
        test_publisher_.PublishInput(camera_message_);
        test_publisher_.Step();
        unit_.Step();
        test_subscriber_.Step();
    }

    void TearDown() override
    {
        test_publisher_.Shutdown();
        unit_.Shutdown();
        test_subscriber_.Shutdown();
    }

    middleware::IntraProcessPubSubFactory factory_;
    const std::string test_image_path_;
    CameraMessage camera_message_;
    ObjectNode unit_;
    middleware::SingleTopicPublisher<CameraTopic> test_publisher_;
    middleware::SingleTopicSubscriber<ObjectListTopic> test_subscriber_;
};

TEST_F(ObjectNodeTest, GivenTypicalInputs_ExpectDetectedObjects)
{
    // When
    RunOnce();

    // Then
    const auto actual = test_subscriber_.GetSample();
    EXPECT_EQ(1, actual.number_of_valid_objects);
    EXPECT_EQ(ObjectId::kBicycle, actual.objects.at(0).id);
}

}  // namespace
}  // namespace perception
