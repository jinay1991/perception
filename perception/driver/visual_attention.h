///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_DRIVER_VISUAL_ATTENTION_H
#define PERCEPTION_DRIVER_VISUAL_ATTENTION_H

#include "perception/datatypes/driver.h"
#include "perception/driver/i_data_source.h"
#include "perception/driver/i_parameter_handler.h"

namespace perception
{
class VisualAttention final
{
  public:
    explicit VisualAttention(const IParameterHandler& parameter_handler, const IDataSource& data_source);

    void Step();

    const VisualAttentionMessage& GetVisualAttentionMessage() const;

  private:
    AttentionState GetAttentionState() const;
    bool IsHeadPoseAvailable() const;
    bool IsHeadPoseAttentive() const;

    const IParameterHandler& parameter_handler_;
    const IDataSource& data_source_;

    VisualAttentionMessage visual_attention_message_;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_VISUAL_ATTENTION_H
