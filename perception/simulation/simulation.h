///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License
///
#ifndef PERCEPTION_SIMULATION_SIMULATION_H
#define PERCEPTION_SIMULATION_SIMULATION_H

#include <string>

namespace perception
{
class Simulation
{
  public:
    Simulation();

    void Init();
    void ExecuteStep();
    void Shutdown();

  private:
    std::string configuration_;
};
}  // namespace perception
#endif  /// PERCEPTION_SIMULATION_SIMULATION_H
