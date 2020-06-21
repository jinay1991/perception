///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/object/node/object_node.h"

#include "middleware/communication/intra_process_pub_sub_factory.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
class ObjectNodeTest : public ::testing::Test
{
  public:
    ObjectNodeTest() : factory_{}, unit_{factory_} {}

  protected:
    void SetUp() override {}
    void TearDown() override {}

  private:
    middleware::IntraProcessPubSubFactory factory_;
    ObjectNode unit_;
};
}  // namespace
}  // namespace perception
