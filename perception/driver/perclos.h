///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_DRIVER_PERCLOS_H
#define PERCEPTION_DRIVER_PERCLOS_H

#include "perception/common/circular_bitset.h"
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
    inline bool IsEyesClosed(const EyeState eye_state) const;

    CircularBitset<kMaxLongtermStorageSize> longterm_storage_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_PERCLOS_H
