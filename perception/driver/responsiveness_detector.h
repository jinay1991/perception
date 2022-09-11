///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_RESPONSIVENESS_DETECTOR_H
#define PERCEPTION_DRIVER_RESPONSIVENESS_DETECTOR_H

#include "perception/driver/i_responsiveness_data_source.h"
#include "perception/driver/i_responsiveness_detector.h"
#include "perception/driver/i_responsiveness_parameter_handler.h"

namespace perception
{
namespace driver
{
/// @brief Definition class of Interface for Responsiveness Detection
class ResponsivenessDetector : public IResponsivenessDetector
{
  public:
    /// @brief Default Constructor
    ///
    /// @param parameter_handler [in] - Instance of the Responsiveness Parameter Handler
    /// @param data_source [in] - Instance of the Responsiveness Data Source
    explicit ResponsivenessDetector(const IResponsivenessParameterHandler& parameter_handler,
                                    const IResponsivenessDataSource& data_source);

    /// @brief Calculate Driver's Responsiveness based on the received data
    void Step() override;

    /// @brief Provides the Responsiveness State, determined based on the received data
    ///
    /// @return state
    ResponsivenessState GetResponsivenessState() const override;

    /// @brief Provides the Responsiveness State confidence, determined based on the received data
    ///
    /// @return confidence [Range: (0.0, 1.0)]
    double GetResponsivenessConfidence() const override;

  private:
    /// @brief Determine Responsiveness State
    void DetermineResponsivenessState();

    /// @brief Determine Responsiveness State confidence [Range: (0.0, 1.0)]
    void DetermineResponsivenessConfidence();

    /// @brief Instance of the Parameter handler
    const IResponsivenessParameterHandler& parameter_handler_;

    /// @brief Instance of Data Source
    const IResponsivenessDataSource& data_source_;

    /// @brief Responsiveness State
    ResponsivenessState state_;

    /// @brief Responsiveness state confidence [Range: (0.0, 1.0)]
    double confidence_;
};
}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_RESPONSIVENESS_DETECTOR_H
