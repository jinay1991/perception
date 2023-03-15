///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/lifecycle/node_runner.h"
#include "perception/lifecycle/test/support/mocks/node_mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

namespace perception
{
namespace lifecycle
{
namespace
{
using ::testing::Return;

class NodeRunnerFixture : public ::testing::Test
{
  public:
    NodeRunnerFixture()
        : node_name_{"test_node"},
          mocked_node_{std::make_unique<test::support::NodeMock>()},
          mocked_node_ptr_{mocked_node_.get()},
          runner_{}
    {
    }

  protected:
    void SetUp() override
    {
        EXPECT_CALL(*mocked_node_ptr_, GetName()).WillRepeatedly(Return(node_name_));
        runner_.RegisterNode(std::move(mocked_node_));
    }

    std::string node_name_;
    std::unique_ptr<test::support::NodeMock> mocked_node_;
    test::support::NodeMock* mocked_node_ptr_;
    NodeRunner runner_;
};

TEST(NodeRunnerTest, RegisterNode_ExpectRegisteredNode)
{
    // Given
    std::unique_ptr<test::support::NodeMock> mocked_node{std::make_unique<test::support::NodeMock>()};
    NodeRunner runner{};
    const std::string name{"test_node"};
    EXPECT_CALL(*mocked_node, GetName()).WillRepeatedly(Return(name));

    // Then
    EXPECT_CALL(*mocked_node, Init()).Times(0);
    EXPECT_CALL(*mocked_node, Step()).Times(0);
    EXPECT_CALL(*mocked_node, Shutdown()).Times(0);

    // When
    runner.RegisterNode(std::move(mocked_node));

    // Then
    EXPECT_TRUE(runner.IsNodeRegistered(name));
}

TEST_F(NodeRunnerFixture, RunOnce_ExpectNodeStepOnce)
{
    // Given
    ASSERT_TRUE(runner_.IsNodeRegistered(node_name_));

    // Then
    EXPECT_CALL(*mocked_node_ptr_, Init()).Times(1);
    EXPECT_CALL(*mocked_node_ptr_, Step()).Times(1);
    EXPECT_CALL(*mocked_node_ptr_, Shutdown()).Times(1);

    // When
    runner_.RunOnce();
}

TEST_F(NodeRunnerFixture, RunForDuration_ExpectNodeStepMultipleTimes)
{
    // Given
    constexpr std::chrono::milliseconds kTestDuration{120UL};
    ASSERT_TRUE(runner_.IsNodeRegistered(node_name_));

    // Then
    constexpr std::int32_t times = kTestDuration / kDefaultCycleDuration;
    EXPECT_CALL(*mocked_node_ptr_, Init()).Times(1);
    EXPECT_CALL(*mocked_node_ptr_, Step()).Times(times);
    EXPECT_CALL(*mocked_node_ptr_, Shutdown()).Times(1);

    // When
    runner_.RunForDuration(kTestDuration);
}
}  // namespace
}  // namespace lifecycle
}  // namespace perception
