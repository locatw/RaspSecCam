#include <stdexcept>
#include <vector>
#include "rsc/server/camera.hpp"
#include "rsc/server/capture_worker.hpp"
#include "rsc/server/task_mediator.hpp"

namespace rsc {
namespace server {

capture_worker::capture_worker(camera& camera, std::shared_ptr<task_mediator>& task_mediator)
	: camera_(camera), task_mediator_(task_mediator), capture_thread_(), capture_thread_canceled_(false)
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
		task_mediator_->request_capturing_permission();

		auto frame = camera_.retrieve();

		task_mediator_->put_camera_frame(frame);

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}

}}
