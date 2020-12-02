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

using OperatorsFixture_WithDegradationState = OperatorFixtureT<TestStringParam<DegradationState>>;

INSTANTIATE_TEST_CASE_P(
    Operators,
    OperatorsFixture_WithDegradationState,
    ::testing::Values(TestStringParam<DegradationState>{DegradationState::kNormalOperation, "kNormalOperation"},
                      TestStringParam<DegradationState>{DegradationState::kValidityError, "kValidityError"},
                      TestStringParam<DegradationState>{DegradationState::kCommunicationError, "kCommunicationError"},
                      TestStringParam<DegradationState>{DegradationState::kSensorBlockage, "kSensorBlockage"},
                      TestStringParam<DegradationState>{DegradationState::kInvalid, "kInvalid"},
                      TestStringParam<DegradationState>{static_cast<DegradationState>(25U), "ERROR"}));

TEST_P(OperatorsFixture_WithDegradationState, to_string)
{
    // Given
    const auto param = GetParam();

    // When
    const std::string name = to_string(param.value);

    // Then
    EXPECT_THAT(name, HasSubstr(param.name));
}

TEST_P(OperatorsFixture_WithDegradationState, stream_operator)
{
    // Given
    const auto param = GetParam();
    std::ostringstream stream;

    // When
    stream << param.value;

    // Then
    EXPECT_THAT(stream.str(), HasSubstr(param.name));
}

using OperatorsFixture_WithHeadPose = OperatorFixtureT<TestStringParam<HeadPose>>;

INSTANTIATE_TEST_CASE_P(Operators,
                        OperatorsFixture_WithHeadPose,
                        ::testing::Values(TestStringParam<HeadPose>{HeadPose::kAttentive, "kAttentive"},
                                          TestStringParam<HeadPose>{HeadPose::kNotAttentive, "kNotAttentive"},
                                          TestStringParam<HeadPose>{HeadPose::kInvalid, "kInvalid"},
                                          TestStringParam<HeadPose>{static_cast<HeadPose>(25U), "ERROR"}));

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

using OperatorsFixture_WithGazePose = OperatorFixtureT<TestStringParam<GazePose>>;

INSTANTIATE_TEST_CASE_P(Operators,
                        OperatorsFixture_WithGazePose,
                        ::testing::Values(TestStringParam<GazePose>{GazePose::kFront, "kFront"},
                                          TestStringParam<GazePose>{GazePose::kLeft, "kLeft"},
                                          TestStringParam<GazePose>{GazePose::kRight, "kRight"},
                                          TestStringParam<GazePose>{GazePose::kDown, "kDown"},
                                          TestStringParam<GazePose>{GazePose::kUp, "kUp"},
                                          TestStringParam<GazePose>{GazePose::kInvalid, "kInvalid"},
                                          TestStringParam<GazePose>{static_cast<GazePose>(25U), "ERROR"}));

TEST_P(OperatorsFixture_WithGazePose, to_string)
{
    // Given
    const auto param = GetParam();

    // When
    const std::string name = to_string(param.value);

    // Then
    EXPECT_THAT(name, HasSubstr(param.name));
}

TEST_P(OperatorsFixture_WithGazePose, stream_operator)
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

INSTANTIATE_TEST_CASE_P(Operators,
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
