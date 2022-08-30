///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/risk_assessment.h"

namespace perception
{
namespace driver
{
namespace
{
constexpr bool IsAwake(const FatigueState fatigue_state) noexcept
{
    return (FatigueState::kAwake == fatigue_state);
}
constexpr bool IsAttentive(const DistractionState distraction_state) noexcept
{
    return (DistractionState::kNotDistracted == distraction_state);
}
constexpr bool IsActive(const ActivityState activity_state) noexcept
{
    return (ActivityState::kHandsOnWheel == activity_state);
}
constexpr bool IsResponsive(const ResponsivenessState responsiveness_state) noexcept
{
    return (ResponsivenessState::kResponsive == responsiveness_state);
}
}  // namespace
RiskAssessment::RiskAssessment() : state_{RiskAssessmentState::kNone} {}

void RiskAssessment::UpdateDriverState(const FatigueState fatigue_state,
                                       const DistractionState distraction_state,
                                       const ActivityState activity_state,
                                       const ResponsivenessState responsiveness_state)
{
    if ((!IsAwake(fatigue_state)) && (!IsResponsive(responsiveness_state)) && (!IsAttentive(distraction_state)) &&
        (!IsActive(activity_state)))
    {
        state_ = RiskAssessmentState::kHigh;
    }
    else if ((!IsAwake(fatigue_state)) || (!IsAttentive(distraction_state)))
    {
        state_ = RiskAssessmentState::kModerate;
    }
    else
    {
        state_ = RiskAssessmentState::kNone;
    }
}

RiskAssessmentState RiskAssessment::GetRiskAssessmentState() const
{
    return state_;
}

}  // namespace driver
}  // namespace perception
