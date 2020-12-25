///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_PERCLOS_H
#define PERCEPTION_DRIVER_PERCLOS_H

#include "perception/common/circular_bitset.h"
#include "perception/common/filter.h"
#include "perception/datatypes/driver.h"

namespace perception
{
/// @brief Assumed Cycle duration
static constexpr std::chrono::milliseconds kAssumedCycleDuration{40ms};

/// @brief Maximum allowed longterm storage size (i.e. max samples to store)
static constexpr std::int32_t kMaxLongtermStorageSize{kMaxEyeStateObservationDuration / kAssumedCycleDuration};

class Perclos
{
  public:
    Perclos();

    void Calculate(const EyeState eye_state);

    double GetClosurePercentage() const;
    double GetAvailabilityPercentage() const;

  private:
    CircularBitset<kMaxLongtermStorageSize> longterm_storage_;
    Filter<EyeState> eye_blink_filter_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_PERCLOS_H
