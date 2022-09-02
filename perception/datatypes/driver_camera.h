///
/// @file
/// @copyright Copyright (c) 2021. MIT License.
///
#ifndef PERCEPTION_DATATYPES_DRIVER_CAMERA_H
#define PERCEPTION_DATATYPES_DRIVER_CAMERA_H

#include <opencv4/opencv2/core.hpp>

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
}  // namespace perception

#endif  /// PERCEPTION_DATATYPES_DRIVER_CAMERA_H