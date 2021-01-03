///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/driver/driver.h"

namespace perception
{
Driver::Driver()
    : parameter_handler_{},
      data_source_{},
      fatigue_{parameter_handler_, data_source_},
      visual_attention_{parameter_handler_, data_source_}
{
}

void Driver::Step()
{
    fatigue_.Step();
    visual_attention_.Step();
}

void Driver::ProcessDriverCameraMessage(const DriverCameraMessage& driver_camera_message)
{
    data_source_.UpdateDriverCameraMessage(driver_camera_message);
}

const VisualAttentionMessage& Driver::GetVisualAttentionMessage() const
{
    return visual_attention_.GetVisualAttentionMessage();
}

const FatigueMessage& Driver::GetFatigueMessage() const
{
    return fatigue_.GetFatigueMessage();
}

}  // namespace perception
