///
/// @file
/// @copyright Copyright (c) 2022. NVIDIA Corporation. All Right Reserved.
///
#include "perception/driver/data_source.h"
#include "perception/driver/datatype/test/support/operators.h"
#include "perception/driver/fatigue.h"
#include "perception/driver/parameter_handler.h"
#include "perception/driver/test/support/driver_simulator.h"

#include <benchmark/benchmark.h>

namespace perception
{
namespace driver
{
namespace
{

class FatigueBenchmarkFixture : public ::benchmark::Fixture
{
  public:
    FatigueBenchmarkFixture()
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

    void DriverDrowsy()
    {
        simulator_.MoveHeadDown(5.0_deg);
        simulator_.CloseEyes();
    }

  private:
    ParameterHandler parameter_handler_;
    DataSource data_source_;

    DriverSimulator simulator_;
    Fatigue unit_;
};

BENCHMARK_F(FatigueBenchmarkFixture, DriverIsDrowsy)(benchmark::State& state)
{
    DriverDrowsy();
    RunBenchmarkTest(state);
}

}  // namespace
}  // namespace driver
}  // namespace perception
