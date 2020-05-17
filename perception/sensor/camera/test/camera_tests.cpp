///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/common/logging/logging.h"
#include "perception/sensor/camera/calibration.h"
#include "perception/sensor/camera/camera.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <opencv4/opencv2/calib3d.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/videoio.hpp>

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
          unit_{},
          test_capture_{test_video_path_},
          test_image_{cv::imread(test_image_path_, cv::IMREAD_UNCHANGED)},
          test_calibration_{"data/camera_calibration", 9, 6},
          test_image_undistorted_{}
    {
    }

    Image GetTestImage() const { return test_image_; };
    Image GetUndistortedTestImage() const { return test_image_undistorted_; }
    Image GetTestVideoImage() const { return test_video_frame_; }

  protected:
    void SetUp() override
    {
        unit_.Init();
        test_calibration_.Init();
        test_calibration_.Execute();
        cv::undistort(test_image_,
                      test_image_undistorted_,
                      test_calibration_.GetCameraMatrix(),
                      test_calibration_.GetDistanceCoeffs());
    }

    void RunOnce()
    {
        unit_.Execute();
        test_capture_ >> test_video_frame_;
    }

    void TearDown() override
    {
        test_calibration_.Shutdown();
        unit_.Shutdown();
    }

    const std::string test_image_path_;
    const std::string test_video_path_;
    const std::string test_invalid_source_;
    Camera unit_;

  private:
    cv::VideoCapture test_capture_;
    cv::Mat test_image_;
    cv::Mat test_video_frame_;
    Calibration test_calibration_;
    cv::Mat test_image_undistorted_;
};

TEST_F(CameraTest, GivenTypicalSourceImage_ExpectValidImage)
{
    unit_.SetSource(test_image_path_);

    RunOnce();

    const auto expected = GetTestImage();
    const auto actual = unit_.GetImage();
    ASSERT_FALSE(actual.empty());
    ASSERT_EQ(expected.size(), actual.size());
}

TEST_F(CameraTest, GivenTypicalSourceVideo_ExpectValidVideoFrame)
{
    unit_.SetSource(test_video_path_);

    RunOnce();

    const auto expected = GetTestVideoImage();
    const auto actual = unit_.GetImage();
    ASSERT_FALSE(actual.empty());
    ASSERT_EQ(expected.size(), actual.size());
}

TEST_F(CameraTest, GivenInvalidSource_ExpectException)
{
    EXPECT_EXIT(unit_.SetSource(test_invalid_source_), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(CameraTest, GivenTypicalSourceImage_ExpectUndistortImage)
{
    unit_.SetSource(test_image_path_);
    RunOnce();

    const auto expected = GetUndistortedTestImage();
    const auto actual = unit_.GetUndistortedImage();
    ASSERT_FALSE(actual.empty());
    ASSERT_EQ(expected.size(), actual.size());
}
}  // namespace
}  // namespace perception
