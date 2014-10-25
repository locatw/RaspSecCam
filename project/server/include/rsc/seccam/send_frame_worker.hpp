#ifndef RSC_SECCAM_SEND_FRAME_WORKER_HPP
#define RSC_SECCAM_SEND_FRAME_WORKER_HPP

#include <atomic>
#include <functional>
#include <memory>
#include <thread>
#include <boost/system/error_code.hpp>

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

	~send_frame_worker();

	void start(std::function<void(const boost::system::error_code&)> on_error);

	void stop();

private:
	void send_frame_repeatedly(std::function<void(const boost::system::error_code&)> on_error);

private:
	std::shared_ptr<task_mediator> task_mediator_;
	std::shared_ptr<connector> connector_;
	std::thread send_frame_thread_;
	std::atomic<bool> send_frame_thread_canceled_;
};

} // namespace seccam
} // namespace rsc

#endif
