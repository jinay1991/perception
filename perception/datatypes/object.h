///
/// @file
/// @copyright Copyright (c) 2020. All Right Reserved.
///
#ifndef PERCEPTION_CAMERA_DATATYPES_OBJECT_H_
#define PERCEPTION_CAMERA_DATATYPES_OBJECT_H_

#include "perception/common/event_data_qualifier/event_data_qualifier.h"
#include "perception/datatypes/lane.h"

#include <units.h>

#include <array>
#include <cstdint>

namespace perception
{

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

struct Object
{
    EventDataQualifier event_data_qualifier;

    units::length::meters_t distance;
    units::length::meters_t longitudinal_distance;
    units::length::meters_t latitudinal_distance;

    units::velocity::meters_per_second_t relative_velocity;
    units::velocity::meters_per_second_t velocity;

    units::time::milliseconds_t time_to_collision;

    units::angle::radian_t yaw;
    units::angle::radian_t pitch;

    BoundingBox bounding_box;
    ObjectId id;

    LaneId lane_id;
};

using Objects = std::array<Object, 100U>;

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

#endif  /// PERCEPTION_CAMERA_DATATYPES_OBJECT_H_