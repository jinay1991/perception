///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/perclos.h"

namespace perception
{
Perclos::Perclos() : percentage{0.0} {}

void Perclos::Calculate(const EyeState /* eye_state */) {}

double Perclos::GetCurrentPercentage() const
{
    return percentage;
}

}  // namespace perception
