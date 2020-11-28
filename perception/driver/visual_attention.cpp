///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/visual_attention.h"

namespace perception
{

VisualAttention::VisualAttention(const IParameters& parameters, const IDataSource& data_source)
    : parameters_{parameters}, data_source_{data_source}, visual_attention_message_{}
{
}

void VisualAttention::Init() {}

void VisualAttention::ExecuteStep() {}

void VisualAttention::Shutdown() {}

const VisualAttentionMessage& VisualAttention::GetVisualAttentionMessage() const
{
    return visual_attention_message_;
}

}  // namespace perception
