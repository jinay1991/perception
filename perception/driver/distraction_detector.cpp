///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/distraction_detector.h"

namespace perception
{
namespace driver
{
namespace
{

/// @brief Gaze Region mapping Interiors
enum class GazeRegion : std::uint8_t
{
    kNotAvailable = 0U,
    kDriverWindShield = 1U,
    kPassengerWindShield = 2U,
    kRearViewMirror = 3U,
    kRoof = 4U,
    kInstrumentCluster = 5U,
    kCentralControl = 6U,
    kDriverSideWindow = 7U,
    kPassengerSideWindow = 8U,
    kInvalid = 255U
};

constexpr GazeRegion GetGazeRegion(const GazeTracking& gaze_tracking) noexcept
{

    return GazeRegion::kDriverWindShield;
}
}  // namespace

DistractionDetector::DistractionDetector(const IDistractionParameterHandler& parameter_handler,
                                         const IDistractionDataSource& data_source)
    : parameter_handler_{parameter_handler},
      data_source_{data_source},
      state_{DistractionState::kInvalid},
      confidence_{0.0}
{
}

void DistractionDetector::Step()
{
    DetermineDistractionState();
    DetermineDistractionConfidence();
}

DistractionState DistractionDetector::GetDistractionState() const
{
    return state_;
}

double DistractionDetector::GetDistractionConfidence() const
{
    return confidence_;
}

void DistractionDetector::DetermineDistractionState()
{
    /// @todo: Implement Algorithm to determin Distraction based on Gaze/Head Pose data
    state_ = DistractionState::kNotDistracted;
}

void DistractionDetector::DetermineDistractionConfidence()
{
    confidence_ = 0.0;
}

}  // namespace driver
}  // namespace perception
