#ifndef INC_RSC_SECCAM_VIDEO_DISTRIBUTION_STATE_HPP
#define INC_RSC_SECCAM_VIDEO_DISTRIBUTION_STATE_HPP

#include "rsc/seccam/app_state_id.hpp"
#include "rsc/seccam/app_event.hpp"
#include "rsc/seccam/fsm/state.hpp"

namespace rsc {
namespace seccam {
	
class video_distribution_state : public fsm::state<app_state_id, app_event>
{
public:
	video_distribution_state();

	void on_entry() override;
};

} // namespace seccam
} // namespace rsc
#endif
