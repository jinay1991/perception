///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/responsiveness_message_builder.h"

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

TEST(ResponsivenessMessageBuilder, Build_ExpectDefaultResponsivenessMessage)
{
    // When
    const auto received_responsiveness_message = ResponsivenessMessageBuilder().Build();

    // Then
    EXPECT_THAT(received_responsiveness_message,
                AllOf(Field(&ResponsivenessMessage::time_point, std::chrono::system_clock::time_point{}),
                      Field(&ResponsivenessMessage::state, ResponsivenessState::kInvalid),
                      Field(&ResponsivenessMessage::confidence, DoubleEq(0.0))));
}

TEST(ResponsivenessMessageBuilder, WithTimePoint_GivenTypicalTimePoint_ExpectUpdatedResponsivenessMessage)
{
    // Given
    const std::chrono::system_clock::time_point time_point{20ms};

    // When
    const ResponsivenessMessage& received_responsiveness_message =
        ResponsivenessMessageBuilder().WithTimePoint(time_point).Build();

    // Then
    EXPECT_THAT(received_responsiveness_message.time_point, time_point);
}

TEST(ResponsivenessMessageBuilder,
     WithResponsivenessLevel_GivenTypicalResponsivenessLevel_ExpectUpdatedResponsivenessMessage)
{
    // Given
    const ResponsivenessState state{ResponsivenessState::kResponsive};

    // When
    const ResponsivenessMessage& received_responsiveness_message =
        ResponsivenessMessageBuilder().WithState(state).Build();

    // Then
    EXPECT_THAT(received_responsiveness_message.state, state);
}

TEST(ResponsivenessMessageBuilder,
     WithResponsivenessConfidence_GivenTypicalResponsivenessConfidence_ExpectUpdatedResponsivenessMessage)
{
    // Given
    const double confidence{35.0};

    // When
    const ResponsivenessMessage& received_responsiveness_message =
        ResponsivenessMessageBuilder().WithConfidence(confidence).Build();

    // Then
    EXPECT_THAT(received_responsiveness_message.confidence, confidence);
}

}  // namespace
}  // namespace driver
}  // namespace perception
