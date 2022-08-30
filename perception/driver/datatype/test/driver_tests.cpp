///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/datatype/driver.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
using ::testing::AllOf;
using ::testing::Field;

constexpr std::chrono::system_clock::time_point kTimePoint{10ms};

TEST(Driver, GlobalConstants)
{
    // Then
    EXPECT_EQ(kMinEyeBlinkRate, 0.15_Hz);
    EXPECT_EQ(kMaxEyeBlinkRate, 0.5_Hz);
    EXPECT_EQ(kMaxEyeLidOpening, 10.0_mm);
    EXPECT_EQ(kMinEyeLidOpening, 1.0_mm);
    EXPECT_EQ(kMinHeadPoseYaw, -80_deg);
    EXPECT_EQ(kMaxHeadPoseYaw, 75_deg);
    EXPECT_EQ(kMinHeadPosePitch, -60_deg);
    EXPECT_EQ(kMaxHeadPosePitch, 70_deg);
    EXPECT_EQ(kMinHeadPoseRoll, -40_deg);
    EXPECT_EQ(kMaxHeadPoseRoll, 36.0_deg);
    EXPECT_EQ(kMaxEyeStateObservationDuration, 5min);
}

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

using OperatorsFixture_WithFaceTracking = OperatorsFixtureT<TestEqualityParam<FaceTracking>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithFaceTracking,
    ::testing::Values(
        //                                       lhs                   ,           rhs                  , is_same?
        TestEqualityParam<FaceTracking>{{ true,  true, 10.0_mm, 1.0_Hz}, { true,  true, 10.0_mm, 1.0_Hz},  true}, // (0)
        TestEqualityParam<FaceTracking>{{ true,  true, 10.0_mm, 1.0_Hz}, {false,  true, 10.0_mm, 1.0_Hz}, false}, // (1)
        TestEqualityParam<FaceTracking>{{ true,  true, 10.0_mm, 1.0_Hz}, { true, false, 10.0_mm, 1.0_Hz}, false}, // (2)
        TestEqualityParam<FaceTracking>{{ true,  true, 10.0_mm, 1.0_Hz}, { true,  true, 20.0_mm, 1.0_Hz}, false}, // (3)
        TestEqualityParam<FaceTracking>{{ true,  true, 10.0_mm, 1.0_Hz}, { true,  true, 10.0_mm, 2.0_Hz}, false}, // (4)
        TestEqualityParam<FaceTracking>{{false,  true, 10.0_mm, 1.0_Hz}, { true,  true, 10.0_mm, 1.0_Hz}, false}, // (5)
        TestEqualityParam<FaceTracking>{{ true, false, 10.0_mm, 1.0_Hz}, { true,  true, 10.0_mm, 1.0_Hz}, false}, // (6)
        TestEqualityParam<FaceTracking>{{ true,  true, 20.0_mm, 1.0_Hz}, { true,  true, 10.0_mm, 1.0_Hz}, false}, // (7)
        TestEqualityParam<FaceTracking>{{ true,  true, 10.0_mm, 2.0_Hz}, { true,  true, 10.0_mm, 1.0_Hz}, false}  // (8)
));
// clang-format on

TEST_P(OperatorsFixture_WithFaceTracking, Equals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_same = (param.lhs == param.rhs);

    // Then
    EXPECT_EQ(is_same, param.is_same);
}

TEST_P(OperatorsFixture_WithFaceTracking, NotEquals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_not_same = (param.lhs != param.rhs);

    // Then
    EXPECT_NE(is_not_same, param.is_same);
}

TEST(FaceTracking, InitialValues)
{
    // Given
    constexpr FaceTracking face_tracking{};

    // Then
    EXPECT_THAT(face_tracking,
                AllOf(Field(&FaceTracking::face_visible, false),
                      Field(&FaceTracking::eye_visible, false),
                      Field(&FaceTracking::eye_lid_opening, 0.0_mm),
                      Field(&FaceTracking::eye_blink_rate, 0.0_Hz)));
}

