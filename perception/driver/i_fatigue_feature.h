///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_FATIGUE_FEATURE_H
#define PERCEPTION_DRIVER_I_FATIGUE_FEATURE_H

#include "perception/driver/datatype/driver.h"
#include "perception/driver/i_feature.h"

namespace perception
{
namespace driver
{
/// @brief Interface to the provide support for the fatigue feature
class IFatigueFeature : public IFeature
{
  public:
    /// @brief Default Destrcutor
    virtual ~IFatigueFeature() = default;

    /// @brief Provide Calculated Fatigue Information
    ///
    /// @return fatigue_message
    virtual const FatigueMessage& GetFatigueMessage() const = 0;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_I_FATIGUE_FEATURE_H
