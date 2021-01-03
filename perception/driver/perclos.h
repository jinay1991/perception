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

/// @brief Perclos Algorithm (Percentage of Eye Closure)
class Perclos final
{
  public:
    /// @brief Default Constructor.
    Perclos();

    /// @brief Calculate Percentage closure
    ///
    /// @param eye_state [in] - Eye State (filtered)
    void Calculate(const EyeState eye_state);

    /// @brief Provide calculated closure percentage
    ///
    /// @return closure_percentage (Range: 0-100%)
    double GetClosurePercentage() const;

    /// @brief Provide current availability of the eye state based on the set eye state so far in 5min window
    ///
    /// @return availability_percentage (Range: 0-100%)
    double GetAvailabilityPercentage() const;

  private:
    /// @brief Check if provided eye state is Closed
    ///
    /// @return True if provided eye state is closed, otherwise False
    static inline constexpr bool IsEyesClosed(const EyeState eye_state);

    /// @brief Circular buffer for storing eye state for 5min. Used to calculate eye closure percentage
    CircularBitset<kMaxLongtermStorageSize> longterm_storage_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_PERCLOS_H
