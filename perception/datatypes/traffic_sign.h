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
/// @brief Maximum Number of Traffic Signs
constexpr std::int32_t kMaxNumberOfTrafficSigns{10U};

/// @brief Traffic Sign Id
enum class TrafficSignId : std::uint8_t
{
    kNone = 0U,
    kSpeedLimit = 1U,
    kRoadWorks = 2U,
    kTurnLeft = 3U,
    kTurnRight = 4U,
    kTwoBumps = 5U,
    kInvalid = 255U,
};

/// @brief Traffic Sign Information
struct TrafficSignMessage
{
    /// @brief Traffic Sign Distance
    units::length::meter_t distance{0.0};

    /// @brief Traffic Sign Id
    TrafficSignId id{TrafficSignId::kInvalid};

    /// @brief Traffic Sign associated Lane Id
    LaneId lane_id{LaneId::kInvalid};
};

/// @brief Traffic Sign List Information
struct TrafficSignListMessage
{
    /// @brief Time Point for captured traffic sign
    std::chrono::system_clock::time_point time_point{};

    /// @brief Number of Valid Traffic Signs
    std::int32_t number_of_valid_traffic_signs{0};

    /// @brief Traffic Sign List
    std::array<TrafficSignMessage, kMaxNumberOfTrafficSigns> traffic_sign_list{};
};

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
