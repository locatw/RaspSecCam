#ifndef INC_RSC_SECCAM_FSM_STATE_FACTORY_HPP
#define INC_RSC_SECCAM_FSM_STATE_FACTORY_HPP

#include <memory>

namespace rsc {
namespace seccam {
namespace fsm {
	
template<class state_id_t, class event_t>
class state_factory
{
public:
	typedef state<state_id_t, event_t> state_type;

public:
	state_factory() = default;

	virtual ~state_factory() = default;

	virtual std::unique_ptr<state_type> create(state_id_t id) = 0;
};

} // namespace fsm
} // namespace seccam
} // namespace rsc

#endif