using OperatorsFixture_WithGazeTracking = OperatorsFixtureT<TestEqualityParam<GazeTracking>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithGazeTracking,
    ::testing::Values(
        //                                       lhs                  ,          rhs                  , is_same?
        TestEqualityParam<GazeTracking>{{10.0_rad, 10.0_rad, 10.0_rad}, {10.0_rad, 10.0_rad, 10.0_rad},  true}, // (0)
        TestEqualityParam<GazeTracking>{{10.0_rad, 10.0_rad, 10.0_rad}, { 2.0_rad, 10.0_rad, 10.0_rad}, false}, // (1)
        TestEqualityParam<GazeTracking>{{10.0_rad, 10.0_rad, 10.0_rad}, {10.0_rad,  2.0_rad, 10.0_rad}, false}, // (2)
        TestEqualityParam<GazeTracking>{{10.0_rad, 10.0_rad, 10.0_rad}, {10.0_rad, 10.0_rad,  2.0_rad}, false}, // (3)
        TestEqualityParam<GazeTracking>{{ 2.0_rad, 10.0_rad, 10.0_rad}, {10.0_rad, 10.0_rad, 10.0_rad}, false}, // (4)
        TestEqualityParam<GazeTracking>{{10.0_rad,  2.0_rad, 10.0_rad}, {10.0_rad, 10.0_rad, 10.0_rad}, false}, // (5)
        TestEqualityParam<GazeTracking>{{10.0_rad, 10.0_rad,  2.0_rad}, {10.0_rad, 10.0_rad, 10.0_rad}, false}  // (6)
));
// clang-format on

TEST_P(OperatorsFixture_WithGazeTracking, Equals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_same = (param.lhs == param.rhs);

    // Then
    EXPECT_EQ(is_same, param.is_same);
}

TEST_P(OperatorsFixture_WithGazeTracking, NotEquals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_not_same = (param.lhs != param.rhs);

    // Then
    EXPECT_NE(is_not_same, param.is_same);
}

TEST(GazeTracking, InitialValues)
{
    // Given
    constexpr GazeTracking gaze_tracking{};

    // Then
    EXPECT_THAT(gaze_tracking,
                AllOf(Field(&GazeTracking::yaw, 0.0_rad),
                      Field(&GazeTracking::pitch, 0.0_rad),
                      Field(&GazeTracking::roll, 0.0_rad)));
}

using OperatorsFixture_WithHeadTracking = OperatorsFixtureT<TestEqualityParam<HeadTracking>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithHeadTracking,
    ::testing::Values(
        //                                       lhs                  ,          rhs                  , is_same?
        TestEqualityParam<HeadTracking>{{10.0_rad, 10.0_rad, 10.0_rad}, {10.0_rad, 10.0_rad, 10.0_rad},  true}, // (0)
        TestEqualityParam<HeadTracking>{{10.0_rad, 10.0_rad, 10.0_rad}, { 2.0_rad, 10.0_rad, 10.0_rad}, false}, // (1)
        TestEqualityParam<HeadTracking>{{10.0_rad, 10.0_rad, 10.0_rad}, {10.0_rad,  2.0_rad, 10.0_rad}, false}, // (2)
        TestEqualityParam<HeadTracking>{{10.0_rad, 10.0_rad, 10.0_rad}, {10.0_rad, 10.0_rad,  2.0_rad}, false}, // (3)
        TestEqualityParam<HeadTracking>{{ 2.0_rad, 10.0_rad, 10.0_rad}, {10.0_rad, 10.0_rad, 10.0_rad}, false}, // (4)
        TestEqualityParam<HeadTracking>{{10.0_rad,  2.0_rad, 10.0_rad}, {10.0_rad, 10.0_rad, 10.0_rad}, false}, // (5)
        TestEqualityParam<HeadTracking>{{10.0_rad, 10.0_rad,  2.0_rad}, {10.0_rad, 10.0_rad, 10.0_rad}, false}  // (6)
));
// clang-format on

TEST_P(OperatorsFixture_WithHeadTracking, Equals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_same = (param.lhs == param.rhs);

    // Then
    EXPECT_EQ(is_same, param.is_same);
}

TEST_P(OperatorsFixture_WithHeadTracking, NotEquals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_not_same = (param.lhs != param.rhs);

    // Then
    EXPECT_NE(is_not_same, param.is_same);
}

TEST(HeadTracking, InitialValues)
{
    // Given
    constexpr HeadTracking head_tracking{};

    // Then
    EXPECT_THAT(head_tracking,
                AllOf(Field(&HeadTracking::yaw, 0.0_rad),
                      Field(&HeadTracking::pitch, 0.0_rad),
                      Field(&HeadTracking::roll, 0.0_rad)));
}

