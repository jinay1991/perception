///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
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

struct TestStruct
{
    std::int32_t value;
};
inline constexpr bool operator==(const TestStruct& lhs, const TestStruct& rhs) noexcept
{
    return (lhs.value == rhs.value);
}
inline constexpr TestStruct operator-(const TestStruct& lhs, const TestStruct& rhs) noexcept
{
    return TestStruct{lhs.value - rhs.value};
}

TEST(CurrentPrevious, Integer_GivenTypicalCurrentPrevious_ExpectUpdatedDelta)
{
    // Given
    const std::int32_t current = 10;
    const std::int32_t previous = 9;
    const CurrentPrevious<std::int32_t> current_previous{current, previous};

    // Then
    EXPECT_THAT(current_previous.GetDelta(), current - previous);
}

TEST(CurrentPrevious, Chrono_GivenTypicalCurrentPrevious_ExpectUpdatedDelta)
{
    // Given
    const std::chrono::milliseconds current = 10ms;
    const std::chrono::milliseconds previous = 9ms;
    const CurrentPrevious<std::chrono::milliseconds> current_previous{current, previous};

    // Then
    EXPECT_THAT(current_previous.GetDelta(), current - previous);
}

TEST(CurrentPrevious, Structure_GivenTypicalCurrentPrevious_ExpectUpdatedDelta)
{
    // Given
    const TestStruct current{10};
    const TestStruct previous{9};
    const CurrentPrevious<TestStruct> current_previous{current, previous};

    // Then
    EXPECT_THAT(current_previous.GetDelta(), TestStruct{current.value - previous.value});
}
}  // namespace
}  // namespace perception