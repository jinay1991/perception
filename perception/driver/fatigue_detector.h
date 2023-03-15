///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_FATIGUE_DETECTOR_H
#define PERCEPTION_DRIVER_FATIGUE_DETECTOR_H

#include "perception/driver/eye_state_filter.h"
#include "perception/driver/i_fatigue_data_source.h"
#include "perception/driver/i_fatigue_detector.h"
#include "perception/driver/i_fatigue_parameter_handler.h"
#include "perception/driver/perclos.h"

namespace perception
{
namespace driver
{
/// @brief Definition class for Fatigue Detection
class FatigueDetector : public IFatigueDetector
{
  public:
    /// @brief Default Constructor
    ///
    /// @param parameter_handler [in] - Instance of the Fatigue Parameter Handler
    /// @param data_source [in] - Instance of the Fatigue Data Source
    explicit FatigueDetector(const IFatigueParameterHandler& parameter_handler, const IFatigueDataSource& data_source);

    /// @brief Calculate Driver's Fatigue based on the received data
    void Step() override;

    /// @brief Provides the Fatigue State, determined based on the received data
    ///
    /// @return fatigue_state
    FatigueState GetFatigueState() const override;

    /// @brief Provides the Fatigue State confidence, determined based on the received data
    ///
    /// @return confidence [Range: (0.0, 1.0)]
    double GetFatigueConfidence() const override;

  private:
    /// @brief Determins Driver's Eye State (Opened/Closed) based on the Eye Lid Opening & Blink Rate
    ///
    /// @return eye state
    void DetermineEyeState();

    /// @brief Determine PERCLOS
    void DeterminePerclos();

    /// @brief Determine Fatigue State based on the Percentage of Eye Closure (Perclos)
    /// @note Fatigue State is directly mapped to the Perclos as follows:
    ///   |    Perclos    | Fatigue State |
    ///   +===============+===============+
    ///   |  0.0 -   7.5% | Awake         |
    ///   |  7.5 -  15.0% | Questionable  |
    ///   | 15.0 -  30.0% | Drowsy        |
    ///   | 30.0 -  60.0% | BeginningSleep|
    ///   | 60.0 - 100.0% | Sleep         |
    ///
    /// @return fatigue state
    void DetermineFatigueState();

    /// @brief Determine Fatigue Confidence [Range: (0.0, 1.0)]
    /// @note Confindence would be the Percentage of Eye state closure in given observation window.
    ///
    /// @return fatigue_confidence
    void DetermineFatigueConfidence();

    /// @brief Filter for Eye blink filter
    EyeStateFilter eye_state_filter_;

    /// @brief Instance to Perclos
    Perclos perclos_;

    /// @brief Instance to calculated fatigue state
    FatigueState state_;

    /// @brief Fatigue State Confidence [Range: (0.0, 1.0)]
    double confidence_;
};
}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_FATIGUE_DETECTOR_H
