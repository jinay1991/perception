///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/driver/fatigue.h"

#include "perception/common/validity_range.h"

namespace perception
{

Fatigue::Fatigue(const IParameterHandler& parameter_handler, const IDataSource& data_source)
    : fatigue_builder_{}, perclos_{}, eye_state_filter_{parameter_handler, data_source}
{
}

void Fatigue::Step()
{
    fatigue_builder_.WithTimepoint(std::chrono::system_clock::now());

    eye_state_filter_.Step();

    const auto eye_state = eye_state_filter_.GetFilteredEyeState();
    fatigue_builder_.WithEyeState(eye_state);

    perclos_.Calculate(eye_state);

    DetermineFatigue();
}

const FatigueMessage& Fatigue::GetFatigueMessage() const
{
    return fatigue_builder_.Build();
}

void Fatigue::DetermineFatigue()
{
    const auto level = DetermineFatigueLevel();
    const auto confidence = DetermineFatigueConfidence();

    fatigue_builder_.WithFatigueLevel(level).WithFatigueConfidence(confidence);
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

}  // namespace perception
