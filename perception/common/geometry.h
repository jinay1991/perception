///
/// @file
/// @copyright Copyright (C) 2023. MIT License.
///
#ifndef PERCEPTION_COMMON_GEOMETRY_H
#define PERCEPTION_COMMON_GEOMETRY_H

#include <cstdint>
#include <type_traits>
#include <vector>

namespace perception
{

template <typename T, std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
struct GenericEulerAngles
{
    T psi;
    T theta;
    T phi;
};

template <typename T, std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
struct GenericPolarVector2D
{
    T radius;
    T angle_phi;
};

template <typename T, std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
struct GenericCartesianVector2D
{
    T x;
    T y;
};

template <typename T, std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
struct GenericCartesianVector3D
{
    T x;
    T y;
    T z;
};

template <typename T, std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
struct GenericFrenetVector2D
{
    T s;
    T d;
};

template <typename T, std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
struct GenericRectangle
{
    T width;
    T height;
};

template <typename T, std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
struct GenericOrientedRectangle
{
    GenericCartesianVector2D<T> center;
    GenericRectangle<T> dimensions;
};

template <typename T, std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
struct GenericCartesianPose2D
{
    GenericCartesianVector2D<T> position;
    T orientation;
};

template <typename T, std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
struct GenericCartesianPose3D
{
    GenericCartesianVector3D<T> position;
    GenericEulerAngles<T> orientation;
};

template <typename T, std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
struct GenericFrenetPose2D
{
    GenericFrenetVector2D<T> position;
    T orientation;
};

template <typename T, std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
struct GenericQaternion
{
    T scalar;
    GenericCartesianVector3D<T> vector;
};

template <typename T>
using GenericCartesianPoint2D = GenericCartesianVector2D<T>;

template <typename T>
using GenericCartesianPoint3D = GenericCartesianVector3D<T>;

template <typename T>
using GenericPolarPoint2D = GenericPolarVector2D<T>;

template <typename T>
using GenericCurve = std::vector<T>;

template <typename T>
using GenericPolyline2D = GenericCurve<GenericCartesianPoint2D<T>>;

template <typename T>
using GenericPolyline3D = GenericCurve<GenericCartesianPoint3D<T>>;

}  // namespace perception

#endif  /// PERCEPTION_COMMON_GEOMETRY_H
