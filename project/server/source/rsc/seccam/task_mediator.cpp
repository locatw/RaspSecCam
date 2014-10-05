#include "rsc/seccam/task_mediator.hpp"

namespace rsc {
namespace seccam {
	
task_mediator::task_mediator()
	: frame_queue_(), frame_not_exists_(), frame_queue_mutex_()
{}

void task_mediator::request_capturing_permission()
{
	std::unique_lock<std::mutex> lock(frame_queue_mutex_);
	if (!frame_queue_.empty()) {
		frame_not_exists_.wait(lock);
	}
}

void task_mediator::put_camera_frame(const std::shared_ptr<camera_frame>& frame)
{
	frame_queue_.push(frame);
}

std::shared_ptr<camera_frame> task_mediator::get_camera_frame()
{
	auto frame = frame_queue_.front();
	pop_from_queue();
	frame_not_exists_.notify_all();

	return frame;
}

void task_mediator::pop_from_queue()
{
	std::lock_guard<std::mutex> lock(frame_queue_mutex_);
	frame_queue_.pop();
}

} // namespace seccam
} // namespace rsc
