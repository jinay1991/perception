///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/object/datatype/object.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <units.h>

namespace perception
{
namespace object
{
namespace
{
using ::testing::AllOf;
using ::testing::Field;

using namespace units::literals;

template <typename T>
class OperatorsFixtureT : public ::testing::TestWithParam<T>
{
};

template <typename T>
struct TestEqualityParam
{
    // Given
    T lhs;
    T rhs;

    // Then
    bool is_same;
};

TEST(Object, GlobalConstants)
{
    // Then
    EXPECT_EQ(kMaxNumberOfObjects, 10UL);
}

using OperatorsFixture_WithBoundingBox = OperatorsFixtureT<TestEqualityParam<BoundingBox>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithBoundingBox,
    ::testing::Values(
        //                                       lhs           ,           rhs                   , is_same?
        TestEqualityParam<BoundingBox>{{ 1.0,  1.0, 10.0, 10.0}, { 1.0,  1.0, 10.0, 10.0},  true}, // (0)
        TestEqualityParam<BoundingBox>{{10.0,  1.0, 10.0, 10.0}, { 1.0,  1.0, 10.0, 10.0}, false}, // (1)
        TestEqualityParam<BoundingBox>{{ 1.0, 10.0, 10.0, 10.0}, { 1.0,  1.0, 10.0, 10.0}, false}, // (2)
        TestEqualityParam<BoundingBox>{{ 1.0,  1.0, 20.0, 10.0}, { 1.0,  1.0, 10.0, 10.0}, false}, // (3)
        TestEqualityParam<BoundingBox>{{ 1.0,  1.0, 10.0, 20.0}, { 1.0,  1.0, 10.0, 10.0}, false}, // (4)
        TestEqualityParam<BoundingBox>{{ 1.0,  1.0, 10.0, 10.0}, {10.0,  1.0, 10.0, 10.0}, false}, // (5)
        TestEqualityParam<BoundingBox>{{ 1.0,  1.0, 10.0, 10.0}, { 1.0, 10.0, 10.0, 10.0}, false}, // (6)
        TestEqualityParam<BoundingBox>{{ 1.0,  1.0, 10.0, 10.0}, { 1.0,  1.0, 20.0, 10.0}, false}, // (7)
        TestEqualityParam<BoundingBox>{{ 1.0,  1.0, 10.0, 10.0}, { 1.0,  1.0, 10.0, 20.0}, false}  // (8)
));
// clang-format on

TEST_P(OperatorsFixture_WithBoundingBox, Equals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_same = (param.lhs == param.rhs);

    // Then
    EXPECT_EQ(is_same, param.is_same);
}

TEST_P(OperatorsFixture_WithBoundingBox, NotEquals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_not_same = (param.lhs != param.rhs);

    // Then
    EXPECT_NE(is_not_same, param.is_same);
}

TEST(BoundingBox, InitialValues)
{
    // Given
    constexpr BoundingBox bounding_box{1.0, 1.0, 10.0, 10.0};

    // Then
    EXPECT_THAT(bounding_box,
                AllOf(Field(&BoundingBox::x, 1.0),
                      Field(&BoundingBox::y, 1.0),
                      Field(&BoundingBox::width, 10.0),
                      Field(&BoundingBox::height, 10.0)));
}

using OperatorsFixture_WithPosition = OperatorsFixtureT<TestEqualityParam<Position>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithPosition,
    ::testing::Values(
        //                                    lhs          ,           rhs         , is_same?
        TestEqualityParam<Position>{{ 1.0_m, 1.0_m, 10.0_m}, {1.0_m, 1.0_m, 10.0_m},  true}, // (0)
        TestEqualityParam<Position>{{ 2.0_m, 1.0_m, 10.0_m}, {1.0_m, 1.0_m, 10.0_m}, false}, // (1)
        TestEqualityParam<Position>{{ 1.0_m, 2.0_m, 10.0_m}, {1.0_m, 1.0_m, 10.0_m}, false}, // (2)
        TestEqualityParam<Position>{{ 1.0_m, 1.0_m, 20.0_m}, {1.0_m, 1.0_m, 10.0_m}, false}, // (3)
        TestEqualityParam<Position>{{ 1.0_m, 1.0_m, 10.0_m}, {2.0_m, 1.0_m, 10.0_m}, false}, // (4)
        TestEqualityParam<Position>{{ 1.0_m, 1.0_m, 10.0_m}, {1.0_m, 2.0_m, 10.0_m}, false}, // (5)
        TestEqualityParam<Position>{{ 1.0_m, 1.0_m, 10.0_m}, {1.0_m, 1.0_m, 20.0_m}, false}  // (6)
));
// clang-format on

TEST_P(OperatorsFixture_WithPosition, Equals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_same = (param.lhs == param.rhs);

    // Then
    EXPECT_EQ(is_same, param.is_same);
}

TEST_P(OperatorsFixture_WithPosition, NotEquals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_not_same = (param.lhs != param.rhs);

    // Then
    EXPECT_NE(is_not_same, param.is_same);
}

TEST(Position, InitialValues)
{
    // Given
    constexpr Position position{1.0_m, 2.0_m, 10.0_m};

    // Then
    EXPECT_THAT(position, AllOf(Field(&Position::x, 1.0_m), Field(&Position::y, 2.0_m), Field(&Position::z, 10.0_m)));
}
}  // namespace
}  // namespace object
}  // namespace perception
