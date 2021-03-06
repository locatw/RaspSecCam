#include <stdexcept>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "rsc/seccam/fsm/state_machine.hpp"

using ::testing::Invoke;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;
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
	explicit state1() : state(state_id::state1) {}

	void on_entry()
	{
		notify_event(event::event1);
	}
};

class state2 : public state<state_id, event>
{
public:
	explicit state2() : state(state_id::state2) {}

	void on_entry()
	{
		notify_event(event::event2);
	}
};

class test_state_factory : public state_factory<state_id, event>
{
public:
	std::unique_ptr<state_type> create(state_id id) override
	{
		switch (id) {
			case state_id::state1:
				return std::unique_ptr<state_type>(new state1());
			case state_id::state2:
				return std::unique_ptr<state_type>(new state2());
			default:
				throw std::runtime_error("unknown state id");
		}
	}
};

class state1_mock : public state<state_id, event>
{
public:
	state1_mock() : state(state_id::state1)
	{
		ON_CALL(*this, on_entry())
			.WillByDefault(Invoke(std::bind(&state1_mock::notify_event, this, event::event1)));
	}

	MOCK_METHOD0(on_entry, void());

	MOCK_METHOD0(on_exit, void());
};

class state2_mock : public state<state_id, event>
{
public:
	state2_mock() : state(state_id::state2) {}

	MOCK_METHOD0(on_entry, void());

	MOCK_METHOD0(on_exit, void());
};

class state_factory_mock : public state_factory<state_id, event>
{
public:
	MOCK_METHOD1(create_mock, state_type*(state_id));

	std::unique_ptr<state_type> create(state_id id) override
	{
		return std::unique_ptr<state_type>(create_mock(id));
	}
};

typedef transition_table_entry<state_id, event> transition_table_entry_type;
typedef transition_table<state_id, event> transition_table_type;
typedef state_machine<state_id, event> state_machine_type;
typedef state_factory<state_id, event> state_factory_type;

TEST(state_machine_test, CheckInitialState)
{
	auto factory = std::unique_ptr<state_factory_type>(new test_state_factory());
	transition_table_type table;
	state_machine_type machine(table, factory, state_id::state1);

	machine.run();

	EXPECT_EQ(state_id::state1,	machine.current_state_id());
}

TEST(state_machine_test, TransitionSuccessfullyOccurred)
{
	auto factory = std::unique_ptr<state_factory_type>(new test_state_factory());
	transition_table_type table = {
		transition_table_entry_type(state_id::state1, event::event1, state_id::state2)
	};
	state_machine_type machine(table, factory, state_id::state1);

	machine.run();

	EXPECT_EQ(state_id::state2, machine.current_state_id());
}

TEST(state_machine_test, InitialStateDoesNotBeCreatedUntilStateMachineRun)
{
	auto factory_mock = std::unique_ptr<state_factory_mock>(new state_factory_mock());
	EXPECT_CALL(*factory_mock, create_mock(state_id::state1))
		.Times(0);

	auto factory = std::unique_ptr<state_factory_type>(static_cast<state_factory_type*>(factory_mock.release()));
	transition_table_type table;
	state_machine_type machine(table, factory, state_id::state1);
}

TEST(state_machine_test, EachStateCreatedOnceWhenTransitState1ToState2)
{
	auto factory_mock = std::unique_ptr<state_factory_mock>(new state_factory_mock());
	EXPECT_CALL(*factory_mock, create_mock(state_id::state1))
		.Times(1)
		.WillOnce(Return(new state1()));
	EXPECT_CALL(*factory_mock, create_mock(state_id::state2))
		.Times(1)
		.WillOnce(Return(new state2()));

	auto factory = std::unique_ptr<state_factory_type>(static_cast<state_factory_type*>(factory_mock.release()));
	transition_table_type table = {
		transition_table_entry_type(state_id::state1, event::event1, state_id::state2)
	};
	state_machine_type machine(table, factory, state_id::state1);

	machine.run();
}

TEST(state_machine_test, EachStateCreatedInOrderWhenTransitState1ToState2)
{
	InSequence seq;

	auto factory_mock = std::unique_ptr<state_factory_mock>(new state_factory_mock());
	EXPECT_CALL(*factory_mock, create_mock(state_id::state1))
		.WillOnce(Return(new state1()));
	EXPECT_CALL(*factory_mock, create_mock(state_id::state2))
		.WillOnce(Return(new state2()));

	auto factory = std::unique_ptr<state_factory_type>(static_cast<state_factory_type*>(factory_mock.release()));
	transition_table_type table = {
		transition_table_entry_type(state_id::state1, event::event1, state_id::state2)
	};
	state_machine_type machine(table, factory, state_id::state1);

	machine.run();
}

