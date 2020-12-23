///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_PERCLOS_H
#define PERCEPTION_DRIVER_PERCLOS_H

#include "perception/datatypes/driver.h"

namespace perception
{
class Perclos
{
  public:
    Perclos();

    void Calculate(const EyeState eye_state);

    double GetClosurePercentage() const;
    double GetAvailabilityPercentage() const;

  private:
    double closure_percentage_;
    double availability_percentage_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_PERCLOS_H
