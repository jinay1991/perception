///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DATATYPES_CAMERA_H
#define PERCEPTION_DATATYPES_CAMERA_H

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/core/base.hpp>

namespace perception
{

struct CalibrationParams
{
    cv::Mat intrinsic;
    cv::Mat extrinsic;
};

using Image = cv::Mat;

}  // namespace perception

#endif  /// PERCEPTION_DATATYPES_CAMERA_H
