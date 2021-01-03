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
class EyeStateFilter
{
  public:
    explicit EyeStateFilter(const IParameterHandler& parameter_handler, const IDataSource& data_source);

    void Step();

    EyeState GetFilteredEyeState() const;

  private:
    void UpdateBlinkDuration();
    EyeState DetermineEyeState() const;

    inline bool IsFaceVisible() const;
    inline bool IsEyeVisible() const;
    inline bool IsEyeBlinkRateValid() const;
    inline bool IsEyeLidOpeningValid() const;
    inline bool IsEyeOpen() const;

    const IParameterHandler& parameter_handler_;
    const IDataSource& data_source_;

    Filter<EyeState> eye_blink_filter_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_EYE_BLINK_FILTER_H
