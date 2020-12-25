///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_PERCLOS_H
#define PERCEPTION_DRIVER_PERCLOS_H

#include "perception/common/circular_bitset.h"
#include "perception/datatypes/driver.h"
#include "perception/common/filter.h"

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
    static constexpr std::chrono::milliseconds kAssumedCycleDuration{40ms};
    static constexpr std::int32_t kWindowSize{kMaxEyeStateObservationDuration / kAssumedCycleDuration};

    CircularBitset<kWindowSize> longterm_storage_;
    Filter<EyeState> eye_blink_filter_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_PERCLOS_H
