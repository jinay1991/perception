///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/datatypes/driver.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
using namespace units::literals;
using namespace std::chrono_literals;

constexpr std::chrono::system_clock::time_point kTimepoint{10ms};

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
        TestEqualityParam<FaceTracking>{{ true,  true, 10.0_mm, 1.0_Hz},  {true,  true, 10.0_mm, 1.0_Hz},  true},
        TestEqualityParam<FaceTracking>{{ true,  true, 10.0_mm, 1.0_Hz}, {false,  true, 10.0_mm, 1.0_Hz}, false},
        TestEqualityParam<FaceTracking>{{ true,  true, 10.0_mm, 1.0_Hz}, { true, false, 10.0_mm, 1.0_Hz}, false},
        TestEqualityParam<FaceTracking>{{ true,  true, 10.0_mm, 1.0_Hz}, { true,  true, 20.0_mm, 1.0_Hz}, false},
        TestEqualityParam<FaceTracking>{{ true,  true, 10.0_mm, 1.0_Hz}, { true,  true, 10.0_mm, 2.0_Hz}, false},
        TestEqualityParam<FaceTracking>{{false,  true, 10.0_mm, 1.0_Hz}, { true,  true, 10.0_mm, 1.0_Hz}, false},
        TestEqualityParam<FaceTracking>{{ true, false, 10.0_mm, 1.0_Hz}, { true,  true, 10.0_mm, 1.0_Hz}, false},
        TestEqualityParam<FaceTracking>{{ true,  true, 20.0_mm, 1.0_Hz}, { true,  true, 10.0_mm, 1.0_Hz}, false},
        TestEqualityParam<FaceTracking>{{ true,  true, 10.0_mm, 2.0_Hz}, { true,  true, 10.0_mm, 1.0_Hz}, false}
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

