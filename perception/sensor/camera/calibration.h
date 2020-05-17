///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_SENSOR_CAMERA_CALIBRATION_H_
#define PERCEPTION_SENSOR_CAMERA_CALIBRATION_H_

#include <opencv4/opencv2/core.hpp>

#include <cstdint>
#include <string>
#include <vector>

namespace perception
{
namespace sensor
{
namespace camera
{
class Calibration
{
  public:
    Calibration();

    /// @brief Construct Calibration utility for certain chessboard pattern
    /// @param dirname [in] - Directory path/name containing calibration images (chessboard images)
    /// @param nx [in] - Number of chessboard blocks in X-axes
    /// @param ny [in] - Number of chessboard blocks in Y-axes
    explicit Calibration(const std::string dirname, const std::int32_t nx, const std::int32_t ny);

    virtual void Init();
    virtual void Execute();
    virtual void Shutdown();

    virtual cv::Mat GetCameraMatrix() const;
    virtual cv::Mat GetDistanceCoeffs() const;
    virtual cv::Mat GetRotationMatrix() const;
    virtual cv::Mat GetTranslationMatrix() const;

  private:
    std::vector<std::string> filelist_;

    cv::Size pattern_size_;
    cv::Size image_size_;

    std::vector<std::vector<cv::Point3f>> object_points_;
    std::vector<std::vector<cv::Point2f>> image_points_;

    cv::Mat camera_matrix_;
    cv::Mat dist_coeffs_;
    cv::Mat rotation_;
    cv::Mat translation_;
};
}  // namespace camera
}  // namespace sensor
}  // namespace perception

#endif  /// PERCEPTION_SENSOR_CAMERA_CALIBRATION_H_
