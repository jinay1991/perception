///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/fatigue.h"

#include "perception/common/validity_range.h"

namespace perception
{

Fatigue::Fatigue(const IParameterHandler& parameter_handler, const IDataSource& data_source)
    : parameter_handler_{parameter_handler}, data_source_{data_source}, fatigue_builder_{}
{
}

void Fatigue::Init() {}

void Fatigue::ExecuteStep()
{
    fatigue_builder_.WithTimepoint(std::chrono::system_clock::now())
        .WithEyeState(GetEyeState())
        .WithFatigueLevel(FatigueLevel::kInvalid)
        .WithFatigueConfidence(0.0);
}

void Fatigue::Shutdown() {}

const FatigueMessage& Fatigue::GetFatigueMessage() const
{
    return fatigue_builder_.Build();
}

EyeState Fatigue::GetEyeState() const
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

bool Fatigue::IsFaceVisible() const
{
    return data_source_.IsFaceVisible();
}

bool Fatigue::IsEyeVisible() const
{
    return ((data_source_.IsEyeVisible()) && (data_source_.GetEyeBlinkRate() <= parameter_handler_.GetEyeBlinkRate()));
}

bool Fatigue::IsEyeOpen() const
{
    return InRange(data_source_.GetEyeLidOpening(),
                   parameter_handler_.GetMinEyeLidOpening(),
                   parameter_handler_.GetMaxEyeLidOpening());
}
}  // namespace perception
