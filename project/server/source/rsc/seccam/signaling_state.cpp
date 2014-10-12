#include "rsc/seccam/capture_worker.hpp"
#include "rsc/seccam/send_frame_worker.hpp"
#include "rsc/seccam/signaling_state.hpp"

namespace rsc {
namespace seccam {
	
signaling_state::signaling_state(std::shared_ptr<send_frame_worker>& send_frame_worker)
	: state(app_state_id::signaling), send_frame_worker_(send_frame_worker)
{}

void signaling_state::on_entry()
{
	send_frame_worker_->start();

	notify_event(app_event::signaling_succeeded);
}

} // namespace seccam
} // namespace rsc
