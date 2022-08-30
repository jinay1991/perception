///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_DRIVER_MESSAGE_BUILDER_H
#define PERCEPTION_DRIVER_DRIVER_MESSAGE_BUILDER_H

#include "perception/driver/datatype/driver.h"

#include <chrono>

namespace perception
{
namespace driver
{
/// @brief Driver Message Builder
class DriverMessageBuilder final
{
  public:
    /// @brief Default constructor.
    DriverMessageBuilder();

    /// @brief Update time point
    ///
    /// @param time_point [in] - time_point to update
    ///
    /// @return this object
    DriverMessageBuilder& WithTimePoint(const std::chrono::system_clock::time_point& time_point);

    /// @brief Update Driver activity Information
    ///
    /// @param activity [in] - driver activity info
    ///
    /// @return this object
    DriverMessageBuilder& WithActivityMessage(const ActivityMessage& activity);

    /// @brief Update Driver Fatigue Information
    ///
    /// @param fatigue [in] - driver fatigue info
    ///
    /// @return this object
    DriverMessageBuilder& WithFatigueMessage(const FatigueMessage& fatigue);

    /// @brief Update Driver Distraction Information
    ///
    /// @param distraction [in] - driver distraction info
    ///
    /// @return this object
    DriverMessageBuilder& WithDistractionMessage(const DistractionMessage& distraction);

    /// @brief Update Driver Responsiveness Information
    ///
    /// @param responsiveness [in] - driver responsiveness info
    ///
    /// @return this object
    DriverMessageBuilder& WithResponsivenessMessage(const ResponsivenessMessage& responsiveness);

    /// @brief Build the driver Message object with all the updated information and provide that object.
    ///
    /// @return driver_message
    const DriverMessage& Build() const;

  private:
    /// @brief Instance of Driver Message
    DriverMessage driver_message_;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_DRIVER_MESSAGE_BUILDER_H
