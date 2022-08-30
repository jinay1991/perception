///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_RESPONSIVENESS_DATA_SOURCE_H
#define PERCEPTION_DRIVER_I_RESPONSIVENESS_DATA_SOURCE_H

namespace perception
{
namespace driver
{
/// @brief Interface class for storing and providing interfaces to access received information (Driver Camera
/// Information)
class IResponsivenessDataSource
{
  public:
    /// @brief Default Destructor
    virtual ~IResponsivenessDataSource() = default;
};
}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_I_RESPONSIVENESS_DATA_SOURCE_H
