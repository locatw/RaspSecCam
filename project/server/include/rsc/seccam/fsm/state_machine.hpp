#ifndef INC_RSC_SECCAM_STATE_MACHINE_HPP
#define INC_RSC_SECCAM_STATE_MACHINE_HPP

#include <algorithm>
#include <memory>
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
		  current_state_()
	{}

	void run()
	{
		current_state_ = create_state(initial_state_);
		current_state_->on_entry();
	}

	state_id_t current_state_id() const
	{
		if (!current_state_) {
			throw std::logic_error("current state is empty");
		}

		return current_state_->id();
	}

	void on_event_occurred(const event_t& event)
	{
		if (!current_state_) {
			return;
		}

		boost::optional<state_id_t> next_state_id = transition_table_.lookup_next_state(current_state_->id(), event);

		if (next_state_id) {
			current_state_ = create_state(*next_state_id);
		}
	}

private:
	std::unique_ptr<state_type> create_state(const state_id_t& state_id)
	{
		using std::placeholders::_1;

		auto state = state_factory_->create(state_id);
		state->event_occurred.connect(std::bind(&this_type::on_event_occurred, this, _1)); 

		return state;
	}

private:
	transition_table_type transition_table_;
	std::unique_ptr<state_factory_type> state_factory_;
	state_id_t initial_state_;
	std::unique_ptr<state_type> current_state_;
};
	
} // namespace fsm
} // namespace seccam
} // namespace rsc

#endif
