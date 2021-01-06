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
    const auto availability_percentage = perclos_.GetAvailabilityPercentage();
    const auto closure_percentage = perclos_.GetClosurePercentage();
    const auto has_observed_eyes_close = closure_percentage > 10.0;
    const auto percentage =
        (has_observed_eyes_close && (availability_percentage < 100.0)) ? availability_percentage : closure_percentage;
    FatigueLevel level{FatigueLevel::kInvalid};

    constexpr double kMaxConfidenceAwake{7.5};
    constexpr double kMaxConfidenceQuestionable{15.0};
    constexpr double kMaxConfidenceDrowsy{30.0};
    constexpr double kMaxConfidenceBeginningSleep{60.0};
    constexpr double kMaxConfidenceSleep{100.0};

    if (percentage < kMaxConfidenceAwake)  // 0.0% - 7.5%
    {
        level = FatigueLevel::kAwake;
    }
    else if (percentage < kMaxConfidenceQuestionable)  // 7.5% - 15.0%
    {
        level = FatigueLevel::kQuestionable;
    }
    else if (percentage < kMaxConfidenceDrowsy)  // 15.0% - 30.0%
    {
        level = FatigueLevel::kDrowsy;
    }
    else if (percentage < kMaxConfidenceBeginningSleep)  // 30.0% - 60.0%
    {
        level = FatigueLevel::kBeginningSleep;
    }
    else if (percentage <= kMaxConfidenceSleep)  // 60.0% - 100.0%
    {
        level = FatigueLevel::kSleep;
    }

    return level;
}

double Fatigue::DetermineFatigueConfidence() const
{
    return perclos_.GetAvailabilityPercentage();
}

}  // namespace perception
