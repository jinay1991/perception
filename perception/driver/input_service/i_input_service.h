///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_INPUT_SERVICE_H
#define PERCEPTION_DRIVER_I_INPUT_SERVICE_H

#include "perception/datatypes/driver.h"

namespace perception
{
class IInputService
{
  public:
    virtual ~IInputService() = default;

    virtual EyeState GetEyeState() const = 0;
    virtual HeadPose GetHeadPose() const = 0;
    virtual GazePose GetGazePose() const = 0;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_I_INPUT_SERVICE_H
