///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///

#include "perception/driver/driver.h"

namespace perception
{
Driver::Driver()
    : parameters_{}, data_source_{}, fatigue_{parameters_, data_source_}, visual_attention_{parameters_, data_source_}
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

const VisualAttentionMessage& Driver::GetVisualAttentionMessage()
{
    return visual_attention_.GetVisualAttentionMessage();
}

const FatigueMessage& Driver::GetFatigueMessage()
{
    return fatigue_.GetFatigueMessage();
}

}  // namespace perception
