///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/driver.h"

#include "perception/driver/activity.h"
#include "perception/driver/data_source.h"
#include "perception/driver/distraction.h"
#include "perception/driver/fatigue.h"
#include "perception/driver/parameter_handler.h"
#include "perception/driver/responsiveness.h"

namespace perception
{
namespace driver
{
Driver::Driver()
    : parameter_handler_{},
      data_source_{},
      fatigue_{std::make_unique<Fatigue>(parameter_handler_, data_source_)},
      distraction_{std::make_unique<Distraction>(parameter_handler_, data_source_)},
      activity_{std::make_unique<Activity>(parameter_handler_, data_source_)},
      responsiveness_{std::make_unique<Responsiveness>(parameter_handler_, data_source_)},
      risk_assessment_{},
      builder_{}
{
}

void Driver::Step()
{
    /// @TODO: Can these be run on Parallel Threads? Identify Synchronisation technique.
    fatigue_->Step();
    distraction_->Step();
    activity_->Step();
    responsiveness_->Step();

    risk_assessment_.UpdateDriverState(GetFatigueMessage().state,
                                       GetDistractionMessage().state,
                                       GetActivityMessage().state,
                                       GetResponsivenessMessage().state);

    builder_.WithActivityMessage(GetActivityMessage())
        .WithDistractionMessage(GetDistractionMessage())
        .WithResponsivenessMessage(GetResponsivenessMessage())
        .WithFatigueMessage(GetFatigueMessage())
        .WithTimePoint(data_source_.GetTimePoint());
}

void Driver::UpdateDriverCameraMessage(const DriverCameraMessage& driver_camera_message)
{
    data_source_.UpdateDriverCameraMessage(driver_camera_message);
}

const FatigueMessage& Driver::GetFatigueMessage() const
{
    return fatigue_->GetFatigueMessage();
}

const DistractionMessage& Driver::GetDistractionMessage() const
{
    return distraction_->GetDistractionMessage();
}

const ActivityMessage& Driver::GetActivityMessage() const
{
    return activity_->GetActivityMessage();
}

const ResponsivenessMessage& Driver::GetResponsivenessMessage() const
{
    return responsiveness_->GetResponsivenessMessage();
}

RiskAssessmentState Driver::GetRiskAssessmentState() const
{
    return risk_assessment_.GetRiskAssessmentState();
}

const DriverMessage& Driver::GetDriverMessage() const
{
    return builder_.Build();
}

}  // namespace driver
}  // namespace perception
