///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_RESPONSIVENESS_H
#define PERCEPTION_DRIVER_RESPONSIVENESS_H

#include "perception/driver/datatype/driver.h"
#include "perception/driver/i_responsiveness_data_source.h"
#include "perception/driver/i_responsiveness_feature.h"
#include "perception/driver/i_responsiveness_parameter_handler.h"
#include "perception/driver/responsiveness_message_builder.h"

namespace perception
{
namespace driver
{
/// @brief Calculate Driver's Responsiveness Information
class Responsiveness : public IResponsivenessFeature
{
  public:
    /// @brief Default Constructor.
    ///
    /// @param parameter_handler [in] - Instance of the Parameter Handler
    /// @param data_source [in] - Instance of the Data Source
    explicit Responsiveness(const IResponsivenessParameterHandler& parameter_handler,
                            const IResponsivenessDataSource& data_source);

    /// @brief Calculate Driver's Responsiveness based on the received inputs
    void Step() override;

    /// @brief Provide Calculated Responsiveness Information
    ///
    /// @return responsiveness_message
    const ResponsivenessMessage& GetResponsivenessMessage() const override;

  private:
    /// @brief Instance of Driver Responsiveness Builder
    ResponsivenessMessageBuilder builder_;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_RESPONSIVENESS_H
