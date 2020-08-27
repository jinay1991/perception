///
/// @file
/// @copyright Copyright (c) 2020. All Right Reserved.
///
#ifndef PERCEPTION_DATATYPES_VEHICLE_DYNAMICS_H
#define PERCEPTION_DATATYPES_VEHICLE_DYNAMICS_H

#include <units.h>

#include <cstdint>

namespace perception
{

enum class DriveSide : std::uint8_t
{
    kLeft = 0U,
    kRight = 1U,
    kInvalid = 255U
};

struct Wheel
{
    units::length::meter_t wheel_circumference;
    units::length::meter_t wheel_diameter;
};

struct Chassis
{
    units::length::meter_t length;
    units::length::meter_t height;
    units::length::meter_t breadth;

    units::length::meter_t clearance;
};

struct VehicleDynamicsMessage
{
    DriveSide drive_side;
    Chassis chassis;

    bool seatbelt_fastened;

    units::velocity::meters_per_second_t velocity;
    units::acceleration::meters_per_second_squared_t acceleration;
    units::acceleration::meters_per_second_squared_t deceleration;
    units::torque::newton_meter_t torque;
    units::length::kilometer_t distance_travelled;

    units::angle::degree_t steering_wheel_angle;
    double curvature;
};

}  // namespace perception
#endif  /// PERCEPTION_DATATYPES_VEHICLE_DYNAMICS_H