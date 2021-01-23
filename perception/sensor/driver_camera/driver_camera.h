///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_SENSOR_DRIVER_CAMERA_DRIVER_CAMERA_H
#define PERCEPTION_SENSOR_DRIVER_CAMERA_DRIVER_CAMERA_H

#include "perception/datatypes/camera.h"
#include "perception/datatypes/driver.h"

#include <opencv4/opencv2/objdetect.hpp>

#include <chrono>

namespace perception
{
/// @brief Face Bounding Box
using Face = cv::Rect;

/// @brief Eye (single) Bounding Box
using Eye = cv::Rect;

/// @brief Eyes (both, Left & Right) Bounding Boxes
struct Eyes
{
    /// @brief Left Eye Bounding Box
    Eye left{};

    /// @brief Right Eye Bounding Box
    Eye right{};
};
/// @brief Driver Camera
class DriverCamera
{
  public:
    /// @brief Constructor.
    DriverCamera();

    /// @brief Initialize Driver Camera
    void Init();

    /// @brief Execute single step for Driver Camera
    void ExecuteStep();

    /// @brief Shutdown/Deinitialize Driver Camera
    void Shutdown();

    /// @brief Set received Camera Message for further processing of the received raw image data to extract Face, Head
    /// and Gaze Tracking information
    ///
    /// @param camera_message  [in] - Camera Message
    void SetCameraMessage(const CameraMessage& camera_message);

    /// @brief Provide Driver Camera Message containing Face, Head and Gaze Tracking information
    ///
    /// @return Driver Camera Message
    const DriverCameraMessage& GetDriverCameraMessage() const;

  private:
    /// @brief Maximum faces to consider per one image
    /// @note This is useful to limit number of faces to consider while processing them.
    static constexpr std::int32_t kMaxFacialFeaturePerImage = 10;

    /// @brief Update Time point for DriverCamera Message (copies camera message time_point)
    void UpdateTimePoint();

    /// @brief Identify and update FaceTracking from captured image
    void UpdateFaceTracking();

    /// @brief Identify and update HeadTracking from captured image
    void UpdateHeadTracking();

    /// @brief Identify and update GazeTracking from captured image
    void UpdateGazeTracking();

    /// @brief Update input image (preprocessed)
    void UpdateInputs();

    /// @brief Identify Face
    ///
    /// @return face Bounding Box
    Face DetermineFace();

    /// @brief Identify Eyes (Left & Right)
    ///
    /// @param face [in] - Face Bounding Box
    ///
    /// @return eyes (left & right)
    Eyes DetermineEyes(const Face& face);

    /// @brief Identify Right Eye
    ///
    /// @param face [in] - Face Bounding Box
    ///
    /// @return right_eye
    Eye DetermineRightEye(const Face& face);

    /// @brief Identify Left Eye
    ///
    /// @param face [in] - Face Bounding Box
    ///
    /// @return left_eye
    Eye DetermineLeftEye(const Face& face);

    /// @brief Identify Eye Lid opening (mm)
    ///
    /// @param eyes [in] - Eyes (left & right)
    ///
    /// @return eye_lid_opening (mm)
    static units::length::millimeter_t DetermineEyeLidOpening(const Eyes& eyes);

    /// @brief Identify Eye Blink Rate (Hz)
    ///
    /// @param eye_lid_opening [in] - Current Eye Lid Opening
    ///
    /// @return eye_blink_rate (Hz)
    units::frequency::hertz_t DetermineEyeBlinkRate(const units::length::millimeter_t eye_lid_opening);

    /// @brief Face Detector
    cv::CascadeClassifier face_cascade_;

    /// @brief Left Eye Detector
    cv::CascadeClassifier left_eye_cascade_;

    /// @brief Right Eye Detector
    cv::CascadeClassifier right_eye_cascade_;

    /// @brief Preprocessed gray image to be used for identifying futher driver features
    Image input_;

    /// @brief Previously detected eye_lid_opening (mm)
    units::length::millimeter_t previous_eye_lid_opening_;

    /// @brief Time (ms) since the last eye state changed
    std::chrono::milliseconds time_since_last_eye_state_change_;

    /// @brief Recorded eye blink rate (Hz)
    units::frequency::hertz_t eye_blink_rate_;

    /// @brief Instance of Camera Message
    CameraMessage camera_message_;

    /// @brief Instance of Driver Camera Message
    DriverCameraMessage driver_camera_message_;
};
}  // namespace perception
#endif  /// PERCEPTION_SENSOR_DRIVER_CAMERA_DRIVER_CAMERA_H
