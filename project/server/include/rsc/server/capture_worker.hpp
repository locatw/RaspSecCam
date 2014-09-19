#ifndef INC_RSC_SERVER_CAPTURE_WORKER_HPP
#define INC_RSC_SERVER_CAPTURE_WORKER_HPP

#include <atomic>
#include <memory>
#include <thread>
#include "concurrent_queue.hpp"

namespace rsc {
namespace server {

class camera;
class camera_frame;
class capture_worker;

class capture_worker
{
public:
	typedef std::shared_ptr<camera_frame> camera_frame_ptr;
	typedef std::shared_ptr<concurrent_queue<camera_frame_ptr>> camera_frame_queue_ptr;

public:
	capture_worker(camera& camera, camera_frame_queue_ptr& frame_queue);

	~capture_worker() = default;

	void start();

	void stop();

private:
	void capture_repeatedly();

private:
	camera& camera_;
	camera_frame_queue_ptr frame_queue_;
	std::thread capture_thread_;
	std::atomic<bool> capture_thread_canceled_;
};

}}

#endif
