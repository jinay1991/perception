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

using OperatorsFixture_WithPose = OperatorsFixtureT<TestEqualityParam<Pose>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithPose,
    ::testing::Values(
        //                                    lhs           ,           rhs              , is_same?
        TestEqualityParam<Pose>{{ 1.0_rad, 2.0_rad, 3.0_rad}, {1.0_rad, 2.0_rad, 3.0_rad},  true}, // (0)
        TestEqualityParam<Pose>{{ 5.0_rad, 2.0_rad, 3.0_rad}, {1.0_rad, 2.0_rad, 3.0_rad}, false}, // (1)
        TestEqualityParam<Pose>{{ 1.0_rad, 5.0_rad, 3.0_rad}, {1.0_rad, 2.0_rad, 3.0_rad}, false}, // (2)
        TestEqualityParam<Pose>{{ 1.0_rad, 2.0_rad, 5.0_rad}, {1.0_rad, 2.0_rad, 3.0_rad}, false}, // (3)
        TestEqualityParam<Pose>{{ 1.0_rad, 2.0_rad, 3.0_rad}, {5.0_rad, 2.0_rad, 3.0_rad}, false}, // (4)
        TestEqualityParam<Pose>{{ 1.0_rad, 2.0_rad, 3.0_rad}, {1.0_rad, 5.0_rad, 3.0_rad}, false}, // (5)
        TestEqualityParam<Pose>{{ 1.0_rad, 2.0_rad, 3.0_rad}, {1.0_rad, 2.0_rad, 5.0_rad}, false}  // (6)
));
// clang-format on

TEST_P(OperatorsFixture_WithPose, Equals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_same = (param.lhs == param.rhs);

    // Then
    EXPECT_EQ(is_same, param.is_same);
}

TEST_P(OperatorsFixture_WithPose, NotEquals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_not_same = (param.lhs != param.rhs);

    // Then
    EXPECT_NE(is_not_same, param.is_same);
}

TEST(Pose, InitialValues)
{
    // Given
    constexpr Pose pose{10.0_rad, 40.0_rad, 30.0_rad};

    // Then
    EXPECT_THAT(pose, AllOf(Field(&Pose::yaw, 10.0_rad), Field(&Pose::pitch, 40.0_rad), Field(&Pose::roll, 30.0_rad)));
}

using OperatorsFixture_WithObjectMessage = OperatorsFixtureT<TestEqualityParam<ObjectMessage>>;

constexpr BoundingBox kTestBoundingBox{1.0, 2.0, 10.0, 20.0};
constexpr BoundingBox kDoubleTestBoundingBox{2.0, 4.0, 20.0, 40.0};
constexpr Position kTestPosition{1.0_m, 3.0_m, 5.0_m};
constexpr Position kDoubleTestPosition{2.0_m, 6.0_m, 10.0_m};
constexpr Pose kTestPose{12.0_rad, 43.0_rad, 13.0_rad};
constexpr Pose kDoubleTestPose{24.0_rad, 86_rad, 26_rad};

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithObjectMessage,
    ::testing::Values(
        //                                                                  lhs                                                                                           ,                                                                               rhs                                                               , is_same?
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, { 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo },  true}, // (0)
        TestEqualityParam<ObjectMessage>{{ 2.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, { 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, false}, // (1)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 3.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, { 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, false}, // (2)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 4.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, { 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, false}, // (3)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 3.0_m, 2.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, { 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, false}, // (4)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 3.0_m, 1.0_us, kDoubleTestPosition, kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, { 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, false}, // (5)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kDoubleTestPose  , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, { 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, false}, // (6)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kDoubleTestBoundingBox, ObjectId::kAnimal , LaneId::kEgo }, { 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, false}, // (7)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kBicycle, LaneId::kEgo }, { 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, false}, // (8)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kLeft}, { 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, false}, // (9)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, { 2.0_m, 3.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, false}, // (10)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, { 1.0_m, 3.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, false}, // (11)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, { 1.0_m, 2.0_m, 4.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, false}, // (12)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, { 1.0_m, 2.0_m, 3.0_m, 2.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, false}, // (13)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, { 1.0_m, 2.0_m, 3.0_m, 1.0_us, kDoubleTestPosition, kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, false}, // (14)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, { 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kDoubleTestPose  , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, false}, // (15)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, { 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kDoubleTestBoundingBox, ObjectId::kAnimal , LaneId::kEgo }, false}, // (16)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, { 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kBicycle, LaneId::kEgo }, false}, // (17)
        TestEqualityParam<ObjectMessage>{{ 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kEgo }, { 1.0_m, 2.0_m, 3.0_m, 1.0_us, kTestPosition      , kTestPose        , kTestBoundingBox      , ObjectId::kAnimal , LaneId::kLeft}, false}  // (18)
));
// clang-format on

TEST_P(OperatorsFixture_WithObjectMessage, Equals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_same = (param.lhs == param.rhs);

    // Then
    EXPECT_EQ(is_same, param.is_same);
}

TEST_P(OperatorsFixture_WithObjectMessage, NotEquals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_not_same = (param.lhs != param.rhs);

    // Then
    EXPECT_NE(is_not_same, param.is_same);
}

TEST(ObjectMessage, InitialValues)
{
    // Given
    constexpr ObjectMessage object_message{};

    // Then
    constexpr Position default_position{};
    constexpr Pose default_pose{};
    constexpr BoundingBox default_bounding_box{};
    EXPECT_THAT(object_message,
                AllOf(Field(&ObjectMessage::distance, 0.0_m),
                      Field(&ObjectMessage::longitudinal_distance, 0.0_m),
                      Field(&ObjectMessage::lateral_distance, 0.0_m),
                      Field(&ObjectMessage::time_to_collision, 0.0_us),
                      Field(&ObjectMessage::position, default_position),
                      Field(&ObjectMessage::pose, default_pose),
                      Field(&ObjectMessage::bounding_box, default_bounding_box),
                      Field(&ObjectMessage::id, ObjectId::kInvalid),
                      Field(&ObjectMessage::lane_id, LaneId::kInvalid)));
}
}  // namespace
}  // namespace object
}  // namespace perception
