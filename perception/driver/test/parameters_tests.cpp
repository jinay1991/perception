///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/parameters.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
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
    EXPECT_THAT(parameters,
                AllOf(Field(&Parameters::eye_lid_opening_range,
                            AllOf(Field(&ValidityRange<units::length::millimeter_t>::lower, kMinEyeLidOpening),
                                  Field(&ValidityRange<units::length::millimeter_t>::upper, kMaxEyeLidOpening))),
                      Field(&Parameters::eye_blink_rate, kMaxEyeBlinkRate)));
}
}  // namespace
}  // namespace perception
