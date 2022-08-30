///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_ACTIVITY_MESSAGE_BUILDER_H
#define PERCEPTION_DRIVER_ACTIVITY_MESSAGE_BUILDER_H

#include "perception/driver/datatype/driver.h"

namespace perception
{
namespace driver
{
/// @brief Activity Message Builder
class ActivityMessageBuilder final
{
  public:
    /// @brief Default constructor.
    ActivityMessageBuilder();

    /// @brief Update time_point of the activity Information
    ///
    /// @param time_point [in] - time_point to update
    ///
    /// @return this object
    ActivityMessageBuilder& WithTimePoint(const std::chrono::system_clock::time_point& time_point);

    /// @brief Update activity state of the activity Information
    ///
    /// @param state [in] - activity state to update
    ///
    /// @return this object
    ActivityMessageBuilder& WithState(const ActivityState state);

    /// @brief Update confidence of the activity Information
    ///
    /// @param confidence [in] - confidence to update
    ///
    /// @return this object
    ActivityMessageBuilder& WithConfidence(const double confidence);

    /// @brief Build the activity Message object with all the updated information and provide that object.
    ///
    /// @return activity_message
    const ActivityMessage& Build() const;

  private:
    /// @brief Instance of Activity Message
    ActivityMessage activity_message_;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_ACTIVITY_MESSAGE_BUILDER_H
