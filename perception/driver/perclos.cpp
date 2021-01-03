///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/driver/perclos.h"

#include "perception/common/validity_range.h"

namespace perception
{

Perclos::Perclos() : longterm_storage_{} {}

void Perclos::Calculate(const EyeState eye_state)
{
    longterm_storage_.push_back(IsEyesClosed(eye_state));
}

double Perclos::GetClosurePercentage() const
{
    const auto longterm_storage_count = static_cast<double>(longterm_storage_.count());
    const auto longterm_storage_size = static_cast<double>(longterm_storage_.size());
    const auto closure_percentage =
        ((longterm_storage_size != 0.0) ? ((longterm_storage_count * 100.0) / longterm_storage_size) : 0.0);
    return Clamp(closure_percentage, 0.0, 100.0);
}

double Perclos::GetAvailabilityPercentage() const
{
    const auto longterm_storage_size = static_cast<double>(longterm_storage_.size());
    const auto longterm_storage_capacity = static_cast<double>(longterm_storage_.capacity());
    const auto availability_percentage =
        ((longterm_storage_capacity != 0.0) ? ((longterm_storage_size * 100.0) / longterm_storage_capacity) : 0.0);
    return Clamp(availability_percentage, 0.0, 100.0);
}

constexpr bool Perclos::IsEyesClosed(const EyeState eye_state)
{
    return (EyeState::kEyesClosed == eye_state);
}

}  // namespace perception
