///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "middleware/lifecycle/node.h"
#include "perception/driver/driver.h"

namespace perception
{
class DriverNode : public middleware::Node
{
  public:
    explicit DriverNode(middleware::IPubSubFactory& factory);

    void Init() override;
    void ExecuteStep() override;
    void Shutdown() override;

  private:
    Driver driver_;
};
}  // namespace perception
