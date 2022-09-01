///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/object/datatype/object.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace object
{
namespace
{
using ::testing::AllOf;
using ::testing::Field;

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

TEST(Object, GlobalConstants)
{
    // Then
    EXPECT_EQ(kMaxNumberOfObjects, 10);
}
}  // namespace
}  // namespace object
}  // namespace perception
