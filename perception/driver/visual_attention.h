///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_DRIVER_VISUAL_ATTENTION_H
#define PERCEPTION_DRIVER_VISUAL_ATTENTION_H

#include "perception/datatypes/driver.h"
#include "perception/driver/i_data_source.h"
#include "perception/driver/i_parameter_handler.h"

namespace perception
{
/// @brief Calculate Driver's Visual Attention Information
class VisualAttention final
{
  public:
    /// @brief Constructor
    ///
    /// @param parameter_handler [in] - Instance of the Parameter Handler
    /// @param data_source [in] - Instance of the Data Source
    explicit VisualAttention(const IParameterHandler& parameter_handler, const IDataSource& data_source);

    /// @brief Calculate Driver's Visual Attention based on the received inputs
    void Step();

    /// @brief Provide Calculated Visual Attention Information
    ///
    /// @return visual_attention_message
    const VisualAttentionMessage& GetVisualAttentionMessage() const;

  private:
    /// @brief Provide current attention state
    ///
    /// @return attention state
    AttentionState GetAttentionState() const;

    /// @brief Provide whether Head Pose is available on received Driver Camera Data
    ///
    /// @return True if data source has valid head pose, otherwise False.
    bool IsHeadPoseAvailable() const;

    /// @brief Provide whether Head Pose is attentive on the Road
    ///
    /// @return True if the Head Pose is attentive on road, otherwise False.
    bool IsHeadPoseAttentive() const;

    /// @brief Instance of Data Source
    const IDataSource& data_source_;

    /// @brief Instance of the Visual Attention Message
    VisualAttentionMessage visual_attention_message_;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_VISUAL_ATTENTION_H
