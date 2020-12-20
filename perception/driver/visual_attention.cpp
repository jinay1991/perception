///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/visual_attention.h"

namespace perception
{

VisualAttention::VisualAttention(const IParameterHandler& parameter_handler, const IDataSource& data_source)
    : parameter_handler_{parameter_handler}, data_source_{data_source}, visual_attention_message_{}
{
}

void VisualAttention::Init() {}

void VisualAttention::ExecuteStep()
{
    visual_attention_message_.attention_state = GetAttentionState();
}

void VisualAttention::Shutdown() {}

const VisualAttentionMessage& VisualAttention::GetVisualAttentionMessage() const
{
    return visual_attention_message_;
}

AttentionState VisualAttention::GetAttentionState() const
{
    AttentionState attention_state{AttentionState::kInvalid};

    if (IsHeadPoseAvailable())
    {
        if (IsHeadPoseAttentive())
        {
            attention_state = AttentionState::kAttentive;
        }
        else
        {
            attention_state = AttentionState::kNotAttentive;
        }
    }
    else
    {
        attention_state = AttentionState::kInvalid;
    }

    return attention_state;
}

bool VisualAttention::IsHeadPoseAvailable() const
{
    return (data_source_.GetHeadTracking().yaw == 0.0_rad);
}

bool VisualAttention::IsHeadPoseAttentive() const
{
    return (data_source_.GetHeadTracking().yaw == 0.0_rad);
}
}  // namespace perception
