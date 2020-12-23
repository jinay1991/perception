///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/common/circular_bitset.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
using ::testing::AllOf;
using ::testing::Field;
using ::testing::Property;

constexpr std::int32_t kTestCircularBitsetSize{10};

TEST(CircularBitset, DefaultConstructor)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{};

    // Then
    EXPECT_THAT(circular_bitset.size(), 0);
    EXPECT_THAT(circular_bitset.empty(), true);
    EXPECT_THAT(circular_bitset.count(), 0);
}

TEST(CircularBitset, ExpliitConstructorWithInitializerList)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{true, false, true, false};

    // Then
    EXPECT_THAT(circular_bitset.size(), 4);
    EXPECT_THAT(circular_bitset.empty(), false);
    EXPECT_THAT(circular_bitset.count(), 2);
}

TEST(CircularBitset, CopyConstructor)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{true, false, true, false};

    // When
    CircularBitset<kTestCircularBitsetSize> another_circular_bitset{circular_bitset};

    // Then
    EXPECT_THAT(circular_bitset, another_circular_bitset);
}

TEST(CircularBitset, CopyAssignment)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{true, false, true, false};
    CircularBitset<kTestCircularBitsetSize> another_circular_bitset{};

    // When
    another_circular_bitset = circular_bitset;

    // Then
    EXPECT_THAT(circular_bitset, another_circular_bitset);
}

TEST(CircularBitset, MoveConstructor)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{true, false, true, false};

    // When
    CircularBitset<kTestCircularBitsetSize> another_circular_bitset{std::move(circular_bitset)};

    // Then
    EXPECT_THAT(circular_bitset, another_circular_bitset);
}

TEST(CircularBitset, MoveAssignment)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{true, false, true, false};
    CircularBitset<kTestCircularBitsetSize> another_circular_bitset{};

    // When
    another_circular_bitset = std::move(circular_bitset);

    // Then
    EXPECT_THAT(circular_bitset, another_circular_bitset);
}

TEST(CircularBitset, Count_GivenTypicalCircularBitset_ExpectCountOfBitset)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{true, false, true, false};

    // Then
    EXPECT_THAT(circular_bitset.count(), 2);
}

TEST(CircularBitset, Size_GivenTypicalCircularBitset_ExpectSizeOfBitset)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{true, false, true, false};

    // Then
    EXPECT_THAT(circular_bitset.size(), 4);
}

TEST(CircularBitset, Empty_GivenTypicalCircularBitset_ExpectFalse)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{true, false, true, false};

    // Then
    EXPECT_THAT(circular_bitset.empty(), false);
}

TEST(CircularBitset, Empty_GivenTypicalCircularBitset_ExpectTrue)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{};

    // Then
    EXPECT_THAT(circular_bitset.empty(), true);
}

TEST(CircularBitset, Capacity_GivenTypicalCircularBitset_ExpectCapacity)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{};

    // Then
    EXPECT_THAT(circular_bitset.capacity(), kTestCircularBitsetSize);
}

TEST(CircularBitset, Full_GivenTypicalCircularBitset_ExpectTrue)
{
    // Given
    CircularBitset<4> circular_bitset{true, true, false, true};

    // Then
    EXPECT_THAT(circular_bitset.full(), true);
}

TEST(CircularBitset, Full_GivenTypicalCircularBitset_ExpectFalse)
{
    // Given
    CircularBitset<4> circular_bitset{true, true, false};

    // Then
    EXPECT_THAT(circular_bitset.full(), false);
}

TEST(CircularBitset, Clear_GivenTypicalCircularBitset_ExpectEmptyBitset)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{true, true, false};
    ASSERT_THAT(circular_bitset.empty(), false);

    // When
    circular_bitset.clear();

    // Then
    EXPECT_THAT(circular_bitset.empty(), true);
    EXPECT_THAT(circular_bitset.size(), 0);
    EXPECT_THAT(circular_bitset.count(), 0);
}

TEST(CircularBitset, Resize_GivenTypicalCircularBitset_ExpectResizedBitset)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{true, true, false};
    ASSERT_THAT(circular_bitset.capacity(), kTestCircularBitsetSize);

    // When
    circular_bitset.resize(kTestCircularBitsetSize / 2);

    // Then
    EXPECT_THAT(circular_bitset.capacity(), kTestCircularBitsetSize / 2);
}

TEST(CircularBitset, Resize_GivenTypicalCircularBitset_ExpectSameBitset)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{true, true, false};
    ASSERT_THAT(circular_bitset.capacity(), kTestCircularBitsetSize);

    // When
    circular_bitset.resize(kTestCircularBitsetSize * 2);

    // Then
    EXPECT_THAT(circular_bitset.capacity(), kTestCircularBitsetSize);
}

TEST(CircularBitset, PushBack_GivenTypicalCircularBitset_ExpectPushedBack)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{true, true, false};
    ASSERT_THAT(circular_bitset.size(), 3);

    // When
    circular_bitset.push_back(true);

    // Then
    EXPECT_THAT(circular_bitset.back(), true);
    EXPECT_THAT(circular_bitset.size(), 4);
}

TEST(CircularBitset, PushBack_GivenTypicalCircularBitset_ExpectPushedBackWithWrappedIndex)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{
        false, true, true, true, true, true, true, true, true, true};
    ASSERT_THAT(circular_bitset.full(), true);
    ASSERT_THAT(circular_bitset.front(), false);

    // When
    circular_bitset.push_back(false);

    // Then
    EXPECT_THAT(circular_bitset.back(), false);
    EXPECT_THAT(circular_bitset.front(), true);
    EXPECT_THAT(circular_bitset.full(), true);
}

TEST(CircularBitset, PopFront_GivenTypicalCircularBitset_ExpectPoppedFront)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{
        true, false, true, true, true, true, true, true, true, true};
    ASSERT_THAT(circular_bitset.size(), kTestCircularBitsetSize);

    // When
    circular_bitset.pop_front();

    // Then
    EXPECT_THAT(circular_bitset.front(), false);
    EXPECT_THAT(circular_bitset.size(), kTestCircularBitsetSize - 1);
}

TEST(CircularBitset, PopFront_GivenEmptyCircularBitset_ExpectNothingPopped)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{};
    ASSERT_THAT(circular_bitset.empty(), true);

    // When
    circular_bitset.pop_front();

    // Then
    EXPECT_THAT(circular_bitset.empty(), true);
}

TEST(CircularBitset, At_GivenTypicalCircularBitset_ExpectBitAtIndex)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{
        true, false, true, true, true, true, true, true, true, true};

    // When
    const auto value = circular_bitset.at(1);

    // Then
    EXPECT_THAT(value, false);
}

TEST(CircularBitset, At_GivenTypicalCircularBitset_ExpectUpdatedBitAtIndex)
{
    // Given
    CircularBitset<kTestCircularBitsetSize> circular_bitset{
        true, false, true, true, true, true, true, true, true, true};
    ASSERT_THAT(circular_bitset.at(1), false);

    // When
    circular_bitset.at(1) = true;

    // Then
    EXPECT_THAT(circular_bitset.at(1), true);
}

}  // namespace
}  // namespace perception
