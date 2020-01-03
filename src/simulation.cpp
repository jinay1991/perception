///
/// @file
///
#include "simulation/simulation.h"

namespace sim
{
Simulation::Simulation() {}

void Simulation::Run()
{
    perception::Perception perception;
    perception.Run("data/grace_hopper.jpg");
}

}  // namespace sim
