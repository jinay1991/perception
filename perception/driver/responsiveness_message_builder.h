///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_RESPONSIVENESS_MESSAGE_BUILDER_H
#define PERCEPTION_DRIVER_RESPONSIVENESS_MESSAGE_BUILDER_H

#include "perception/driver/datatype/driver.h"

#include <chrono>

namespace perception
{
namespace driver
{
/// @brief Fatiuge Message Builder
class ResponsivenessMessageBuilder final
{
  public:
    /// @brief Default constructor.
    ResponsivenessMessageBuilder();

    /// @brief Update time_point of the Responsiveness Information
    ///
    /// @param time_point [in] - time_point to update
    ///
    /// @return this object
    ResponsivenessMessageBuilder& WithTimePoint(const std::chrono::system_clock::time_point& time_point);

    /// @brief Update Driver's responsiveness state
    ///
    /// @param state [in] - responsiveness state
    ///
    /// @return this object
    ResponsivenessMessageBuilder& WithState(const ResponsivenessState state);

    /// @brief Update confidence of the Responsiveness Information
    ///
    /// @param confidence [in] - confidence to update
    ///
    /// @return this object
    ResponsivenessMessageBuilder& WithConfidence(const double confidence);

    /// @brief Build the Responsiveness Message object with all the updated information and provide that object.
    ///
    /// @return responsiveness_message
    const ResponsivenessMessage& Build() const;

  private:
    /// @brief Instance of Responsiveness Message
    ResponsivenessMessage responsiveness_message_;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_RESPONSIVENESS_MESSAGE_BUILDER_H
