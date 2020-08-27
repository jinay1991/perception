///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/sensor/camera/camera.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <opencv4/opencv2/calib3d.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>

#include <string>

namespace perception
{
namespace
{

class CameraTest : public ::testing::Test
{
  public:
    CameraTest()
        : test_image_path_{"data/grace_hopper.jpg"},
          test_video_path_{"data/Megamind.avi"},
          test_invalid_source_{"invalid/path/to/source"},
          unit_{test_image_path_},
          test_capture_{test_video_path_},
          test_image_{cv::imread(test_image_path_, cv::IMREAD_UNCHANGED)},
          test_calibration_{},
          test_image_undistorted_{}
    {
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
    void SetUp() override { unit_.Init(); }

    void RunOnce()
    {
        test_capture_ >> test_video_frame_;
        unit_.Step();
    }

    void TearDown() override { unit_.Shutdown(); }

    const std::string test_image_path_;
    const std::string test_video_path_;
    const std::string test_invalid_source_;
    Camera unit_;

  private:
    cv::VideoCapture test_capture_;
    cv::Mat test_image_;
    cv::Mat test_video_frame_;
    CalibrationParams test_calibration_;
    cv::Mat test_image_undistorted_;
};

TEST_F(CameraTest, GivenTypicalSourceImage_ExpectValidImage)
{
    // Given
    unit_.SetSource(test_image_path_);

    // When
    RunOnce();

    // Then
    const auto expected = GetExpectedCameraMessage();
    const auto actual = unit_.GetCameraMessage();
    EXPECT_FALSE(actual.undistorted_image.empty());
    EXPECT_EQ(expected.undistorted_image.size(), actual.undistorted_image.size());
    EXPECT_FALSE(actual.image.empty());
    EXPECT_EQ(expected.image.size(), actual.image.size());
    EXPECT_FALSE(actual.calibration_params.intrinsic.empty());
    EXPECT_EQ(expected.calibration_params.intrinsic.size(), actual.calibration_params.intrinsic.size());
    EXPECT_FALSE(actual.calibration_params.extrinsic.empty());
    EXPECT_EQ(expected.calibration_params.extrinsic.size(), actual.calibration_params.extrinsic.size());
}

TEST_F(CameraTest, GivenTypicalSourceVideo_ExpectValidVideoFrame)
{
    // Given
    unit_.SetSource(test_video_path_);

    // When
    RunOnce();

    // Then
    const auto expected = GetTestVideoImage();
    const auto actual = unit_.GetCameraMessage();
    EXPECT_FALSE(actual.image.empty());
    EXPECT_FALSE(expected.empty());
    EXPECT_EQ(expected.size(), actual.image.size());
}

TEST_F(CameraTest, GivenInvalidSource_ExpectException)
{
    // Then
    EXPECT_EXIT(Camera{test_invalid_source_}, ::testing::KilledBySignal(SIGABRT), "");
    EXPECT_EXIT(unit_.SetSource(test_invalid_source_), ::testing::KilledBySignal(SIGABRT), "");
}

}  // namespace
}  // namespace perception
