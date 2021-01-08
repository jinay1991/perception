///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License
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

    /// @brief Longitudinal distance (3D space)
    units::length::meter_t longitudinal_distance{0.0};

    /// @brief Lateral distance (3D space)
    units::length::meter_t lateral_distance{0.0};

    /// @brief Traffic Sign Id
    TrafficSignId id{TrafficSignId::kInvalid};
};

/// @brief Traffic Sign List Information
struct TrafficSignListMessage
{
    /// @brief Time Point for captured traffic sign
    std::chrono::system_clock::time_point time_point{};

    /// @brief Number of Valid Traffic Signs
    std::int32_t number_of_valid_traffic_signs{0};

    /// @brief Traffic Sign List
    std::array<TrafficSignMessage, kMaxNumberOfTrafficSigns> traffic_signs{};
};

}  // namespace perception

#endif  /// PERCEPTION_DATATYPE_TRAFFIC_SIGN_H
