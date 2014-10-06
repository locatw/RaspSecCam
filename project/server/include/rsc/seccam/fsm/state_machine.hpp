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
		  initial_state_(initial_state),
		  state_stack_(),
		  transition_occurred_(false)
	{}

	void run()
	{
		initialize_state_stack();

		auto initial_state = create_state(initial_state_);
		state_stack_.push(std::shared_ptr<state_type>(std::move(initial_state)));

		do {
			transition_occurred_ = false;

			auto current_state = get_current_state();
			current_state->on_entry();
		} while (transition_occurred_);
	}

	state_id_t current_state_id() const
	{
		return get_current_state()->id();
	}

	void on_event_occurred(const event_t& event)
	{
		auto current_state = get_current_state();
		boost::optional<state_id_t> next_state_id = transition_table_.lookup_next_state(current_state->id(), event);

		if (next_state_id) {
			state_stack_.pop();
			current_state->on_exit();

			auto next_state = create_state(*next_state_id);
			state_stack_.push(std::shared_ptr<state_type>(std::move(next_state)));

			transition_occurred_ = true;
		}
	}

private:
	std::shared_ptr<state_type> get_current_state()
	{
		return std::const_pointer_cast<state_type>(static_cast<const state_machine*>(this)->get_current_state());
	}

	std::shared_ptr<const state_type> get_current_state() const
	{
		if (state_stack_.empty()) {
			throw std::logic_error("current state is empty");
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
	state_id_t initial_state_;
	std::stack<std::shared_ptr<state_type>> state_stack_;
	bool transition_occurred_;
};
	
} // namespace fsm
} // namespace seccam
} // namespace rsc

#endif
