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
    visual_attention_message_.head_pose = GetHeadPose();
}

void VisualAttention::Shutdown() {}

const VisualAttentionMessage& VisualAttention::GetVisualAttentionMessage() const
{
    return visual_attention_message_;
}

HeadPose VisualAttention::GetHeadPose() const
{
    HeadPose head_pose{HeadPose::kInvalid};

    if (IsHeadPoseAvailable())
    {
        if (IsHeadPoseAttentive())
        {
            head_pose = HeadPose::kAttentive;
        }
        else
        {
            head_pose = HeadPose::kNotAttentive;
        }
    }
    else
    {
        head_pose = HeadPose::kInvalid;
    }

    return head_pose;
}

bool VisualAttention::IsHeadPoseAvailable() const
{
    return true;
}

bool VisualAttention::IsHeadPoseAttentive() const
{
    return true;
}
}  // namespace perception