TEST(state_machine_test, OnEntryMethodCalledWhenNoTransitionOccurred)
{
	auto state1_mock_obj = std::unique_ptr<NiceMock<state1_mock>>(new NiceMock<state1_mock>());
	EXPECT_CALL(*state1_mock_obj, on_entry())
		.Times(1);

	auto factory_mock = std::unique_ptr<NiceMock<state_factory_mock>>(new NiceMock<state_factory_mock>());
	ON_CALL(*factory_mock, create_mock(state_id::state1))
		.WillByDefault(Return(state1_mock_obj.release()));

	auto factory = std::unique_ptr<state_factory_type>(static_cast<state_factory_type*>(factory_mock.release()));
	transition_table_type table;
	state_machine_type machine(table, factory, state_id::state1);

	machine.run();
}

TEST(state_machine_test, OnExitMethodDoesNotCalledWhenNoTransitionOccurred)
{
	auto state1_mock_obj = std::unique_ptr<NiceMock<state1_mock>>(new NiceMock<state1_mock>());
	EXPECT_CALL(*state1_mock_obj, on_exit())
		.Times(0);

	auto factory_mock = std::unique_ptr<NiceMock<state_factory_mock>>(new NiceMock<state_factory_mock>());
	ON_CALL(*factory_mock, create_mock(state_id::state1))
		.WillByDefault(Return(state1_mock_obj.release()));

	auto factory = std::unique_ptr<state_factory_type>(static_cast<state_factory_type*>(factory_mock.release()));
	transition_table_type table;
	state_machine_type machine(table, factory, state_id::state1);

	machine.run();
}

TEST(state_machine_test, OnEntryAndOnExitMethodCalledWhenTransitionOccurred)
{
	auto state1_mock_obj = std::unique_ptr<NiceMock<state1_mock>>(new NiceMock<state1_mock>());
	EXPECT_CALL(*state1_mock_obj, on_entry())
		.Times(1);
	EXPECT_CALL(*state1_mock_obj, on_exit())
		.Times(1);

	auto state2_mock_obj = std::unique_ptr<NiceMock<state2_mock>>(new NiceMock<state2_mock>());

	auto factory_mock = std::unique_ptr<NiceMock<state_factory_mock>>(new NiceMock<state_factory_mock>());
	ON_CALL(*factory_mock, create_mock(state_id::state1))
		.WillByDefault(Return(state1_mock_obj.release()));
	ON_CALL(*factory_mock, create_mock(state_id::state2))
		.WillByDefault(Return(state2_mock_obj.release()));

	auto factory = std::unique_ptr<state_factory_type>(static_cast<state_factory_type*>(factory_mock.release()));
	transition_table_type table = {
		transition_table_entry_type(state_id::state1, event::event1, state_id::state2)
	};
	state_machine_type machine(table, factory, state_id::state1);

	machine.run();
}

TEST(state_machine_test, AnonymousTransitionOccurred)
{
	auto state1_mock_obj = std::unique_ptr<NiceMock<state1_mock>>(new NiceMock<state1_mock>());
	ON_CALL(*state1_mock_obj, on_entry())
		.WillByDefault(Return());

	auto state2_mock_obj = std::unique_ptr<NiceMock<state2_mock>>(new NiceMock<state2_mock>());

	auto factory_mock = std::unique_ptr<NiceMock<state_factory_mock>>(new NiceMock<state_factory_mock>());
	ON_CALL(*factory_mock, create_mock(state_id::state1))
		.WillByDefault(Return(state1_mock_obj.release()));
	ON_CALL(*factory_mock, create_mock(state_id::state2))
		.WillByDefault(Return(state2_mock_obj.release()));

	auto factory = std::unique_ptr<state_factory_type>(static_cast<state_factory_type*>(factory_mock.release()));
	transition_table_type table = {
		transition_table_entry_type(state_id::state1, boost::none, state_id::state2)
	};
	state_machine_type machine(table, factory, state_id::state1);

	machine.run();

	EXPECT_EQ(state_id::state2, machine.current_state_id());
}
