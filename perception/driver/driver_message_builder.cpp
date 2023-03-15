///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/driver_message_builder.h"

namespace perception
{
namespace driver
{

DriverMessageBuilder::DriverMessageBuilder() : driver_message_{} {}

DriverMessageBuilder& DriverMessageBuilder::WithTimePoint(const std::chrono::system_clock::time_point& time_point)
{
    driver_message_.time_point = time_point;
    return *this;
}

DriverMessageBuilder& DriverMessageBuilder::WithActivityMessage(const ActivityMessage& activity)
{
    driver_message_.activity = activity;
    return *this;
}

DriverMessageBuilder& DriverMessageBuilder::WithFatigueMessage(const FatigueMessage& fatigue)
{
    driver_message_.fatigue = fatigue;
    return *this;
}

DriverMessageBuilder& DriverMessageBuilder::WithDistractionMessage(const DistractionMessage& distraction)
{
    driver_message_.distraction = distraction;
    return *this;
}

DriverMessageBuilder& DriverMessageBuilder::WithResponsivenessMessage(const ResponsivenessMessage& responsiveness)
{
    driver_message_.responsiveness = responsiveness;
    return *this;
}

const DriverMessage& DriverMessageBuilder::Build() const
{
    return driver_message_;
}

}  // namespace driver
}  // namespace perception
