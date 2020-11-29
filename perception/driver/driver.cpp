///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
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

void Driver::Init()
{
    fatigue_.Init();
    visual_attention_.Init();
}

void Driver::ExecuteStep()
{
    fatigue_.ExecuteStep();
    visual_attention_.ExecuteStep();
}

void Driver::Shutdown()
{
    fatigue_.Shutdown();
    visual_attention_.Shutdown();
}

void Driver::ProcessDriverCameraSystemMessage(const DriverCameraSystemMessage& driver_camera_system_message)
{
    data_source_.UpdateDriverCameraSystemMessage(driver_camera_system_message);
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
