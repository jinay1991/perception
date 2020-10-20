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

using ::testing::AllOf;
using ::testing::Eq;
using ::testing::Field;
using ::testing::Property;

class CameraTest : public ::testing::Test
{
  public:
    CameraTest()
        : test_image_path_{"data/grace_hopper.jpg"},
          test_video_path_{"data/Megamind.avi"},
          test_invalid_path_{"invalid/path/to/source"},
          unit_{test_image_path_},
          test_capture_{test_video_path_},
          test_image_{cv::imread(test_image_path_, cv::IMREAD_UNCHANGED)},
          test_calibration_{},
          test_image_undistorted_{}
    {
        cv::undistort(test_image_, test_image_undistorted_, test_calibration_.intrinsic, test_calibration_.extrinsic);
    }

  protected:
    void SetUp() override { unit_.Init(); }

    void RunOnce()
    {
        test_capture_ >> test_video_frame_;
        unit_.Step();
    }

    void TearDown() override { unit_.Shutdown(); }

    const Image& GetTestVideoFrame() const { return test_video_frame_; }
    const Image& GetTestImage() const { return test_image_; }
    const Image& GetTestImageUndistorted() const { return test_image_undistorted_; }
    const cv::Mat& GetTestIntrinsicParam() const { return test_calibration_.intrinsic; }
    const cv::Mat& GetTestExtrinsicParam() const { return test_calibration_.extrinsic; }

    const CameraMessage& GetResults() const { return unit_.GetCameraMessage(); }

    const std::string test_image_path_;
    const std::string test_video_path_;
    const std::string test_invalid_path_;
    Camera unit_;

    cv::VideoCapture test_capture_;
    cv::Mat test_image_;
    cv::Mat test_video_frame_;

    const CalibrationParams test_calibration_;
    cv::Mat test_image_undistorted_;
};

TEST_F(CameraTest, GivenTypicalSourceImage_ExpectValidImage)
{
    // Given
    unit_.SetSource(test_image_path_);

    // When
    RunOnce();

    // Then
    const auto& actual = GetResults();
    EXPECT_THAT(actual,
                AllOf(Field(&CameraMessage::image,
                            AllOf(Property(&Image::empty, false), Field(&Image::size, GetTestImage().size))),
                      Field(&CameraMessage::undistorted_image,
                            AllOf(Property(&Image::empty, false), Field(&Image::size, GetTestImageUndistorted().size))),
                      Field(&CameraMessage::calibration_params,
                            AllOf(Field(&CalibrationParams::intrinsic,
                                        AllOf(Property(&cv::Mat::empty, false),
                                              Field(&cv::Mat::size, GetTestIntrinsicParam().size))),
                                  Field(&CalibrationParams::extrinsic,
                                        AllOf(Property(&cv::Mat::empty, false),
                                              Field(&cv::Mat::size, GetTestExtrinsicParam().size)))))));
}

TEST_F(CameraTest, GivenTypicalSourceVideo_ExpectValidVideoFrame)
{
    // Given
    unit_.SetSource(test_video_path_);

    // When
    RunOnce();

    // Then
    const auto& actual = GetResults();
    EXPECT_THAT(actual,
                Field(&CameraMessage::image,
                      AllOf(Property(&Image::empty, false), Field(&Image::size, GetTestVideoFrame().size))));
}

TEST_F(CameraTest, GivenInvalidSource_ExpectException)
{
    // Then
    EXPECT_EXIT(Camera{test_invalid_path_}, ::testing::KilledBySignal(SIGABRT), "");
    EXPECT_EXIT(unit_.SetSource(test_invalid_path_), ::testing::KilledBySignal(SIGABRT), "");
}

}  // namespace
}  // namespace perception
