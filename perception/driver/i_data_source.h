///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_DATA_SOURCE_H
#define PERCEPTION_DRIVER_I_DATA_SOURCE_H

#include "perception/datatypes/driver.h"

namespace perception
{
class IDataSource
{
  public:
    virtual ~IDataSource() = default;

    virtual std::chrono::system_clock::time_point GetTimePoint() const = 0;
    virtual const HeadTracking& GetHeadTracking() const = 0;
    virtual const FaceTracking& GetFaceTracking() const = 0;
    virtual const GazeTracking& GetGazeTracking() const = 0;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_I_DATA_SOURCE_H
