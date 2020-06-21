///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/object/object.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
class ObjectTest : public ::testing::Test
{
  public:
    ObjectTest() : unit_{} {}

  protected:
    void SetUp() override
    {
        unit_.Init();
        // unit_.SetCameraMessage();
    }
    void RunOnce() { unit_.Step(); }
    void TearDown() override { unit_.Shutdown(); }

    virtual ObjectListMessage GetResults() const { return unit_.GetObjectListMessage(); }

  private:
    Object unit_;
};

TEST_F(ObjectTest, GivenTypicalCameraMessage_ExpectObjects) {}
}  // namespace
}  // namespace perception
