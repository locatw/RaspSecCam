#ifndef INC_RSC_SECCAM_SIGNALING_STATE_HPP
#define INC_RSC_SECCAM_SIGNALING_STATE_HPP

#include "rsc/seccam/app_state_id.hpp"
#include "rsc/seccam/app_event.hpp"
#include "rsc/seccam/fsm/state.hpp"

namespace rsc {
namespace seccam {
	
class signaling_state : public fsm::state<app_state_id, app_event>
{
public:
	signaling_state();

	void on_entry() override;
};

} // namespace seccam
} // namespace rsc
#endif
