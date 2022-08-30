///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/node/driver_node.h"

#include "perception/driver/datatype/driver.h"
#include "perception/driver/driver.h"

#include <units.h>

#include <memory>

namespace perception
{
namespace driver
{
namespace
{

DriverCameraMessage CreateTypicalDriverCameraMessage() noexcept
{
    using namespace units::literals;

    DriverCameraMessage message{};
    message.time_point = std::chrono::system_clock::now();
    message.face_tracking.eye_visible = true;
    message.face_tracking.face_visible = true;
    message.face_tracking.eye_lid_opening = 10_mm;
    message.face_tracking.eye_blink_rate = 20_Hz;
    return message;
}
}  // namespace

DriverNode::DriverNode() : Node{"driver_node"}, driver_{std::make_unique<Driver>()} {}

void DriverNode::Init()
{
    /// @note For testing, message is populated with custom function
    const auto message = CreateTypicalDriverCameraMessage();

    driver_->UpdateDriverCameraMessage(message);
}

void DriverNode::Step()
{
    driver_->Step();
}

void DriverNode::Shutdown() {}

const DriverMessage& DriverNode::GetDriverMessage() const
{
    return driver_->GetDriverMessage();
}

lifecycle::NodePtr CreateDriverNode()
{
    return std::make_unique<DriverNode>();
}

}  // namespace driver
}  // namespace perception
