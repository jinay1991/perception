///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///

#include "perception/driver/driver.h"

namespace perception
{
Driver::Driver()
    : parameters_{},
      input_service_{parameters_},
      output_service_{parameters_},
      degradation_{parameters_, input_service_, output_service_},
      fatigue_{parameters_, input_service_, output_service_},
      visual_attention_{parameters_, input_service_, output_service_}
{
}

void Driver::Init()
{
    fatigue_.Init();
    visual_attention_.Init();
}

void Driver::ExecuteStep()
{
    /// Collective update inputs & degradation
    input_service_.UpdateInputs();
    degradation_.UpdateState();

    /// Run algorithms
    fatigue_.ExecuteStep();
    visual_attention_.ExecuteStep();

    /// Collective update outputs
    output_service_.UpdateOutputs();
}

void Driver::Shutdown()
{
    fatigue_.Shutdown();
    visual_attention_.Shutdown();
}

void Driver::ProcessDriverCameraSystem(const DriverCameraSystem& dcs_data)
{
    input_service_.SetDriverCameraSystemData(dcs_data);
}

VisualAttentionMessage Driver::GetVisualAttentionMessage() const
{
    return output_service_.GetVisualAttentionMessage();
}

FatigueMessage Driver::GetFatigueMessage() const
{
    return output_service_.GetFatigueMessage();
}

DegradationMessage Driver::GetDegradationMessage() const
{
    return output_service_.GetDegradationMessage();
}
}  // namespace perception
