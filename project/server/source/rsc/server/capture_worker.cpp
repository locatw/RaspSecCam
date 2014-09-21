#include <stdexcept>
#include <vector>
#include "rsc/server/camera.hpp"
#include "rsc/server/capture_worker.hpp"

namespace rsc {
namespace server {

capture_worker::capture_worker(camera& camera, concurrent_queue<camera_frame::ptr>::ptr& frame_queue)
	: camera_(camera), frame_queue_(frame_queue), capture_thread_(), capture_thread_canceled_(false)
{}

void capture_worker::start()
{
	if (!camera_.is_opened()) {
		throw std::runtime_error("camera is not opened.");
	}

	capture_thread_ = std::thread(&capture_worker::capture_repeatedly, this);
}

void capture_worker::stop()
{
	capture_thread_canceled_ = true;

	if (capture_thread_.joinable()) {
		capture_thread_.join();
	}
}

void capture_worker::capture_repeatedly()
{
	while (!capture_thread_canceled_) {
		auto frame = camera_.retrieve();
		
		frame_queue_->push(frame);
	}
}

}}
