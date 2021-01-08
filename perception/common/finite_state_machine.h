///
/// @file
/// @copyright Copyright (c) 2021. MIT License.
///
#ifndef PERCEPTION_COMMON_FINITE_STATE_MACHINE_H
#define PERCEPTION_COMMON_FINITE_STATE_MACHINE_H

#include <functional>
#include <map>
#include <type_traits>

namespace perception
{

/// @brief Simple Finite State Machine
///
/// @tparam T - State Type (must be enum/enum class type)
template <typename T>
class FiniteStateMachine final
{
  public:
    /// @brief State Transition Guard (function) type
    using Guard = std::function<bool()>;

    /// @brief State Transition Action (function) type
    using Action = std::function<void()>;

    /// @brief Default Constructor (Initializes initial state to 0U)
    inline constexpr FiniteStateMachine() : FiniteStateMachine{static_cast<T>(0U)} {}

    /// @brief Constructor.
    ///
    /// @param initial_state [in] - Initial State for State Machine
    inline constexpr explicit FiniteStateMachine(const T initial_state) noexcept
        : state_actions_{},
          transitions_{},
          transition_actions_{},
          initial_state_{initial_state},
          current_state_{initial_state_},
          current_state_actions_{}
    {
        static_assert(std::is_enum<T>::value, "State type must be enum/enum class type.");
    }

    /// @brief Add Transition to State Machine - Registers transition guard, which will be used to check if
    /// transition from -> to state possible or not.
    ///
    /// @param from_state [in] - Transition from State
    /// @param to_state [in] - Transition to State
    /// @param guard [in] - Transition Guard
    inline constexpr void AddTransition(const T from_state, const T to_state, const Guard& guard) noexcept
    {
        const ToTransition to_transition{to_state, guard};
        transitions_.insert({from_state, to_transition});
    }

    /// @brief Add Transition action to State Machine - Registers transition action, which will be executed upon
    /// transition from -> to state
    ///
    /// @param from_state [in] - Transition from State
    /// @param to_state [in] - Transition to State
    /// @param action [in] - Transition action
    inline constexpr void AddTransitionAction(const T from_state, const T to_state, const Action& action) noexcept
    {
        const Transition transition{from_state, to_state};
        transition_actions_.insert({transition, action});
    }

    /// @brief Add State Action. To be executed based on entry/exit or during state if set.
    ///
    /// @param state [in] - State for which actions to be registered
    /// @param entry_action [in] - Registers action to be executed while entering the state
    /// @param state_action [in] - Registers action to be executed while in state
    /// @param exit_action [in] - Registers action to be executed while exiting the state
    inline constexpr void AddStateActions(const T state,
                                          const Action& entry_action = nullptr,
                                          const Action& state_action = nullptr,
                                          const Action& exit_action = nullptr) noexcept
    {
        ReplaceCurrentActionsIfRelevant(state, entry_action, state_action, exit_action);
        state_actions_.insert({state, Actions{entry_action, state_action, exit_action}});
    }

    /// @brief Check for State Transition, if possible performs transitions and executes registered actions.
    inline constexpr void Step()
    {
        if (!PerformStateTransition())
        {
            ExecuteAction(current_state_actions_.state_action);
        }
    }

    /// @brief Resets state to initial state.
    /// @note Registered transitions and actions will be unchanged. If intended to reset them as well, create new object
    /// instead.
    inline constexpr void Reset() noexcept { ChangeState(initial_state_); }

    /// @brief Provide current state of State Machine
    ///
    /// @return current_state
    inline constexpr T GetCurrentState() const noexcept { return current_state_; }

  private:
    /// @brief Transition (transition state and guard to check)
    struct ToTransition
    {
        /// @brief State to which transition to be performed if Guard is passed
        T to_state{};

        /// @brief Guard to be checked to allow transition
        Guard guard{nullptr};
    };

    /// @brief State Action
    struct Actions
    {
        /// @brief State Entry Action. To be called upon entering the state.
        Action entry_action{nullptr};

