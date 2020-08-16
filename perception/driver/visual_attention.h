///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_VISUAL_ATTENTION_H
#define PERCEPTION_DRIVER_VISUAL_ATTENTION_H

#include "perception/driver/i_parameters.h"
#include "perception/driver/input_service.h"
#include "perception/driver/output_service.h"

namespace perception
{
class VisualAttention
{
  public:
    explicit VisualAttention(const IParameters& parameters,
                             const InputService& input_service,
                             OutputService& output_service)
        : parameters_{parameters},
          input_service_{input_service},
          output_service_{output_service},
          visual_attention_message_{}
    {
    }

    void Init() {}

    void ExecuteStep()
    {
        visual_attention_message_.gaze_pose = input_service_.GetGazePose();
        visual_attention_message_.head_pose = input_service_.GetHeadPose();

        output_service_.UpdateVisualAttention(visual_attention_message_);
    }

    void Shutdown() {}

  private:
    const IParameters& parameters_;
    const InputService& input_service_;
    OutputService& output_service_;

    VisualAttentionMessage visual_attention_message_;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_VISUAL_ATTENTION_H
