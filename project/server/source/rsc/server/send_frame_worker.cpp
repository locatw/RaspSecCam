#include "rsc/server/send_frame_worker.hpp"
#include "rsc/server/net/frame_transfer_service.hpp"

namespace rsc {
namespace server {
	
send_frame_worker::send_frame_worker(
	net::frame_transfer_service& frame_transfer_service,
	concurrent_queue<camera_frame::ptr>::ptr& frame_queue)
	: frame_transfer_service_(frame_transfer_service),
	  frame_queue_(frame_queue),
	  send_frame_thread_(),
	  send_frame_thread_canceled_(false)
{}

void send_frame_worker::start()
{
	send_frame_thread_ = std::thread(&send_frame_worker::send_frame_repeatedly, this);
}

void send_frame_worker::stop()
{
	send_frame_thread_canceled_ = true;

	if (send_frame_thread_.joinable()) {
		send_frame_thread_.join();
	}
}

void send_frame_worker::send_frame_repeatedly()
{
	while (!send_frame_thread_canceled_) {
		auto& frame = frame_queue_->front();
		frame_queue_->pop();

		frame_transfer_service_.send(frame);
	}
}

} // namespace server
} // namespace rsc
