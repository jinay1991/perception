///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///

#include "perception/driver/degradation.h"

namespace perception
{

Degradation::Degradation(const IParameters& parameters,
                         const InputService& input_service,
                         OutputService& output_service)
    : parameters_{parameters}, input_service_{input_service}, output_service_{output_service}, degradation_message_{}
{
}

void Degradation::UpdateState()
{
    degradation_message_.state = DegradationState::kNormalOperation;
    output_service_.UpdateDegradation(degradation_message_);
}
}  // namespace perception
