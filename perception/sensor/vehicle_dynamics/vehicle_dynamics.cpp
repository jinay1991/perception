///
/// @file
/// @copyright Copyright (c) 2020. All Rights Reserved.
///
#include "perception/sensor/vehicle_dynamics/vehicle_dynamics.h"

#include <units.h>

namespace perception
{
using namespace units::literals;

VehicleDynamics::VehicleDynamics() : vehicle_dynamics_message_{} {}

void VehicleDynamics::Init() {}

void VehicleDynamics::Step()
{
    vehicle_dynamics_message_.velocity = 10.0_mps;
    vehicle_dynamics_message_.acceleration = 10.0_mps_sq;
}

void VehicleDynamics::Shutdown() {}

const VehicleDynamicsMessage& VehicleDynamics::GetVehicleDynamicsMessage() const
{
    return vehicle_dynamics_message_;
}

}  // namespace perception