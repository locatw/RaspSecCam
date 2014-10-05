#include "rsc/server/send_frame_worker.hpp"
#include "rsc/server/task_mediator.hpp"

namespace asio = boost::asio;

namespace rsc {
namespace server {
	
send_frame_worker::send_frame_worker(std::shared_ptr<task_mediator>& task_mediator)
	: io_service_(),
	  acceptor_(),
	  socket_(),
	  task_mediator_(task_mediator),
	  send_frame_thread_(),
	  send_frame_thread_canceled_(false)
{}

void send_frame_worker::accept(unsigned short port)
{
	io_service_ = std::unique_ptr<asio::io_service>(new asio::io_service());
	acceptor_ = std::unique_ptr<asio::ip::tcp::acceptor>(
					new asio::ip::tcp::acceptor(
						*io_service_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)));
	socket_ = std::unique_ptr<asio::ip::tcp::socket>(new asio::ip::tcp::socket(*io_service_));

	boost::system::error_code error;
	acceptor_->accept(*socket_, error);

	if (error) {
		throw std::runtime_error("cannot accept");
	}
}

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

		send_data(&data_size, sizeof(size_t));
		send_data(frame->data(), data_size);
	}
}

void send_frame_worker::send_data(const void* data, size_t data_byte_size)
{
	boost::system::error_code error;
	asio::write(*socket_, asio::buffer(data, data_byte_size), error);

	if (error) {
		const std::string message = "cannot send data: " + error.message();
		throw std::runtime_error(message);
	}
}

} // namespace server
} // namespace rsc
