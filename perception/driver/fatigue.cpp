///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/fatigue.h"

#include "perception/common/validity_range.h"

namespace perception
{
namespace driver
{

Fatigue::Fatigue(const IFatigueParameterHandler& parameter_handler, const IFatigueDataSource& data_source)
    : builder_{}, detector_{parameter_handler, data_source}
{
}

void Fatigue::Step()
{
    detector_.Step();

    builder_.WithTimePoint(std::chrono::system_clock::now())
        .WithState(detector_.GetFatigueState())
        .WithConfidence(detector_.GetFatigueConfidence());
}

const FatigueMessage& Fatigue::GetFatigueMessage() const
{
    return builder_.Build();
}

}  // namespace driver
}  // namespace perception
