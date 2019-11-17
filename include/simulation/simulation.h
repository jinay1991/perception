///
/// @file
///
#ifndef SIMULATION_SIMULATION_H_
#define SIMULATION_SIMULATION_H_

#include <string>

namespace sim
{
class Simulation
{
  public:
    Simulation(const std::string& video_file);
    void Run();
};
}  // namespace sim
#endif  /// SIMULATION_SIMULATION_H_