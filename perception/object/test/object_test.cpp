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
    void SetUp() override {}
    void TearDown() override {}

  private:
    Object unit_;
};
}  // namespace
}  // namespace perception