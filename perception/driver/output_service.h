///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_DRIVER_OUTPUT_SERVICE_H
#define PERCEPTION_DRIVER_OUTPUT_SERVICE_H

#include "perception/datatypes/driver.h"
#include "perception/driver/i_parameters.h"

namespace perception
{
class OutputService
{
  public:
    explicit OutputService(const IParameters& parameters)
        : parameters_{parameters}, visual_attention_message_{}, fatigue_message_{}, degradation_message_{}
    {
    }
    ~OutputService() = default;

    VisualAttentionMessage GetVisualAttentionMessage() const { return visual_attention_message_; }
    FatigueMessage GetFatigueMessage() const { return fatigue_message_; }
    DegradationMessage GetDegradationMessage() const { return degradation_message_; }

    void UpdateOutputs() {}

    void UpdateVisualAttention(const VisualAttentionMessage& visual_attention_message)
    {
        visual_attention_message_ = visual_attention_message;
    }

    void UpdateFatigue(const FatigueMessage& fatigue_message) { fatigue_message_ = fatigue_message; }

    void UpdateDegradation(const DegradationMessage& degradation_message)
    {
        degradation_message_ = degradation_message;
    }

  private:
    const IParameters& parameters_;

    VisualAttentionMessage visual_attention_message_;
    FatigueMessage fatigue_message_;
    DegradationMessage degradation_message_;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_OUTPUT_SERVICE_H