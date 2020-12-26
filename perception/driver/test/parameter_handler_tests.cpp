///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/parameter_handler.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{

TEST(ParameterHandlerTest, SetMinEyeLidOpening_GivenTypicalEyeLidOpening_ExpectUpdatedParameterHandler)
{
    // Given
    ParameterHandler parameter_handler{};
    const units::length::millimeter_t eye_lid_opening = 10.0_mm;

    // When
    parameter_handler.SetMinEyeLidOpening(eye_lid_opening);

    // Then
    EXPECT_EQ(eye_lid_opening, parameter_handler.GetMinEyeLidOpening());
}

TEST(ParameterHandlerTest, SetMaxEyeLidOpening_GivenTypicalEyeLidOpening_ExpectUpdatedParameterHandler)
{
    // Given
    ParameterHandler parameter_handler{};
    const units::length::millimeter_t eye_lid_opening = 10.0_mm;

    // When
    parameter_handler.SetMaxEyeLidOpening(eye_lid_opening);

    // Then
    EXPECT_EQ(eye_lid_opening, parameter_handler.GetMaxEyeLidOpening());
}

TEST(ParameterHandlerTest, SetEyeBlinkRate_GivenTypicalEyeBlinkRate_ExpectUpdatedParameterHandler)
{
    // Given
    ParameterHandler parameter_handler{};
    const units::frequency::hertz_t eye_blink_rate = 2.0_Hz;
    const std::chrono::milliseconds eye_blink_duration =
        std::chrono::seconds{static_cast<std::int32_t>(std::floor(1.0 / eye_blink_rate.value()))};

    // When
    parameter_handler.SetEyeBlinkRate(eye_blink_rate);

    // Then
    EXPECT_EQ(eye_blink_rate, parameter_handler.GetEyeBlinkRate());
    EXPECT_EQ(eye_blink_duration, parameter_handler.GetEyeBlinkDuration());
}
}  // namespace
}  // namespace perception
