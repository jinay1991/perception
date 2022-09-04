///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/driver.h"
#include "perception/driver/test/support/driver_simulator.h"

#include <benchmark/benchmark.h>

namespace perception
{
namespace driver
{
namespace
{

class DriverBenchmarkFixture : public ::benchmark::Fixture
{
  public:
    DriverBenchmarkFixture() : simulator_{}, unit_{} {}

  protected:
    void RunBenchmarkTest(benchmark::State& state)
    {
        for (auto _ : state)
        {
            state.PauseTiming();
            simulator_.Step();
            state.ResumeTiming();

            unit_.Step();
        }
    }

    void LookStraight() { simulator_.LookStraight(); }

  private:
    DriverSimulator simulator_;
    Driver unit_;
};

BENCHMARK_F(DriverBenchmarkFixture, DriverIsLookingStraight)(benchmark::State& state)
{
    LookStraight();
    RunBenchmarkTest(state);
}

}  // namespace
}  // namespace driver
}  // namespace perception
