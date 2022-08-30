///
/// @file
/// @copyright Copyright (c) 2022. NVIDIA Corporation. All Rights Reserved.
///
#include "perception/lifecycle/test/support/mocks/node_mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace lifecycle
{
namespace test
{
namespace support
{
namespace
{

class NodeMockFixture : public ::testing::Test
{
  public:
    NodeMockFixture() : mocked_node_{} {}

  protected:
    ::testing::NiceMock<NodeMock> mocked_node_;
};

TEST_F(NodeMockFixture, Init)
{
    // Then
    EXPECT_CALL(mocked_node_, Init()).Times(1);

    // When
    mocked_node_.Init();
}

TEST_F(NodeMockFixture, Step)
{
    // Then
    EXPECT_CALL(mocked_node_, Step()).Times(1);

    // When
    mocked_node_.Step();
}

TEST_F(NodeMockFixture, Shutdown)
{
    // Then
    EXPECT_CALL(mocked_node_, Shutdown()).Times(1);

    // When
    mocked_node_.Shutdown();
}

TEST_F(NodeMockFixture, GetName)
{
    // Then
    EXPECT_CALL(mocked_node_, GetName()).Times(1);

    // When
    mocked_node_.GetName();
}
}  // namespace
}  // namespace support
}  // namespace test
}  // namespace lifecycle
}  // namespace perception
