#include <thread>
#include "rsc/seccam/capture_worker.hpp"
#include "rsc/seccam/video_distribution_state.hpp"

namespace rsc {
namespace seccam {
	
video_distribution_state::video_distribution_state(std::shared_ptr<capture_worker>& capture_worker)
	: state(app_state_id::video_distribution), capture_worker_(capture_worker)
{}

void video_distribution_state::on_entry()
{
	capture_worker_->start();

	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

} // namespace seccam
} // namespace rsc
