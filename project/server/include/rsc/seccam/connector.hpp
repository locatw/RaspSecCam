#ifndef INC_RSC_SECCAM_CONNECTOR_HPP
#define INC_RSC_SECCAM_CONNECTOR_HPP

#include <memory>
#include <vector>
#include <boost/asio.hpp>

namespace rsc {
namespace seccam {
	
class connector
{
public:
	connector();

	void accept(unsigned short port);

	std::vector<char> read(size_t read_byte_size, boost::system::error_code& error);

	void write(const void* data, size_t data_byte_size, boost::system::error_code& error);

	bool is_established() const;

private:
	std::unique_ptr<boost::asio::io_service> io_service_;
	std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
	std::unique_ptr<boost::asio::ip::tcp::socket> socket_;
};

} // namespace seccam
} // namespace rsc

#endif
