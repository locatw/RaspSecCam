#include "rsc/seccam/camera_frame.hpp"
#include "rsc/seccam/connector.hpp"
#include "rsc/seccam/send_frame_worker.hpp"
#include "rsc/seccam/task_mediator.hpp"

namespace asio = boost::asio;

namespace rsc {
namespace seccam {
	
send_frame_worker::send_frame_worker(
	std::shared_ptr<task_mediator>& task_mediator,
	std::shared_ptr<connector>& connector)
	: task_mediator_(task_mediator),
	  connector_(connector),
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
		auto frame = task_mediator_->get_camera_frame();
		const size_t data_size = frame->size();

		connector_->write(&data_size, sizeof(size_t));
		connector_->write(frame->data(), data_size);
	}
}

} // namespace seccam
} // namespace rsc
