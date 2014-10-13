#include "rsc/seccam/connector.hpp"

namespace asio = boost::asio;

namespace rsc {
namespace seccam {
	
connector::connector()
	: io_service_(), acceptor_(), socket_()
{}

void connector::accept(unsigned short port)
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

void connector::write(const void* data, size_t data_byte_size)
{
	boost::system::error_code error;
	asio::write(*socket_, asio::buffer(data, data_byte_size), error);

	if (error) {
		const std::string message = "cannot send data: " + error.message();
		throw std::runtime_error(message);
	}
}

bool connector::is_established() const
{
	return acceptor_->is_open();
}

} // namespace seccam
} // namespace rsc
