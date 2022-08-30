///
/// @file
/// @copyright Copyright (c) 2022. NVIDIA Corporation. All Rights Reserved.
///
#include "perception/lifecycle/node.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace lifecycle
{
namespace
{
class MockNode : public Node
{
  public:
    explicit MockNode(const std::string name) : Node{name} {}

    MOCK_METHOD0(Init, void());
    MOCK_METHOD0(Step, void());
    MOCK_METHOD0(Shutdown, void());
};

TEST(NodeTest, GetName_ExpectNodeName)
{
    // Given
    const std::string name = "test_node";
    const MockNode node{name};

    // When
    const auto result = node.GetName();

    // Then
    EXPECT_EQ(result, name);
}

}  // namespace
}  // namespace lifecycle
}  // namespace perception
