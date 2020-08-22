///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_DATATYPES_LANE_H
#define PERCEPTION_DATATYPES_LANE_H

#include <units.h>

#include <array>
#include <cstdint>
#include <ostream>
#include <string>

namespace perception
{

constexpr units::length::meter_t kMaxLaneWidth{3.75};

enum class LaneId : std::int32_t
{
    kNextToLeft = -2,
    kLeft = -1,
    kEgo = 0,
    kRight = 1,
    kNextToRight = 2
};

enum class LaneType : std::uint8_t
{
    kDashed = 0U,
    kSolid = 1U,
    kSolidDashed = 2U,
    kInvalid = 255U
};

struct LanePoint
{
    double x;
    double y;
};

struct LaneLine
{
    std::array<LanePoint, 5U> left;
    std::array<LanePoint, 5U> right;
};

struct LaneMessage
{
    LaneId id;
    LaneType type;
    LaneLine line;
};

inline const char* to_string(const LaneId& id)
{
    switch (id)
    {
        case LaneId::kNextToLeft:
            return "kNextToLeft";
        case LaneId::kLeft:
            return "kLeft";
        case LaneId::kEgo:
            return "kEgo";
        case LaneId::kRight:
            return "kRight";
        case LaneId::kNextToRight:
            return "kNextToRight";
        default:
            return "ERROR: Unknown LaneId";
    }
    return "ERROR: Unknown LaneId";
}

inline std::ostream& operator<<(std::ostream& stream, const LaneId& id)
{
    const char* name = to_string(id);
    stream << name;
    return stream;
}

inline const char* to_string(const LaneType& type)
{
    switch (type)
    {
        case LaneType::kDashed:
            return "kDashed";
        case LaneType::kSolid:
            return "kSolid";
        case LaneType::kSolidDashed:
            return "kSolidDashed";
        case LaneType::kInvalid:
            return "kInvalid";
        default:
            return "ERROR: Unknown LaneType";
    }
    return "ERROR: Unknown LaneType";
}

inline std::ostream& operator<<(std::ostream& stream, const LaneType& type)
{
    const char* name = to_string(type);
    stream << name;
    return stream;
}
}  // namespace perception

#endif  // PERCEPTION_DATATYPES_LANE_H
