///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_RESPONSIVENESS_FEATURE_H
#define PERCEPTION_DRIVER_I_RESPONSIVENESS_FEATURE_H

#include "perception/driver/datatype/driver.h"
#include "perception/driver/i_feature.h"

namespace perception
{
namespace driver
{
/// @brief Interface to the provide support for the activity feature
class IResponsivenessFeature : public IFeature
{
  public:
    /// @brief Default Destrcutor
    virtual ~IResponsivenessFeature() = default;

    /// @brief Provide Calculated Responsiveness Information
    ///
    /// @return responsiveness_message
    virtual const ResponsivenessMessage& GetResponsivenessMessage() const = 0;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_I_RESPONSIVENESS_FEATURE_H
