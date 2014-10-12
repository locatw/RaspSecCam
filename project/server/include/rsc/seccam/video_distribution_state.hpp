#ifndef INC_RSC_SECCAM_VIDEO_DISTRIBUTION_STATE_HPP
#define INC_RSC_SECCAM_VIDEO_DISTRIBUTION_STATE_HPP

#include <memory>
#include "rsc/seccam/app_state_id.hpp"
#include "rsc/seccam/app_event.hpp"
#include "rsc/seccam/fsm/state.hpp"

namespace rsc {
namespace seccam {
	
class capture_worker;

class video_distribution_state : public fsm::state<app_state_id, app_event>
{
public:
	video_distribution_state(std::shared_ptr<capture_worker>& capture_worker);

	void on_entry() override;

private:
	std::shared_ptr<capture_worker>& capture_worker_;
};

} // namespace seccam
} // namespace rsc
#endif
