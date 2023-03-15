///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_ACTIVITY_FEATURE_H
#define PERCEPTION_DRIVER_I_ACTIVITY_FEATURE_H

#include "perception/driver/datatype/driver.h"
#include "perception/driver/i_feature.h"

namespace perception
{
namespace driver
{
/// @brief Interface to the provide support for the activity feature
class IActivityFeature : public IFeature
{
  public:
    /// @brief Default Destrcutor
    virtual ~IActivityFeature() = default;

    /// @brief Provide Calculated Activity Information
    ///
    /// @return activity_message
    virtual const ActivityMessage& GetActivityMessage() const = 0;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_I_ACTIVITY_FEATURE_H
