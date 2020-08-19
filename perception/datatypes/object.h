///
/// @file
/// @copyright Copyright (c) 2020. All Right Reserved.
///
#ifndef PERCEPTION_DATATYPES_OBJECT_H
#define PERCEPTION_DATATYPES_OBJECT_H

#include "perception/datatypes/lane.h"

#include <units.h>

#include <algorithm>
#include <array>
#include <cstdint>

namespace perception
{
constexpr std::int32_t kMaxNumberOfObjects{100U};

enum class LabelId : std::uint8_t
{
    kPerson = 0U,
    kBicycle = 1U,
    kCar = 2U,
    kMotorcycle = 3U,
    kAirplane = 4U,
    kBus = 5U,
    kTrain = 6U,
    kTruck = 7U,
    kBoat = 8U,
    kTrafficLight = 9U,
    kStopSign = 12U,
    kBird = 15U,
    kCat = 16U,
    kDog = 17U,
    kHorse = 18U,
    kSheep = 19U,
    kCow = 20U,
    kElephant = 21U,
    kBear = 22U,
    kZebra = 23U,
    kGiraffe = 24U,
    kInvalid = 255U
};

enum class ObjectId : std::uint8_t
{
    kUnknown = 0U,
    kCar = 1U,
    kTruck = 2U,
    kMotorBike = 3U,
    kBicycle = 4U,
    kPedestrian = 5U,
    kAnimal = 6U,
    kTrafficSign_Stop = 7U,
    kTrafficLight = 8U,
    kObstacle = 9U,
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

struct ObjectListMessage
{
    std::int32_t number_of_valid_objects;
    std::array<ObjectMessage, kMaxNumberOfObjects> objects;
};

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
        case ObjectId::kAnimal:
            return "kAnimal";
        case ObjectId::kTrafficSign_Stop:
            return "kTrafficSign_Stop";
        case ObjectId::kTrafficLight:
            return "kTrafficLight";
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

inline std::ostream& operator<<(std::ostream& stream, const ObjectMessage& object)
{
    stream << "Object {Id: " << object.id << ", {x: " << object.bounding_box.x << ", y: " << object.bounding_box.y
           << ", w: " << object.bounding_box.width << ", h: " << object.bounding_box.height
           << "}, distance: " << object.distance << ", velocity: " << object.velocity << "}";
    return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const ObjectListMessage& object_list)
{
    for (auto idx = 0; idx < object_list.number_of_valid_objects; ++idx)
    {
        stream << "(+) " << object_list.objects.at(idx) << std::endl;
    }
    return stream;
}

}  // namespace perception

#endif  /// PERCEPTION_DATATYPES_OBJECT_H
