#include "rsc/seccam/capture_worker.hpp"
#include "rsc/seccam/send_frame_worker.hpp"
#include "rsc/seccam/signaling_state.hpp"

namespace rsc {
namespace seccam {
	
signaling_state::signaling_state()
	: state(app_state_id::signaling)
{}

void signaling_state::on_entry()
{
	notify_event(app_event::signaling_succeeded);
}

} // namespace seccam
} // namespace rsc
