///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_SENSOR_DRIVER_CAMERA_DRIVER_CAMERA_H
#define PERCEPTION_SENSOR_DRIVER_CAMERA_DRIVER_CAMERA_H

#include "perception/datatypes/camera.h"
#include "perception/datatypes/driver.h"

#include <opencv4/opencv2/objdetect.hpp>

namespace perception
{

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
    /// @param camera_message [in] - Camera Message
    void SetCameraMessage(const CameraMessage& camera_message);

    /// @brief Provide Driver Camera Message containing Face, Head and Gaze Tracking information
    ///
    /// @return Driver Camera Message
    const DriverCameraMessage& GetDriverCameraMessage() const;

  private:
    static constexpr std::int32_t kMaxFacialFeaturePerImage = 10;

    /// @brief Facial feature (Eyes) Bounding box
    struct EyesFeature
    {
        /// @brief Left Eye Bounding Box
        cv::Rect left{};

        /// @brief Right Eye Bounding Box
        cv::Rect right{};
    };

    struct FacialFeature
    {
        /// @brief Face Bounding Box
        cv::Rect face{};

        /// @brief Eye Bounding Boxes
        EyesFeature eyes;
    };

    using FacialFeatureList = std::array<FacialFeature, kMaxFacialFeaturePerImage>;

    /// @brief Update Time point for DriverCamera Message (copies camera message time_point)
    void UpdateTimePoint();

    /// @brief Identify and update FaceTracking from captured image
    void UpdateFaceTracking();

    /// @brief Identify and update HeadTracking from captured image
    void UpdateHeadTracking();

    /// @brief Identify and update GazeTracking from captured image
    void UpdateGazeTracking();

    /// @brief Performs Face/Eye detection and updates faces information
    void UpdateFacialFeatureList();

    /// @brief Face Detector
    cv::CascadeClassifier face_cascade_;

    /// @brief Left Eye Detector
    cv::CascadeClassifier left_eye_cascade_;

    /// @brief Right Eye Detector
    cv::CascadeClassifier right_eye_cascade_;

    /// @brief Facial features
    FacialFeatureList facial_feature_list_;

    /// @brief Instance of Camera Message
    CameraMessage camera_message_;

    /// @brief Instance of Driver Camera Message
    DriverCameraMessage driver_camera_message_;
};
}  // namespace perception
#endif  /// PERCEPTION_SENSOR_DRIVER_CAMERA_DRIVER_CAMERA_H
