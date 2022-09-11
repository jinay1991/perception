///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/activity_detector.h"

namespace perception
{
namespace driver
{
ActivityDetector::ActivityDetector(const IActivityParameterHandler& parameter_handler,
                                   const IActivityDataSource& data_source)
    : parameter_handler_{parameter_handler},
      data_source_{data_source},
      state_{ActivityState::kInvalid},
      confidence_{0.0}
{
}

void ActivityDetector::Step()
{
    DetermineActivityState();
    DetermineActivityConfidence();
}

ActivityState ActivityDetector::GetActivityState() const
{
    return state_;
}

double ActivityDetector::GetActivityConfidence() const
{
    return confidence_;
}

void ActivityDetector::DetermineActivityState()
{
    /// @todo: Implement algorithm to determine Driver's Activity
    state_ = ActivityState::kHandsOnWheel;
}

void ActivityDetector::DetermineActivityConfidence()
{
    confidence_ = 0.0;
}

}  // namespace driver
}  // namespace perception
