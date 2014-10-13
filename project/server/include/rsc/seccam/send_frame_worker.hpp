#ifndef RSC_SECCAM_SEND_FRAME_WORKER_HPP
#define RSC_SECCAM_SEND_FRAME_WORKER_HPP

#include <atomic>
#include <memory>
#include <thread>

namespace rsc {
namespace seccam {

class connector;
class task_mediator;

class send_frame_worker
{
public:
	send_frame_worker(
		std::shared_ptr<task_mediator>& task_mediator,
		std::shared_ptr<connector>& connector);

	~send_frame_worker() = default;

	void start();

	void stop();

private:
	void send_frame_repeatedly();

private:
	std::shared_ptr<task_mediator> task_mediator_;
	std::shared_ptr<connector> connector_;
	std::thread send_frame_thread_;
	std::atomic<bool> send_frame_thread_canceled_;
};

} // namespace seccam
} // namespace rsc

#endif
