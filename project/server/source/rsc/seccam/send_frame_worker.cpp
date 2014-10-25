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

void send_frame_worker::start(std::function<void(const boost::system::error_code&)> on_error)
{
	send_frame_thread_canceled_ = false;
	send_frame_thread_ = std::thread(&send_frame_worker::send_frame_repeatedly, this, on_error);
}

void send_frame_worker::stop()
{
	send_frame_thread_canceled_ = true;

	if (send_frame_thread_.joinable()) {
		send_frame_thread_.join();
	}
}

void send_frame_worker::send_frame_repeatedly(std::function<void(const boost::system::error_code&)> on_error)
{
	while (!send_frame_thread_canceled_) {
		auto frame = task_mediator_->get_camera_frame();
		const size_t data_size = frame->size();

		{
			boost::system::error_code error;
			
			connector_->write(&data_size, sizeof(size_t), error);
			if (error) {
				on_error(error);
				break;
			}
		}
		{
			boost::system::error_code error;
			
			connector_->write(frame->data(), data_size, error);
			if (error) {
				on_error(error);
				break;
			}
		}
	}
}

} // namespace seccam
} // namespace rsc
