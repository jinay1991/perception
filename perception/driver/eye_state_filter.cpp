///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/eye_state_filter.h"

#include "perception/common/validity_range.h"

namespace perception
{
namespace driver
{
EyeStateFilter::EyeStateFilter(const IFatigueParameterHandler& parameter_handler, const IFatigueDataSource& data_source)
    : parameter_handler_{parameter_handler}, data_source_{data_source}, eye_blink_filter_{EyeState::kInvalid}
{
}

void EyeStateFilter::Step()
{
    UpdateBlinkDuration();

    const auto eye_state = DetermineEyeState();
    eye_blink_filter_.Update(eye_state, 40ms);
}

EyeState EyeStateFilter::GetFilteredEyeState() const
{
    return eye_blink_filter_.GetCurrentState();
}

EyeState EyeStateFilter::DetermineEyeState() const
{
    EyeState eye_state{EyeState::kInvalid};
    if (IsFaceVisible() && IsEyeVisible())
    {
        if (IsEyeOpen())
        {
            eye_state = EyeState::kEyesOpen;
        }
        else
        {
            eye_state = EyeState::kEyesClosed;
        }
    }
    else
    {
        eye_state = EyeState::kEyesUnknown;
    }

    return eye_state;
}

void EyeStateFilter::UpdateBlinkDuration()
{
    eye_blink_filter_.SetHoldDuration(data_source_.GetEyeBlinkDuration());
}

bool EyeStateFilter::IsFaceVisible() const
{
    return data_source_.IsFaceVisible();
}

bool EyeStateFilter::IsEyeVisible() const
{
    return (IsEyeBlinkRateValid() && (data_source_.IsEyeVisible()));
}

bool EyeStateFilter::IsEyeBlinkRateValid() const
{
    return InRangeInclusive(data_source_.GetEyeBlinkRate(),
                            parameter_handler_.GetMinEyeBlinkRate(),
                            parameter_handler_.GetMaxEyeBlinkRate());
}

bool EyeStateFilter::IsEyeOpen() const
{
    return (IsEyeLidOpeningValid() &&
            (data_source_.GetEyeLidOpening() > (parameter_handler_.GetMaxEyeLidOpening() / 2.0)));
}

bool EyeStateFilter::IsEyeLidOpeningValid() const
{
    return InRangeInclusive(data_source_.GetEyeLidOpening(),
                            parameter_handler_.GetMinEyeLidOpening(),
                            parameter_handler_.GetMaxEyeLidOpening());
}
}  // namespace driver
}  // namespace perception
