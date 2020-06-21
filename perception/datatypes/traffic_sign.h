///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_DATATYPE_TRAFFIC_SIGN_H
#define PERCEPTION_DATATYPE_TRAFFIC_SIGN_H

#include "perception/datatypes/lane.h"

#include <units.h>

#include <array>
#include <cstdint>

namespace perception
{
constexpr std::int32_t kMaxNumberOfTrafficSigns{10U};

enum class TrafficSignId : std::int32_t
{
    kNone = 0U,
    kSpeedLimit = 1U,
    kRoadWorks = 2U,
    kTurnLeft = 3U,
    kTurnRight = 4U,
    kTwoBumps = 5U,
    kInvalid = 255U,
};

struct TrafficSignMessage
{
    units::length::meter_t distance;

    TrafficSignId id;
    LaneId lane_id;
};

using TrafficSignListMessage = std::array<TrafficSignMessage, kMaxNumberOfTrafficSigns>;

inline const char* to_string(const TrafficSignId& id)
{
    switch (id)
    {
        case TrafficSignId::kNone:
            return "kNone";
        case TrafficSignId::kSpeedLimit:
            return "kSpeedLimit";
        case TrafficSignId::kRoadWorks:
            return "kRoadWorks";
        case TrafficSignId::kTurnLeft:
            return "kTurnLeft";
        case TrafficSignId::kTurnRight:
            return "kTurnRight";
        case TrafficSignId::kTwoBumps:
            return "kTwoBumps";
        case TrafficSignId::kInvalid:
            return "kInvalid";
        default:
            return "ERROR: Unknown TrafficSignId";
    }
    return "ERROR: Unknown TrafficSignId";
}

inline std::ostream& operator<<(std::ostream& stream, const TrafficSignId& id)
{
    const char* name = to_string(id);
    stream << name;
    return stream;
}
}  // namespace perception

#endif  /// PERCEPTION_DATATYPE_TRAFFIC_SIGN_H
