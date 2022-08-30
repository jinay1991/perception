///
/// @file
/// @copyright Copyright (c) 2022. NVIDIA Corporation. All Rights Reserved.
///
#include "perception/lifecycle/null_node.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace lifecycle
{
namespace
{

TEST(NullNodeTest, Coverage)
{
    // Given
    NullNode node{};

    // When/Then
    EXPECT_NO_THROW(node.Init());
    EXPECT_NO_THROW(node.Step());
    EXPECT_NO_THROW(node.Shutdown());
    EXPECT_EQ(node.GetName(), "null_node");
}
}  // namespace
}  // namespace lifecycle
}  // namespace perception
