///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
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

class ValidityRangeFixture_InRange : public ::testing::TestWithParam<TestInRangeParam<std::int32_t>>
{
};

// clang-format off
INSTANTIATE_TEST_CASE_P(
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
