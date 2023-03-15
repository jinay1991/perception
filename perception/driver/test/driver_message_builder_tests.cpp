///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/activity_message_builder.h"
#include "perception/driver/distraction_message_builder.h"
#include "perception/driver/driver_message_builder.h"
#include "perception/driver/fatigue_message_builder.h"
#include "perception/driver/responsiveness_message_builder.h"

#include <gtest/gtest.h>

namespace perception
{
namespace driver
{
namespace
{
TEST(DriverMessageBuilderTest, Build_ExpectDefaultDriverMessage)
{
    // Given
    const DriverMessage driver_message{};

    // When
    const auto result = DriverMessageBuilder().Build();

    // Then
    EXPECT_EQ(result, driver_message);
}

TEST(DriverMessageBuilderTest, WithTimePoint_GivenTypicalTimePoint_ExpectUpdatedDriverMessage)
{
    // Given
    const std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();

    // When
    const auto result = DriverMessageBuilder().WithTimePoint(time_point).Build();

    // Then
    EXPECT_EQ(result.time_point, time_point);
}

TEST(DriverMessageBuilderTest, WithFatigueMessage_GivenTypicalMessage_ExpectUpdatedDriverMessage)
{
    // Given
    const FatigueMessage fatigue = FatigueMessageBuilder().WithState(FatigueState::kAwake).Build();

    // When
    const auto result = DriverMessageBuilder().WithFatigueMessage(fatigue).Build();

    // Then
    EXPECT_EQ(result.fatigue, fatigue);
}

TEST(DriverMessageBuilderTest, WithDistractionMessage_GivenTypicalMessage_ExpectUpdatedDriverMessage)
{
    // Given
    const DistractionMessage distraction = DistractionMessageBuilder().WithState(DistractionState::kDistracted).Build();

    // When
    const auto result = DriverMessageBuilder().WithDistractionMessage(distraction).Build();

    // Then
    EXPECT_EQ(result.distraction, distraction);
}

TEST(DriverMessageBuilderTest, WithActivityMessage_GivenTypicalMessage_ExpectUpdatedDriverMessage)
{
    // Given
    const ActivityMessage activity = ActivityMessageBuilder().WithState(ActivityState::kNotAvailable).Build();

    // When
    const auto result = DriverMessageBuilder().WithActivityMessage(activity).Build();

    // Then
    EXPECT_EQ(result.activity, activity);
}

TEST(DriverMessageBuilderTest, WithResponsiveness_GivenTypicalMessage_ExpectUpdatedDriverMessage)
{
    // Given
    const ResponsivenessMessage responsiveness =
        ResponsivenessMessageBuilder().WithState(ResponsivenessState::kResponsive).Build();

    // When
    const auto result = DriverMessageBuilder().WithResponsivenessMessage(responsiveness).Build();

    // Then
    EXPECT_EQ(result.responsiveness, responsiveness);
}

}  // namespace
}  // namespace driver
}  // namespace perception
