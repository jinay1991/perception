///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DATATYPES_DRIVER_H
#define PERCEPTION_DATATYPES_DRIVER_H

#include "perception/driver/datatype/driver_camera_message.h"
#include "perception/driver/datatype/driver_message.h"

#include <units.h>

#include <chrono>

namespace perception
{
namespace driver
{

using namespace units::literals;
using namespace std::chrono_literals;

/// @brief Maximum eye blink rate (hertz)
static constexpr units::frequency::hertz_t kMinEyeBlinkRate{0.15};

/// @brief Maximum eye blink rate (hertz)
static constexpr units::frequency::hertz_t kMaxEyeBlinkRate{0.5};

/// @brief Maximum eye lid opening (mm)
static constexpr units::length::millimeter_t kMaxEyeLidOpening{10.0};

/// @brief Minimum eye lid opening (mm)
static constexpr units::length::millimeter_t kMinEyeLidOpening{1.0};

/// @brief Maximum possible yaw angle for human head in range (rad). Range between -80 to 75 deg
static constexpr units::angle::radian_t kMinHeadPoseYaw = units::angle::degree_t{-80.0};

/// @brief Maximum possible yaw angle for human head in range (rad). Range between -80 to 75 deg
static constexpr units::angle::radian_t kMaxHeadPoseYaw = units::angle::degree_t{75.0};

/// @brief Maximum possible pitch angle for human head in range (rad). Range between -60 to 70 deg
static constexpr units::angle::radian_t kMinHeadPosePitch = units::angle::degree_t{-60.0};

/// @brief Maximum possible pitch angle for human head in range (rad). Range between -60 to 70 deg
static constexpr units::angle::radian_t kMaxHeadPosePitch = units::angle::degree_t{70.0};

/// @brief Maximum possible roll angle for human head in range (rad). Range between -40 to 36 deg
static constexpr units::angle::radian_t kMinHeadPoseRoll = units::angle::degree_t{-40.0};

/// @brief Maximum possible roll angle for human head in range (rad). Range between -40 to 36 deg
static constexpr units::angle::radian_t kMaxHeadPoseRoll = units::angle::degree_t{36.0};

/// @brief Maximum duration till which eye state is being observed (ms)
static constexpr std::chrono::milliseconds kMaxEyeStateObservationDuration{5min};

/// @brief Max assumed cycle duration (ms)
static constexpr std::chrono::milliseconds kMaxCycleDuration{40UL};

/// @brief Maximum allowed longterm storage size (i.e. max samples to store)
static constexpr std::size_t kObservationStorageSize{kMaxEyeStateObservationDuration / kMaxCycleDuration};

/// @brief Minimum (ego) velocity required for active Driver Monitoring (NCAP Requirement)
static constexpr units::velocity::meters_per_second_t kMinVelocity{10_kph};

/// @brief Maximum (ego) velocity required for active Driver Monitoring (NCAP Requirement)
static constexpr units::velocity::meters_per_second_t kMaxVelocity{200_kph};

}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DATATYPES_DRIVER_H
