///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/datatype/test/support/operators.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace driver
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

using OperatorsFixture_WithHeadPose = OperatorFixtureT<TestStringParam<DistractionState>>;

INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithHeadPose,
    ::testing::Values(TestStringParam<DistractionState>{DistractionState::kNotDistracted, "kNotDistracted"},
                      TestStringParam<DistractionState>{DistractionState::kDistracted, "kDistracted"},
                      TestStringParam<DistractionState>{DistractionState::kInvalid, "kInvalid"},
                      TestStringParam<DistractionState>{static_cast<DistractionState>(25U), "ERROR"}));

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

using OperatorsFixture_WithFatigueState = OperatorFixtureT<TestStringParam<FatigueState>>;

INSTANTIATE_TEST_SUITE_P(Operators,
                         OperatorsFixture_WithFatigueState,
                         ::testing::Values(TestStringParam<FatigueState>{FatigueState::kAwake, "kAwake"},
                                           TestStringParam<FatigueState>{FatigueState::kQuestionable, "kQuestionable"},
                                           TestStringParam<FatigueState>{FatigueState::kDrowsy, "kDrowsy"},
                                           TestStringParam<FatigueState>{FatigueState::kBeginningSleep,
                                                                         "kBeginningSleep"},
                                           TestStringParam<FatigueState>{FatigueState::kSleep, "kSleep"},
                                           TestStringParam<FatigueState>{FatigueState::kInvalid, "kInvalid"},
                                           TestStringParam<FatigueState>{static_cast<FatigueState>(25U), "ERROR"}));

TEST_P(OperatorsFixture_WithFatigueState, to_string)
{
    // Given
    const auto param = GetParam();

    // When
    const std::string name = to_string(param.value);

    // Then
    EXPECT_THAT(name, HasSubstr(param.name));
}

TEST_P(OperatorsFixture_WithFatigueState, stream_operator)
{
    // Given
    const auto param = GetParam();
    std::ostringstream stream;

    // When
    stream << param.value;

    // Then
    EXPECT_THAT(stream.str(), HasSubstr(param.name));
}

using OperatorsFixture_WithDistractionState = OperatorFixtureT<TestStringParam<DistractionState>>;

INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithDistractionState,
    ::testing::Values(TestStringParam<DistractionState>{DistractionState::kNotDistracted, "kNotDistracted"},
                      TestStringParam<DistractionState>{DistractionState::kDistracted, "kDistracted"},
                      TestStringParam<DistractionState>{DistractionState::kInvalid, "kInvalid"},
                      TestStringParam<DistractionState>{static_cast<DistractionState>(25U), "ERROR"}));

TEST_P(OperatorsFixture_WithDistractionState, to_string)
{
    // Given
    const auto param = GetParam();

    // When
    const std::string name = to_string(param.value);

    // Then
    EXPECT_THAT(name, HasSubstr(param.name));
}

TEST_P(OperatorsFixture_WithDistractionState, stream_operator)
{
    // Given
    const auto param = GetParam();
    std::ostringstream stream;

    // When
    stream << param.value;

    // Then
    EXPECT_THAT(stream.str(), HasSubstr(param.name));
}

using OperatorsFixture_WithActivityState = OperatorFixtureT<TestStringParam<ActivityState>>;

INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithActivityState,
    ::testing::Values(TestStringParam<ActivityState>{ActivityState::kNotAvailable, "kNotAvailable"},
                      TestStringParam<ActivityState>{ActivityState::kCalling, "kCalling"},
                      TestStringParam<ActivityState>{ActivityState::kHandsOnWheel, "kHandsOnWheel"},
                      TestStringParam<ActivityState>{ActivityState::kHandsOffWheel, "kHandsOffWheel"},
                      TestStringParam<ActivityState>{ActivityState::kTexting, "kTexting"},
                      TestStringParam<ActivityState>{ActivityState::kInvalid, "kInvalid"},
                      TestStringParam<ActivityState>{static_cast<ActivityState>(25U), "ERROR"}));

TEST_P(OperatorsFixture_WithActivityState, to_string)
{
    // Given
    const auto param = GetParam();

    // When
    const std::string name = to_string(param.value);

    // Then
    EXPECT_THAT(name, HasSubstr(param.name));
}

TEST_P(OperatorsFixture_WithActivityState, stream_operator)
{
    // Given
    const auto param = GetParam();
    std::ostringstream stream;

    // When
    stream << param.value;

    // Then
    EXPECT_THAT(stream.str(), HasSubstr(param.name));
}

using OperatorsFixture_WithRiskAssessmentState = OperatorFixtureT<TestStringParam<RiskAssessmentState>>;

INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithRiskAssessmentState,
    ::testing::Values(TestStringParam<RiskAssessmentState>{RiskAssessmentState::kNone, "kNone"},
                      TestStringParam<RiskAssessmentState>{RiskAssessmentState::kModerate, "kModerate"},
                      TestStringParam<RiskAssessmentState>{RiskAssessmentState::kHigh, "kHigh"},
                      TestStringParam<RiskAssessmentState>{RiskAssessmentState::kInvalid, "kInvalid"},
                      TestStringParam<RiskAssessmentState>{static_cast<RiskAssessmentState>(25U), "ERROR"}));

TEST_P(OperatorsFixture_WithRiskAssessmentState, to_string)
{
    // Given
    const auto param = GetParam();

    // When
    const std::string name = to_string(param.value);

    // Then
    EXPECT_THAT(name, HasSubstr(param.name));
}

TEST_P(OperatorsFixture_WithRiskAssessmentState, stream_operator)
{
    // Given
    const auto param = GetParam();
    std::ostringstream stream;

    // When
    stream << param.value;

    // Then
    EXPECT_THAT(stream.str(), HasSubstr(param.name));
}

using OperatorsFixture_WithResponsivenessState = OperatorFixtureT<TestStringParam<ResponsivenessState>>;

INSTANTIATE_TEST_SUITE_P(
    Operators,
    OperatorsFixture_WithResponsivenessState,
    ::testing::Values(TestStringParam<ResponsivenessState>{ResponsivenessState::kNotAvailable, "kNotAvailable"},
                      TestStringParam<ResponsivenessState>{ResponsivenessState::kNonResponsive, "kNonResponsive"},
                      TestStringParam<ResponsivenessState>{ResponsivenessState::kResponsive, "kResponsive"},
                      TestStringParam<ResponsivenessState>{ResponsivenessState::kInvalid, "kInvalid"},
                      TestStringParam<ResponsivenessState>{static_cast<ResponsivenessState>(25U), "ERROR"}));

TEST_P(OperatorsFixture_WithResponsivenessState, to_string)
{
    // Given
    const auto param = GetParam();

    // When
    const std::string name = to_string(param.value);

    // Then
    EXPECT_THAT(name, HasSubstr(param.name));
}

TEST_P(OperatorsFixture_WithResponsivenessState, stream_operator)
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
}  // namespace driver
}  // namespace perception
