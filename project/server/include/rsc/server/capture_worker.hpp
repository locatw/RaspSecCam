#ifndef INC_RSC_SERVER_CAPTURE_WORKER_HPP
#define INC_RSC_SERVER_CAPTURE_WORKER_HPP

#include <atomic>
#include <memory>
#include <thread>
#include "rsc/server/camera_frame.hpp"
#include "rsc/server/concurrent_queue.hpp"

namespace rsc {
namespace server {

class camera;

class capture_worker
{
public:
	capture_worker(camera& camera, concurrent_queue<camera_frame::ptr>::ptr& frame_queue);

	~capture_worker() = default;

	void start();

	void stop();

private:
	void capture_repeatedly();

private:
	camera& camera_;
	concurrent_queue<camera_frame::ptr>::ptr frame_queue_;
	std::thread capture_thread_;
	std::atomic<bool> capture_thread_canceled_;
};

}}

#endif
