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

    builder_.WithActivityMessage(activity_->GetActivityMessage())
        .WithDistractionMessage(distraction_->GetDistractionMessage())
        .WithResponsivenessMessage(responsiveness_->GetResponsivenessMessage())
        .WithFatigueMessage(fatigue_->GetFatigueMessage())
        .WithTimePoint(data_source_.GetTimePoint());
}

void Driver::UpdateDriverCameraMessage(const DriverCameraMessage& driver_camera_message)
{
    data_source_.UpdateDriverCameraMessage(driver_camera_message);
}

const DriverMessage& Driver::GetDriverMessage() const
{
    return builder_.Build();
}

}  // namespace driver
}  // namespace perception
