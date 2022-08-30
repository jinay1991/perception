///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_NODE_DRIVER_NODE_H
#define PERCEPTION_DRIVER_NODE_DRIVER_NODE_H

#include "perception/driver/i_driver.h"
#include "perception/lifecycle/node.h"

#include <memory>

namespace perception
{
namespace driver
{

/// @brief Driver Node
class DriverNode : public lifecycle::Node
{
  public:
    /// @brief Default Constructor
    DriverNode();

    /// @brief Initialize Driver Node
    void Init() override;

    /// @brief Perform Cyclic Step of the Node
    void Step() override;

    /// @brief Shutdown Driver Node
    void Shutdown() override;

    /// @brief Provides Driver's State information
    ///
    /// @return driver_message
    const DriverMessage& GetDriverMessage() const;

  private:
    /// @brief Instance of Driver Model
    std::unique_ptr<IDriver> driver_;
};

lifecycle::NodePtr CreateDriverNode();

}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_NODE_DRIVER_NODE_H
