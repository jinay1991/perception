///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_DISTRACTION_FEATURE_H
#define PERCEPTION_DRIVER_I_DISTRACTION_FEATURE_H

#include "perception/driver/datatype/driver.h"
#include "perception/driver/i_feature.h"

namespace perception
{
namespace driver
{
/// @brief Interface to the provide support for the distraction feature
class IDistractionFeature : public IFeature
{
  public:
    /// @brief Default Destrcutor
    virtual ~IDistractionFeature() = default;

    /// @brief Provide Calculated Distraction Information
    ///
    /// @return distraction_message
    virtual const DistractionMessage& GetDistractionMessage() const = 0;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_I_DISTRACTION_FEATURE_H
