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

Perclos::Perclos() : longterm_storage_{} {}

void Perclos::Calculate(const EyeState eye_state)
{
    longterm_storage_.push_back(IsEyeStateClosed(eye_state));
}

void Perclos::SetEyeStateObservationDuration(const std::chrono::milliseconds duration)
{
    static_assert(0ms != kMaxCycleDuration, "Maximum cycle duration can not be set to 0ms!");
    const auto capacity = static_cast<std::size_t>(duration / kMaxCycleDuration);
    longterm_storage_.resize(capacity);
}

std::chrono::milliseconds Perclos::GetEyeStateObservationDuration() const
{
    return (longterm_storage_.capacity() * kMaxCycleDuration);
}

double Perclos::GetClosurePercentage() const
{
    const auto longterm_storage_count = static_cast<double>(longterm_storage_.count());
    const auto longterm_storage_size = static_cast<double>(longterm_storage_.size());
    const auto closure_percentage = ((longterm_storage_size > std::numeric_limits<double>::epsilon())
                                         ? ((longterm_storage_count * 100.0) / longterm_storage_size)
                                         : 0.0);
    return Clamp(closure_percentage, 0.0, 100.0);
}

double Perclos::GetAvailabilityPercentage() const
{
    const auto longterm_storage_size = static_cast<double>(longterm_storage_.size());
    const auto longterm_storage_capacity = static_cast<double>(longterm_storage_.capacity());
    const auto availability_percentage = ((longterm_storage_capacity > std::numeric_limits<double>::epsilon())
                                              ? ((longterm_storage_size * 100.0) / longterm_storage_capacity)
                                              : 0.0);
    return Clamp(availability_percentage, 0.0, 100.0);
}

}  // namespace driver
}  // namespace perception
