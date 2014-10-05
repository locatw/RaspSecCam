#ifndef RSC_SERVER_SEND_FRAME_WORKER_HPP
#define RSC_SERVER_SEND_FRAME_WORKER_HPP

#include <atomic>
#include <memory>
#include <thread>
#include <boost/asio.hpp>
#include "rsc/server/camera_frame.hpp"

namespace rsc {
namespace server {

namespace net {
class frame_transfer_service;
} // namespace net

class task_mediator;

class send_frame_worker
{
public:
	send_frame_worker(std::shared_ptr<task_mediator>& task_mediator);

	~send_frame_worker() = default;

	void accept(unsigned short port);

	void start();

	void stop();

private:
	void send_frame_repeatedly();

	void send_data(const void* data, size_t data_byte_size);

private:
	std::unique_ptr<boost::asio::io_service> io_service_;
	std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
	std::unique_ptr<boost::asio::ip::tcp::socket> socket_;
	std::shared_ptr<task_mediator> task_mediator_;
	std::thread send_frame_thread_;
	std::atomic<bool> send_frame_thread_canceled_;
};

} // namespace server
} // namespace rsc

#endif