using OperatorsFixture_WithFatigueMessage = OperatorsFixtureT<TestEqualityParam<FatigueMessage>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithFatigueMessage,
    ::testing::Values(
        //                                              lhs                              ,          rhs                                   , is_same?
        TestEqualityParam<FatigueMessage>{{      kTimePoint,  FatigueState::kAwake, 10.0}, {      kTimePoint,  FatigueState::kAwake, 10.0},  true},// (0)
        TestEqualityParam<FatigueMessage>{{      kTimePoint,  FatigueState::kAwake, 10.0}, {kTimePoint + 1ms,  FatigueState::kAwake, 10.0}, false},// (1)
        TestEqualityParam<FatigueMessage>{{      kTimePoint,  FatigueState::kAwake, 10.0}, {      kTimePoint, FatigueState::kDrowsy, 10.0}, false},// (2)
        TestEqualityParam<FatigueMessage>{{      kTimePoint,  FatigueState::kAwake, 10.0}, {      kTimePoint,  FatigueState::kAwake,  2.0}, false},// (3)
        TestEqualityParam<FatigueMessage>{{kTimePoint + 1ms,  FatigueState::kAwake, 10.0}, {      kTimePoint,  FatigueState::kAwake, 10.0}, false},// (4)
        TestEqualityParam<FatigueMessage>{{      kTimePoint, FatigueState::kDrowsy, 10.0}, {      kTimePoint,  FatigueState::kAwake, 10.0}, false},// (5)
        TestEqualityParam<FatigueMessage>{{      kTimePoint,  FatigueState::kAwake,  2.0}, {      kTimePoint,  FatigueState::kAwake, 10.0}, false} // (6)
));
// clang-format on

TEST_P(OperatorsFixture_WithFatigueMessage, Equals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_same = (param.lhs == param.rhs);

    // Then
    EXPECT_EQ(is_same, param.is_same);
}

TEST_P(OperatorsFixture_WithFatigueMessage, NotEquals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_not_same = (param.lhs != param.rhs);

    // Then
    EXPECT_NE(is_not_same, param.is_same);
}

TEST(FatigueMessage, InitialValues)
{
    // Given
    constexpr FatigueMessage fatigue_message{};

    // Then
    EXPECT_THAT(fatigue_message,
                AllOf(Field(&FatigueMessage::state, FatigueState::kInvalid), Field(&FatigueMessage::confidence, 0.0)));
}

using OperatorsFixture_WithDistractionMessage = OperatorsFixtureT<TestEqualityParam<DistractionMessage>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithDistractionMessage,
    ::testing::Values(
        //                                              lhs                                               ,          rhs                                                , is_same?
        TestEqualityParam<DistractionMessage>{{      kTimePoint,    DistractionState::kNotDistracted, 0.0}, {      kTimePoint,    DistractionState::kNotDistracted, 0.0},  true}, // (0)
        TestEqualityParam<DistractionMessage>{{      kTimePoint,    DistractionState::kNotDistracted, 0.0}, {kTimePoint + 1ms,    DistractionState::kNotDistracted, 0.0}, false}, // (1)
        TestEqualityParam<DistractionMessage>{{      kTimePoint,    DistractionState::kNotDistracted, 0.0}, {      kTimePoint,    DistractionState::kNotDistracted, 1.0}, false}, // (2)
        TestEqualityParam<DistractionMessage>{{      kTimePoint,    DistractionState::kNotDistracted, 0.0}, {      kTimePoint,    DistractionState::kDistracted   , 0.0}, false}, // (3)
        TestEqualityParam<DistractionMessage>{{kTimePoint + 1ms,    DistractionState::kNotDistracted, 0.0}, {      kTimePoint,    DistractionState::kNotDistracted, 0.0}, false}, // (4)
        TestEqualityParam<DistractionMessage>{{      kTimePoint,    DistractionState::kNotDistracted, 1.0}, {      kTimePoint,    DistractionState::kNotDistracted, 0.0}, false}, // (5)
        TestEqualityParam<DistractionMessage>{{      kTimePoint,       DistractionState::kDistracted, 0.0}, {      kTimePoint,    DistractionState::kNotDistracted, 0.0}, false}  // (6)

));
// clang-format on

TEST_P(OperatorsFixture_WithDistractionMessage, Equals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_same = (param.lhs == param.rhs);

    // Then
    EXPECT_EQ(is_same, param.is_same);
}

TEST_P(OperatorsFixture_WithDistractionMessage, NotEquals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_not_same = (param.lhs != param.rhs);

    // Then
    EXPECT_NE(is_not_same, param.is_same);
}

