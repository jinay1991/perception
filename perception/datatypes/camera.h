///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DATATYPES_CAMERA_H
#define PERCEPTION_DATATYPES_CAMERA_H

#include <opencv4/opencv2/core.hpp>

#include <chrono>

namespace perception
{

/// @brief Default Calibration Parameter (Camera Matrix - Intrinsic)
static const cv::Mat kDefaultCameraMatrix{
    cv::Mat_<double>({3, 3},
                     {143.7731622001827, 0, 639.4992635869854, 0, 843.0640731131716, 359.4998035115606, 0, 0, 1})};

/// @brief Default Calibration Parameter (Distance Coefficient - Extrinsic)
static const cv::Mat kDefaultDistanceCoefficient{cv::Mat_<double>({1, 5},
                                                                  {-0.01112356934821852,
                                                                   3.230689066061821e-05,
                                                                   -0.0001903011178685738,
                                                                   0.001629532931646507,
                                                                   -2.704303436336158e-08})};

/// @brief Camera Calibration parameters
struct CalibrationParams
{
    /// @brief Camera Matrix (3x3)
    cv::Mat intrinsic{kDefaultCameraMatrix};

    /// @brief Distance Coefficients (1x5)
    cv::Mat extrinsic{kDefaultDistanceCoefficient};
};

/// @brief Camera Image type
using Image = cv::Mat;

/// @brief Camera Captured information
struct CameraMessage
{
    /// @brief Time Point for captured data
    std::chrono::system_clock::time_point time_point{};

    /// @brief distorted image (original camera captured)
    Image image{};

    /// @brief undistorted image (based on the calibration parameters)
    Image undistorted_image{};

    /// @brief Calibration parameters (intrinsic, extrinsic)
    CalibrationParams calibration_params{};
};

}  // namespace perception

#endif  /// PERCEPTION_DATATYPES_CAMERA_H
