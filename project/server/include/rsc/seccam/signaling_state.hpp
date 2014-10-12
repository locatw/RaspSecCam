#ifndef INC_RSC_SECCAM_SIGNALING_STATE_HPP
#define INC_RSC_SECCAM_SIGNALING_STATE_HPP

#include <memory>
#include "rsc/seccam/app_state_id.hpp"
#include "rsc/seccam/app_event.hpp"
#include "rsc/seccam/fsm/state.hpp"

namespace rsc {
namespace seccam {

class send_frame_worker;
	
class signaling_state : public fsm::state<app_state_id, app_event>
{
public:
	signaling_state(std::shared_ptr<send_frame_worker>& send_frame_worker);

	void on_entry() override;

private:
	std::shared_ptr<send_frame_worker>& send_frame_worker_;
};

} // namespace seccam
} // namespace rsc
#endif
