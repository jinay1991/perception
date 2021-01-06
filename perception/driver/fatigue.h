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
class Fatigue final
{
  public:
    explicit Fatigue(const IParameterHandler& parameter_handler, const IDataSource& data_source);

    void Step();

    const FatigueMessage& GetFatigueMessage() const;

  private:
    void DetermineFatigue();
    EyeState DetermineEyeState() const;
    FatigueLevel DetermineFatigueLevel() const;
    double DetermineFatigueConfidence() const;

    FatigueMessageBuilder fatigue_builder_;

    Perclos perclos_;
    EyeStateFilter eye_state_filter_;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_FATIGUE_H