        /// @brief State Action. To be called everytime till in same state.
        Action state_action{nullptr};

        /// @brief State Exit Action. To be called upon leaving the state.
        Action exit_action{nullptr};
    };

    /// @brief State actions list map. Hold all the registered state actions as to map actions with its associated
    /// states
    using StateActionsList = std::map<T, Actions>;

    /// @brief Transition (from -> to) state pair
    using Transition = std::pair<T, T>;

    /// @brief State Transition information map. Hold transition informations including guard.
    /// @note It can hold (many to many relation) values - one state can have multiple to_transition. Due to this,
    /// multimap is preferred here.
    using TransitionList = std::multimap<T, ToTransition>;

    /// @brief State Transition Action map. Hold transitions actions for each defined Transition pair (from -> to)
    using TransitionActionList = std::map<Transition, Action>;

    /// @brief Perform State Transition if not performed already
    ///
    /// @return True if state transition successfully performed, otherwise False.
    inline constexpr bool PerformStateTransition()
    {
        const auto possible_transitions = transitions_.equal_range(current_state_);
        for (auto transition = possible_transitions.first; transition != possible_transitions.second; ++transition)
        {
            const auto& to_transition = transition->second;
            if (IsTransitionPossible(to_transition.guard))
            {
                ExecuteAction(current_state_actions_.exit_action);
                ExecuteTransitionAction(std::make_pair(current_state_, to_transition.to_state));
                ChangeState(to_transition.to_state);
                ExecuteAction(current_state_actions_.entry_action);
                return true;
            }
        }
        return false;
    }

    /// @brief Execute provided action if available
    ///
    /// @param action [in] - Action to be executed
    inline constexpr void ExecuteAction(const Action& action)
    {
        if (action != nullptr)
        {
            action();
        }
    }

    /// @brief Execute Transition actions for provided Transition if available
    ///
    /// @param transition [in] - Transition to be checked for it's transition actions
    inline constexpr void ExecuteTransitionAction(const Transition& transition)
    {
        if (transition_actions_.find(transition) != transition_actions_.end())
        {
            const auto transition_action = transition_actions_.at(transition);
            ExecuteAction(transition_action);
        }
    }

    /// @brief Check if transition is possible based on the provided guard. Executes guard in order to determine this.
    ///
    /// @return True if guard is available and passed, otherwise False
    inline constexpr bool IsTransitionPossible(const Guard& guard) { return ((guard != nullptr) && guard()); }

    /// @brief Change state to new state
    ///
    /// @param state [in] - State to switch to
    inline constexpr void ChangeState(const T state) noexcept
    {
        current_state_ = state;
        if (state_actions_.count(current_state_) == 0)
        {
            current_state_actions_ = Actions{nullptr, nullptr, nullptr};
            return;
        }
        current_state_actions_ = state_actions_.at(current_state_);
    }

    /// @brief Replace current actions if provided state matches current_state
    ///
    /// @param state [in] - state associated with actions
    /// @param entry_action [in] - State Entry action
    /// @param state_action [in] - State action
    /// @param exit_action [in] - State Exit action
    inline constexpr void ReplaceCurrentActionsIfRelevant(const T state,
                                                          const Action& entry_action,
                                                          const Action& state_action,
                                                          const Action& exit_action) noexcept
    {
        if (current_state_ == state)
        {
            current_state_actions_ = Actions{entry_action, state_action, exit_action};
        }
    }

    /// @brief List of state actions
    StateActionsList state_actions_;

    /// @brief List of transitions
    TransitionList transitions_;

    /// @brief List of transition actions
    TransitionActionList transition_actions_;

    /// @brief Initial State
    const T initial_state_;

    /// @brief Current State
    T current_state_;

    /// @brief Current State action
    Actions current_state_actions_;
};

}  // namespace perception

#endif  /// PERCEPTION_COMMON_FINITE_STATE_MACHINE_H