using OperatorsFixture_WithGazeTracking = OperatorsFixtureT<TestEqualityParam<GazeTracking>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators, 
    OperatorsFixture_WithGazeTracking, 
    ::testing::Values(
        //                                       lhs                  ,          rhs                  , is_same?
        TestEqualityParam<GazeTracking>{{10.0_rad, 10.0_rad, 10.0_rad}, {10.0_rad, 10.0_rad, 10.0_rad},  true},
        TestEqualityParam<GazeTracking>{{10.0_rad, 10.0_rad, 10.0_rad}, { 2.0_rad, 10.0_rad, 10.0_rad}, false},
        TestEqualityParam<GazeTracking>{{10.0_rad, 10.0_rad, 10.0_rad}, {10.0_rad,  2.0_rad, 10.0_rad}, false},
        TestEqualityParam<GazeTracking>{{10.0_rad, 10.0_rad, 10.0_rad}, {10.0_rad, 10.0_rad,  2.0_rad}, false},
        TestEqualityParam<GazeTracking>{{ 2.0_rad, 10.0_rad, 10.0_rad}, {10.0_rad, 10.0_rad, 10.0_rad}, false},
        TestEqualityParam<GazeTracking>{{10.0_rad,  2.0_rad, 10.0_rad}, {10.0_rad, 10.0_rad, 10.0_rad}, false},
        TestEqualityParam<GazeTracking>{{10.0_rad, 10.0_rad,  2.0_rad}, {10.0_rad, 10.0_rad, 10.0_rad}, false}
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

using OperatorsFixture_WithHeadTracking = OperatorsFixtureT<TestEqualityParam<HeadTracking>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators, 
    OperatorsFixture_WithHeadTracking, 
    ::testing::Values(
        //                                       lhs                  ,          rhs                  , is_same?
        TestEqualityParam<HeadTracking>{{10.0_rad, 10.0_rad, 10.0_rad}, {10.0_rad, 10.0_rad, 10.0_rad},  true},
        TestEqualityParam<HeadTracking>{{10.0_rad, 10.0_rad, 10.0_rad}, { 2.0_rad, 10.0_rad, 10.0_rad}, false},
        TestEqualityParam<HeadTracking>{{10.0_rad, 10.0_rad, 10.0_rad}, {10.0_rad,  2.0_rad, 10.0_rad}, false},
        TestEqualityParam<HeadTracking>{{10.0_rad, 10.0_rad, 10.0_rad}, {10.0_rad, 10.0_rad,  2.0_rad}, false},
        TestEqualityParam<HeadTracking>{{ 2.0_rad, 10.0_rad, 10.0_rad}, {10.0_rad, 10.0_rad, 10.0_rad}, false},
        TestEqualityParam<HeadTracking>{{10.0_rad,  2.0_rad, 10.0_rad}, {10.0_rad, 10.0_rad, 10.0_rad}, false},
        TestEqualityParam<HeadTracking>{{10.0_rad, 10.0_rad,  2.0_rad}, {10.0_rad, 10.0_rad, 10.0_rad}, false}
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

using OperatorsFixture_WithFatigueMessage = OperatorsFixtureT<TestEqualityParam<FatigueMessage>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators, 
    OperatorsFixture_WithFatigueMessage, 
    ::testing::Values(
        //                                              lhs                                               ,          rhs                                                  , is_same?
        TestEqualityParam<FatigueMessage>{{      kTimepoint, EyeState::kEyesClosed,  FatigueLevel::kAwake, 10.0}, {      kTimepoint, EyeState::kEyesClosed,  FatigueLevel::kAwake, 10.0},  true},
        TestEqualityParam<FatigueMessage>{{      kTimepoint, EyeState::kEyesClosed,  FatigueLevel::kAwake, 10.0}, {kTimepoint + 1ms, EyeState::kEyesClosed,  FatigueLevel::kAwake, 10.0}, false},
        TestEqualityParam<FatigueMessage>{{      kTimepoint, EyeState::kEyesClosed,  FatigueLevel::kAwake, 10.0}, {      kTimepoint,   EyeState::kEyesOpen,  FatigueLevel::kAwake, 10.0}, false},
        TestEqualityParam<FatigueMessage>{{      kTimepoint, EyeState::kEyesClosed,  FatigueLevel::kAwake, 10.0}, {      kTimepoint, EyeState::kEyesClosed, FatigueLevel::kDrowsy, 10.0}, false},
        TestEqualityParam<FatigueMessage>{{      kTimepoint, EyeState::kEyesClosed,  FatigueLevel::kAwake, 10.0}, {      kTimepoint, EyeState::kEyesClosed,  FatigueLevel::kAwake,  2.0}, false},
        TestEqualityParam<FatigueMessage>{{kTimepoint + 1ms, EyeState::kEyesClosed,  FatigueLevel::kAwake, 10.0}, {      kTimepoint, EyeState::kEyesClosed,  FatigueLevel::kAwake, 10.0}, false},
        TestEqualityParam<FatigueMessage>{{      kTimepoint,   EyeState::kEyesOpen,  FatigueLevel::kAwake, 10.0}, {      kTimepoint, EyeState::kEyesClosed,  FatigueLevel::kAwake, 10.0}, false},
        TestEqualityParam<FatigueMessage>{{      kTimepoint, EyeState::kEyesClosed, FatigueLevel::kDrowsy, 10.0}, {      kTimepoint, EyeState::kEyesClosed,  FatigueLevel::kAwake, 10.0}, false},
        TestEqualityParam<FatigueMessage>{{      kTimepoint, EyeState::kEyesClosed,  FatigueLevel::kAwake,  2.0}, {      kTimepoint, EyeState::kEyesClosed,  FatigueLevel::kAwake, 10.0}, false}
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

using OperatorsFixture_WithVisualAttentionMessage = OperatorsFixtureT<TestEqualityParam<VisualAttentionMessage>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators, 
    OperatorsFixture_WithVisualAttentionMessage, 
    ::testing::Values(
        //                                              lhs                                        ,          rhs                                     , is_same?
        TestEqualityParam<VisualAttentionMessage>{{      kTimepoint,    AttentionState::kAttentive}, {      kTimepoint,    AttentionState::kAttentive},  true},
        TestEqualityParam<VisualAttentionMessage>{{      kTimepoint,    AttentionState::kAttentive}, {kTimepoint + 1ms,    AttentionState::kAttentive}, false},
        TestEqualityParam<VisualAttentionMessage>{{      kTimepoint,    AttentionState::kAttentive}, {      kTimepoint, AttentionState::kNotAttentive}, false},
        TestEqualityParam<VisualAttentionMessage>{{kTimepoint + 1ms,    AttentionState::kAttentive}, {      kTimepoint,    AttentionState::kAttentive}, false},
        TestEqualityParam<VisualAttentionMessage>{{      kTimepoint, AttentionState::kNotAttentive}, {      kTimepoint,    AttentionState::kAttentive}, false}
        
));
// clang-format on

TEST_P(OperatorsFixture_WithVisualAttentionMessage, Equals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_same = (param.lhs == param.rhs);

    // Then
    EXPECT_EQ(is_same, param.is_same);
}

TEST_P(OperatorsFixture_WithVisualAttentionMessage, NotEquals)
{
    // Given
    const auto param = GetParam();

    // When
    const auto is_not_same = (param.lhs != param.rhs);

    // Then
    EXPECT_NE(is_not_same, param.is_same);
}

using OperatorsFixture_WithDriverCameraMessage = OperatorsFixtureT<TestEqualityParam<DriverCameraMessage>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Operators, 
    OperatorsFixture_WithDriverCameraMessage, 
    ::testing::Values(
        //                                              lhs                                        ,          rhs                                     , is_same?
        TestEqualityParam<DriverCameraMessage>{{      kTimepoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, {      kTimepoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}},  true},
        TestEqualityParam<DriverCameraMessage>{{      kTimepoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, {kTimepoint + 1ms, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, false},
        TestEqualityParam<DriverCameraMessage>{{      kTimepoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, {      kTimepoint, HeadTracking{ 2.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, false},
        TestEqualityParam<DriverCameraMessage>{{      kTimepoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, {      kTimepoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true,  2.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, false},
        TestEqualityParam<DriverCameraMessage>{{      kTimepoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, {      kTimepoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad,  2.0_rad, 10.0_rad}}, false},
        TestEqualityParam<DriverCameraMessage>{{kTimepoint + 1ms, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, {      kTimepoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, false},
        TestEqualityParam<DriverCameraMessage>{{      kTimepoint, HeadTracking{ 2.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, {      kTimepoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, false},
        TestEqualityParam<DriverCameraMessage>{{      kTimepoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true,  2.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, {      kTimepoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, false},
        TestEqualityParam<DriverCameraMessage>{{      kTimepoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad,  2.0_rad, 10.0_rad}}, {      kTimepoint, HeadTracking{10.0_rad, 10.0_rad, 10.0_rad}, FaceTracking{true, true, 10.0_mm, 1.0_Hz}, GazeTracking{10.0_rad, 10.0_rad, 10.0_rad}}, false}
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
}  // namespace
}  // namespace perception
