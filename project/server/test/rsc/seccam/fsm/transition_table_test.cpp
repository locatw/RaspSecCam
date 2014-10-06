#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "rsc/seccam/fsm/transition_table.hpp"

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

typedef transition_table_entry<state_id, event> transition_table_entry_type;
typedef transition_table<state_id, event> transition_table_type;

TEST(transition_table_test, ConstructSingleEntryTable)
{
	transition_table_type table = {
		transition_table_entry_type(state_id::state1, event::event1, state_id::state1)
	};

	EXPECT_EQ(1, table.size());
}

TEST(transition_table_test, ConstructTwoEntryTable)
{
	transition_table_type table = {
		transition_table_entry_type(state_id::state1, event::event1, state_id::state1),
		transition_table_entry_type(state_id::state1, event::event1, state_id::state2)
	};

	EXPECT_EQ(2, table.size());
}