TEST(DistractionMessage, InitialValues)
{
    // Given
    constexpr DistractionMessage distraction_message{};

    // Then
    EXPECT_THAT(distraction_message,
                AllOf(Field(&DistractionMessage::state, DistractionState::kInvalid),
                      Field(&DistractionMessage::confidence, 0.0)));
}

using OperatorsFixture_WithActivityMessage = OperatorsFixtureT<TestEqualityParam<ActivityMessage>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithActivityMessage,
    ::testing::Values(
        //                                              lhs                                         ,          rhs                                             , is_same?
        TestEqualityParam<ActivityMessage>{{      kTimePoint,    ActivityState::kTexting      , 0.0}, {      kTimePoint,    ActivityState::kTexting      , 0.0},  true}, // (0)
        TestEqualityParam<ActivityMessage>{{      kTimePoint,    ActivityState::kTexting      , 0.0}, {kTimePoint + 1ms,    ActivityState::kTexting      , 0.0}, false}, // (1)
        TestEqualityParam<ActivityMessage>{{      kTimePoint,    ActivityState::kTexting      , 0.0}, {      kTimePoint,    ActivityState::kTexting      , 1.0}, false}, // (2)
        TestEqualityParam<ActivityMessage>{{      kTimePoint,    ActivityState::kTexting      , 0.0}, {      kTimePoint,    ActivityState::kNotAvailable , 0.0}, false}, // (3)
        TestEqualityParam<ActivityMessage>{{      kTimePoint,    ActivityState::kTexting      , 0.0}, {      kTimePoint,    ActivityState::kCalling      , 0.0}, false}, // (4)
        TestEqualityParam<ActivityMessage>{{      kTimePoint,    ActivityState::kTexting      , 0.0}, {      kTimePoint,    ActivityState::kHandsOnWheel , 0.0}, false}, // (5)
        TestEqualityParam<ActivityMessage>{{      kTimePoint,    ActivityState::kTexting      , 0.0}, {      kTimePoint,    ActivityState::kHandsOffWheel, 0.0}, false}, // (6)
        TestEqualityParam<ActivityMessage>{{      kTimePoint,    ActivityState::kTexting      , 0.0}, {      kTimePoint,    ActivityState::kInvalid      , 0.0}, false}, // (7)
        TestEqualityParam<ActivityMessage>{{kTimePoint + 1ms,    ActivityState::kTexting      , 0.0}, {      kTimePoint,    ActivityState::kTexting      , 0.0}, false}, // (8)
        TestEqualityParam<ActivityMessage>{{      kTimePoint,    ActivityState::kTexting      , 1.0}, {      kTimePoint,    ActivityState::kTexting      , 0.0}, false}, // (9)
        TestEqualityParam<ActivityMessage>{{      kTimePoint,    ActivityState::kNotAvailable , 0.0}, {      kTimePoint,    ActivityState::kTexting      , 0.0}, false}, // (10)
        TestEqualityParam<ActivityMessage>{{      kTimePoint,    ActivityState::kCalling      , 0.0}, {      kTimePoint,    ActivityState::kTexting      , 0.0}, false}, // (11)
        TestEqualityParam<ActivityMessage>{{      kTimePoint,    ActivityState::kHandsOnWheel , 0.0}, {      kTimePoint,    ActivityState::kTexting      , 0.0}, false}, // (12)
        TestEqualityParam<ActivityMessage>{{      kTimePoint,    ActivityState::kHandsOffWheel, 0.0}, {      kTimePoint,    ActivityState::kTexting      , 0.0}, false}, // (13)
        TestEqualityParam<ActivityMessage>{{      kTimePoint,    ActivityState::kInvalid      , 0.0}, {      kTimePoint,    ActivityState::kTexting      , 0.0}, false}  // (14)
));
// clang-format on

TEST_P(OperatorsFixture_WithActivityMessage, Equals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_same = (param.lhs == param.rhs);

    // Then
    EXPECT_EQ(is_same, param.is_same);
}

TEST_P(OperatorsFixture_WithActivityMessage, NotEquals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_not_same = (param.lhs != param.rhs);

    // Then
    EXPECT_NE(is_not_same, param.is_same);
}

TEST(ActivityMessage, InitialValues)
{
    // Given
    constexpr ActivityMessage activity_message{};

    // Then
    EXPECT_THAT(
        activity_message,
        AllOf(Field(&ActivityMessage::state, ActivityState::kInvalid), Field(&ActivityMessage::confidence, 0.0)));
}

