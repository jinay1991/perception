///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/lane/lane.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
class LaneTest : public ::testing::Test
{
  public:
    LaneTest() : unit_{} {}

  protected:
    void SetUp() override { unit_.Init(); }
    void RunOnce() { unit_.Step(); }
    void TearDown() override { unit_.Shutdown(); }

    const LaneMessage& GetResults() const { return unit_.GetLaneMessage(); }

  private:
    Lane unit_;
};

TEST_F(LaneTest, GivenTypicalInputs_ExpectLaneDetection)
{
    // When
    RunOnce();

    // Then
    const auto& result = GetResults();
    EXPECT_EQ(LaneId::kInvalid, result.id);
    EXPECT_EQ(LaneType::kInvalid, result.type);
}

}  // namespace
}  // namespace perception
