///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/fatigue.h"

#include "perception/common/validity_range.h"

namespace perception
{

Fatigue::Fatigue(const IParameterHandler& parameter_handler, const IDataSource& data_source)
    : parameter_handler_{parameter_handler},
      data_source_{data_source},
      fatigue_builder_{},
      perclos_{},
      eye_blink_filter_{EyeState::kInvalid}
{
}

void Fatigue::Init() {}

void Fatigue::ExecuteStep()
{
    fatigue_builder_.WithTimepoint(std::chrono::system_clock::now());

    DetermineFatigue();
}

void Fatigue::Shutdown() {}

const FatigueMessage& Fatigue::GetFatigueMessage() const
{
    return fatigue_builder_.Build();
}

void Fatigue::DetermineFatigue()
{
    const auto eye_state = DetermineEyeState();

    perclos_.Calculate(eye_state);

    const auto level = DetermineFatigueLevel();
    const auto confidence = DetermineFatigueConfidence();

    fatigue_builder_.WithEyeState(eye_state).WithFatigueLevel(level).WithFatigueConfidence(confidence);
}

EyeState Fatigue::DetermineEyeState() const
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

EyeState Fatigue::ApplyEyeBlinkFilter(const EyeState& eye_state)
{
    eye_blink_filter_.SetHoldDuration(data_source_.GetEyeBlinkDuration());
    eye_blink_filter_.Update(eye_state, kAssumedCycleDuration);
    return eye_blink_filter_.GetCurrentState();
}

FatigueLevel Fatigue::DetermineFatigueLevel() const
{
    const double percentage = perclos_.GetClosurePercentage();
    FatigueLevel level{FatigueLevel::kInvalid};

    constexpr double kConfidenceAwake{7.5};
    constexpr double kConfidenceDrowsy{15.0};
    constexpr double kConfidenceBeginningSleep{30.0};
    constexpr double kConfidenceSleep{60.0};

    if (percentage < kConfidenceAwake)
    {
        level = FatigueLevel::kAwake;
    }
    else if (percentage < kConfidenceDrowsy)
    {
        level = FatigueLevel::kDrowsy;
    }
    else if (percentage < kConfidenceBeginningSleep)
    {
        level = FatigueLevel::kBeginningSleep;
    }
    else if (percentage < kConfidenceSleep)
    {
        level = FatigueLevel::kSleep;
    }
    else
    {
        level = FatigueLevel::kInvalid;
    }

    return level;
}

double Fatigue::DetermineFatigueConfidence() const
{
    return perclos_.GetAvailabilityPercentage();
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