using OperatorsFixture_WithResponsivenessMessage = OperatorsFixtureT<TestEqualityParam<ResponsivenessMessage>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithResponsivenessMessage,
    ::testing::Values(
        //                                                          lhs                                      ,                     rhs                                     , is_same?
        TestEqualityParam<ResponsivenessMessage>{{      kTimePoint, ResponsivenessState::kNotAvailable , 0.0}, {      kTimePoint, ResponsivenessState::kNotAvailable , 0.0},  true}, // (0)
        TestEqualityParam<ResponsivenessMessage>{{      kTimePoint, ResponsivenessState::kNotAvailable , 0.0}, {kTimePoint + 1ms, ResponsivenessState::kNotAvailable , 0.0}, false}, // (1)
        TestEqualityParam<ResponsivenessMessage>{{      kTimePoint, ResponsivenessState::kNotAvailable , 0.0}, {      kTimePoint, ResponsivenessState::kNonResponsive, 0.0}, false}, // (2)
        TestEqualityParam<ResponsivenessMessage>{{      kTimePoint, ResponsivenessState::kNotAvailable , 0.0}, {      kTimePoint, ResponsivenessState::kResponsive   , 0.0}, false}, // (3)
        TestEqualityParam<ResponsivenessMessage>{{      kTimePoint, ResponsivenessState::kNotAvailable , 0.0}, {      kTimePoint, ResponsivenessState::kInvalid      , 0.0}, false}, // (4)
        TestEqualityParam<ResponsivenessMessage>{{      kTimePoint, ResponsivenessState::kNotAvailable , 0.0}, {      kTimePoint, ResponsivenessState::kNotAvailable , 1.0}, false}, // (5)
        TestEqualityParam<ResponsivenessMessage>{{kTimePoint + 1ms, ResponsivenessState::kNotAvailable , 0.0}, {      kTimePoint, ResponsivenessState::kNotAvailable , 0.0}, false}, // (6)
        TestEqualityParam<ResponsivenessMessage>{{      kTimePoint, ResponsivenessState::kNonResponsive, 0.0}, {      kTimePoint, ResponsivenessState::kNotAvailable , 0.0}, false}, // (7)
        TestEqualityParam<ResponsivenessMessage>{{      kTimePoint, ResponsivenessState::kResponsive   , 0.0}, {      kTimePoint, ResponsivenessState::kNotAvailable , 0.0}, false}, // (8)
        TestEqualityParam<ResponsivenessMessage>{{      kTimePoint, ResponsivenessState::kInvalid      , 0.0}, {      kTimePoint, ResponsivenessState::kNotAvailable , 0.0}, false}, // (9)
        TestEqualityParam<ResponsivenessMessage>{{      kTimePoint, ResponsivenessState::kNotAvailable , 1.0}, {      kTimePoint, ResponsivenessState::kNotAvailable , 0.0}, false}  // (10)
));
// clang-format on

TEST_P(OperatorsFixture_WithResponsivenessMessage, Equals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_same = (param.lhs == param.rhs);

    // Then
    EXPECT_EQ(is_same, param.is_same);
}

TEST_P(OperatorsFixture_WithResponsivenessMessage, NotEquals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_not_same = (param.lhs != param.rhs);

    // Then
    EXPECT_NE(is_not_same, param.is_same);
}

TEST(ResponsivenessMessage, InitialValues)
{
    // Given
    constexpr ResponsivenessMessage responsiveness_message{};

    // Then
    EXPECT_THAT(responsiveness_message,
                AllOf(Field(&ResponsivenessMessage::state, ResponsivenessState::kInvalid),
                      Field(&ResponsivenessMessage::confidence, 0.0)));
}

