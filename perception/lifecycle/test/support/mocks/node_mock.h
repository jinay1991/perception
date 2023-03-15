///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/lifecycle/i_node.h"

#include <gmock/gmock.h>

#include <string>

namespace perception
{
namespace lifecycle
{
namespace test
{
namespace support
{
class NodeMock : public INode
{
  public:
    NodeMock() = default;

    MOCK_METHOD0(Init, void());
    MOCK_METHOD0(Step, void());
    MOCK_METHOD0(Shutdown, void());
    MOCK_CONST_METHOD0(GetName, std::string());
};
}  // namespace support
}  // namespace test
}  // namespace lifecycle
}  // namespace perception
