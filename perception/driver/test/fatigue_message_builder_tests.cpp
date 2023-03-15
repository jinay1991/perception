///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/fatigue_message_builder.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace driver
{
namespace
{
using ::testing::AllOf;
using ::testing::DoubleEq;
using ::testing::Field;

TEST(FatigueMessageBuilder, Build_ExpectDefaultFatigueMessage)
{
    // When
    const auto received_fatigue_message = FatigueMessageBuilder().Build();

    // Then
    EXPECT_THAT(received_fatigue_message,
                AllOf(Field(&FatigueMessage::time_point, std::chrono::system_clock::time_point{}),
                      Field(&FatigueMessage::state, FatigueState::kInvalid),
                      Field(&FatigueMessage::confidence, DoubleEq(0.0))));
}

TEST(FatigueMessageBuilder, WithTimePoint_GivenTypicalTimePoint_ExpectUpdatedFatigueMessage)
{
    // Given
    const std::chrono::system_clock::time_point time_point{20ms};

    // When
    const FatigueMessage& received_fatigue_message = FatigueMessageBuilder().WithTimePoint(time_point).Build();

    // Then
    EXPECT_THAT(received_fatigue_message.time_point, time_point);
}

TEST(FatigueMessageBuilder, WithFatigueLevel_GivenTypicalFatigueLevel_ExpectUpdatedFatigueMessage)
{
    // Given
    const FatigueState state{FatigueState::kBeginningSleep};

    // When
    const FatigueMessage& received_fatigue_message = FatigueMessageBuilder().WithState(state).Build();

    // Then
    EXPECT_THAT(received_fatigue_message.state, state);
}

TEST(FatigueMessageBuilder, WithFatigueConfidence_GivenTypicalFatigueConfidence_ExpectUpdatedFatigueMessage)
{
    // Given
    const double confidence{35.0};

    // When
    const FatigueMessage& received_fatigue_message = FatigueMessageBuilder().WithConfidence(confidence).Build();

    // Then
    EXPECT_THAT(received_fatigue_message.confidence, confidence);
}

}  // namespace
}  // namespace driver
}  // namespace perception
