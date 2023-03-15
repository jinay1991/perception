///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_DISTRACTION_DETECTOR_H
#define PERCEPTION_DRIVER_DISTRACTION_DETECTOR_H

#include "perception/driver/i_distraction_data_source.h"
#include "perception/driver/i_distraction_detector.h"
#include "perception/driver/i_distraction_parameter_handler.h"

namespace perception
{
namespace driver
{
/// @brief Definition class of Interface for Distraction Detection
class DistractionDetector : public IDistractionDetector
{
  public:
    /// @brief Default Constructor
    ///
    /// @param parameter_handler [in] - Instance of the Distraction Parameter Handler
    /// @param data_source [in] - Instance of the Distraction Data Source
    explicit DistractionDetector(const IDistractionParameterHandler& /* parameter_handler */,
                                 const IDistractionDataSource& /* data_source */);

    /// @brief Calculate Driver's Distraction based on the received data
    void Step() override;

    /// @brief Provides the Distraction State, determined based on the received data
    ///
    /// @return state
    DistractionState GetDistractionState() const override;

    /// @brief Provides the Distraction State confidence, determined based on the received data
    ///
    /// @return confidence [Range: (0.0, 1.0)]
    double GetDistractionConfidence() const override;

  private:
    /// @brief Determine Distraction State
    void DetermineDistractionState();

    /// @brief Determine Distraction State confidence [Range: (0.0, 1.0)]
    void DetermineDistractionConfidence();

    /// @brief Instance of the Parameter handler
    const IDistractionParameterHandler& parameter_handler_;

    /// @brief Instance of Data Source
    const IDistractionDataSource& data_source_;

    /// @brief Distraction State
    DistractionState state_;

    /// @brief Distraction state confidence [Range: (0.0, 1.0)]
    double confidence_;
};
}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_DISTRACTION_DETECTOR_H
