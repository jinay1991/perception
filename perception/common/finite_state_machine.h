///
/// @file
/// @copyright Copyright (c) 2021. MIT License.
///
#ifndef PERCEPTION_COMMON_FINITE_STATE_MACHINE_H
#define PERCEPTION_COMMON_FINITE_STATE_MACHINE_H

#include <functional>
#include <map>

namespace perception
{

template <typename State>
class FiniteStateMachine
{
    static_assert(std::is_enum<State>::value, "State template argument is not of enum type");

  public:
    using Guard = std::function<bool()>;
    using Action = std::function<void()>;

    explicit FiniteStateMachine(const State initial_state)
        : state_actions_{},
          transitions_{},
          transition_actions_{},
          initial_state_{initial_state},
          current_state_{initial_state},
          current_state_actions_{}
    {
    }

    void AddTransition(const State from_state, const State to_state, const Guard& guard) noexcept
    {
        const ToTransition to_transition{to_state, guard};
        transitions_.insert({from_state, to_transition});
    }

    void AddTransitionAction(const State from_state, const State to_state, const Action& transition_action) noexcept
    {
        transition_actions_.insert({std::make_pair(from_state, to_state), transition_action});
    }

    void AddStateAction(const State state,
                        const Action& entry_action = nullptr,
                        const Action& state_action = nullptr,
                        const Action& exit_action = nullptr) noexcept
    {
        ReplaceCurrentActionsIfRelevantForCurrentState(state, entry_action, state_action, exit_action);
        state_actions_[state] = Actions{entry_action, state_action, exit_action};
    }

    void Step()
    {
        if (!WasTransitionToOtherStatePerformed())
        {
            ExecuteAction(current_state_actions_.state_action);
        }
    }

    void Reset() noexcept { SwitchState(initial_state_); }

    State GetCurrentState() const { return current_state_; }

  private:
    struct ToTransition
    {
        State to_state;
        Guard guard;
    };

    struct Actions
    {
        Action entry_action{nullptr};
        Action state_action{nullptr};
        Action exit_action{nullptr};
    };

    struct StateActions
    {
        State state;

        Action entry_action{nullptr};
        Action state_action{nullptr};
        Action exit_action{nullptr};
    };

    using StateActionList = std::map<State, Actions>;
    using Transition = std::pair<State, State>;
    using TransitionList = std::multimap<State, ToTransition>;
    using TransitionActionList = std::map<Transition, Action>;

    bool WasTransitionToOtherStatePerformed()
    {
        const auto possible_transitions = transitions_.equal_range(current_state_);
        for (auto transition = possible_transitions.first; transition != possible_transitions.second; ++transition)
        {
            const auto& to_transition = transition->second;
            if (IsTransitionPossible(to_transition.guard))
            {
                ExecuteAction(current_state_actions_.exit_action);
                ExecuteTransitionAction(std::make_pair(current_state_, to_transition.to_state));
                SwitchState(to_transition.to_state);
                ExecuteAction(current_state_actions_.entry_action);
                return true;
            }
        }
        return false;
    }

    void ExecuteAction(const Action& action)
    {
        if (action != nullptr)
        {
            action();
        }
    }

    void ExecuteTransitionAction(const Transition& transition)
    {
        if (transition_actions_.find(transition) != transition_actions_.end())
        {
            const auto transition_action = transition_actions_.at(transition);
            if (transition_action != nullptr)
            {
                transition_action();
            }
        }
    }

    bool IsTransitionPossible(const Guard& guard) { return ((guard != nullptr) && guard()); }

    void SwitchState(const State state) noexcept
    {
        current_state_ = state;
        if (state_actions_.count(current_state_) == 0)
        {
            current_state_actions_ = {nullptr, nullptr, nullptr};
            return;
        }
        current_state_actions_ = state_actions_.at(current_state_);
    }

    void ReplaceCurrentActionsIfRelevantForCurrentState(const State state,
                                                        const Action& entry_action,
                                                        const Action& state_action,
                                                        const Action& exit_action) noexcept
    {
        if (current_state_ == state)
        {
            current_state_actions_ = Actions{entry_action, state_action, exit_action};
        }
    }

    StateActionList state_actions_;
    TransitionList transitions_;
    TransitionActionList transition_actions_;

    const State initial_state_;

    State current_state_;

    Actions current_state_actions_;
};

}  // namespace perception

#endif  /// PERCEPTION_COMMON_FINITE_STATE_MACHINE_H
