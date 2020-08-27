///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "middleware/communication/intra_process_pub_sub_factory.h"
#include "middleware/lifecycle/test/single_topic_subscriber.h"
#include "perception/communication/topics.h"
#include "perception/sensor/camera/calibration.h"
#include "perception/sensor/camera/node/camera_node.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <opencv4/opencv2/calib3d.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/videoio.hpp>

#include <string>

namespace perception
{
namespace
{

class CameraNodeTest : public ::testing::Test
{
  public:
    CameraNodeTest()
        : test_image_path_{"data/grace_hopper.jpg"},
          factory_{},
          unit_{factory_},
          test_subscriber_{"test_subscriber", factory_},
          calibration_params_{},
          test_image_{cv::imread(test_image_path_, cv::IMREAD_UNCHANGED)},
          test_image_undistorted_{}
    {
        factory_.RegisterTopic<CameraTopic>();
    }

    CameraMessage GetExpectedCameraMessage() const
    {
        return CameraMessage{std::chrono::system_clock::now(),
                             test_image_,
                             test_image_undistorted_,
                             {calibration_params_.intrinsic, calibration_params_.extrinsic}};
    }

  protected:
    void SetUp() override
    {
        test_subscriber_.Init();
        unit_.Init();

        cv::undistort(
            test_image_, test_image_undistorted_, calibration_params_.intrinsic, calibration_params_.extrinsic);
    }

    void RunOnce()
    {
        unit_.Step();
        test_subscriber_.Step();
    }

    void TearDown() override
    {
        test_subscriber_.Shutdown();
        unit_.Shutdown();
    }

    const std::string test_image_path_;
    middleware::IntraProcessPubSubFactory factory_;
    CameraNode unit_;
    middleware::SingleTopicSubscriber<CameraTopic> test_subscriber_;

  private:
    const CalibrationParams calibration_params_;
    cv::Mat test_image_;
    cv::Mat test_image_undistorted_;
};

TEST_F(CameraNodeTest, GivenTypicalSourceImage_ExpectValidImage)
{
    // Given
    unit_.SetSource(test_image_path_);

    // When
    RunOnce();

    // Then
    const auto expected = GetExpectedCameraMessage();
    const auto actual = test_subscriber_.GetSample();
    EXPECT_FALSE(actual.undistorted_image.empty());
    EXPECT_EQ(expected.undistorted_image.size(), actual.undistorted_image.size());
    EXPECT_FALSE(actual.image.empty());
    EXPECT_EQ(expected.image.size(), actual.image.size());
    EXPECT_FALSE(actual.calibration_params.intrinsic.empty());
    EXPECT_EQ(expected.calibration_params.intrinsic.size(), actual.calibration_params.intrinsic.size());
    EXPECT_FALSE(actual.calibration_params.extrinsic.empty());
    EXPECT_EQ(expected.calibration_params.extrinsic.size(), actual.calibration_params.extrinsic.size());
}

}  // namespace
}  // namespace perception
