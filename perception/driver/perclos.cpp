///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/perclos.h"

namespace perception
{
Perclos::Perclos() : closure_percentage_{0.0}, availability_percentage_{0.0} {}

void Perclos::Calculate(const EyeState /* eye_state */)
{
    availability_percentage_ = 100.0;
}

double Perclos::GetClosurePercentage() const
{
    return closure_percentage_;
}

double Perclos::GetAvailabilityPercentage() const
{
    return availability_percentage_;
}

}  // namespace perception
