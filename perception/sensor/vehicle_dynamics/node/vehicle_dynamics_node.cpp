///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/sensor/vehicle_dynamics/node/vehicle_dynamics_node.h"

#include "perception/communication/topics.h"

namespace perception
{
VehicleDynamicsNode::VehicleDynamicsNode(middleware::IPubSubFactory& factory)
    : Node{"vehicle_dynamics_node", factory}, vehicle_dynamics_{}
{
}

void VehicleDynamicsNode::Init()
{
    vehicle_dynamics_.Init();
    InitPublisher();
}

void VehicleDynamicsNode::InitPublisher()
{
    AddPublisher<VehicleDynamicsTopic>([this]() { return vehicle_dynamics_.GetVehicleDynamicsMessage(); });
}

void VehicleDynamicsNode::ExecuteStep()
{
    vehicle_dynamics_.Step();
}

void VehicleDynamicsNode::Shutdown()
{
    vehicle_dynamics_.Shutdown();
}

}  // namespace perception
