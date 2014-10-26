#include <stdexcept>
#include <boost/log/trivial.hpp>
#include "rsc/seccam/connector.hpp"

namespace asio = boost::asio;

namespace rsc {
namespace seccam {
	
connector::connector()
	: io_service_(new asio::io_service()), acceptor_(), socket_(new asio::ip::tcp::socket(*io_service_))
{}

void connector::accept(unsigned short port)
{
	if (socket_) {
		socket_->close();
	}
	if (acceptor_) {
		acceptor_->close();
	}
	if (io_service_) {
		io_service_->stop();
	}

	acceptor_ = std::unique_ptr<asio::ip::tcp::acceptor>(
					new asio::ip::tcp::acceptor(
						*io_service_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)));

	BOOST_LOG_TRIVIAL(info) << "wait for connection";

	boost::system::error_code error;
	acceptor_->accept(*socket_, error);

	if (error) {
		throw std::runtime_error("cannot accept");
	}

	auto remote_endpoint = socket_->remote_endpoint();
	BOOST_LOG_TRIVIAL(info) << "connected from " << remote_endpoint.address().to_string();
}

std::vector<char> connector::read(size_t read_byte_size, boost::system::error_code& error)
{
	if (!is_established()) {
		throw std::runtime_error("connection is not established");
	}

	asio::streambuf buffer;
	asio::read(*socket_, buffer, asio::transfer_exactly(read_byte_size), error);

	if (!error || error == asio::error::eof) {
		const char* begin = asio::buffer_cast<const char*>(buffer.data());
		const char* end = begin + buffer.size();
		return std::vector<char>(begin, end);
	}
	else {
		return std::vector<char>();
	}
}

void connector::write(const void* data, size_t data_byte_size, boost::system::error_code& error)
{
	asio::write(*socket_, asio::buffer(data, data_byte_size), error);

	if (error) {
		BOOST_LOG_TRIVIAL(error) << error.message();
	}
}

bool connector::is_established() const
{
	return socket_->is_open();
}

} // namespace seccam
} // namespace rsc
