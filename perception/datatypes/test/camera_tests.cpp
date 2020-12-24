///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/datatypes/camera.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
using ::testing::AllOf;
using ::testing::Field;

TEST(Camera, GlobalConstants)
{
    // Then
    EXPECT_THAT(kDefaultCameraMatrix,
                AllOf(Field(&cv::Mat::dims, 2), Field(&cv::Mat::rows, 3), Field(&cv::Mat::cols, 3)));
    EXPECT_THAT(kDefaultDistanceCoefficient,
                AllOf(Field(&cv::Mat::dims, 2), Field(&cv::Mat::rows, 1), Field(&cv::Mat::cols, 5)));
}

}  // namespace
}  // namespace perception
