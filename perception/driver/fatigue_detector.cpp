///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/fatigue_detector.h"

namespace perception
{
namespace driver
{

FatigueDetector::FatigueDetector(const IFatigueParameterHandler& parameter_handler,
                                 const IFatigueDataSource& data_source)
    : eye_state_filter_{parameter_handler, data_source}, perclos_{}, state_{FatigueState::kInvalid}, confidence_{0.0}
{
}

void FatigueDetector::Step()
{
    DetermineEyeState();
    DeterminePerclos();
    DetermineFatigueState();
    DetermineFatigueConfidence();
}

FatigueState FatigueDetector::GetFatigueState() const
{
    return state_;
}

double FatigueDetector::GetFatigueConfidence() const
{
    return confidence_;
}

void FatigueDetector::DetermineEyeState()
{
    eye_state_filter_.Step();
}

void FatigueDetector::DeterminePerclos()
{
    perclos_.Calculate(eye_state_filter_.GetFilteredEyeState());
}

void FatigueDetector::DetermineFatigueState()
{
    const auto availability_percentage = perclos_.GetAvailabilityPercentage();
    const auto closure_percentage = perclos_.GetClosurePercentage();
    const auto has_observed_eyes_close = closure_percentage > 10.0;
    const auto percentage =
        (has_observed_eyes_close && (availability_percentage < 100.0)) ? availability_percentage : closure_percentage;

    static constexpr double kMaxConfidenceAwake{7.5};
    static constexpr double kMaxConfidenceQuestionable{15.0};
    static constexpr double kMaxConfidenceDrowsy{30.0};
    static constexpr double kMaxConfidenceBeginningSleep{60.0};

    if (percentage < kMaxConfidenceAwake)  // 0.0% - 7.5%
    {
        state_ = FatigueState::kAwake;
    }
    else if (percentage < kMaxConfidenceQuestionable)  // 7.5% - 15.0%
    {
        state_ = FatigueState::kQuestionable;
    }
    else if (percentage < kMaxConfidenceDrowsy)  // 15.0% - 30.0%
    {
        state_ = FatigueState::kDrowsy;
    }
    else if (percentage < kMaxConfidenceBeginningSleep)  // 30.0% - 60.0%
    {
        state_ = FatigueState::kBeginningSleep;
    }
    else  // 60.0% - 100.0%
    {
        state_ = FatigueState::kSleep;
    }
}

void FatigueDetector::DetermineFatigueConfidence()
{
    confidence_ = perclos_.GetAvailabilityPercentage() / 100.0;
}
}  // namespace driver
}  // namespace perception
