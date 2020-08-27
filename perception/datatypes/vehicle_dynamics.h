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

/// @brief Driving Side (Left/Right Hand Drive)
enum class DriveSide : std::uint8_t
{
    kLeft = 0U,
    kRight = 1U,
    kInvalid = 255U
};

/// @brief Vehicle Wheel Information
struct Wheel
{
    /// @brief Vehicle Wheel Circumference
    units::length::meter_t wheel_circumference{0.0};

    /// @brief Vehicle Wheel Diameter
    units::length::meter_t wheel_diameter{0.0};
};

/// @brief Vehicle Chassis Information
struct Chassis
{
    /// @brief Vehicle Chassis Length
    units::length::meter_t length{0.0};

    /// @brief Vehicle Chassis Height
    units::length::meter_t height{0.0};

    /// @brief Vehicle Chassis Breadth
    units::length::meter_t breadth{0.0};

    /// @brief Vehicle Chassis Road clearance
    units::length::meter_t clearance{0.0};
};

/// @brief Vehicle Dynamics Information
struct VehicleDynamicsMessage
{
    /// @brief Time Point for captured data
    std::chrono::system_clock::time_point time_point{};

    /// @brief Vehicle Drive Side
    DriveSide drive_side{DriveSide::kInvalid};

    /// @brief Vehicle Chassis Information
    Chassis chassis{};

    /// @brief Vehicle Wheel Information
    Wheel wheel{};

    /// @brief Driver Seatbelt Fastened
    bool seatbelt_fastened{false};

    /// @brief Vehicle Velocity
    units::velocity::meters_per_second_t velocity{0.0};

    /// @brief Vehicle Acceleration
    units::acceleration::meters_per_second_squared_t acceleration{0.0};

    /// @brief Vehicle Deceleration (braking)
    units::acceleration::meters_per_second_squared_t deceleration{0.0};

    /// @brief Vehicle Torque
    units::torque::newton_meter_t torque{0.0};

    /// @brief Vehicle Distance travelled since started
    units::length::kilometer_t distance_travelled{0.0};

    /// @brief Vehicle Steering Wheel Angle
    units::angle::degree_t steering_wheel_angle{0.0};

    /// @brief Vehicle Curvature (meter^-1)
    double curvature{0.0};
};

}  // namespace perception
#endif  /// PERCEPTION_DATATYPES_VEHICLE_DYNAMICS_H