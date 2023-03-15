///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/object/datatype/object.h"

#include <chrono>
#include <ostream>
#include <sstream>
#include <string>

namespace perception
{
namespace object
{

inline std::string to_string(const ObjectId& id) noexcept
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

inline std::ostream& operator<<(std::ostream& out, const ObjectId& id) noexcept
{
    out << to_string(id);
    return out;
}

inline std::string to_string(const Position& position) noexcept
{
    std::stringstream ss{"Position "};
    ss << "{x: " << position.x << ", y: " << position.y << ", z: " << position.z << "}";
    return ss.str();
}

inline std::ostream& operator<<(std::ostream& out, const Position& position) noexcept
{
    out << to_string(position);
    return out;
}

inline std::string to_string(const Pose& pose) noexcept
{
    std::stringstream ss{"Pose "};
    ss << "{yaw: " << pose.yaw << ", pitch: " << pose.pitch << ", roll: " << pose.roll << "}";
    return ss.str();
}

inline std::ostream& operator<<(std::ostream& out, const Pose& pose) noexcept
{
    out << to_string(pose);
    return out;
}

inline std::string to_string(const BoundingBox& bounding_box) noexcept
{
    std::stringstream ss{"BoundingBox "};
    ss << "{x: " << bounding_box.x << ", y: " << bounding_box.y << ", w: " << bounding_box.width
       << ", h: " << bounding_box.height << "}";
    return ss.str();
}

inline std::ostream& operator<<(std::ostream& out, const BoundingBox& bounding_box) noexcept
{
    out << to_string(bounding_box);
    return out;
}

inline std::string to_string(const ObjectMessage& object_message) noexcept
{
    std::stringstream ss{"Object "};
    ss << "{Id: " << object_message.id << ", " << object_message.bounding_box
       << ", distance: " << object_message.distance
       << ", longitudinal_distance: " << object_message.longitudinal_distance
       << ", lateral_distance: " << object_message.lateral_distance << ", ttc: " << object_message.time_to_collision
       << ", lane_id: " << object_message.lane_id << ", " << object_message.position << ", " << object_message.pose
       << "}";
    return ss.str();
}

inline std::ostream& operator<<(std::ostream& out, const ObjectMessage& object_message) noexcept
{
    out << to_string(object_message);
    return out;
}

inline std::string to_string(const ObjectListMessage& object_list) noexcept
{
    std::stringstream ss{"ObjectList "};
    for (auto idx = 0; idx < object_list.number_of_valid_objects; ++idx)
    {
        ss << " (+) " << object_list.objects.at(idx) << "\n";
    }
    return ss.str();
}

inline std::ostream& operator<<(std::ostream& out, const ObjectListMessage& object_list) noexcept
{
    out << to_string(object_list);
    return out;
}
}  // namespace object
}  // namespace perception
