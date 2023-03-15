///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_DISTRACTION_PARAMETER_HANDLER_H
#define PERCEPTION_DRIVER_I_DISTRACTION_PARAMETER_HANDLER_H

namespace perception
{
namespace driver
{

/// @brief Distraction Parameter handler interface
class IDistractionParameterHandler
{
  public:
    /// @brief Default Destructor
    virtual ~IDistractionParameterHandler() = default;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_I_DISTRACTION_PARAMETER_HANDLER_H
