///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/datatype/driver.h"

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

}  // namespace
}  // namespace driver
}  // namespace perception
