#ifndef INC_RSC_SERVER_NET_FRAME_TRANSFER_SERVICE_HPP
#define INC_RSC_SERVER_NET_FRAME_TRANSFER_SERVICE_HPP

#include <string>
#include <boost/asio.hpp>
#include "rsc/server/camera_frame.hpp"

namespace rsc {
namespace server {
namespace net {
	
class frame_transfer_service
{
public:
	frame_transfer_service();

	virtual ~frame_transfer_service() = default;

	virtual void connect(const std::string& ip_address, unsigned short port);

	virtual void send(const camera_frame::ptr& frame);

private:
	void send_data(const void* data, size_t data_byte_size);

private:
	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::socket socket_;
};

} // namespace net
} // namespace server
} // namespace rsc

#endif
