///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_DRIVER_FATIGUE_H
#define PERCEPTION_DRIVER_FATIGUE_H

#include "perception/datatypes/driver.h"
#include "perception/driver/eye_state_filter.h"
#include "perception/driver/fatigue_message_builder.h"
#include "perception/driver/i_data_source.h"
#include "perception/driver/i_parameter_handler.h"
#include "perception/driver/perclos.h"

namespace perception
{
/// @brief Calculate Driver's Fatigue Information
class Fatigue final
{
  public:
    /// @brief Default Constructor.
    ///
    /// @param parameter_handler [in] - Instance of the Parameter Handler
    /// @param data_source [in] - Instance of the Data Source
    explicit Fatigue(const IParameterHandler& parameter_handler, const IDataSource& data_source);

    /// @brief Calculate Driver's Fatigue based on the received inputs
    void Step();

    /// @brief Provide Calculated Fatigue Information
    ///
    /// @return fatigue_message
    const FatigueMessage& GetFatigueMessage() const;

  private:
    /// @brief Determines Driver's Fatigue based on the Driver's Eyes states
    /// @note Update Perclos window with current eye state to calculate percentage closure for given eye state
    /// observation window.
    void DetermineFatigue();

    /// @brief Determins Driver's Eye State (Opened/Closed) based on the Eye Lid Opening & Blink Rate
    ///
    /// @return eye state
    EyeState DetermineEyeState();

    /// @brief Determine Fatigue Level based on the Percentage of Eye Closure (Perclos)
    /// @note Fatigue Level is directly mapped to the Perclos as follows:
    ///   |    Perclos    | Fatigue Level |
    ///   +===============+===============+
    ///   |  0.0 -   7.5% | Awake         |
    ///   |  7.5 -  15.0% | Questionable  |
    ///   | 15.0 -  30.0% | Drowsy        |
    ///   | 30.0 -  60.0% | BeginningSleep|
    ///   | 60.0 - 100.0% | Sleep         |
    ///
    /// @return fatigue_level
    FatigueLevel DetermineFatigueLevel() const;

    /// @brief Determines Fatigue Confidence.
    /// @note Confindence would be the Percentage of Eye state closure in given observation window.
    ///
    /// @return fatigue_confidence
    double DetermineFatigueConfidence() const;

    /// @brief Instance to Fatigue Message Builder
    FatigueMessageBuilder fatigue_builder_;

    /// @brief Instance to Perclos
    Perclos perclos_;

    /// @brief Filter for Eye blink filter
    EyeStateFilter eye_state_filter_;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_FATIGUE_H
