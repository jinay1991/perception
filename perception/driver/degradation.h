///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_DEGRADATION_H
#define PERCEPTION_DRIVER_DEGRADATION_H

#include "perception/driver/i_parameters.h"
#include "perception/driver/input_service.h"
#include "perception/driver/output_service.h"

namespace perception
{
class Degradation
{
  public:
    explicit Degradation(const IParameters& parameters,
                         const InputService& input_service,
                         OutputService& output_service)
        : parameters_{parameters},
          input_service_{input_service},
          output_service_{output_service},
          degradation_message_{}
    {
    }

    void UpdateState()
    {
        degradation_message_.state = DegradationState::kNormalOperation;
        output_service_.UpdateDegradation(degradation_message_);
    }

  private:
    const IParameters& parameters_;
    const InputService& input_service_;
    OutputService& output_service_;

    DegradationMessage degradation_message_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_DEGRADATION_H
