///
/// @file
/// @copyright Copyright (c) 2023. MIT License
///
#ifndef PERCEPTION_DATATYPE_TRAFFIC_LIGHT_H
#define PERCEPTION_DATATYPE_TRAFFIC_LIGHT_H

#include "perception/datatypes/lane.h"

#include <units.h>

#include <array>
#include <cstdint>
#include <ostream>

namespace perception
{
/// @brief Maximum Number of Traffic Lights
constexpr std::int32_t kMaxNumberOfTrafficLights{10};

/// @brief Traffic Light Id
enum class TrafficLightId : std::uint8_t
{
    kNone = 0U,
    kRed = 1U,
    kGreen = 2U,
    kYellow = 3U,
    kInvalid = 255U,
};

/// @brief Traffic Light Information
struct TrafficLightMessage
{
    /// @brief Traffic Light Distance
    units::length::meter_t distance{0.0};

    /// @brief Traffic Sign Id
    TrafficLightId id{TrafficLightId::kInvalid};

    /// @brief Traffic Light associated Lane Id
    LaneId lane_id{LaneId::kInvalid};
};

/// @brief Traffic Light List Information
struct TrafficLightListMessage
{
    /// @brief Time Point for captured traffic light
    std::chrono::system_clock::time_point time_point{};

    /// @brief Number of valid Traffic Lights
    std::int32_t number_of_valid_traffic_lights{0};

    /// @brief Traffic Light List
    std::array<TrafficLightMessage, kMaxNumberOfTrafficLights> traffic_light_list{};
};

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

#endif  /// PERCEPTION_DATATYPE_TRAFFIC_LIGHT_H
