///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/node/driver_node.h"

#include <gtest/gtest.h>

#include <chrono>

namespace perception
{
namespace driver
{
namespace
{
class DriverNodeFixture : public ::testing::Test
{
  public:
    DriverNodeFixture() : driver_{} {}

  protected:
    void SetUp() override { driver_.Init(); }

    void TearDown() override { driver_.Shutdown(); }

    void RunOnce() { driver_.Step(); }

    void RunForDuration(const std::chrono::milliseconds duration)
    {
        using namespace std::chrono_literals;
        constexpr std::chrono::milliseconds kDefaultCycleDuration{40UL};
        for (auto time_passed = 0ms; time_passed < duration; time_passed += kDefaultCycleDuration)
        {
            RunOnce();
        }
    }

    bool IsDriverDrowsy() const { return (driver_.GetDriverMessage().fatigue.state != FatigueState::kAwake); }

  private:
    DriverNode driver_;
};

TEST_F(DriverNodeFixture, RunOnce_GivenTypicalDriverCameraMessage_ExpectDriverDrowsy)
{
    // When
    RunOnce();

    // Then
    EXPECT_FALSE(IsDriverDrowsy());
}

TEST_F(DriverNodeFixture, RunForDuration_GivenTypicalDriverCameraMessage_ExpectDriverDrowsy)
{
    // Given
    using namespace std::chrono_literals;

    // When
    RunForDuration(10ms);

    // Then
    EXPECT_FALSE(IsDriverDrowsy());
}

TEST(DriverNodeTest, CreateDriverNode)
{
    // Given
    lifecycle::NodePtr node{nullptr};

    // When
    EXPECT_NO_THROW(node = CreateDriverNode());

    // Then
    EXPECT_NE(node.get(), nullptr);
    EXPECT_EQ(node->GetName(), "driver_node");
}
}  // namespace
}  // namespace driver
}  // namespace perception
