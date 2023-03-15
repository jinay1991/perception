///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/responsiveness_message_builder.h"

namespace perception
{
namespace driver
{
ResponsivenessMessageBuilder::ResponsivenessMessageBuilder() : responsiveness_message_{} {}

ResponsivenessMessageBuilder& ResponsivenessMessageBuilder::WithTimePoint(
    const std::chrono::system_clock::time_point& time_point)
{
    responsiveness_message_.time_point = time_point;
    return *this;
}

ResponsivenessMessageBuilder& ResponsivenessMessageBuilder::WithState(const ResponsivenessState state)
{
    responsiveness_message_.state = state;
    return *this;
}

ResponsivenessMessageBuilder& ResponsivenessMessageBuilder::WithConfidence(const double confidence)
{
    responsiveness_message_.confidence = confidence;
    return *this;
}

const ResponsivenessMessage& ResponsivenessMessageBuilder::Build() const
{
    return responsiveness_message_;
}

}  // namespace driver
}  // namespace perception
