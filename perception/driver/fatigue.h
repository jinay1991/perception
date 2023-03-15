///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_FATIGUE_H
#define PERCEPTION_DRIVER_FATIGUE_H

#include "perception/driver/fatigue_detector.h"
#include "perception/driver/fatigue_message_builder.h"
#include "perception/driver/i_fatigue_data_source.h"
#include "perception/driver/i_fatigue_feature.h"
#include "perception/driver/i_fatigue_parameter_handler.h"

namespace perception
{
namespace driver
{
/// @brief Calculate Driver's Fatigue Information
class Fatigue final : public IFatigueFeature
{
  public:
    /// @brief Default Constructor.
    ///
    /// @param parameter_handler [in] - Instance of the Parameter Handler
    /// @param data_source [in] - Instance of the Data Source
    explicit Fatigue(const IFatigueParameterHandler& parameter_handler, const IFatigueDataSource& data_source);

    /// @brief Calculate Driver's Fatigue based on the received inputs
    void Step() override;

    /// @brief Provide Calculated Fatigue Information
    ///
    /// @return fatigue_message
    const FatigueMessage& GetFatigueMessage() const override;

  private:
    /// @brief Instance to Fatigue Message Builder
    FatigueMessageBuilder builder_;

    /// @brief Instance to Fatigue Detector
    FatigueDetector detector_;
};
}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_FATIGUE_H
