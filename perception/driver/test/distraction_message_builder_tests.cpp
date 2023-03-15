///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/distraction_message_builder.h"

#include <gtest/gtest.h>

namespace perception
{
namespace driver
{
namespace
{
TEST(DistractionMessageBuilderTest, Build_ExpectDefaultDistractionMessage)
{
    // Given
    const DistractionMessage distraction_message{};

    // When
    const auto result = DistractionMessageBuilder().Build();

    // Then
    EXPECT_EQ(result, distraction_message);
}

TEST(DistractionMessageBuilderTest, WithTimePoint_GivenTypicalTimePoint_ExpectUpdatedDistractionMessage)
{
    // Given
    const std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();

    // When
    const auto result = DistractionMessageBuilder().WithTimePoint(time_point).Build();

    // Then
    EXPECT_EQ(result.time_point, time_point);
}

TEST(DistractionMessageBuilderTest, WithState_GivenTypicalState_ExpectUpdatedDistractionMessage)
{
    // Given
    const DistractionState state{DistractionState::kDistracted};

    // When
    const auto result = DistractionMessageBuilder().WithState(state).Build();

    // Then
    EXPECT_EQ(result.state, state);
}

TEST(DistractionMessageBuilderTest, WithConfidence_GivenTypicalConfidence_ExpectUpdatedDistractionMessage)
{
    // Given
    const double confidence{0.12};

    // When
    const auto result = DistractionMessageBuilder().WithConfidence(confidence).Build();

    // Then
    EXPECT_EQ(result.confidence, confidence);
}

}  // namespace
}  // namespace driver
}  // namespace perception
