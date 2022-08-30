///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_DRIVER_H
#define PERCEPTION_DRIVER_DRIVER_H

#include "perception/driver/data_source.h"
#include "perception/driver/datatype/driver.h"
#include "perception/driver/driver_message_builder.h"
#include "perception/driver/i_activity_feature.h"
#include "perception/driver/i_distraction_feature.h"
#include "perception/driver/i_driver.h"
#include "perception/driver/i_fatigue_feature.h"
#include "perception/driver/i_responsiveness_feature.h"
#include "perception/driver/parameter_handler.h"
#include "perception/driver/risk_assessment.h"

#include <memory>

namespace perception
{
namespace driver
{

/// @brief Driver Montioring Wrapper class
class Driver final : public IDriver
{
  public:
    /// @brief Default Constructor
    Driver();

    /// @brief Evaluate Driver's Fatigue and Visual Distraction
    void Step();

    /// @brief Process received input (driver camera message)
    ///
    /// @param driver_camera_message [in] - Driver Camera Message
    void UpdateDriverCameraMessage(const DriverCameraMessage& driver_camera_message) override;

    /// @brief Provide calculated Driver's Fatigue Information
    ///
    /// @return fatigue_message
    const FatigueMessage& GetFatigueMessage() const override;

    /// @brief Provide calculated Driver's Distraction Information
    ///
    /// @return distraction_message
    const DistractionMessage& GetDistractionMessage() const override;

    /// @brief Provide calculated Driver's Activity Information
    ///
    /// @return activity_message
    const ActivityMessage& GetActivityMessage() const override;

    //// @brief Provide calculated Driver's responsiveness
    ///
    /// @return responsiveness_message
    const ResponsivenessMessage& GetResponsivenessMessage() const override;

    /// @brief Provide Risk Assessment based on the calculated Fatigue, Distraction and Activity
    ///
    /// @return risk_assessment
    RiskAssessmentState GetRiskAssessmentState() const;

    /// @brief Provide (monitored) Driver's State Information
    ///
    /// @return driver_message
    const DriverMessage& GetDriverMessage() const override;

  private:
    /// @brief Instance of the Parameter handler
    ParameterHandler parameter_handler_;

    /// @brief Instance of Data Source
    DataSource data_source_;

    /// @brief Instance of Fatigue to identify Driver's Fatigue
    std::unique_ptr<IFatigueFeature> fatigue_;

    /// @brief Instance of Distraction to identify Driver's Distraction
    std::unique_ptr<IDistractionFeature> distraction_;

    /// @brief Instance of Activity to identify Driver's Activity
    std::unique_ptr<IActivityFeature> activity_;

    /// @brief Instance of Responsiveness to identify Driver's Responsiveness
    std::unique_ptr<IResponsivenessFeature> responsiveness_;

    /// @brief Instance of Risk Assessment for Driver's state
    RiskAssessment risk_assessment_;

    /// @brief Instance of Driver Message Builder
    DriverMessageBuilder builder_;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_DRIVER_H
