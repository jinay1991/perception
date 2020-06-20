///
/// @file
/// @copyright Copyright (c) 2020. All Right Reserved.
///
#ifndef PERCEPTION_CAMERA_DATATYPES_OBJECT_H
#define PERCEPTION_CAMERA_DATATYPES_OBJECT_H

#include "perception/datatypes/lane.h"

#include <units.h>

#include <algorithm>
#include <array>
#include <cstdint>

namespace perception
{
constexpr std::int32_t kMaxNumberofObjects{100U};

enum class ObjectId : std::uint8_t
{
    kUnknown = 0U,
    kCar = 1U,
    kTruck = 2U,
    kMotorBike = 3U,
    kBicycle = 4U,
    kPedestrian = 5U,
    kObstacle = 6U,
    kInvalid = 255U
};

struct BoundingBox
{
    double x;
    double y;
    double width;
    double height;
};

struct ObjectMessage
{
    units::length::meter_t distance;
    units::length::meter_t longitudinal_distance;
    units::length::meter_t latitudinal_distance;

    units::velocity::meters_per_second_t relative_velocity;
    units::velocity::meters_per_second_t velocity;

    units::time::microsecond_t time_to_collision;

    units::angle::radian_t yaw;
    units::angle::radian_t pitch;

    BoundingBox bounding_box;
    ObjectId id;

    LaneId lane_id;
};

using ObjectListMessage = std::array<ObjectMessage, kMaxNumberofObjects>;

inline bool operator==(const BoundingBox& lhs, const BoundingBox& rhs) noexcept
{
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.width == rhs.width) && (lhs.height == rhs.height));
}

inline bool operator!=(const BoundingBox& lhs, const BoundingBox& rhs) noexcept
{
    return (!(lhs == rhs));
}

inline bool operator==(const ObjectMessage& lhs, const ObjectMessage& rhs) noexcept
{
    return ((lhs.distance == rhs.distance) && (lhs.longitudinal_distance == rhs.longitudinal_distance) &&
            (lhs.latitudinal_distance == rhs.latitudinal_distance) &&
            (lhs.relative_velocity == rhs.relative_velocity) && (lhs.velocity == rhs.velocity) &&
            (lhs.time_to_collision == rhs.time_to_collision) && (lhs.yaw == rhs.yaw) && (lhs.pitch == rhs.pitch) &&
            (lhs.bounding_box == rhs.bounding_box) && (lhs.id == rhs.id) && (lhs.lane_id == rhs.lane_id));
}

inline bool operator!=(const ObjectMessage& lhs, const ObjectMessage& rhs) noexcept
{
    return (!(lhs == rhs));
}

inline const char* to_string(const ObjectId& id)
{
    switch (id)
    {
        case ObjectId::kUnknown:
            return "kUnknown";
        case ObjectId::kCar:
            return "kCar";
        case ObjectId::kTruck:
            return "kTruck";
        case ObjectId::kMotorBike:
            return "kMotorBike";
        case ObjectId::kBicycle:
            return "kBicycle";
        case ObjectId::kPedestrian:
            return "kPedestrian";
        case ObjectId::kObstacle:
            return "kObstacle";
        case ObjectId::kInvalid:
            return "kInvalid";
        default:
            return "ERROR: Unknown ObjectId";
    }
    return "ERROR: Unknown ObjectId";
}

inline std::ostream& operator<<(std::ostream& stream, const ObjectId& id)
{
    const char* name = to_string(id);
    stream << name;
    return stream;
}

}  // namespace perception

#endif  /// PERCEPTION_CAMERA_DATATYPES_OBJECT_H
