///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_DRIVER_FATIGUE_MESSAGE_BUILDER_H
#define PERCEPTION_DRIVER_FATIGUE_MESSAGE_BUILDER_H

#include "perception/datatypes/driver.h"

namespace perception
{
/// @brief Fatiuge Message Builder
class FatigueMessageBuilder final
{
  public:
    /// @brief Default constructor.
    FatigueMessageBuilder();

    /// @brief Update time_point of the Fatigue Information
    ///
    /// @param time_point [in] - time_point to update
    ///
    /// @return this object
    FatigueMessageBuilder& WithTimepoint(const std::chrono::system_clock::time_point& time_point);

    /// @brief Update fatigue level of the Fatigue Information
    ///
    /// @param level [in] - fatigue level to update
    ///
    /// @return this object
    FatigueMessageBuilder& WithFatigueLevel(const FatigueLevel level);

    /// @brief Update confidence of the Fatigue Information
    ///
    /// @param confidence [in] - confidence to update
    ///
    /// @return this object
    FatigueMessageBuilder& WithFatigueConfidence(const double confidence);

    /// @brief Update eye_state of the Fatigue Information
    ///
    /// @param eye_state [in] - eye_state to update
    ///
    /// @return this object
    FatigueMessageBuilder& WithEyeState(const EyeState eye_state);

    /// @brief Build the Fatigue Message object with all the updated information and provide that object.
    ///
    /// @return fatigue_message
    const FatigueMessage& Build() const;

  private:
    FatigueMessage fatigue_message_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_FATIGUE_MESSAGE_BUILDER_H
