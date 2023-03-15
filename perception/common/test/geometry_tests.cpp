///
/// @file
/// @copyright Copyright (C) 2023. MIT License.
///
#include "perception/common/geometry.h"

#include <gtest/gtest.h>

namespace perception
{
namespace
{

template <typename T>
using MemoryFootprintFixture = ::testing::Test;

using UnderlyingTypes = ::testing::Types<float, double>;
TYPED_TEST_SUITE(MemoryFootprintFixture, UnderlyingTypes);

TYPED_TEST(MemoryFootprintFixture, GenericCartesianVector2D)
{
    EXPECT_EQ(sizeof(GenericCartesianVector2D<TypeParam>), 2 * sizeof(TypeParam));
}

TYPED_TEST(MemoryFootprintFixture, GenericCartesianVector3D)
{
    EXPECT_EQ(sizeof(GenericCartesianVector3D<TypeParam>), 3 * sizeof(TypeParam));
}

TYPED_TEST(MemoryFootprintFixture, GenericEulerAngles)
{
    EXPECT_EQ(sizeof(GenericEulerAngles<TypeParam>), 3 * sizeof(TypeParam));
}

TYPED_TEST(MemoryFootprintFixture, GenericPolarVector2D)
{
    EXPECT_EQ(sizeof(GenericPolarVector2D<TypeParam>), 2 * sizeof(TypeParam));
}

TYPED_TEST(MemoryFootprintFixture, GenericFrenetVector2D)
{
    EXPECT_EQ(sizeof(GenericFrenetVector2D<TypeParam>), 2 * sizeof(TypeParam));
}

TYPED_TEST(MemoryFootprintFixture, GenericRectangle)
{
    EXPECT_EQ(sizeof(GenericRectangle<TypeParam>), 2 * sizeof(TypeParam));
}

TYPED_TEST(MemoryFootprintFixture, GenericOrientedRectangle)
{
    EXPECT_EQ(sizeof(GenericOrientedRectangle<TypeParam>), 4 * sizeof(TypeParam));
}

TYPED_TEST(MemoryFootprintFixture, GenericCartesianPose2D)
{
    EXPECT_EQ(sizeof(GenericCartesianPose2D<TypeParam>), 3 * sizeof(TypeParam));
}

TYPED_TEST(MemoryFootprintFixture, GenericCartesianPose3D)
{
    EXPECT_EQ(sizeof(GenericCartesianPose3D<TypeParam>), 6 * sizeof(TypeParam));
}

TYPED_TEST(MemoryFootprintFixture, GenericFrenetPose2D)
{
    EXPECT_EQ(sizeof(GenericFrenetPose2D<TypeParam>), 3 * sizeof(TypeParam));
}

TYPED_TEST(MemoryFootprintFixture, GenericQaternion)
{
    EXPECT_EQ(sizeof(GenericQaternion<TypeParam>), 4 * sizeof(TypeParam));
}
}  // namespace
}  // namespace perception
