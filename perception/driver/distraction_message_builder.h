///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_DISTRACTION_MESSAGE_BUILDER_H
#define PERCEPTION_DRIVER_DISTRACTION_MESSAGE_BUILDER_H

#include "perception/driver/datatype/driver.h"

#include <chrono>

namespace perception
{
namespace driver
{
/// @brief Distraction Message Builder
class DistractionMessageBuilder final
{
  public:
    /// @brief Default constructor.
    DistractionMessageBuilder();

    /// @brief Update time_point of the distraction Information
    ///
    /// @param time_point [in] - time_point to update
    ///
    /// @return this object
    DistractionMessageBuilder& WithTimePoint(const std::chrono::system_clock::time_point& time_point);

    /// @brief Update distraction state of the distraction Information
    ///
    /// @param state [in] - distraction state to update
    ///
    /// @return this object
    DistractionMessageBuilder& WithState(const DistractionState state);

    /// @brief Update confidence of the distraction Information
    ///
    /// @param confidence [in] - confidence to update
    ///
    /// @return this object
    DistractionMessageBuilder& WithConfidence(const double confidence);

    /// @brief Build the distraction Message object with all the updated information and provide that object.
    ///
    /// @return distraction_message
    const DistractionMessage& Build() const;

  private:
    /// @brief Instance of Distraction Message
    DistractionMessage distraction_message_;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_DISTRACTION_MESSAGE_BUILDER_H
