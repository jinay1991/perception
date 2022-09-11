///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DATATYPES_DRIVER_CAMERA_MESSAGE_H
#define PERCEPTION_DATATYPES_DRIVER_CAMERA_MESSAGE_H

#include <units.h>

#include <chrono>

namespace perception
{
namespace driver
{

/// @brief Driver Face Tracking Information
struct FaceTracking
{
    /// @brief Driver Face Visibility
    bool face_visible{false};

    /// @brief Driver Eye visibility
    bool eye_visible{false};

    /// @brief Driver Eye lid opening (mm)
    units::length::millimeter_t eye_lid_opening{0.0};

    /// @brief Driver Eye blink rate (hertz)
    units::frequency::hertz_t eye_blink_rate{0.0};
};

/// @brief Driver Gaze Tracking Information
struct GazeTracking
{
    /// @brief Driver Gaze Tracking Yaw (rad) - Left/Right Movements
    units::angle::radian_t yaw{0.0};

    /// @brief Driver Gaze Tracking Pitch (rad) - Up/Down Movements
    units::angle::radian_t pitch{0.0};

    /// @brief Driver Gaze Tracking Roll (rad) - Diagonal Left/Right Movements
    units::angle::radian_t roll{0.0};
};

/// @brief Driver Head Tracking Information
struct HeadTracking
{
    /// @brief Driver Head Tracking Yaw (rad) - Left/Right Movements
    units::angle::radian_t yaw{0.0};

    /// @brief Driver Head Tracking Pitch (rad) - Up/Down Movements
    units::angle::radian_t pitch{0.0};

    /// @brief Driver Head Tracking Roll (rad) - Diagonal/Tilt Left/Right Movements
    units::angle::radian_t roll{0.0};
};

/// @brief Driver Camera System Information
struct DriverCameraMessage
{
    /// @brief Time Point for captured data
    std::chrono::system_clock::time_point time_point{};

    /// @brief Head Tracking Information
    HeadTracking head_tracking{};

    /// @brief Face Tracking Information
    FaceTracking face_tracking{};

    /// @brief Gaze Tracking Information
    GazeTracking gaze_tracking{};
};

/// @brief Equality operator for elementwise comparision for FaceTracking
///
/// @param lhs [in] - lvalue (FaceTracking)
/// @param rhs [in] - rvalue (FaceTracking)
///
/// @return True if (lhs == rhs), otherwise false.
constexpr bool operator==(const FaceTracking& lhs, const FaceTracking& rhs) noexcept
{
    return ((lhs.face_visible == rhs.face_visible) && (lhs.eye_visible == rhs.eye_visible) &&
            (lhs.eye_lid_opening == rhs.eye_lid_opening) && (lhs.eye_blink_rate == rhs.eye_blink_rate));
}

/// @brief Inequality operator for elementwise comparision for FaceTracking
///
/// @param lhs [in] - lvalue (FaceTracking)
/// @param rhs [in] - rvalue (FaceTracking)
///
/// @return True if (lhs != rhs), otherwise false.
constexpr bool operator!=(const FaceTracking& lhs, const FaceTracking& rhs) noexcept
{
    return !(lhs == rhs);
}

/// @brief Equality operator for elementwise comparision for GazeTracking
///
/// @param lhs [in] - lvalue (GazeTracking)
/// @param rhs [in] - rvalue (GazeTracking)
///
/// @return True if (lhs == rhs), otherwise false.
constexpr bool operator==(const GazeTracking& lhs, const GazeTracking& rhs) noexcept
{
    return ((lhs.yaw == rhs.yaw) && (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll));
}

/// @brief Inequality operator for elementwise comparision for GazeTracking
///
/// @param lhs [in] - lvalue (GazeTracking)
/// @param rhs [in] - rvalue (GazeTracking)
///
/// @return True if (lhs != rhs), otherwise false.
constexpr bool operator!=(const GazeTracking& lhs, const GazeTracking& rhs) noexcept
{
    return !(lhs == rhs);
}

/// @brief Equality operator for elementwise comparision for GazeTracking
///
/// @param lhs [in] - lvalue (HeadTracking)
/// @param rhs [in] - rvalue (HeadTracking)
///
/// @return True if (lhs == rhs), otherwise false.
constexpr bool operator==(const HeadTracking& lhs, const HeadTracking& rhs) noexcept
{
    return ((lhs.yaw == rhs.yaw) && (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll));
}

/// @brief Inequality operator for elementwise comparision for HeadTracking
///
/// @param lhs [in] - lvalue (HeadTracking)
/// @param rhs [in] - rvalue (HeadTracking)
///
/// @return True if (lhs != rhs), otherwise false.
constexpr bool operator!=(const HeadTracking& lhs, const HeadTracking& rhs) noexcept
{
    return !(lhs == rhs);
}

/// @brief Equality operator for elementwise comparision for DriverCameraMessage
///
/// @param lhs [in] - lvalue (DriverCameraMessage)
/// @param rhs [in] - rvalue (DriverCameraMessage)
///
/// @return True if (lhs == rhs), otherwise false.
constexpr bool operator==(const DriverCameraMessage& lhs, const DriverCameraMessage& rhs) noexcept
{
    return ((lhs.time_point == rhs.time_point) && (lhs.head_tracking == rhs.head_tracking) &&
            (lhs.face_tracking == rhs.face_tracking) && (lhs.gaze_tracking == rhs.gaze_tracking));
}

/// @brief Inequality operator for elementwise comparision for DriverCameraMessage
///
/// @param lhs [in] - lvalue (DriverCameraMessage)
/// @param rhs [in] - rvalue (DriverCameraMessage)
///
/// @return True if (lhs != rhs), otherwise false.
constexpr bool operator!=(const DriverCameraMessage& lhs, const DriverCameraMessage& rhs) noexcept
{
    return !(lhs == rhs);
}
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DATATYPES_DRIVER_CAMERA_MESSAGE_H
