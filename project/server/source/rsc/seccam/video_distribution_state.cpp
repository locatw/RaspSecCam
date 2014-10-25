#include <functional>
#include <thread>
#include "rsc/seccam/capture_worker.hpp"
#include "rsc/seccam/send_frame_worker.hpp"
#include "rsc/seccam/video_distribution_state.hpp"

namespace rsc {
namespace seccam {
	
video_distribution_state::video_distribution_state(
	std::shared_ptr<capture_worker>& capture_worker,
	std::shared_ptr<send_frame_worker>& send_frame_worker)
	: state(app_state_id::video_distribution),
	  capture_worker_(capture_worker),
	  send_frame_worker_(send_frame_worker)
{}

void video_distribution_state::on_entry()
{
	using std::placeholders::_1;
	
	try {
		std::unique_lock<std::mutex> lock(mutex_);

		capture_worker_->start();
		send_frame_worker_->start(std::bind(&video_distribution_state::on_error, this, _1));

		error_condition_.wait(lock);

		capture_worker_->stop();
		send_frame_worker_->stop();

		notify_event(app_event::error_occurred);
	}
	catch (...) {
		notify_event(app_event::error_occurred);
	}
}

void video_distribution_state::on_error(const boost::system::error_code& error)
{
	error_condition_.notify_all();
}

} // namespace seccam
} // namespace rsc
