#ifndef RSC_SERVER_SEND_FRAME_WORKER_HPP
#define RSC_SERVER_SEND_FRAME_WORKER_HPP

#include <atomic>
#include <thread>
#include "rsc/server/camera_frame.hpp"
#include "rsc/server/concurrent_queue.hpp"

namespace rsc {
namespace server {

namespace net {
class frame_transfer_service;
} // namespace net

class send_frame_worker
{
public:
	send_frame_worker(
		net::frame_transfer_service& frame_transfer_service,
		concurrent_queue<camera_frame::ptr>::ptr& frame_queue);

	~send_frame_worker() = default;

	void start();

	void stop();

private:
	void send_frame_repeatedly();

private:
	net::frame_transfer_service& frame_transfer_service_;
	concurrent_queue<camera_frame::ptr>::ptr frame_queue_;
	std::thread send_frame_thread_;
	std::atomic<bool> send_frame_thread_canceled_;
};

} // namespace server
} // namespace rsc

#endif
