///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/responsiveness.h"

namespace perception
{
namespace driver
{
Responsiveness::Responsiveness(const IResponsivenessParameterHandler& /* parameter_handler */,
                               const IResponsivenessDataSource& /* data_source */)
    : builder_{}
{
}

void Responsiveness::Step()
{
    builder_.WithState(ResponsivenessState::kResponsive).WithConfidence(0.0);
}

const ResponsivenessMessage& Responsiveness::GetResponsivenessMessage() const
{
    return builder_.Build();
}

}  // namespace driver
}  // namespace perception
