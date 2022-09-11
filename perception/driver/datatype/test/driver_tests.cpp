///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/datatype/driver.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace driver
{
namespace
{

TEST(Driver, GlobalConstants)
{
    // Then
    EXPECT_EQ(kMinEyeBlinkRate, 0.15_Hz);
    EXPECT_EQ(kMaxEyeBlinkRate, 0.5_Hz);
    EXPECT_EQ(kMaxEyeLidOpening, 10.0_mm);
    EXPECT_EQ(kMinEyeLidOpening, 1.0_mm);
    EXPECT_EQ(kMinHeadPoseYaw, -80_deg);
    EXPECT_EQ(kMaxHeadPoseYaw, 75_deg);
    EXPECT_EQ(kMinHeadPosePitch, -60_deg);
    EXPECT_EQ(kMaxHeadPosePitch, 70_deg);
    EXPECT_EQ(kMinHeadPoseRoll, -40_deg);
    EXPECT_EQ(kMaxHeadPoseRoll, 36.0_deg);
    EXPECT_EQ(kMaxEyeStateObservationDuration, 5min);
}

}  // namespace
}  // namespace driver
}  // namespace perception
