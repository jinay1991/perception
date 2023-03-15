///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_DATA_SOURCE_H
#define PERCEPTION_DRIVER_I_DATA_SOURCE_H

#include "perception/driver/datatype/driver.h"
#include "perception/driver/i_activity_data_source.h"
#include "perception/driver/i_distraction_data_source.h"
#include "perception/driver/i_fatigue_data_source.h"
#include "perception/driver/i_responsiveness_data_source.h"

namespace perception
{
namespace driver
{
/// @brief Interface class for storing and providing interfaces to access received information (Driver Camera
/// Information)
class IDataSource : public IFatigueDataSource,
                    public IDistractionDataSource,
                    public IActivityDataSource,
                    public IResponsivenessDataSource
{
  public:
    /// @brief Default Destructor
    virtual ~IDataSource() = default;

    /// @brief Interface to obtain timestamp information from the driver camera information
    ///
    /// @return time_point
    virtual std::chrono::system_clock::time_point GetTimePoint() const = 0;
};
}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_I_DATA_SOURCE_H
