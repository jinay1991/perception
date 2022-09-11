///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/distraction.h"

#include "perception/driver/distraction_detector.h"

#include <chrono>

namespace perception
{
namespace driver
{
Distraction::Distraction(const IDistractionParameterHandler& parameter_handler,
                         const IDistractionDataSource& data_source)
    : builder_{}, detector_{std::make_unique<DistractionDetector>(parameter_handler, data_source)}
{
}

void Distraction::Step()
{
    detector_->Step();

    builder_.WithTimePoint(std::chrono::system_clock::now())
        .WithState(detector_->GetDistractionState())
        .WithConfidence(detector_->GetDistractionConfidence());
}

const DistractionMessage& Distraction::GetDistractionMessage() const
{
    return builder_.Build();
}
}  // namespace driver
}  // namespace perception
