///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/common/validity_range.h"

#include <gtest/gtest.h>

namespace perception
{
namespace
{

template <typename T>
struct TestInRangeParam
{
    // Given
    T value;
    T lower;
    T upper;

    // Then
    bool result;
};

template <typename T>
class ValidityRangeT : public ::testing::TestWithParam<T>
{
};

using ValidityRangeFixture_InRange = ValidityRangeT<TestInRangeParam<std::int32_t>>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    ValidityRange,
    ValidityRangeFixture_InRange,
    ::testing::Values(
        //                            value, lower, upper, result
        TestInRangeParam<std::int32_t>{   9,     0,    10,   true},
        TestInRangeParam<std::int32_t>{  11,     0,    10,  false},
        TestInRangeParam<std::int32_t>{  -1,     0,    10,  false}
));
// clang-format on

TEST_P(ValidityRangeFixture_InRange, InRange_GivenTypicalInputs_ExpectCheckedResult)
{
    // Given
    const auto param = GetParam();

    // When
    const bool result = InRange(param.value, param.lower, param.upper);

    // Then
    EXPECT_EQ(result, param.result);
}

TEST_P(ValidityRangeFixture_InRange, InRange_GivenTypicalValidityRange_ExpectCheckedResult)
{
    // Given
    const auto param = GetParam();
    const ValidityRange<std::int32_t> range{param.lower, param.upper};

    // When
    const bool result = InRange(param.value, range);

    // Then
    EXPECT_EQ(result, param.result);
}

using ValidityRangeFixture_InRangeInclusive = ValidityRangeT<TestInRangeParam<std::int32_t>>;
// clang-format off
INSTANTIATE_TEST_SUITE_P(
    ValidityRange,
    ValidityRangeFixture_InRangeInclusive,
    ::testing::Values(
        //                            value, lower, upper, result
        TestInRangeParam<std::int32_t>{   9,     0,    10,   true},
        TestInRangeParam<std::int32_t>{  10,     0,    10,   true},
        TestInRangeParam<std::int32_t>{  11,     0,    10,  false},
        TestInRangeParam<std::int32_t>{  -1,     0,    10,  false},
        TestInRangeParam<std::int32_t>{   0,     0,    10,   true}
));
// clang-format on

TEST_P(ValidityRangeFixture_InRangeInclusive, InRangeInclusive_GivenTypicalInputs_ExpectCheckedResult)
{
    // Given
    const auto param = GetParam();

    // When
    const bool result = InRangeInclusive(param.value, param.lower, param.upper);

    // Then
    EXPECT_EQ(result, param.result);
}

TEST_P(ValidityRangeFixture_InRangeInclusive, InRangeInclusive_GivenTypicalValidityRange_ExpectCheckedResult)
{
    // Given
    const auto param = GetParam();
    const ValidityRange<std::int32_t> range{param.lower, param.upper};

    // When
    const bool result = InRangeInclusive(param.value, range);

    // Then
    EXPECT_EQ(result, param.result);
}

template <typename T>
struct TestClampParam
{
    // Given
    T value;
    T lower;
    T upper;

    // Then
    T result;
};

class ValidityRangeFixture_Clamp : public ::testing::TestWithParam<TestClampParam<std::int32_t>>
{
};

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    ValidityRange,
    ValidityRangeFixture_Clamp,
    ::testing::Values(
        //                          value, lower, upper, result
        TestClampParam<std::int32_t>{   9,     0,    10,    9},
        TestClampParam<std::int32_t>{  11,     0,    10,   10},
        TestClampParam<std::int32_t>{  -1,     0,    10,    0}
));
// clang-format on

TEST_P(ValidityRangeFixture_Clamp, Clamp_GivenTypicalInputs_ExpectClampedResult)
{
    // Given
    const auto param = GetParam();

    // When
    const auto result = Clamp(param.value, param.lower, param.upper);

    // Then
    EXPECT_EQ(result, param.result);
}

TEST_P(ValidityRangeFixture_Clamp, Clamp_GivenTypicalValidityRange_ExpectClampedResult)
{
    // Given
    const auto param = GetParam();
    const ValidityRange<std::int32_t> range{param.lower, param.upper};

    // When
    const auto result = Clamp(param.value, range);

    // Then
    EXPECT_EQ(result, param.result);
}

TEST(ValidityRangeTest, IntegerEquality)
{
    const ValidityRange<std::int32_t> lhs{1, 10};
    const ValidityRange<std::int32_t> rhs{1, 11};

    EXPECT_EQ(lhs, lhs);
    EXPECT_NE(lhs, rhs);
}

TEST(ValidityRangeTest, DoubleEquality)
{
    const ValidityRange<double> lhs{1.0, 11.0};
    const ValidityRange<double> rhs{1.0, 11.1};

    EXPECT_EQ(lhs, lhs);
    EXPECT_NE(lhs, rhs);
}
}  // namespace
}  // namespace perception
