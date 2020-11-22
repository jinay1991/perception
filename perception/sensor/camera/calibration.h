///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_SENSOR_CAMERA_CALIBRATION_H
#define PERCEPTION_SENSOR_CAMERA_CALIBRATION_H

#include <opencv4/opencv2/core.hpp>

#include <cstdint>
#include <string>
#include <vector>

namespace perception
{
/// @brief Camera Calibration
class Calibration
{
  public:
    /// @brief Construct Calibration utility for certain chessboard pattern
    /// @param dirname [in] Directory path/name containing calibration images (chessboard images)
    /// @param nx [in] Number of chessboard blocks in X-axes
    /// @param ny [in] Number of chessboard blocks in Y-axes
    explicit Calibration(const std::string dirname, const std::int32_t nx, const std::int32_t ny);

    /// @brief Initialize Calibration. Prepare image points and object points for Calibration
    void Init();

    /// @brief Executes Calibration with collected image points and object points
    void Execute();

    /// @brief Release resources used for calibration
    void Shutdown();

    /// @brief Provides Camera Calibration Parameters [Camera Matrix]
    const cv::Mat& GetCameraMatrix() const;

    /// @brief Provides Camera Calibration Parameters [Distance Coefficients]
    const cv::Mat& GetDistanceCoeffs() const;

    /// @brief Provides Camera Calibration Parameters [Rotational Matrix]
    const cv::Mat& GetRotationMatrix() const;

    /// @brief Provides Camera Calibration Parameters [Translation Matrix]
    const cv::Mat& GetTranslationMatrix() const;

  private:
    /// @brief List of filepath (calibration images)
    std::vector<std::string> filelist_;

    /// @brief Chessboard Pattern Size (nx, ny)
    const cv::Size pattern_size_;

    /// @brief Calibration Image Size
    cv::Size image_size_;

    /// @brief Object Points (3D)
    std::vector<std::vector<cv::Point3f>> object_points_;

    /// @brief Image Points (2D)
    std::vector<std::vector<cv::Point2f>> image_points_;

    /// @brief Camera Calibration Parameters [Camera Matrix]
    cv::Mat camera_matrix_;

    /// @brief Camera Calibration Parameters [Distance Coefficients]
    cv::Mat dist_coeffs_;

    /// @brief Camera Calibration Parameters [Rotational Matrix]
    cv::Mat rotation_;

    /// @brief Camera Calibration Parameters [Translation Matrix]
    cv::Mat translation_;
};
}  // namespace perception

#endif  /// PERCEPTION_SENSOR_CAMERA_CALIBRATION_H
