///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "middleware/lifecycle/node.h"
#include "perception/driver/driver.h"

namespace perception
{
/// @brief Driver Node
class DriverNode : public middleware::Node
{
  public:
    /// @brief Constructor
    /// @param factory [in] Middleware Publisher/Subscriber Factory
    explicit DriverNode(middleware::IPubSubFactory& factory);

    /// @brief Initialize Driver Node
    void Init() override;

    /// @brief Execute single step for Driver Node
    void ExecuteStep() override;

    /// @brief Shutdown/Deinitialize Camera Node
    void Shutdown() override;

  private:
    /// @brief Instance for Driver (to calculate Fatigue & Visual attention)
    Driver driver_;
};
}  // namespace perception
