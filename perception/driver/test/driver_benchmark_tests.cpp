///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "middleware/communication/intra_process_pub_sub_factory.h"
#include "perception/driver/node/driver_node.h"
#include "perception/driver/test/support/driver_consumer_node.h"
#include "perception/driver/test/support/driver_simulator_node.h"

#include <benchmark/benchmark.h>

namespace perception
{
namespace
{

class DriverBenchmarkFixture : public ::benchmark::Fixture
{
  public:
    DriverBenchmarkFixture() : factory_{}, simulator_{factory_}, unit_{factory_}, consumer_{factory_} {}

  protected:
    void SetUp(const benchmark::State& /* state */) override
    {
        simulator_.Init();
        unit_.Init();
        consumer_.Init();
    }

    void TearDown(const benchmark::State& /* state */) override
    {
        simulator_.Shutdown();
        unit_.Shutdown();
        consumer_.Shutdown();
    }

    void RunBenchmarkTest(benchmark::State& state)
    {
        for (auto _ : state)
        {
            state.PauseTiming();
            simulator_.Step();
            state.ResumeTiming();

            unit_.Step();

            state.PauseTiming();
            consumer_.Step();
            state.ResumeTiming();
        }
    }

    void LookStraight() { simulator_.LookStraight(); }

    const FatigueMessage& GetFatigueMessage() const { return consumer_.GetFatigueMessage(); }
    const VisualAttentionMessage& GetVisualAttentionMessage() const { return consumer_.GetVisualAttentionMessage(); }

  private:
    middleware::IntraProcessPubSubFactory factory_;
    DriverSimulatorNode simulator_;
    DriverNode unit_;
    DriverConsumerNode consumer_;
};

BENCHMARK_F(DriverBenchmarkFixture, DriverIsLookingStraight)(benchmark::State& state)
{
    LookStraight();
    RunBenchmarkTest(state);
}

}  // namespace
}  // namespace perception
