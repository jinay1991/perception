///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/activity.h"

#include "perception/driver/activity_detector.h"

#include <chrono>

namespace perception
{
namespace driver
{
Activity::Activity(const IActivityParameterHandler& parameter_handler, const IActivityDataSource& data_source)
    : builder_{}, detector_{std::make_unique<ActivityDetector>(parameter_handler, data_source)}
{
}

void Activity::Step()
{
    detector_->Step();

    builder_.WithTimePoint(std::chrono::system_clock::now())
        .WithState(detector_->GetActivityState())
        .WithConfidence(detector_->GetActivityConfidence());
}

const ActivityMessage& Activity::GetActivityMessage() const
{
    return builder_.Build();
}
}  // namespace driver
}  // namespace perception
