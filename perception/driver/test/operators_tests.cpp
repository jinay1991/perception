///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/test/support/operators.h"

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

using OperatorsFixture_WithHeadPose = OperatorFixtureT<TestStringParam<AttentionState>>;

INSTANTIATE_TEST_SUITE_P(Operators,
                         OperatorsFixture_WithHeadPose,
                         ::testing::Values(TestStringParam<AttentionState>{AttentionState::kAttentive, "kAttentive"},
                                           TestStringParam<AttentionState>{AttentionState::kNotAttentive,
                                                                           "kNotAttentive"},
                                           TestStringParam<AttentionState>{AttentionState::kInvalid, "kInvalid"},
                                           TestStringParam<AttentionState>{static_cast<AttentionState>(25U), "ERROR"}));

TEST_P(OperatorsFixture_WithHeadPose, to_string)
{
    // Given
    const auto param = GetParam();

    // When
    const std::string name = to_string(param.value);

    // Then
    EXPECT_THAT(name, HasSubstr(param.name));
}

TEST_P(OperatorsFixture_WithHeadPose, stream_operator)
{
    // Given
    const auto param = GetParam();
    std::ostringstream stream;

    // When
    stream << param.value;

    // Then
    EXPECT_THAT(stream.str(), HasSubstr(param.name));
}

using OperatorsFixture_WithEyeState = OperatorFixtureT<TestStringParam<EyeState>>;

INSTANTIATE_TEST_SUITE_P(Operators,
                         OperatorsFixture_WithEyeState,
                         ::testing::Values(TestStringParam<EyeState>{EyeState::kEyesOpen, "kEyesOpen"},
                                           TestStringParam<EyeState>{EyeState::kEyesClosed, "kEyesClosed"},
                                           TestStringParam<EyeState>{EyeState::kEyesUnknown, "kEyesUnknown"},
                                           TestStringParam<EyeState>{EyeState::kInvalid, "kInvalid"},
                                           TestStringParam<EyeState>{static_cast<EyeState>(25U), "ERROR"}));

TEST_P(OperatorsFixture_WithEyeState, to_string)
{
    // Given
    const auto param = GetParam();

    // When
    const std::string name = to_string(param.value);

    // Then
    EXPECT_THAT(name, HasSubstr(param.name));
}

TEST_P(OperatorsFixture_WithEyeState, stream_operator)
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
