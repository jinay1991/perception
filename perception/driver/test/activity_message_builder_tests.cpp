///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/activity_message_builder.h"

#include <gtest/gtest.h>

namespace perception
{
namespace driver
{
namespace
{
TEST(ActivityMessageBuilderTest, Build_ExpectDefaultDriverCameraMessage)
{
    // Given
    const ActivityMessage activity_message{};

    // When
    const auto result = ActivityMessageBuilder().Build();

    // Then
    EXPECT_EQ(result, activity_message);
}

TEST(ActivityMessageBuilderTest, WithTimePoint_GivenTypicalTimePoint_ExpectUpdatedDistractionMessage)
{
    // Given
    const std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();

    // When
    const auto result = ActivityMessageBuilder().WithTimePoint(time_point).Build();

    // Then
    EXPECT_EQ(result.time_point, time_point);
}

TEST(ActivityMessageBuilderTest, WithState_GivenTypicalState_ExpectUpdatedDistractionMessage)
{
    // Given
    const ActivityState state{ActivityState::kHandsOffWheel};

    // When
    const auto result = ActivityMessageBuilder().WithState(state).Build();

    // Then
    EXPECT_EQ(result.state, state);
}

TEST(ActivityMessageBuilderTest, WithConfidence_GivenTypicalConfidence_ExpectUpdatedDistractionMessage)
{
    // Given
    const double confidence{0.12};

    // When
    const auto result = ActivityMessageBuilder().WithConfidence(confidence).Build();

    // Then
    EXPECT_EQ(result.confidence, confidence);
}

}  // namespace
}  // namespace driver
}  // namespace perception
