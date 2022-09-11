///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/perclos.h"

#include "perception/common/validity_range.h"

namespace perception
{
namespace driver
{
namespace
{
constexpr bool IsEyeStateClosed(const EyeState eye_state) noexcept
{
    return (EyeState::kEyesClosed == eye_state);
}
}  // namespace

Perclos::Perclos() : observation_{} {}

void Perclos::Calculate(const EyeState eye_state)
{
    observation_.push_back(IsEyeStateClosed(eye_state));
}

void Perclos::SetEyeStateObservationDuration(const std::chrono::milliseconds duration)
{
    static_assert(0ms != kMaxCycleDuration, "Maximum cycle duration can not be set to 0ms!");
    const auto capacity = static_cast<std::size_t>(duration / kMaxCycleDuration);
    observation_.resize(capacity);
}

std::chrono::milliseconds Perclos::GetEyeStateObservationDuration() const
{
    return (observation_.capacity() * kMaxCycleDuration);
}

double Perclos::GetClosurePercentage() const
{
    const auto observation_count = static_cast<double>(observation_.count());
    const auto observation_size = static_cast<double>(observation_.size());
    const auto closure_percentage =
        ((observation_size > std::numeric_limits<double>::epsilon()) ? ((observation_count * 100.0) / observation_size)
                                                                     : 0.0);
    return Clamp(closure_percentage, 0.0, 100.0);
}

double Perclos::GetAvailabilityPercentage() const
{
    const auto observation_size = static_cast<double>(observation_.size());
    const auto observation_capacity = static_cast<double>(observation_.capacity());
    const auto availability_percentage = ((observation_capacity > std::numeric_limits<double>::epsilon())
                                              ? ((observation_size * 100.0) / observation_capacity)
                                              : 0.0);
    return Clamp(availability_percentage, 0.0, 100.0);
}

}  // namespace driver
}  // namespace perception
