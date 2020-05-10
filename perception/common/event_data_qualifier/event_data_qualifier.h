///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_COMMON_EVENT_DATA_QUALIFIER_EVENT_DATA_QUALIFIER_H_
#define PERCEPTION_COMMON_EVENT_DATA_QUALIFIER_EVENT_DATA_QUALIFIER_H_

#include <cstdint>
#include <ostream>

namespace perception
{
enum class EventDataQualifier : std::uint8_t
{
    kEventDataNotAvailable = 0U,
    kEventDataAvailable = 1U,
    kEventDataInvalid = 255U,
};

inline const char* to_string(const EventDataQualifier& event_data_qualifier)
{
    switch (event_data_qualifier)
    {
        case EventDataQualifier::kEventDataNotAvailable:
            return "kEventDataNotAvailable";
        case EventDataQualifier::kEventDataAvailable:
            return "kEventDataAvailable";
        case EventDataQualifier::kEventDataInvalid:
            return "kEventDataInvalid";
        default:
            return "ERROR: Unknown event_data_qualifier is received.";
    }
    return "ERROR: Unknown event_data_qualifier is received.";
}

inline std::ostream& operator<<(std::ostream& stream, const EventDataQualifier& event_data_qualifier)
{
    const char* name = to_string(event_data_qualifier);
    stream << name;
    return stream;
}

}  // namespace perception

#endif  /// PERCEPTION_COMMON_EVENT_DATA_QUALIFIER_EVENT_DATA_QUALIFIER_H_