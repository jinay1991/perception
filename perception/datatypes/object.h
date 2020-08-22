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
/// @brief Maximum number of Objects to save
constexpr std::int32_t kMaxNumberOfObjects{100U};

/// @brief Label Id (direct mapping for important classes of COCO)
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

/// @brief Object Id (classification label)
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

/// @brief Object Detection Bounding Box - Image (2D) space
struct BoundingBox
{
    /// @brief Top Left point x-coordinate
    double x;

    /// @brief Top Left point y-coordinate
    double y;

    /// @brief Bounding Box width
    double width;

    /// @brief Bounding Box height
    double height;
};

/// @brief Position - XYZ (3D space)
/// @note For 3D Point, x axis pointing in the right side from the camera, y axis pointing down, and z axis pointing in
/// the direction camera is faced.
struct Position
{
    /// @brief distance in X axis
    units::length::meter_t x;

    /// @brief distance in Y axis
    units::length::meter_t y;

    /// @brief distance in Z axis
    units::length::meter_t z;
};

/// @brief Pose - Euler Angles
struct Pose
{
    /// @brief Yaw Angle (radian)
    units::angle::radian_t yaw;

    /// @brief Pitch Angle (radian)
    units::angle::radian_t pitch;

    /// @brief Roll Angle (radian)
    units::angle::radian_t roll;
};

/// @brief Object Properties
struct ObjectMessage
{
    /// @brief Distance from Camera (3D space)
    units::length::meter_t distance;

    /// @brief Longitudinal distance (3D space)
    units::length::meter_t longitudinal_distance;

    /// @brief Lateral distance (3D space)
    units::length::meter_t lateral_distance;

    /// @brief Object (relative) velocity
    units::velocity::meters_per_second_t relative_velocity;

    /// @brief Object (absolute) velocity
    units::velocity::meters_per_second_t velocity;

    /// @brief Time to collision to the Object
    units::time::microsecond_t time_to_collision;

    /// @brief Object Position (3D)
    Position position;

    /// @brief Object Pose
    Pose pose;

    /// @brief Object detection bounding box (2D space)
    BoundingBox bounding_box;

    /// @brief Object Id (classification label)
    ObjectId id;

    /// @brief Object's associated LaneId
    LaneId lane_id;
};

/// @brief Object List Message (list of objects)
struct ObjectListMessage
{
    /// @brief Number of valid Objects detected
    /// @note Here, valid is considered based on the detection confidence (threshold is default to 50%)
    std::int32_t number_of_valid_objects;

    /// @brief List of Valid Objects
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

inline bool operator==(const Position& lhs, const Position& rhs) noexcept
{
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z));
}

inline bool operator!=(const Position& lhs, const Position& rhs) noexcept
{
    return (!(lhs == rhs));
}

inline bool operator==(const Pose& lhs, const Pose& rhs) noexcept
{
    return ((lhs.yaw == rhs.yaw) && (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll));
}

inline bool operator!=(const Pose& lhs, const Pose& rhs) noexcept
{
    return (!(lhs == rhs));
}

inline bool operator==(const ObjectMessage& lhs, const ObjectMessage& rhs) noexcept
{
    return ((lhs.distance == rhs.distance) && (lhs.longitudinal_distance == rhs.longitudinal_distance) &&
            (lhs.lateral_distance == rhs.lateral_distance) && (lhs.relative_velocity == rhs.relative_velocity) &&
            (lhs.velocity == rhs.velocity) && (lhs.time_to_collision == rhs.time_to_collision) &&
            (lhs.position == rhs.position) && (lhs.pose == rhs.pose) && (lhs.bounding_box == rhs.bounding_box) &&
            (lhs.id == rhs.id) && (lhs.lane_id == rhs.lane_id));
}

inline bool operator!=(const ObjectMessage& lhs, const ObjectMessage& rhs) noexcept
{
    return (!(lhs == rhs));
}

inline bool operator==(const ObjectListMessage& lhs, const ObjectListMessage& rhs) noexcept
{
    return ((lhs.number_of_valid_objects == rhs.number_of_valid_objects) && (lhs.objects == rhs.objects));
}

inline bool operator!=(const ObjectListMessage& lhs, const ObjectListMessage& rhs) noexcept
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

inline std::ostream& operator<<(std::ostream& stream, const Position& position)
{
    stream << "Position {x: " << position.x << ", y: " << position.y << ", z: " << position.z << "}";
    return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const Pose& pose)
{
    stream << "Pose {yaw: " << pose.yaw << ", pitch: " << pose.pitch << ", roll: " << pose.roll << "}";
    return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const BoundingBox& bounding_box)
{
    stream << "BoundingBox {x: " << bounding_box.x << ", y: " << bounding_box.y << ", w: " << bounding_box.width
           << ", h: " << bounding_box.height << "}";
    return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const ObjectMessage& object)
{
    stream << "Object {Id: " << object.id << ", " << object.bounding_box << ", distance: " << object.distance
           << ", longitudinal_distance: " << object.longitudinal_distance
           << ", lateral_distance: " << object.lateral_distance << ", velocity: " << object.velocity
           << ", relative_velocity: " << object.relative_velocity << ", ttc: " << object.time_to_collision
           << ", lane_id: " << object.lane_id << ", " << object.position << ", " << object.pose << "}";
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
