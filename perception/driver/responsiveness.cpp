///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/responsiveness.h"

#include "perception/driver/responsiveness_detector.h"

#include <chrono>

namespace perception
{
namespace driver
{
Responsiveness::Responsiveness(const IResponsivenessParameterHandler& parameter_handler,
                               const IResponsivenessDataSource& data_source)
    : builder_{}, detector_{std::make_unique<ResponsivenessDetector>(parameter_handler, data_source)}
{
}

void Responsiveness::Step()
{
    detector_->Step();

    builder_.WithTimePoint(std::chrono::system_clock::now())
        .WithState(detector_->GetResponsivenessState())
        .WithConfidence(detector_->GetResponsivenessConfidence());
}

const ResponsivenessMessage& Responsiveness::GetResponsivenessMessage() const
{
    return builder_.Build();
}

}  // namespace driver
}  // namespace perception
