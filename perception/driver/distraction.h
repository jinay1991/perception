///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_DISTRACTION_H
#define PERCEPTION_DRIVER_DISTRACTION_H

#include "perception/driver/distraction_detector.h"
#include "perception/driver/distraction_message_builder.h"
#include "perception/driver/i_distraction_data_source.h"
#include "perception/driver/i_distraction_feature.h"
#include "perception/driver/i_distraction_parameter_handler.h"

namespace perception
{
namespace driver
{
/// @brief Calculate Driver's Distraction Information
class Distraction : public IDistractionFeature
{
  public:
    /// @brief Default Constructor.
    ///
    /// @param parameter_handler [in] - Instance of the Distraction Parameter Handler
    /// @param data_source [in] - Instance of the Distraction Data Source
    explicit Distraction(const IDistractionParameterHandler& parameter_handler,
                         const IDistractionDataSource& data_source);

    /// @brief Calculate Driver's Distraction based on the received inputs
    void Step() override;

    /// @brief Provide Calculated Distraction Information
    ///
    /// @return distraction_message
    const DistractionMessage& GetDistractionMessage() const override;

  private:
    /// @brief Instance to Distraction Message Builder
    DistractionMessageBuilder builder_;

    /// @brief Instance to Driver Distraction Identifier
    DistractionDetector detector_;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_DISTRACTION_H
