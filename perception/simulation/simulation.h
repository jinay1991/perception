///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_SIMULATION_SIMULATION_H_
#define PERCEPTION_SIMULATION_SIMULATION_H_

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
#endif  /// PERCEPTION_SIMULATION_SIMULATION_H_