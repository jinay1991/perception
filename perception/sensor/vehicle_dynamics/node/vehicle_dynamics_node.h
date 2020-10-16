///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_SENSOR_VEHICLE_DYNAMICS_NODE_VEHICLE_DYNAMICS_NODE_H
#define PERCEPTION_SENSOR_VEHICLE_DYNAMICS_NODE_VEHICLE_DYNAMICS_NODE_H

#include "middleware/communication/i_pub_sub_factory.h"
#include "middleware/lifecycle/node.h"
#include "perception/sensor/vehicle_dynamics/vehicle_dynamics.h"

#include <string>

namespace perception
{

/// @brief Vehicle Dynamics Node
class VehicleDynamicsNode final : public middleware::Node
{
  public:
    /// @brief Constructor
    /// @param factor[in] Middleware Publisher/Subscriber Factory
    explicit VehicleDynamicsNode(middleware::IPubSubFactory& factory);

    /// @brief Initialize Vehicle Dynamics Node
    void Init() override;

    /// @brief Execute single step for Vehicle Dynamics Node
    void ExecuteStep() override;

    /// @brief Shutdown/Deinitialize Vehicle Dynamics Node
    void Shutdown() override;

  private:
    /// @brief Initialize Publishers
    virtual void InitPublisher();

    /// @brief Instance of Vehicle Dynamics Sensor
    VehicleDynamics vehicle_dynamics_;
};
}  // namespace perception

#endif  /// PERCEPTION_SENSOR_VEHICLE_DYNAMICS_NODE_VEHICLE_DYNAMICS_NODE_H
