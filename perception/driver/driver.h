///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_DRIVER_H
#define PERCEPTION_DRIVER_DRIVER_H

#include "perception/datatypes/driver.h"
#include "perception/driver/degradation.h"
#include "perception/driver/fatigue.h"
#include "perception/driver/parameters.h"
#include "perception/driver/visual_attention.h"

namespace perception
{
class Driver
{
  public:
    Driver();
    ~Driver() = default;

    void Init();
    void ExecuteStep();
    void Shutdown();

    void ProcessDriverCameraSystem(const DriverCameraSystem& dcs_data);

    VisualAttentionMessage GetVisualAttentionMessage() const;
    FatigueMessage GetFatigueMessage() const;
    DegradationMessage GetDegradationMessage() const;

  private:
    Parameters parameters_;

    InputService input_service_;
    OutputService output_service_;

    Degradation degradation_;
    Fatigue fatigue_;
    VisualAttention visual_attention_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_DRIVER_H
