///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_DRIVER_FATIGUE_MESSAGE_BUILDER_H
#define PERCEPTION_DRIVER_FATIGUE_MESSAGE_BUILDER_H

#include "perception/datatypes/driver.h"

namespace perception
{
class FatigueMessageBuilder
{
  public:
    FatigueMessageBuilder();

    FatigueMessageBuilder& WithTimepoint(const std::chrono::system_clock::time_point& time_point);
    FatigueMessageBuilder& WithFatigueLevel(const FatigueLevel level);
    FatigueMessageBuilder& WithFatigueConfidence(const double confidence);
    FatigueMessageBuilder& WithEyeState(const EyeState eye_state);

    const FatigueMessage& Build() const;

  private:
    FatigueMessage fatigue_message_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_FATIGUE_MESSAGE_BUILDER_H
