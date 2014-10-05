#ifndef INC_RSC_SECCAM_CAPTURE_WORKER_HPP
#define INC_RSC_SECCAM_CAPTURE_WORKER_HPP

#include <atomic>
#include <memory>
#include <thread>
#include "rsc/seccam/camera_frame.hpp"

namespace rsc {
namespace seccam {

class camera;
class task_mediator;

class capture_worker
{
public:
	capture_worker(camera& camera, std::shared_ptr<task_mediator>& task_mediator);

	~capture_worker() = default;

	void start();

	void stop();

private:
	void capture_repeatedly();

private:
	camera& camera_;
	std::shared_ptr<task_mediator> task_mediator_;
	std::thread capture_thread_;
	std::atomic<bool> capture_thread_canceled_;
};

}}

#endif
