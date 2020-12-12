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
    double GetCurrentPercentage() const;

  private:
    double percentage;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_PERCLOS_H
