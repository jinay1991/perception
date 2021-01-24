///
/// @file
/// @copyright Copyright (c) 2021. MIT License.
///
#ifndef PERCEPTION_DRIVER_EYE_BLINK_FILTER_H
#define PERCEPTION_DRIVER_EYE_BLINK_FILTER_H

#include "perception/common/filter.h"
#include "perception/datatypes/driver.h"
#include "perception/driver/i_data_source.h"
#include "perception/driver/i_parameter_handler.h"

namespace perception
{
/// @brief Eye State Filter to remove the eye blinks and flickers
class EyeStateFilter
{
  public:
    /// @brief Default Constructor.
    ///
    /// @param parameter_handler [in] - Instance of the Parameter Handler
    /// @param data_source [in] - Instance of the Data Source
    explicit EyeStateFilter(const IParameterHandler& parameter_handler, const IDataSource& data_source);

    /// @brief Calculate Driver's Eye state based on the received inputs
    void Step();

    /// @brief Provide Filtered Eye State
    ///
    /// @return eye_state
    EyeState GetFilteredEyeState() const;

  private:
    /// @brief Update current blink duration
    void UpdateBlinkDuration();

    /// @brief Determine eye state based on the filter
    EyeState DetermineEyeState() const;

    /// @brief Provide whether Face is visible based on the driver camera information
    ///
    /// @return True if face is available, otherwise False.
    inline bool IsFaceVisible() const;

    /// @brief Check whether Eyes are visible based on the driver camera information
    ///
    /// @return True if eyes are available, otherwise False.
    inline bool IsEyeVisible() const;

    /// @brief Check whether provided eye blink rate is valid
    ///
    /// @return True if eye blink rate is valid, otherwise False.
    inline bool IsEyeBlinkRateValid() const;

    /// @brief Check whether provided eye lid opening is valid
    ///
    /// @return True if eye lid opening is valid, otherwise False.
    inline bool IsEyeLidOpeningValid() const;

    /// @brief Check whether eyes are open
    ///
    /// @return True if eyes are open, otherwise False.
    inline bool IsEyeOpen() const;

    /// @brief Instance of the Parameter handler
    const IParameterHandler& parameter_handler_;

    /// @brief Instance of Data Source
    const IDataSource& data_source_;

    /// @brief Filter to remove Eye Blinks
    Filter<EyeState> eye_blink_filter_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_EYE_BLINK_FILTER_H
