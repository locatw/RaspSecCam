#ifndef RSC_SECCAM_SEND_FRAME_WORKER_HPP
#define RSC_SECCAM_SEND_FRAME_WORKER_HPP

#include <atomic>
#include <functional>
#include <memory>
#include <thread>
#include <boost/log/trivial.hpp>
#include <boost/system/error_code.hpp>
#include "rsc/seccam/camera_frame.hpp"
#include "rsc/seccam/connector.hpp"
#include "rsc/seccam/task_mediator.hpp"

namespace rsc {
namespace seccam {

template<class protocol_t>
class send_frame_worker
{
public:
	send_frame_worker(
		std::shared_ptr<task_mediator>& task_mediator,
		std::shared_ptr<connector>& connector)
		: task_mediator_(task_mediator),
		  protocol_(connector),
		  send_frame_thread_(),
		  send_frame_thread_canceled_(false)
	{}

	~send_frame_worker()
	{
		stop();
	}

	void start(std::function<void(const boost::system::error_code&)> on_error)
	{
		send_frame_thread_canceled_ = false;
		send_frame_thread_ = std::thread(&send_frame_worker::send_frame_repeatedly, this, on_error);
	}

	void stop()
	{
		send_frame_thread_canceled_ = true;
	
		if (send_frame_thread_.joinable()) {
			send_frame_thread_.join();
		}
	}

private:
	void send_frame_repeatedly(std::function<void(const boost::system::error_code&)> on_error)
	{
		BOOST_LOG_TRIVIAL(info) << "start sending frame";
	
		while (!send_frame_thread_canceled_) {
			auto frame = task_mediator_->get_camera_frame();
			boost::system::error_code error;

			protocol_.send(frame, error);
			if (error) {
				on_error(error);
				break;
			}
		}
		task_mediator_->notify_disconnection();
	
		BOOST_LOG_TRIVIAL(info) << "sending frame stopped";
	}

private:
	std::shared_ptr<task_mediator> task_mediator_;
	protocol_t protocol_;
	std::thread send_frame_thread_;
	std::atomic<bool> send_frame_thread_canceled_;
};

} // namespace seccam
} // namespace rsc

#endif
