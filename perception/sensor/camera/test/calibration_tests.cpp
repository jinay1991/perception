///
/// @file
/// @copyright Copyright (c) 2023. MIT License
///
#include "perception/sensor/camera/calibration.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <opencv4/opencv2/calib3d.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/core/base.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>

namespace perception
{
namespace
{
class CalibrationTest : public ::testing::Test
{
  public:
    CalibrationTest()
        : unit_{"data/camera_calibration", 9, 6},
          test_image_path_{"data/camera_calibration/calibration1.jpg"},
          test_undistorted_image_path_{"data/undistorted_calibration1.jpg"}
    {
    }

  protected:
    void SetUp() override { unit_.Init(); }
    void RunOnce() { unit_.Execute(); }
    void TearDown() override { unit_.Shutdown(); }

    Calibration unit_;
    const std::string test_image_path_;
    const std::string test_undistorted_image_path_;
};

TEST_F(CalibrationTest, WhenInitialized_ExpectedEmptyCalibrationMatrix)
{
    ASSERT_TRUE(unit_.GetCameraMatrix().empty());
    ASSERT_TRUE(unit_.GetDistanceCoefficients().empty());
    ASSERT_TRUE(unit_.GetRotationMatrix().empty());
    ASSERT_TRUE(unit_.GetTranslationMatrix().empty());
}
TEST_F(CalibrationTest, GivenTypicalCalibrationInputs_ExpectedCalibrationMatrix)
{
    RunOnce();

    ASSERT_FALSE(unit_.GetCameraMatrix().empty());
    ASSERT_FALSE(unit_.GetDistanceCoefficients().empty());
    ASSERT_FALSE(unit_.GetRotationMatrix().empty());
    ASSERT_FALSE(unit_.GetTranslationMatrix().empty());
}

TEST_F(CalibrationTest, GivenDistortedImage_ExpectUndistortedImage)
{
    RunOnce();
    const auto camera_matrix = unit_.GetCameraMatrix();
    const auto distance_coeffs = unit_.GetDistanceCoefficients();
    ASSERT_FALSE(camera_matrix.empty());
    ASSERT_FALSE(distance_coeffs.empty());

    const cv::Mat image = cv::imread(test_image_path_, cv::IMREAD_GRAYSCALE);
    cv::Mat actual{};
    cv::undistort(image, actual, camera_matrix, distance_coeffs);
    ASSERT_EQ(image.size(), actual.size());

    const cv::Mat expected = cv::imread(test_undistorted_image_path_, cv::IMREAD_GRAYSCALE);
    ASSERT_EQ(actual.size(), expected.size());
}
}  // namespace
}  // namespace perception
