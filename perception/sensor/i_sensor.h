///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_SENSOR_I_SENSOR_H
#define PERCEPTION_SENSOR_I_SENSOR_H

#include <cstdint>

namespace perception
{
namespace sensor
{
/// @brief Sensor Types
enum class SensorType : std::uint8_t
{
    kNotAssigned = 0U,
    kCamera = 1U,
    kRadar = 2U,
    kLidar = 3U,
    kUltrasound = 4U,
    kInvalid = 255U
};

/// @brief Sensor ID
using SensorId = std::int32_t;

/// @brief Interface to Sensor (Sensor Abstraction)
class ISensor
{
  public:
    /// @brief Default Destructor
    virtual ~ISensor() = default;

    /// @brief Sets ID to the Sensor
    ///
    /// @param id [in] - Sensor ID
    virtual void SetSensorId(const SensorId id) = 0;

    /// @brief Sets Type of the Sensor
    ///
    /// @param type [in] - Type of Sensor (Camera, Radar or Lidar)
    virtual void SetSensorType(const SensorType type) = 0;

    /// @brief Initialize the Sensor and Abstraction
    virtual void Init() = 0;

    /// @brief Cyclic Step for Sensor Abtraction Layer
    virtual void Step() = 0;

    /// @brief Release/Deinitialize the Sensor and Abstraction
    virtual void Shutdown() = 0;
};
}  // namespace sensor
}  // namespace perception

#endif  /// PERCEPTION_SENSOR_I_SENSOR_H
