///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_ACTIVITY_H
#define PERCEPTION_DRIVER_ACTIVITY_H

#include "perception/driver/activity_message_builder.h"
#include "perception/driver/i_activity_data_source.h"
#include "perception/driver/i_activity_detector.h"
#include "perception/driver/i_activity_feature.h"
#include "perception/driver/i_activity_parameter_handler.h"

#include <memory>

namespace perception
{
namespace driver
{
/// @brief Calculate Driver's Activity Information
class Activity : public IActivityFeature
{
  public:
    /// @brief Default Constructor.
    ///
    /// @param parameter_handler [in] - Instance of the Parameter Handler
    /// @param data_source [in] - Instance of the Data Source
    explicit Activity(const IActivityParameterHandler& parameter_handler, const IActivityDataSource& data_source);

    /// @brief Calculate Driver's Activity based on the received inputs
    void Step() override;

    /// @brief Provide Calculated Activity Information
    ///
    /// @return activity_message
    const ActivityMessage& GetActivityMessage() const override;

  private:
    /// @brief Instance to Activity Message Builder
    ActivityMessageBuilder builder_;

    /// @brief Instance to Driver Activity Identifier
    std::unique_ptr<IActivityDetector> detector_;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_ACTIVITY_H
