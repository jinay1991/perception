///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/sensor/driver_camera/driver_camera.h"

#include "perception/common/logging.h"

#include <opencv4/opencv2/imgproc.hpp>

namespace perception
{
namespace
{
/// @brief Invalid Bounding Box
const cv::Rect kInvalidBox{0, 0, 0, 0};

/// @brief Invalid Face Bounding Box
const Face kInvalidFace{kInvalidBox};

/// @brief Invalid Eye Bounding Box
const Eye kInvalidEye{kInvalidBox};

/// @brief Invalid Eyes (left/right) Bounding Boxes
const Eyes kInvalidEyes{kInvalidBox, kInvalidBox};

/// @brief Check whether provided bounding box is valid by checking non-zero entities.
///
/// @param bounding_box [in] - Bounding box (Rect) to check for validity
///
/// @return True if provided box persist valid values and forms valid box, otherwise False.
bool IsBoundingBoxValid(const cv::Rect& bounding_box)
{
    return ((bounding_box.x != 0) && (bounding_box.y != 0) && (bounding_box.width != 0) && (bounding_box.height != 0));
}
}  // namespace

DriverCamera::DriverCamera()
    : face_cascade_{"external/opencv/share/opencv4/haarcascades/haarcascade_frontalface_alt2.xml"},
      left_eye_cascade_{"external/opencv/share/opencv4/haarcascades/haarcascade_lefteye_2splits.xml"},
      right_eye_cascade_{"external/opencv/share/opencv4/haarcascades/haarcascade_righteye_2splits.xml"},
      input_{},
      previous_eye_lid_opening_{},
      time_since_last_eye_state_change_{0ms},
      eye_blink_rate_{},
      camera_message_{},
      driver_camera_message_{}
{
    CHECK(!face_cascade_.empty());
    CHECK(!left_eye_cascade_.empty());
    CHECK(!right_eye_cascade_.empty());
}

void DriverCamera::Init() {}

void DriverCamera::ExecuteStep()
{
    UpdateInputs();

    UpdateFaceTracking();
    UpdateHeadTracking();
    UpdateGazeTracking();
}

void DriverCamera::Shutdown() {}

void DriverCamera::SetCameraMessage(const CameraMessage& camera_message)
{
    camera_message_ = camera_message;
}

const DriverCameraMessage& DriverCamera::GetDriverCameraMessage() const
{
    return driver_camera_message_;
}

void DriverCamera::UpdateTimePoint()
{
    driver_camera_message_.time_point = camera_message_.time_point;
}

void DriverCamera::UpdateFaceTracking()
{
    const Face face = DetermineFace();
    if (IsBoundingBoxValid(face))
    {
        driver_camera_message_.face_tracking.face_visible = true;
        const Eyes eyes = DetermineEyes(face);
        if (IsBoundingBoxValid(eyes.left) || IsBoundingBoxValid(eyes.right))
        {
            driver_camera_message_.face_tracking.eye_visible = true;
            driver_camera_message_.face_tracking.eye_lid_opening = DetermineEyeLidOpening(eyes);
            driver_camera_message_.face_tracking.eye_blink_rate =
                DetermineEyeBlinkRate(driver_camera_message_.face_tracking.eye_lid_opening);
        }
    }
}

void DriverCamera::UpdateHeadTracking()
{
    const HeadTracking head_tracking{};
    driver_camera_message_.head_tracking = head_tracking;
}

void DriverCamera::UpdateGazeTracking()
{
    const GazeTracking gaze_tracking{};
    driver_camera_message_.gaze_tracking = gaze_tracking;
}

void DriverCamera::UpdateInputs()
{
    cv::cvtColor(camera_message_.undistorted_image, input_, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(input_, input_);
}

Face DriverCamera::DetermineFace()
{
    std::vector<Face> detected_faces{};
    face_cascade_.detectMultiScale(input_, detected_faces);

    return (detected_faces.empty() ? kInvalidFace : detected_faces.at(0U));
}

Eyes DriverCamera::DetermineEyes(const Face& face)
{
    Eyes eyes = kInvalidEyes;
    eyes.left = DetermineLeftEye(face);
    eyes.right = DetermineRightEye(face);
    return eyes;
}

Eye DriverCamera::DetermineRightEye(const cv::Rect& face)
{
    const Image detected_face = input_(face);
    std::vector<Eye> detected_right_eye{};
    right_eye_cascade_.detectMultiScale(detected_face, detected_right_eye);

    return (detected_right_eye.empty() ? kInvalidEye : detected_right_eye.at(0U));
}

Eye DriverCamera::DetermineLeftEye(const cv::Rect& face)
{
    const Image detected_face = input_(face);
    std::vector<Eye> detected_left_eye{};
    left_eye_cascade_.detectMultiScale(detected_face, detected_left_eye);

    return (detected_left_eye.empty() ? kInvalidEye : detected_left_eye.at(0U));
}

units::length::millimeter_t DriverCamera::DetermineEyeLidOpening(const Eyes& eyes)
{
    units::length::millimeter_t eye_lid_opening;
    if (IsBoundingBoxValid(eyes.left) || IsBoundingBoxValid(eyes.right))  // atleast one eye is open
    {
        eye_lid_opening = kMaxEyeLidOpening;
    }
    else
    {
        eye_lid_opening = kMinEyeLidOpening;
    }
    return eye_lid_opening;
}

units::frequency::hertz_t DriverCamera::DetermineEyeBlinkRate(const units::length::millimeter_t eye_lid_opening)
{
    if (previous_eye_lid_opening_ != eye_lid_opening)
    {
        previous_eye_lid_opening_ = eye_lid_opening;
        if (time_since_last_eye_state_change_ != 0ms)
        {
            eye_blink_rate_ =
                units::frequency::kilohertz_t{1.0 / static_cast<double>(time_since_last_eye_state_change_.count())};
        }
        else
        {
            eye_blink_rate_ = 0_Hz;
        }
        time_since_last_eye_state_change_ = 0ms;
    }
    else
    {
        time_since_last_eye_state_change_ +=
            std::chrono::duration_cast<std::chrono::milliseconds>(driver_camera_message_.time_point.time_since_epoch());
    }
    return eye_blink_rate_;
}

}  // namespace perception
