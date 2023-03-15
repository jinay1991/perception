///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/activity_message_builder.h"

namespace perception
{
namespace driver
{
ActivityMessageBuilder::ActivityMessageBuilder() : activity_message_{} {}

ActivityMessageBuilder& ActivityMessageBuilder::WithTimePoint(const std::chrono::system_clock::time_point& time_point)
{
    activity_message_.time_point = time_point;
    return *this;
}

ActivityMessageBuilder& ActivityMessageBuilder::WithState(const ActivityState state)
{
    activity_message_.state = state;
    return *this;
}

ActivityMessageBuilder& ActivityMessageBuilder::WithConfidence(const double confidence)
{
    activity_message_.confidence = confidence;
    return *this;
}

const ActivityMessage& ActivityMessageBuilder::Build() const
{
    return activity_message_;
}
}  // namespace driver
}  // namespace perception
