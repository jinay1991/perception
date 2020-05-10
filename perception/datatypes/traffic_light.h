///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_CAMERA_DATATYPE_TRAFFIC_LIGHT_H_
#define PERCEPTION_CAMERA_DATATYPE_TRAFFIC_LIGHT_H_

#include "perception/common/event_data_qualifier/event_data_qualifier.h"

#include <units.h>

#include <array>
#include <cstdint>
#include <ostream>

namespace perception
{
enum class TrafficLightId : std::uint8_t
{
    kNone = 0U,
    kRed = 1U,
    kGreen = 2U,
    kYellow = 3U,
    kInvalid = 255U,
};

struct TrafficLight
{
    EventDataQualifier event_data_qualifer;

    units::length::meters_t distance;

    TrafficLightId id;
    LaneId lane_id;
};

using TrafficLightList = std::array<TrafficLight, 10U>;

inline const char* to_string(const TrafficLightId& id)
{
    switch (id)
    {
        case TrafficLightId::kNone:
            return "kNone";
        case TrafficLightId::kRed:
            return "kRed";
        case TrafficLightId::kGreen:
            return "kGreen";
        case TrafficLightId::kYellow:
            return "kYellow";
        case TrafficLightId::kInvalid:
            return "kInvalid";
        default:
            return "ERROR: Unknown TrafficLightId";
    }
    return "ERROR: Unknown TrafficLightId";
}

inline std::ostream& operator<<(std::ostream& stream, const TrafficLightId& id)
{
    const char* name = to_string(id);
    stream << name;
    return stream;
}
}  // namespace perception

#endif  /// PERCEPTION_CAMERA_DATATYPE_TRAFFIC_LIGHT_H_