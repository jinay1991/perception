///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_FATIGUE_MESSAGE_BUILDER_H
#define PERCEPTION_DRIVER_FATIGUE_MESSAGE_BUILDER_H

#include "perception/driver/datatype/driver.h"

#include <chrono>

namespace perception
{
namespace driver
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
    FatigueMessageBuilder& WithTimePoint(const std::chrono::system_clock::time_point& time_point);

    /// @brief Update fatigue state of the Fatigue Information
    ///
    /// @param state [in] - fatigue state to update
    ///
    /// @return this object
    FatigueMessageBuilder& WithState(const FatigueState state);

    /// @brief Update confidence of the Fatigue Information
    ///
    /// @param confidence [in] - confidence to update
    ///
    /// @return this object
    FatigueMessageBuilder& WithConfidence(const double confidence);

    /// @brief Build the Fatigue Message object with all the updated information and provide that object.
    ///
    /// @return fatigue_message
    const FatigueMessage& Build() const;

  private:
    /// @brief Instance of Fatigue Message
    FatigueMessage fatigue_message_;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_FATIGUE_MESSAGE_BUILDER_H
