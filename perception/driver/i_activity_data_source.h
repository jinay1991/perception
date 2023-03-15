///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_ACTIVITY_DATA_SOURCE_H
#define PERCEPTION_DRIVER_I_ACTIVITY_DATA_SOURCE_H

#include "perception/driver/datatype/driver.h"

namespace perception
{
namespace driver
{
/// @brief Interface class for storing and providing interfaces to access received information (Driver Camera
/// Information)
class IActivityDataSource
{
  public:
    /// @brief Default Destructor
    virtual ~IActivityDataSource() = default;
};
}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_I_ACTIVITY_DATA_SOURCE_H
