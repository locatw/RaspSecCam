#ifndef INC_RSC_SECCAM_FSM_TRANSITION_TABLE_ENTRY_HPP
#define INC_RSC_SECCAM_FSM_TRANSITION_TABLE_ENTRY_HPP

#include <boost/optional.hpp>

namespace rsc {
namespace seccam {
namespace fsm {
	
template<class state_id_t, class event_t>
class transition_table_entry
{
public:
	/**
	 * constructor.
	 * when event is boost::none, it indicates anonymous transition.
	 *
	 * @param[in] source_state transition source state
	 * @param[in] event trigger event. if boost::none is specified, transition occurred when no event occurred.
	 * @param[in] target_state transition target state
	 */
	transition_table_entry(state_id_t source_state, const boost::optional<event_t>& event, state_id_t target_state)
		: source_(source_state), event_(event), target_(target_state)
	{}

	state_id_t source() const
	{
		return source_;
	}

	boost::optional<event_t> event() const
	{
		return event_;
	}

	state_id_t target() const
	{
		return target_;
	}

private:
	state_id_t source_;
	boost::optional<event_t> event_;
	state_id_t target_;
};

} // namespace fsm
} // namespace seccam
} // namespace rsc
#endif
