///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_DRIVER_DRIVER_H
#define PERCEPTION_DRIVER_DRIVER_H

#include "perception/datatypes/driver.h"
#include "perception/driver/data_source.h"
#include "perception/driver/fatigue.h"
#include "perception/driver/parameter_handler.h"
#include "perception/driver/visual_attention.h"

namespace perception
{
class Driver final
{
  public:
    /// @brief Default Constructor
    Driver();

    /// @brief Evaluate Driver's Fatigue and Visual Attention
    void Step();

    /// @brief Process received input (driver camera message)
    ///
    /// @param driver_camera_message [in] - Driver Camera Message
    void ProcessDriverCameraMessage(const DriverCameraMessage& driver_camera_message);

    /// @brief Provide calculated Driver's Visual Attention Information
    ///
    /// @return visual_attention_message
    const VisualAttentionMessage& GetVisualAttentionMessage() const;

    /// @brief Provide calcualted Driver's Fatigue Information
    ///
    /// @return fatigue_message
    const FatigueMessage& GetFatigueMessage() const;

  private:
    /// @brief Instance of the Parameter handler
    ParameterHandler parameter_handler_;

    /// @brief Instance of Data Source
    DataSource data_source_;

    /// @brief Instance of Fatigue to calculate Driver's Fatigue
    Fatigue fatigue_;

    /// @brief Instance of Visual Attention to calculate Driver's Visual Attention
    VisualAttention visual_attention_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_DRIVER_H
