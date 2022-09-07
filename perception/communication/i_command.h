///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_COMMUNICATION_I_COMMAND_H
#define PERCEPTION_COMMUNICATION_I_COMMAND_H

#include <memory>

namespace perception
{
namespace communication
{
/// @brief Interface to Command
class ICommand
{
  public:
    /// @brief Default Destructor
    virtual ~ICommand() = default;

    /// @brief Execute the Command
    virtual void Execute() = 0;
};

/// @brief Pointer Instance to ICommand
using CommandPtr = std::unique_ptr<ICommand>;

}  // namespace communication
}  // namespace perception
#endif  /// PERCEPTION_COMMUNICATION_I_COMMAND_H
