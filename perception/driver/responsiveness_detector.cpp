///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/responsiveness_detector.h"

#include <chrono>

namespace perception
{
namespace driver
{
ResponsivenessDetector::ResponsivenessDetector(const IResponsivenessParameterHandler& parameter_handler,
                                               const IResponsivenessDataSource& data_source)
    : parameter_handler_{parameter_handler},
      data_source_{data_source},
      state_{ResponsivenessState::kInvalid},
      confidence_{0.0}
{
}

void ResponsivenessDetector::Step()
{
    DetermineResponsivenessState();
    DetermineResponsivenessConfidence();
}

ResponsivenessState ResponsivenessDetector::GetResponsivenessState() const
{
    return state_;
}

double ResponsivenessDetector::GetResponsivenessConfidence() const
{
    return confidence_;
}

void ResponsivenessDetector::DetermineResponsivenessState()
{
    state_ = ResponsivenessState::kResponsive;
}

void ResponsivenessDetector::DetermineResponsivenessConfidence()
{
    confidence_ = 0.0;
}

}  // namespace driver
}  // namespace perception
