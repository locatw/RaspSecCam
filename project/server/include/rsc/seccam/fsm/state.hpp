#ifndef INC_RSC_SECCAM_FSM_STATE_HPP
#define INC_RSC_SECCAM_FSM_STATE_HPP

#include <boost/signals2.hpp>

namespace rsc {
namespace seccam {
namespace fsm {

template<class state_id_t, class event_t>
class state
{
public:
	explicit state(state_id_t id)
		: id_(id)
	{}

	virtual ~state() = default;

	virtual void on_entry()
	{}

	virtual void on_exit()
	{}

	state_id_t id() const
	{
		return id_;
	}

	void notify_event(const event_t& event)
	{
		event_occurred(event);
	}

public:
	boost::signals2::signal<void(const event_t&)> event_occurred;

private:
	state_id_t id_;
};
	
} // namespace fsm
} // namespace seccam
} // namespace rsc

#endif
