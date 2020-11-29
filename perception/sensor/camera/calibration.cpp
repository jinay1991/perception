///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/sensor/camera/calibration.h"

#include "perception/common/logging.h"

#include <opencv4/opencv2/calib3d.hpp>
#include <opencv4/opencv2/calib3d/calib3d.hpp>
#include <opencv4/opencv2/core/hal/interface.h>
#include <opencv4/opencv2/core/types.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>

#include <iterator>
#include <numeric>

namespace perception
{

Calibration::Calibration(const std::string dirname, const std::int32_t nx, const std::int32_t ny)
    : filelist_{},
      pattern_size_{nx, ny},
      image_size_{},
      object_points_{},
      image_points_{},
      camera_matrix_{},
      dist_coeffs_{},
      rotation_{},
      translation_{}
{
    cv::glob(dirname, filelist_, true);
}

void Calibration::Init()
{
    std::vector<cv::Point3f> pattern_points{};
    for (std::int32_t w = 0; w < pattern_size_.width; ++w)
    {
        for (std::int32_t h = 0; h < pattern_size_.height; ++h)
        {
            pattern_points.push_back(cv::Point3f(w, h, 0));
        }
    }

    /// @todo Use threads to improve performance.
    for (const auto& filename : filelist_)
    {
        const cv::Mat image = cv::imread(filename, cv::IMREAD_GRAYSCALE);
        image_size_ = image.size();

        std::vector<cv::Point2f> corners{};
        if (!cv::findChessboardCorners(
                image,
                pattern_size_,
                corners,
                cv::CALIB_CB_FAST_CHECK | cv::CALIB_CB_NORMALIZE_IMAGE | cv::CALIB_CB_ADAPTIVE_THRESH))
        {
            continue;
        }

        image_points_.push_back(corners);
        object_points_.push_back(pattern_points);
    }
}
void Calibration::Execute()
{
    const double root_mean_square = cv::calibrateCamera(
        object_points_, image_points_, image_size_, camera_matrix_, dist_coeffs_, rotation_, translation_);

    LOG(INFO) << "Root Mean Square (RMS) Error reported after calibrating " << filelist_.size()
              << " images for CAMERA: " << root_mean_square;
}

void Calibration::Shutdown() {}

const cv::Mat& Calibration::GetCameraMatrix() const
{
    return camera_matrix_;
}

const cv::Mat& Calibration::GetDistanceCoeffs() const
{
    return dist_coeffs_;
}

const cv::Mat& Calibration::GetRotationMatrix() const
{
    return rotation_;
}

const cv::Mat& Calibration::GetTranslationMatrix() const
{
    return translation_;
}

}  // namespace perception
