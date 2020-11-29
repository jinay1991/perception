///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_COMMUNICATION_TOPICS_H
#define PERCEPTION_COMMUNICATION_TOPICS_H

#include "middleware/communication/topic.h"
#include "perception/datatypes/camera.h"
#include "perception/datatypes/driver.h"
#include "perception/datatypes/lane.h"
#include "perception/datatypes/object.h"
#include "perception/datatypes/vehicle_dynamics.h"

namespace perception
{

class CameraTopic : public middleware::Topic<CameraMessage>
{
};

class LaneTopic : public middleware::Topic<LaneMessage>
{
};

class ObjectListTopic : public middleware::Topic<ObjectListMessage>
{
};

class VehicleDynamicsTopic : public middleware::Topic<VehicleDynamicsMessage>
{
};

class DriverCameraSystemTopic : public middleware::Topic<DriverCameraSystemMessage>
{
};

class FatigueTopic : public middleware::Topic<FatigueMessage>
{
};

class VisualAttentionTopic : public middleware::Topic<VisualAttentionMessage>
{
};

}  // namespace perception

#endif  /// PERCEPTION_COMMUNICATION_TOPICS_H
