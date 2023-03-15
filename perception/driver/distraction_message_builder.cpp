///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/distraction_message_builder.h"

namespace perception
{
namespace driver
{
DistractionMessageBuilder::DistractionMessageBuilder() : distraction_message_{} {}

DistractionMessageBuilder& DistractionMessageBuilder::WithTimePoint(
    const std::chrono::system_clock::time_point& time_point)
{
    distraction_message_.time_point = time_point;
    return *this;
}

DistractionMessageBuilder& DistractionMessageBuilder::WithState(const DistractionState state)
{
    distraction_message_.state = state;
    return *this;
}

DistractionMessageBuilder& DistractionMessageBuilder::WithConfidence(const double confidence)
{
    distraction_message_.confidence = confidence;
    return *this;
}

const DistractionMessage& DistractionMessageBuilder::Build() const
{
    return distraction_message_;
}
}  // namespace driver
}  // namespace perception
