///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "middleware/communication/intra_process_pub_sub_factory.h"
#include "middleware/lifecycle/test/single_topic_subscriber.h"
#include "perception/common/logging/logging.h"
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
          test_video_path_{"data/Megamind.avi"},
          test_invalid_source_{"invalid/path/to/source"},
          factory_{},
          unit_{factory_},
          test_subscriber_{"test_subscriber", factory_},
          test_capture_{test_video_path_},
          test_image_{cv::imread(test_image_path_, cv::IMREAD_UNCHANGED)},
          test_calibration_{},
          test_image_undistorted_{}
    {
        factory_.RegisterTopic<CameraTopic>();
        cv::undistort(test_image_, test_image_undistorted_, test_calibration_.intrinsic, test_calibration_.extrinsic);
    }

    Image GetTestImage() const { return test_image_; };

    CameraMessage GetExpectedCameraMessage() const
    {
        return CameraMessage{std::chrono::system_clock::now(),
                             test_image_,
                             test_image_undistorted_,
                             {test_calibration_.intrinsic, test_calibration_.extrinsic}};
    }
    Image GetTestVideoImage() const { return test_video_frame_; }

  protected:
    void SetUp() override
    {
        test_subscriber_.Init();
        unit_.Init();
    }

    void RunOnce()
    {
        test_capture_ >> test_video_frame_;
        unit_.Step();
        test_subscriber_.Step();
    }

    void TearDown() override
    {
        test_subscriber_.Shutdown();
        unit_.Shutdown();
    }

    const std::string test_image_path_;
    const std::string test_video_path_;
    const std::string test_invalid_source_;
    middleware::IntraProcessPubSubFactory factory_;
    CameraNode unit_;
    middleware::SingleTopicSubscriber<CameraTopic> test_subscriber_;

  private:
    cv::VideoCapture test_capture_;
    cv::Mat test_image_;
    cv::Mat test_video_frame_;
    CalibrationParams test_calibration_;
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
    ASSERT_FALSE(actual.undistorted_image.empty());
    ASSERT_EQ(expected.undistorted_image.size(), actual.undistorted_image.size());
    ASSERT_FALSE(actual.image.empty());
    ASSERT_EQ(expected.image.size(), actual.image.size());
    ASSERT_FALSE(actual.calibration_params.intrinsic.empty());
    ASSERT_EQ(expected.calibration_params.intrinsic.size(), actual.calibration_params.intrinsic.size());
    ASSERT_FALSE(actual.calibration_params.extrinsic.empty());
    ASSERT_EQ(expected.calibration_params.extrinsic.size(), actual.calibration_params.extrinsic.size());
}

TEST_F(CameraNodeTest, GivenTypicalSourceVideo_ExpectValidVideoFrame)
{
    unit_.SetSource(test_video_path_);

    RunOnce();

    const auto expected = GetTestVideoImage();
    const auto actual = test_subscriber_.GetSample();
    ASSERT_FALSE(actual.image.empty());
    ASSERT_FALSE(expected.empty());
    ASSERT_EQ(expected.size(), actual.image.size());
}

TEST_F(CameraNodeTest, GivenInvalidSource_ExpectException)
{
    EXPECT_EXIT(CameraNode(factory_).SetSource(test_invalid_source_), ::testing::KilledBySignal(SIGABRT), "");
}

}  // namespace
}  // namespace perception
