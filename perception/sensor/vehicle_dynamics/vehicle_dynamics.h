///
/// @file
/// @copyright Copyright (c) 2020. All Rights Reserved.
///
#ifndef PERCEPTION_SENSOR_VEHICLE_DYNAMICS_H
#define PERCEPTION_SENSOR_VEHICLE_DYNAMICS_H

#include "perception/datatypes/vehicle_dynamics.h"

namespace perception
{
class VehicleDynamics
{
  public:
    VehicleDynamics();

    void Init();
    void Step();
    void Shutdown();

    virtual VehicleDynamicsMessage GetVehicleDynamicsMessage() const;

  private:
    VehicleDynamicsMessage vehicle_dynamics_message_;
};
}  // namespace perception

#endif  /// PERCEPTION_SENSOR_VEHICLE_DYNAMICS_H