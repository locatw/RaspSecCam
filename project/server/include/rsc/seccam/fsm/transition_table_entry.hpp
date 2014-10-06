#ifndef INC_RSC_SECCAM_FSM_TRANSITION_TABLE_ENTRY_HPP
#define INC_RSC_SECCAM_FSM_TRANSITION_TABLE_ENTRY_HPP

namespace rsc {
namespace seccam {
namespace fsm {
	
template<class state_id_t, class event_t>
class transition_table_entry
{
public:
	transition_table_entry(state_id_t source_state, event_t event, state_id_t target_state)
		: source_(source_state), event_(event), target_(target_state)
	{}

	state_id_t source() const
	{
		return source_;
	}

	event_t event() const
	{
		return event_;
	}

	state_id_t target() const
	{
		return target_;
	}

private:
	state_id_t source_;
	event_t event_;
	state_id_t target_;
};

} // namespace fsm
} // namespace seccam
} // namespace rsc
#endif
