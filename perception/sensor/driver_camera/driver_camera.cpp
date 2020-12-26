///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/sensor/driver_camera/driver_camera.h"

#include "perception/common/logging.h"

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>

#include <iterator>

namespace perception
{

DriverCamera::DriverCamera()
    : face_cascade_{"external/opencv/share/opencv4/haarcascades/haarcascade_frontalface_alt2.xml"},
      left_eye_cascade_{"external/opencv/share/opencv4/haarcascades/haarcascade_lefteye_2splits.xml"},
      right_eye_cascade_{"external/opencv/share/opencv4/haarcascades/haarcascade_righteye_2splits.xml"},
      facial_feature_list_{},
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
    UpdateFacialFeatureList();

    const FaceTracking face_tracking{};
    driver_camera_message_.face_tracking = face_tracking;
}

void DriverCamera::UpdateFacialFeatureList()
{
    Image undistorted_gray_image{};
    cv::cvtColor(camera_message_.undistorted_image, undistorted_gray_image, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(undistorted_gray_image, undistorted_gray_image);

    std::vector<cv::Rect> faces{};
    face_cascade_.detectMultiScale(undistorted_gray_image, faces);

    std::transform(faces.cbegin(),
                   faces.cend(),
                   facial_feature_list_.begin(),
                   [&left_eye_cascade = left_eye_cascade_,
                    &right_eye_cascade = right_eye_cascade_,
                    &undistorted_gray_image](const cv::Rect& face) {
                       const Image detected_face = undistorted_gray_image(face);
                       std::vector<cv::Rect> detected_left_eye{};
                       std::vector<cv::Rect> detected_right_eye{};
                       left_eye_cascade.detectMultiScale(detected_face, detected_left_eye);
                       right_eye_cascade.detectMultiScale(detected_face, detected_right_eye);

                       const cv::Rect invalid_box{0, 0, 0, 0};
                       FacialFeature facial_feature{};
                       facial_feature.face = face;
                       facial_feature.eyes.left = detected_left_eye.empty() ? invalid_box : detected_left_eye.at(0U);
                       facial_feature.eyes.right = detected_right_eye.empty() ? invalid_box : detected_right_eye.at(0U);
                       return facial_feature;
                   });
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

}  // namespace perception
