#ifndef INC_RSC_SECCAM_FSM_TRANSITION_TABLE_HPP
#define INC_RSC_SECCAM_FSM_TRANSITION_TABLE_HPP

#include <algorithm>
#include <initializer_list>
#include <vector>
#include <boost/optional.hpp>
#include "rsc/seccam/fsm/transition_table_entry.hpp"

namespace rsc {
namespace seccam {
namespace fsm {
	
template<class state_id_t, class event_t>
class transition_table
{
public:
	typedef transition_table<state_id_t, event_t> this_type;
	typedef transition_table_entry<state_id_t, event_t> entry_type;

public:
	transition_table() = default;

	transition_table(const this_type& other) = default;

	transition_table(std::initializer_list<entry_type> list)
		: entries_(list.begin(), list.end())
	{}

	boost::optional<state_id_t> lookup_next_state(const state_id_t& source_state_id, const boost::optional<event_t>& event) const
	{
		auto found_entry = std::find_if(entries_.begin(), entries_.end(),
				[&](const entry_type& entry) {
					return (entry.source() == source_state_id) &&
							(entry.event() == event);
				});

		if (found_entry != entries_.end()) {
			return boost::optional<state_id_t>(found_entry->target());
		}
		else {
			return boost::none;
		}
	}

	size_t size() const
	{
		return entries_.size();
	}

private:
	std::vector<entry_type> entries_;
};

} // namespace fsm
} // namespace seccam
} // namespace rsc
#endif
