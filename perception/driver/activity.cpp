///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/activity.h"

namespace perception
{
namespace driver
{
Activity::Activity(const IActivityParameterHandler& /* parameter_handler */,
                   const IActivityDataSource& /* data_source */)
    : builder_{}
{
}

void Activity::Step()
{
    builder_.WithState(ActivityState::kNotAvailable);
}

const ActivityMessage& Activity::GetActivityMessage() const
{
    return builder_.Build();
}
}  // namespace driver
}  // namespace perception
