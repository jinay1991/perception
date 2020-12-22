///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/fatigue_message_builder.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
using ::testing::AllOf;
using ::testing::Field;
using namespace std::chrono_literals;

TEST(FatigueMessageBuilder, Build_ExpectDefaultFatigueMessage)
{
    // When
    const FatigueMessage& received_fatigue_message = FatigueMessageBuilder().Build();

    // Then
    EXPECT_THAT(received_fatigue_message,
                AllOf(Field(&FatigueMessage::time_point, std::chrono::system_clock::time_point{}),
                      Field(&FatigueMessage::level, FatigueLevel::kInvalid),
                      Field(&FatigueMessage::confidence, 0.0),
                      Field(&FatigueMessage::eye_state, EyeState::kInvalid)));
}

TEST(FatigueMessageBuilder, WithTimepoint_GivenTypicalTimepoint_ExpectUpdatedFatigueMessage)
{
    // Given
    const std::chrono::system_clock::time_point time_point{20ms};

    // When
    const FatigueMessage& received_fatigue_message = FatigueMessageBuilder().WithTimepoint(time_point).Build();

    // Then
    EXPECT_THAT(received_fatigue_message, Field(&FatigueMessage::time_point, time_point));
}

TEST(FatigueMessageBuilder, WithFatigueLevel_GivenTypicalFatigueLevel_ExpectUpdatedFatigueMessage)
{
    // Given
    const FatigueLevel level{FatigueLevel::kBeginningSleep};

    // When
    const FatigueMessage& received_fatigue_message = FatigueMessageBuilder().WithFatigueLevel(level).Build();

    // Then
    EXPECT_THAT(received_fatigue_message, Field(&FatigueMessage::level, level));
}

TEST(FatigueMessageBuilder, WithFatigueConfidence_GivenTypicalFatigueConfidence_ExpectUpdatedFatigueMessage)
{
    // Given
    const double confidence{35.0};

    // When
    const FatigueMessage& received_fatigue_message = FatigueMessageBuilder().WithFatigueConfidence(confidence).Build();

    // Then
    EXPECT_THAT(received_fatigue_message, Field(&FatigueMessage::confidence, confidence));
}

TEST(FatigueMessageBuilder, WithEyeState_GivenTypicalEyeState_ExpectUpdatedFatigueMessage)
{
    // Given
    const EyeState eye_state{EyeState::kEyesClosed};

    // When
    const FatigueMessage& received_fatigue_message = FatigueMessageBuilder().WithEyeState(eye_state).Build();

    // Then
    EXPECT_THAT(received_fatigue_message, Field(&FatigueMessage::eye_state, eye_state));
}
}  // namespace
}  // namespace perception
