///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_FATIGUE_H
#define PERCEPTION_DRIVER_FATIGUE_H

#include "perception/datatypes/driver.h"
#include "perception/driver/fatigue_message_builder.h"
#include "perception/driver/i_data_source.h"
#include "perception/driver/i_parameter_handler.h"
#include "perception/driver/perclos.h"

namespace perception
{
class Fatigue
{
  public:
    explicit Fatigue(const IParameterHandler& parameter_handler, const IDataSource& data_source);

    void Init();
    void ExecuteStep();
    void Shutdown();

    const FatigueMessage& GetFatigueMessage() const;

  private:
    void DetermineFatigue();
    EyeState DetermineEyeState() const;
    FatigueLevel DetermineFatigueLevel() const;
    double DetermineFatigueConfidence() const;

    bool IsFaceVisible() const;
    bool IsEyeVisible() const;
    bool IsEyeOpen() const;

    const IParameterHandler& parameter_handler_;
    const IDataSource& data_source_;

    FatigueMessageBuilder fatigue_builder_;

    Perclos perclos_;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_FATIGUE_H
