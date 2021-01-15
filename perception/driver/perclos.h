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

    /// @brief Set/Adjust Longterm Storage Window size based on the provided duration
    /// @note This will resize the longterm storage (w/o re-allocation) hence duration must be less than
    /// kMaxEyeStateObservationDuration. If provided more than that, resize will not be performed and return without any
    /// change.
    ///
    /// @param duration [in] - observation window duration to be updated to.
    void SetEyeStateObservationDuration(const std::chrono::milliseconds duration);

    /// @brief Provide current observation window duration (must not be more than kMaxEyeStateObservationDuration)
    ///
    /// @return duration (Range: 0ms - kMaxEyeStateObservationDuration)
    std::chrono::milliseconds GetEyeStateObservationDuration() const;

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
