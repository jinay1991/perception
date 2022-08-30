///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/parameter_handler.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace driver
{
namespace
{
using ::testing::AllOf;
using ::testing::Property;

TEST(ParameterHandler, Constructor_ExpectDefaultValues)
{
    // Given
    const ParameterHandler parameter_handler{};

    // Then
    EXPECT_THAT(parameter_handler,
                AllOf(Property(&ParameterHandler::GetMinEyeLidOpening, kMinEyeLidOpening),
                      Property(&ParameterHandler::GetMaxEyeLidOpening, kMaxEyeLidOpening),
                      Property(&ParameterHandler::GetMinEyeBlinkRate, kMinEyeBlinkRate),
                      Property(&ParameterHandler::GetMaxEyeBlinkRate, kMaxEyeBlinkRate),
                      Property(&ParameterHandler::GetMinVelocity, kMinVelocity),
                      Property(&ParameterHandler::GetMaxVelocity, kMaxVelocity)));
}
TEST(ParameterHandler, SetMinEyeLidOpening_GivenTypicalEyeLidOpening_ExpectUpdatedParameterHandler)
{
    // Given
    ParameterHandler parameter_handler{};
    const units::length::millimeter_t eye_lid_opening = 10.0_mm;

    // When
    parameter_handler.SetMinEyeLidOpening(eye_lid_opening);

    // Then
    EXPECT_EQ(eye_lid_opening, parameter_handler.GetMinEyeLidOpening());
}

TEST(ParameterHandler, SetMaxEyeLidOpening_GivenTypicalEyeLidOpening_ExpectUpdatedParameterHandler)
{
    // Given
    ParameterHandler parameter_handler{};
    const units::length::millimeter_t eye_lid_opening = 10.0_mm;

    // When
    parameter_handler.SetMaxEyeLidOpening(eye_lid_opening);

    // Then
    EXPECT_EQ(eye_lid_opening, parameter_handler.GetMaxEyeLidOpening());
}

TEST(ParameterHandler, SetMinEyeBlinkRate_GivenTypicalEyeBlinkRate_ExpectUpdatedParameterHandler)
{
    // Given
    ParameterHandler parameter_handler{};
    const units::frequency::hertz_t eye_blink_rate = 2.0_Hz;

    // When
    parameter_handler.SetMinEyeBlinkRate(eye_blink_rate);

    // Then
    EXPECT_EQ(eye_blink_rate, parameter_handler.GetMinEyeBlinkRate());
}

TEST(ParameterHandler, SetMaxEyeBlinkRate_GivenTypicalEyeBlinkRate_ExpectUpdatedParameterHandler)
{
    // Given
    ParameterHandler parameter_handler{};
    const units::frequency::hertz_t eye_blink_rate = 2.0_Hz;

    // When
    parameter_handler.SetMaxEyeBlinkRate(eye_blink_rate);

    // Then
    EXPECT_EQ(eye_blink_rate, parameter_handler.GetMaxEyeBlinkRate());
}

TEST(ParameterHandler, SetMinVelocity_GivenTypicalVelocity_ExpectUpdatedParameterHandler)
{
    // Given
    ParameterHandler parameter_handler{};
    const units::velocity::meters_per_second_t velocity = 8.0_kph;

    // When
    parameter_handler.SetMinVelocity(velocity);

    // Then
    EXPECT_EQ(velocity, parameter_handler.GetMinVelocity());
}

TEST(ParameterHandler, SetMaxVelocity_GivenTypicalVelocity_ExpectUpdatedParameterHandler)
{
    // Given
    ParameterHandler parameter_handler{};
    const units::velocity::meters_per_second_t velocity = 130.0_kph;

    // When
    parameter_handler.SetMaxVelocity(velocity);

    // Then
    EXPECT_EQ(velocity, parameter_handler.GetMaxVelocity());
}
}  // namespace
}  // namespace driver
}  // namespace perception
