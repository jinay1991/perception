///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_DISTRACTION_DATA_SOURCE_H
#define PERCEPTION_DRIVER_I_DISTRACTION_DATA_SOURCE_H

#include "perception/driver/datatype/driver.h"

namespace perception
{
namespace driver
{
/// @brief Interface class for storing and providing interfaces to access received information (Driver Camera
/// Information)
class IDistractionDataSource
{
  public:
    /// @brief Default Destructor
    virtual ~IDistractionDataSource() = default;

    /// @brief Interface to obtain Head tracking information from the driver camera information
    ///
    /// @return head_tracking
    virtual const HeadTracking& GetHeadTracking() const = 0;

    /// @brief Interface to obtain Gaze Tracking information from the driver camera information
    ///
    /// @return gaze_tracking
    virtual const GazeTracking& GetGazeTracking() const = 0;
};
}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_I_DISTRACTION_DATA_SOURCE_H
