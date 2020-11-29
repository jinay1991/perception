///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_DRIVER_H
#define PERCEPTION_DRIVER_DRIVER_H

#include "perception/datatypes/driver.h"
#include "perception/driver/data_source.h"
#include "perception/driver/fatigue.h"
#include "perception/driver/parameter_handler.h"
#include "perception/driver/visual_attention.h"

namespace perception
{
class Driver
{
  public:
    Driver();

    void Init();
    void ExecuteStep();
    void Shutdown();

    void ProcessDriverCameraSystemMessage(const DriverCameraSystemMessage& driver_camera_system_message);

    const VisualAttentionMessage& GetVisualAttentionMessage() const;
    const FatigueMessage& GetFatigueMessage() const;

  private:
    ParameterHandler parameter_handler_;
    DataSource data_source_;
    Fatigue fatigue_;
    VisualAttention visual_attention_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_DRIVER_H
