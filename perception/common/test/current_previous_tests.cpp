///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/common/current_previous.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>

namespace perception
{
namespace
{
using namespace std::chrono_literals;

/// @brief Test Structure
struct TestStruct
{
    /// @brief Test value
    std::int32_t value;
};

/// @brief Equal Comparision operator for TestStruct
///
/// @param lhs [in] - LVALUE
/// @param rhs [in] - RVALUE
///
/// @return True if lhs == rhs, otherwise False.
constexpr bool operator==(const TestStruct& lhs, const TestStruct& rhs) noexcept
{
    return (lhs.value == rhs.value);
}

/// @brief Substraction operator for TestStruct
///
/// @param lhs [in] - LVALUE
/// @param rhs [in] - RVALUE
///
/// @return Resultant TestStruct (lhs - rhs)
constexpr TestStruct operator-(const TestStruct& lhs, const TestStruct& rhs) noexcept
{
    return TestStruct{lhs.value - rhs.value};
}

TEST(CurrentPrevious, SetCurrent_GivenTypicalCurrentPreviousValues_ExpectUpdatedCurrentValue)
{
    // Given
    const std::int32_t current = 10;
    const std::int32_t previous = 9;
    const std::int32_t delta = current - previous;
    const std::int32_t new_current = current + 1;
    const std::int32_t new_delta = new_current - previous;
    CurrentPrevious<std::int32_t> current_previous{current, previous};
    ASSERT_THAT(current_previous.GetCurrent(), current);
    ASSERT_THAT(current_previous.GetDelta(), delta);

    // When
    current_previous.SetCurrent(new_current);

    // Then
    EXPECT_THAT(current_previous.GetCurrent(), new_current);
    EXPECT_THAT(current_previous.GetDelta(), new_delta);
}

TEST(CurrentPrevious, SetPrevious_GivenTypicalCurrentPreviousValues_ExpectUpdatedPreviousValue)
{
    // Given
    const std::int32_t current = 10;
    const std::int32_t previous = 9;
    const std::int32_t delta = current - previous;
    const std::int32_t new_previous = previous - 1;
    const std::int32_t new_delta = current - new_previous;
    CurrentPrevious<std::int32_t> current_previous{current, previous};
    ASSERT_THAT(current_previous.GetPrevious(), previous);
    ASSERT_THAT(current_previous.GetDelta(), delta);

    // When
    current_previous.SetPrevious(new_previous);

    // Then
    EXPECT_THAT(current_previous.GetPrevious(), new_previous);
    EXPECT_THAT(current_previous.GetDelta(), new_delta);
}

TEST(CurrentPrevious, GetCurrent_GivenTypicalCurrentPreviousValues_ExpectCurrentValue)
{
    // Given
    const std::int32_t current = 10;
    const std::int32_t previous = 9;
    const CurrentPrevious<std::int32_t> current_previous{current, previous};

    // Then
    EXPECT_THAT(current_previous.GetCurrent(), current);
}

TEST(CurrentPrevious, GetPrevious_GivenTypicalCurrentPreviousValues_ExpectPreviousValue)
{
    // Given
    const std::int32_t current = 10;
    const std::int32_t previous = 9;
    const CurrentPrevious<std::int32_t> current_previous{current, previous};

    // Then
    EXPECT_THAT(current_previous.GetPrevious(), previous);
}

TEST(CurrentPrevious, GetDelta_GivenTypicalCurrentPreviousValues_ExpectDeltaValue)
{
    // Given
    const std::int32_t current = 10;
    const std::int32_t previous = 9;
    const std::int32_t delta = current - previous;
    const CurrentPrevious<std::int32_t> current_previous{current, previous};

    // Then
    EXPECT_THAT(current_previous.GetDelta(), delta);
}

TEST(CurrentPrevious, GetDelta_GivenChronoTypeCurrentPreviousValues_ExpectDeltaValue)
{
    // Given
    const std::chrono::milliseconds current = 10ms;
    const std::chrono::milliseconds previous = 9ms;
    const std::chrono::milliseconds delta = current - previous;
    const CurrentPrevious<std::chrono::milliseconds> current_previous{current, previous};

    // Then
    EXPECT_THAT(current_previous.GetDelta(), delta);
}

TEST(CurrentPrevious, GetDelta_GivenTestStructTypeCurrentPreviousValues_ExpectDeltaValue)
{
    // Given
    const TestStruct current{10};
    const TestStruct previous{9};
    const TestStruct delta{current - previous};
    const CurrentPrevious<TestStruct> current_previous{current, previous};

    // Then
    EXPECT_THAT(current_previous.GetDelta(), delta);
}
}  // namespace
}  // namespace perception
