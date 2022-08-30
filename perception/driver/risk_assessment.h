///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_RISK_ASSESSMENT_H
#define PERCEPTION_DRIVER_RISK_ASSESSMENT_H

#include "perception/driver/datatype/driver.h"

namespace perception
{
namespace driver
{
/// @brief Risk Assessment implementaiton to determine risk associated with the Driver's current state
class RiskAssessment
{
  public:
    /// @brief Default Constructor
    RiskAssessment();

    /// @brief Update driver's current attentiveness
    ///
    /// @param fatigue_state [in] Fatigue State
    /// @param distraction_state [in] Distraction State
    /// @param activity_state [in] Activity State
    /// @param responsiveness_state [in] Responsiveness State
    void UpdateDriverState(const FatigueState fatigue_state,
                           const DistractionState distraction_state,
                           const ActivityState activity_state,
                           const ResponsivenessState responsiveness_state);

    /// @brief Interface to obtain risk assessment state information based on driver's attentiveness
    ///
    /// @return risk_assessment
    RiskAssessmentState GetRiskAssessmentState() const;

  private:
    /// @brief Risk Assessment State
    RiskAssessmentState state_;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_RISK_ASSESSMENT_H
