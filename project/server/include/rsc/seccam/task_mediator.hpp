#ifndef INC_RSC_SECCAM_TASK_MEDIATOR_HPP
#define INC_RSC_SECCAM_TASK_MEDIATOR_HPP

#include <condition_variable>
#include <memory>
#include <mutex>
#include "rsc/seccam/concurrent_queue.hpp"

namespace rsc {
namespace seccam {

class camera_frame;

class task_mediator
{
public:
	task_mediator();

	virtual ~task_mediator() = default;

	virtual void request_capturing_permission();

	virtual void put_camera_frame(const std::shared_ptr<camera_frame>& frame);

	virtual std::shared_ptr<camera_frame> get_camera_frame();

	virtual void notify_disconnection();

private:
	void pop_from_queue();

private:
	concurrent_queue<std::shared_ptr<camera_frame>> frame_queue_;
	std::condition_variable frame_not_exists_;
	std::mutex frame_queue_mutex_;
};

} // namespace seccam
} // namespace rsc

#endif
