///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/driver.h"
#include "middleware/lifecycle/node.h"

namespace perception
{
class DriverNode : public middleware::Node
{
  public:
    explicit DriverNode(middleware::IPubSubFactory& factor);

    void Init() override;
    void ExecuteStep() override;
    void Shutdown() override;

  private:
    Driver driver_;
};
}  // namespace perception
