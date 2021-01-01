///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/traffic_sign/test/support/operators.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
using ::testing::HasSubstr;

template <typename T>
class OperatorFixtureT : public ::testing::TestWithParam<T>
{
};

template <typename T>
struct TestStringParam
{
    // Given
    T value;

    // Then
    std::string name;
};

using OperatorsFixture_WithTrafficSignId = OperatorFixtureT<TestStringParam<TrafficSignId>>;

INSTANTIATE_TEST_SUITE_P(Operators,
                         OperatorsFixture_WithTrafficSignId,
                         ::testing::Values(TestStringParam<TrafficSignId>{TrafficSignId::kNone, "kNone"},
                                           TestStringParam<TrafficSignId>{TrafficSignId::kSpeedLimit, "kSpeedLimit"},
                                           TestStringParam<TrafficSignId>{TrafficSignId::kRoadWorks, "kRoadWorks"},
                                           TestStringParam<TrafficSignId>{TrafficSignId::kTurnLeft, "kTurnLeft"},
                                           TestStringParam<TrafficSignId>{TrafficSignId::kTurnRight, "kTurnRight"},
                                           TestStringParam<TrafficSignId>{TrafficSignId::kTwoBumps, "kTwoBumps"},
                                           TestStringParam<TrafficSignId>{TrafficSignId::kInvalid, "kInvalid"},
                                           TestStringParam<TrafficSignId>{static_cast<TrafficSignId>(100U), "ERROR"}));

TEST_P(OperatorsFixture_WithTrafficSignId, to_string)
{
    // Given
    const auto param = GetParam();

    // When
    const std::string name = to_string(param.value);

    // Then
    EXPECT_THAT(name, HasSubstr(param.name));
}

TEST_P(OperatorsFixture_WithTrafficSignId, stream_operator)
{
    // Given
    const auto param = GetParam();
    std::ostringstream stream;

    // When
    stream << param.value;

    // Then
    EXPECT_THAT(stream.str(), HasSubstr(param.name));
}

}  // namespace
}  // namespace perception
