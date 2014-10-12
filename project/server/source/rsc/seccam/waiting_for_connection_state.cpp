#include "rsc/seccam/send_frame_worker.hpp"
#include "rsc/seccam/waiting_for_connection_state.hpp"

namespace rsc {
namespace seccam {
	
waiting_for_connection_state::waiting_for_connection_state(std::shared_ptr<send_frame_worker>& send_frame_worker)
	: state(app_state_id::waiting_for_connection), send_frame_worker_(send_frame_worker)
{}

void waiting_for_connection_state::on_entry()
{
	send_frame_worker_->accept(31400);

	notify_event(app_event::connection_established);
}

} // namespace seccam
} // namespace rsc
