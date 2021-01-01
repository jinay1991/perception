///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_TRAFFIC_SIGN_TEST_SUPPORT_OPERATORS_H
#define PERCEPTION_TRAFFIC_SIGN_TEST_SUPPORT_OPERATORS_H

#include "perception/datatypes/traffic_sign.h"

#include <ostream>
#include <string>

namespace perception
{

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

#endif  /// PERCEPTION_TRAFFIC_SIGN_TEST_SUPPORT_OPERATORS_H
