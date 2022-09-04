///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/data_source.h"
#include "perception/driver/datatype/test/support/operators.h"
#include "perception/driver/distraction.h"
#include "perception/driver/parameter_handler.h"
#include "perception/driver/test/support/driver_simulator.h"

#include <benchmark/benchmark.h>

namespace perception
{
namespace driver
{
namespace
{

class DistractionBenchmarkFixture : public ::benchmark::Fixture
{
  public:
    DistractionBenchmarkFixture()
        : parameter_handler_{}, data_source_{}, simulator_{}, unit_{parameter_handler_, data_source_}
    {
    }

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

    void DriverDistracted()
    {
        simulator_.MoveHeadLeft(35.0_deg);
        simulator_.MoveGazeLeft(45.0_deg);
    }

  private:
    ParameterHandler parameter_handler_;
    DataSource data_source_;

    DriverSimulator simulator_;
    Distraction unit_;
};

BENCHMARK_F(DistractionBenchmarkFixture, DriverIsDistracted)(benchmark::State& state)
{
    DriverDistracted();
    RunBenchmarkTest(state);
}

}  // namespace
}  // namespace driver
}  // namespace perception
