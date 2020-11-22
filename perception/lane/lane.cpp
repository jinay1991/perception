///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/lane/lane.h"

namespace perception
{
namespace
{
void PerformAbsoluteSobelThreshold(const cv::Mat& image,
                                   const char orientation = 'x',
                                   const std::int32_t kernel_size = 3,
                                   const std::int32_t lower_threshold = 0,
                                   const std::int32_t upper_threshold = 255)
{
    // Perform Sobel Threshold
}

void CalculateGradientDirection(const cv::Mat& image,
                                const std::int32_t kernel_size = 3,
                                const std::int32_t lower_threshold = 0,
                                const std::int32_t upper_threshold = 255)
{
    // Calculate Gradient Threshold
    // Perform Threshold
}

}  // namespace
Lane::Lane() {}

void Lane::Init() {}

void Lane::Step() {}

void Lane::Shutdown() {}

}  // namespace perception
