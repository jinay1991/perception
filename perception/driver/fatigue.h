///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_FATIGUE_H
#define PERCEPTION_DRIVER_FATIGUE_H

#include "perception/driver/i_parameters.h"
#include "perception/driver/input_service.h"
#include "perception/driver/output_service.h"

namespace perception
{
class Fatigue
{
  public:
    explicit Fatigue(const IParameters& parameters, const InputService& input_service, OutputService& output_service)
        : parameters_{parameters}, input_service_{input_service}, output_service_{output_service}, fatigue_message_{}
    {
    }

    void Init() {}
    void ExecuteStep()
    {
        fatigue_message_.eye_state = input_service_.GetEyeState();
        output_service_.UpdateFatigue(fatigue_message_);
    }
    void Shutdown() {}

  private:
    const IParameters& parameters_;
    const InputService& input_service_;
    OutputService& output_service_;

    FatigueMessage fatigue_message_;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_FATIGUE_H
