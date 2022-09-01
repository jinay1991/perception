///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License
///
#include "perception/sensor/camera/camera.h"

#include "perception/common/logging.h"

#include <opencv4/opencv2/calib3d.hpp>

#include <chrono>

namespace perception
{
namespace
{  /// @brief Default chessboard data for calibration
const std::string kDefaultChessboardData{"data/camera_calibration"};

/// @brief Default number of chessboard blocks in x axis
constexpr std::int32_t kDefaultNumberOfChessboardBlocksX{9};

/// @brief Default number of chessboard blocks in y axis
constexpr std::int32_t kDefaultNumberOfChessboardBlocksY{6};
}  // namespace

Camera::Camera(const std::string& source)
    : source_{source},
      capture_device_{source_},
      calibration_{kDefaultChessboardData, kDefaultNumberOfChessboardBlocksX, kDefaultNumberOfChessboardBlocksY}
{
    CHECK(capture_device_.isOpened());
}

void Camera::Init()
{
    Calibrate();
}

void Camera::Step()
{
    Image image{};
    capture_device_ >> image;

    Image undistorted_image{};
    cv::undistort(image, undistorted_image, calibration_.GetCameraMatrix(), calibration_.GetDistanceCoefficients());

    camera_message_.time_point = std::chrono::system_clock::now();
    camera_message_.calibration_params.intrinsic = calibration_.GetCameraMatrix();
    camera_message_.calibration_params.extrinsic = calibration_.GetDistanceCoefficients();
    camera_message_.image = image;
    camera_message_.undistorted_image = undistorted_image;
}

void Camera::Shutdown()
{
    calibration_.Shutdown();
    capture_device_.release();
}

void Camera::SetSource(const std::string source)
{
    capture_device_.open(source);
    CHECK(capture_device_.isOpened());

    LOG(INFO) << "Reading " << source << " source.";
}

const CameraMessage& Camera::GetCameraMessage() const
{
    return camera_message_;
}

void Camera::Calibrate()
{
    calibration_.Init();
    calibration_.Execute();
}

}  // namespace perception
