///
/// @file
/// @copyright Copyright (C) 2021. MIT License.
///
#include "perception/common/finite_state_machine.h"

#include <benchmark/benchmark.h>

#include <chrono>

namespace perception
{
namespace
{
using namespace std::chrono_literals;

constexpr std::chrono::milliseconds kDefaultCycleDuration{40ms};
constexpr std::chrono::milliseconds kTimeTransitionToRun{1min};
constexpr std::chrono::milliseconds kTimeTransitionToRelease{5min};
constexpr std::chrono::milliseconds kTimeTransitionToInit{6min};

enum class State : std::uint8_t
{
    kInit = 0U,
    kRun = 2U,
    kRelease = 4U,
    kInvalid = 5U
};

class FiniteStateMachineBenchmarkFixture : public benchmark::Fixture
{
  public:
    FiniteStateMachineBenchmarkFixture() : state_machine_{State::kInit}, time_since_startup_{0ms} {}

  protected:
    void SetUp(const benchmark::State& /* state */) override
    {
        state_machine_.AddTransition(State::kInit, State::kRun, [&] { return ToRun(); });
        state_machine_.AddTransition(State::kRun, State::kRelease, [&] { return ToRelease(); });
        state_machine_.AddTransition(State::kRelease, State::kInit, [&] { return ToInit(); });
    }
    void TearDown(const benchmark::State& /* state */) override { state_machine_.Reset(); }

    void RunBenchmarkTest(benchmark::State& state)
    {
        for (auto _ : state)
        {
            state.PauseTiming();
            time_since_startup_ += kDefaultCycleDuration;
            state.ResumeTiming();

            state_machine_.Step();
        }
    }

  private:
    constexpr bool IsRunning() const noexcept { return (State::kRun == state_machine_.GetCurrentState()); }

    constexpr bool IsTimeSinceStartupExceeded(const std::chrono::milliseconds duration) const noexcept
    {
        return (time_since_startup_ >= duration);
    }

    constexpr bool ToRun() const noexcept
    {
        return ((!IsRunning()) && IsTimeSinceStartupExceeded(kTimeTransitionToRun));
    }

    constexpr bool ToRelease() const noexcept
    {
        return (IsRunning() && IsTimeSinceStartupExceeded(kTimeTransitionToRelease));
    }

    constexpr bool ToInit() const noexcept
    {
        return (IsRunning() && IsTimeSinceStartupExceeded(kTimeTransitionToInit));
    }

    FiniteStateMachine<State> state_machine_;

    std::chrono::milliseconds time_since_startup_;
};

BENCHMARK_F(FiniteStateMachineBenchmarkFixture, SeveralStateTransitions)(benchmark::State& state)
{
    RunBenchmarkTest(state);
}

}  // namespace
}  // namespace perception