using OperatorsFixture_WithDriverMessage = OperatorsFixtureT<TestEqualityParam<DriverMessage>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithDriverMessage,
    ::testing::Values(
        //                                                                                                                                                                                                      lhs                                                                                                                ,                                                                                                                              rhs                                                                                                                                                      , is_same?
        TestEqualityParam<DriverMessage>{{      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, {      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}},  true}, // (0)
        TestEqualityParam<DriverMessage>{{      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, {      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kDrowsy, 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, false}, // (1)
        TestEqualityParam<DriverMessage>{{      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, {      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kNotDistracted, 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, false}, // (2)
        TestEqualityParam<DriverMessage>{{      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, {      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kCalling, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, false}, // (3)
        TestEqualityParam<DriverMessage>{{      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, {      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kResponsive  , 1.0}}, false}, // (4)
        TestEqualityParam<DriverMessage>{{      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, {kTimePoint + 2ms, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, false}, // (5)
        TestEqualityParam<DriverMessage>{{      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kDrowsy, 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, {      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, false}, // (6)
        TestEqualityParam<DriverMessage>{{      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kNotDistracted, 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, {      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, false}, // (7)
        TestEqualityParam<DriverMessage>{{      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kCalling, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, {      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, false}, // (8)
        TestEqualityParam<DriverMessage>{{      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kResponsive  , 1.0}}, {      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, false}, // (9)
        TestEqualityParam<DriverMessage>{{kTimePoint + 2ms, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, {      kTimePoint, FatigueMessage{kTimePoint, FatigueState::kAwake , 1.0}, DistractionMessage{kTimePoint, DistractionState::kDistracted   , 1.0}, ActivityMessage{kTimePoint, ActivityState::kTexting, 1.0}, ResponsivenessMessage{kTimePoint, ResponsivenessState::kNotAvailable, 1.0}}, false}  // (10)
));
// clang-format on

TEST_P(OperatorsFixture_WithDriverMessage, Equals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_same = (param.lhs == param.rhs);

    // Then
    EXPECT_EQ(is_same, param.is_same);
}

TEST_P(OperatorsFixture_WithDriverMessage, NotEquals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_not_same = (param.lhs != param.rhs);

    // Then
    EXPECT_NE(is_not_same, param.is_same);
}

TEST(DriverMessage, InitialValues)
{
    // Given
    constexpr DriverMessage driver_message{};
    constexpr FatigueMessage default_fatigue{};
    constexpr DistractionMessage default_distraction{};
    constexpr ActivityMessage default_activity{};

    // Then
    EXPECT_THAT(driver_message,
                AllOf(Field(&DriverMessage::fatigue, default_fatigue),
                      Field(&DriverMessage::distraction, default_distraction),
                      Field(&DriverMessage::activity, default_activity)));
}

using OperatorsFixture_WithDriverCameraMessage = OperatorsFixtureT<TestEqualityParam<DriverCameraMessage>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithDriverCameraMessage,
    ::testing::Values(
        //                                                                                                                                               lhs                                        ,                                                                                                              rhs                                     , is_same?
        TestEqualityParam<DriverCameraMessage>{{      kTimePoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, {      kTimePoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}},  true}, // (0)
        TestEqualityParam<DriverCameraMessage>{{      kTimePoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, {kTimePoint + 1ms, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, false}, // (1)
        TestEqualityParam<DriverCameraMessage>{{      kTimePoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, {      kTimePoint, HeadTracking{ 2.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, false}, // (2)
        TestEqualityParam<DriverCameraMessage>{{      kTimePoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, {      kTimePoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true,  2.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, false}, // (3)
        TestEqualityParam<DriverCameraMessage>{{      kTimePoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, {      kTimePoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad,  2.0_rad, 10.0_rad}}, false}, // (4)
        TestEqualityParam<DriverCameraMessage>{{kTimePoint + 1ms, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, {      kTimePoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, false}, // (5)
        TestEqualityParam<DriverCameraMessage>{{      kTimePoint, HeadTracking{ 2.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, {      kTimePoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, false}, // (6)
        TestEqualityParam<DriverCameraMessage>{{      kTimePoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true,  2.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, {      kTimePoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, false}, // (7)
        TestEqualityParam<DriverCameraMessage>{{      kTimePoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad,  2.0_rad, 10.0_rad}}, {      kTimePoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, false}  // (8)
));
// clang-format on

TEST_P(OperatorsFixture_WithDriverCameraMessage, Equals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_same = (param.lhs == param.rhs);

    // Then
    EXPECT_EQ(is_same, param.is_same);
}

TEST_P(OperatorsFixture_WithDriverCameraMessage, NotEquals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_not_same = (param.lhs != param.rhs);

    // Then
    EXPECT_NE(is_not_same, param.is_same);
}

TEST(DriverCameraMessage, InitialValues)
{
    // Given
    constexpr DriverCameraMessage driver_camera_message{};
    constexpr FaceTracking default_face_tracking{};
    constexpr GazeTracking default_gaze_tracking{};
    constexpr HeadTracking default_head_tracking{};

    // Then
    EXPECT_THAT(driver_camera_message,
                AllOf(Field(&DriverCameraMessage::face_tracking, default_face_tracking),
                      Field(&DriverCameraMessage::head_tracking, default_head_tracking),
                      Field(&DriverCameraMessage::gaze_tracking, default_gaze_tracking)));
}

}  // namespace
}  // namespace perception
