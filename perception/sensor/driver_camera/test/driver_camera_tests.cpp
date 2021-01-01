///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/sensor/driver_camera/driver_camera.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <opencv4/opencv2/calib3d.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>

namespace perception
{
namespace
{
using ::testing::AllOf;
using ::testing::Field;

class DriverCameraFixture : public ::testing::Test
{
  public:
    DriverCameraFixture()
        : test_image_path_{"data/grace_hopper.jpg"},
          test_image_{cv::imread(test_image_path_, cv::IMREAD_UNCHANGED)},
          unit_{}
    {
    }

  protected:
    void SetUp() override { unit_.Init(); }
    void TearDown() override { unit_.Shutdown(); }

    void RunOnce() { unit_.ExecuteStep(); }

    void SetCameraMessage() { unit_.SetCameraMessage(GenerateCameraMessage()); }
    const DriverCameraMessage& GetDriverCameraMessage() const { return unit_.GetDriverCameraMessage(); }

  private:
    CameraMessage GenerateCameraMessage() const
    {
        const CalibrationParams calibration_params{};
        CameraMessage camera_message{};
        camera_message.time_point = std::chrono::system_clock::now();
        camera_message.image = test_image_;
        camera_message.calibration_params = calibration_params;

        cv::undistort(camera_message.image,
                      camera_message.undistorted_image,
                      camera_message.calibration_params.intrinsic,
                      camera_message.calibration_params.extrinsic);
        return camera_message;
    }

    const std::string test_image_path_;
    const cv::Mat test_image_;
    CameraMessage camera_message_;
    DriverCamera unit_;
};

TEST_F(DriverCameraFixture, DriverCamera_GivenTypicalCameraMessage_ExpectUpdatedDriverCameraMessage)
{
    // Given
    SetCameraMessage();

    // When
    RunOnce();

    // Then
    const auto& actual = GetDriverCameraMessage();
    EXPECT_THAT(actual,
                Field(&DriverCameraMessage::face_tracking,
                      AllOf(Field(&FaceTracking::face_visibility, false),
                            Field(&FaceTracking::eye_visibility, false),
                            Field(&FaceTracking::eye_lid_opening, 0_mm),
                            Field(&FaceTracking::eye_blink_rate, 0.0_Hz))));
}

}  // namespace
}  // namespace perception
