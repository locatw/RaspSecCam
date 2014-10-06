#include <stdexcept>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "rsc/seccam/fsm/state_machine.hpp"

using namespace rsc::seccam::fsm;

enum class state_id
{
	state1,
	state2
};

enum class event
{
	event1,
	event2
};

class state1 : public state<state_id, event>
{
public:
	explicit state1(state_id id) : state(id) {}

	void on_entry()
	{
		notify_event(event::event1);
	}
};

class state2 : public state<state_id, event>
{
public:
	explicit state2(state_id id) : state(id) {}

	void on_entry()
	{
		notify_event(event::event2);
	}
};

class test_state_factory : public state_factory<state_id, event>
{
public:
	std::unique_ptr<state<state_id, event>> create(state_id id) override
	{
		switch (id) {
			case state_id::state1:
				return std::unique_ptr<state<state_id, event>>(new state1(id));
			case state_id::state2:
				return std::unique_ptr<state<state_id, event>>(new state2(id));
			default:
				throw std::runtime_error("unknown state id");
		}
	}
};

typedef transition_table_entry<state_id, event> transition_table_entry_type;
typedef transition_table<state_id, event> transition_table_type;
typedef state_machine<state_id, event> state_machine_type;


TEST(state_machine_test, CheckInitialState)
{
	auto factory = std::unique_ptr<state_factory<state_id, event>>(new test_state_factory());
	transition_table_type table;
	state_machine_type machine(table, factory, state_id::state1);

	EXPECT_EQ(state_id::state1,	machine.current_state_id());
}

TEST(state_machine_test, TransitionSuccessfullyOccurred)
{
	auto factory = std::unique_ptr<state_factory<state_id, event>>(new test_state_factory());
	transition_table<state_id, event> table = {
		transition_table_entry<state_id, event>(state_id::state1, event::event1, state_id::state2)
	};
	state_machine<state_id, event> machine(table, factory, state_id::state1);

	machine.run();

	EXPECT_EQ(state_id::state2, machine.current_state_id());
}
