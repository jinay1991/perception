///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/parameters.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace driver
{
namespace
{
using ::testing::AllOf;
using ::testing::Field;

TEST(Parameters, InitialValues)
{
    // Given
    constexpr Parameters parameters{};

    // Then
    EXPECT_THAT(
        parameters,
        AllOf(Field(&Parameters::fatigue_params,
                    AllOf(Field(&FatigueParameters::eye_lid_opening_range,
                                AllOf(Field(&ValidityRange<units::length::millimeter_t>::lower, kMinEyeLidOpening),
                                      Field(&ValidityRange<units::length::millimeter_t>::upper, kMaxEyeLidOpening))),
                          Field(&FatigueParameters::eye_blink_rate,
                                AllOf(Field(&ValidityRange<units::frequency::hertz_t>::lower, kMinEyeBlinkRate),
                                      Field(&ValidityRange<units::frequency::hertz_t>::upper, kMaxEyeBlinkRate))))),
              Field(&Parameters::system_params,
                    AllOf(Field(
                        &SystemParameters::velocity,
                        AllOf(Field(&ValidityRange<units::velocity::meters_per_second_t>::lower, kMinVelocity),
                              Field(&ValidityRange<units::velocity::meters_per_second_t>::upper, kMaxVelocity)))))));
}
}  // namespace
}  // namespace driver
}  // namespace perception
