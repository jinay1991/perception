///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/risk_assessment.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace driver
{
namespace
{
using ::testing::AllOf;
using ::testing::Field;

class RiskAssessmentFixture : public ::testing::Test
{
  public:
    RiskAssessmentFixture() : unit_{} {}

  protected:
    void UpdateDriverState(const FatigueState fatigue_state,
                           const DistractionState distraction_state,
                           const ActivityState activity_state,
                           const ResponsivenessState responsiveness_state)
    {
        unit_.UpdateDriverState(fatigue_state, distraction_state, activity_state, responsiveness_state);
    }

    RiskAssessmentState GetRiskAssessmentState() const { return unit_.GetRiskAssessmentState(); }

  private:
    RiskAssessment unit_;
};

template <typename T>
class RiskAssessmentFixtureT : public RiskAssessmentFixture, public ::testing::WithParamInterface<T>
{
};

struct TestDriverStateParam
{
    // Given
    FatigueState fatigue_state;
    DistractionState distraction_state;
    ActivityState activity_state;
    ResponsivenessState responsiveness_state;

    // Then
    RiskAssessmentState result;
};

using RiskAssessmentFixture_WithDriverState = RiskAssessmentFixtureT<TestDriverStateParam>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
      RiskAssessment,
      RiskAssessmentFixture_WithDriverState,
      ::testing::Values(
            ///                      fatigue_state    ,      distraction_state          ,  activity_state              ,             responsiveness_state   ,       (expected) result
            TestDriverStateParam{FatigueState::kAwake , DistractionState::kNotDistracted, ActivityState::kHandsOnWheel , ResponsivenessState::kResponsive   , RiskAssessmentState::kNone    }, // (0)
            TestDriverStateParam{FatigueState::kDrowsy, DistractionState::kNotDistracted, ActivityState::kHandsOnWheel , ResponsivenessState::kResponsive   , RiskAssessmentState::kModerate}, // (1)
            TestDriverStateParam{FatigueState::kAwake , DistractionState::kDistracted   , ActivityState::kHandsOnWheel , ResponsivenessState::kResponsive   , RiskAssessmentState::kModerate}, // (2)
            TestDriverStateParam{FatigueState::kAwake , DistractionState::kNotDistracted, ActivityState::kHandsOffWheel, ResponsivenessState::kResponsive   , RiskAssessmentState::kNone    }, // (3)
            TestDriverStateParam{FatigueState::kAwake , DistractionState::kNotDistracted, ActivityState::kHandsOnWheel , ResponsivenessState::kNonResponsive, RiskAssessmentState::kNone    }, // (4)
            TestDriverStateParam{FatigueState::kDrowsy, DistractionState::kDistracted   , ActivityState::kHandsOffWheel, ResponsivenessState::kNonResponsive, RiskAssessmentState::kHigh    }  // (5)
));
// clang-format on

TEST_P(RiskAssessmentFixture_WithDriverState, UpdateDriverState_GivenTypicalDriverState_ExpectRiskAssessmentState)
{
    // Given
    const auto param = GetParam();

    // When
    UpdateDriverState(param.fatigue_state, param.distraction_state, param.activity_state, param.responsiveness_state);

    // Then
    const auto result = GetRiskAssessmentState();
    EXPECT_EQ(result, param.result);
}
}  // namespace
}  // namespace driver
}  // namespace perception
