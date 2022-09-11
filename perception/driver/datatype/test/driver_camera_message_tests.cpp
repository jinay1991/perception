///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/datatype/driver_camera_message.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace driver
{
namespace
{
using ::testing::AllOf;
using ::testing::Field;

constexpr std::chrono::system_clock::time_point kTimePoint{10ms};

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
}  // namespace driver
}  // namespace perception
