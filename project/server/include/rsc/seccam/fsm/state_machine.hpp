#ifndef INC_RSC_SECCAM_STATE_MACHINE_HPP
#define INC_RSC_SECCAM_STATE_MACHINE_HPP

#include <algorithm>
#include <memory>
#include <stack>
#include <stdexcept>
#include <boost/optional.hpp>
#include "rsc/seccam/fsm/state.hpp"
#include "rsc/seccam/fsm/state_factory.hpp"
#include "rsc/seccam/fsm/transition_table.hpp"
#include "rsc/seccam/fsm/transition_table_entry.hpp"

namespace rsc {
namespace seccam {
namespace fsm {

template<class state_id_t, class event_t>
class state_machine
{
public:
	typedef state_machine<state_id_t, event_t> this_type;
	typedef transition_table<state_id_t, event_t> transition_table_type;
	typedef state<state_id_t, event_t> state_type;
	typedef state_factory<state_id_t, event_t> state_factory_type;

public:
	state_machine(
		transition_table_type& transition_table,
		std::unique_ptr<state_factory_type>& state_factory,
		state_id_t initial_state)
		: transition_table_(transition_table),
		  state_factory_(std::move(state_factory)),
		  initial_state_id_(initial_state),
		  state_stack_(),
		  transition_occurred_(false),
		  event_occurred_(false)
	{}

	void run()
	{
		initialize_state_stack();

		// transit to initial state.
		// no state exists, so pass a null_state as current_state.
		auto null_state = std::shared_ptr<state_type>();
		transit(null_state, initial_state_id_);

		// transit repeatedly until no transition occurred.
		do {
			transition_occurred_ = false;
			event_occurred_ = false;

			auto current_state = get_current_state();
			current_state->on_entry();

			// if no event occurred, check anonymous transition.
			if (!event_occurred_) {
				transit_if_target_state_exists(current_state, boost::none);
			}
		} while (transition_occurred_);
	}

	state_id_t current_state_id() const
	{
		return get_current_state()->id();
	}

	void on_event_occurred(const event_t& event)
	{
		event_occurred_ = true;

		auto current_state = get_current_state();
		transit_if_target_state_exists(current_state, event);
	}

private:
	void transit_if_target_state_exists(std::shared_ptr<state_type>& current_state, const boost::optional<event_t>& occurred_event)
	{
		boost::optional<state_id_t> next_state_id = transition_table_.lookup_next_state(current_state->id(), occurred_event);
		if (next_state_id) {
			transit(current_state, *next_state_id);
		}
	}

	void transit(std::shared_ptr<state_type>& current_state, const state_id_t& next_state_id)
	{
		if (current_state) {
			current_state->on_exit();
			state_stack_.pop();
		}

		auto next_state = create_state(next_state_id);
		state_stack_.push(std::shared_ptr<state_type>(std::move(next_state)));

		transition_occurred_ = true;
	}

	std::shared_ptr<state_type> get_current_state()
	{
		return std::const_pointer_cast<state_type>(static_cast<const state_machine*>(this)->get_current_state());
	}

	std::shared_ptr<const state_type> get_current_state() const
	{
		if (state_stack_.empty()) {
			throw std::logic_error("no current state exists");
		}

		return std::const_pointer_cast<const state_type>(state_stack_.top());
	}

	std::unique_ptr<state_type> create_state(const state_id_t& state_id)
	{
		using std::placeholders::_1;

		auto state = state_factory_->create(state_id);
		state->event_occurred.connect(std::bind(&this_type::on_event_occurred, this, _1)); 

		return state;
	}

	void initialize_state_stack()
	{
		std::stack<std::shared_ptr<state_type>> new_stack;

		state_stack_.swap(new_stack);
	}

private:
	transition_table_type transition_table_;
	std::unique_ptr<state_factory_type> state_factory_;
	state_id_t initial_state_id_;
	// stack a current state to top.
	std::stack<std::shared_ptr<state_type>> state_stack_;
	bool transition_occurred_;
	bool event_occurred_;
};
	
} // namespace fsm
} // namespace seccam
} // namespace rsc

#endif
