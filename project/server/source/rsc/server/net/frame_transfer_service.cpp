#include <stdexcept>
#include "rsc/server/net/frame_transfer_service.hpp"
#include "rsc/server/camera_frame.hpp"

namespace asio = boost::asio;

namespace rsc {
namespace server {
namespace net {

frame_transfer_service::frame_transfer_service()
	: io_service_(), socket_(io_service_)
{}

void frame_transfer_service::connect(const std::string& ip_address, unsigned short port)
{
	const asio::ip::address address = asio::ip::address::from_string(ip_address);

	boost::system::error_code error;
	socket_.connect(asio::ip::tcp::endpoint(address, port), error);

	if (error) {
		throw std::runtime_error("connection failed");
	}
}

void frame_transfer_service::send(const camera_frame::ptr& frame)
{
	const size_t data_size = frame->size();
	send_data(&data_size, sizeof(size_t));

	send_data(frame->data(), data_size);
}

void frame_transfer_service::send_data(const void* data, size_t data_byte_size)
{
	boost::system::error_code error;
	asio::write(socket_, asio::buffer(data, data_byte_size), error);

	if (error) {
		throw std::runtime_error("cannot send data");
	}
}

} // namespace net
} // namespace server
} // namespace rsc
