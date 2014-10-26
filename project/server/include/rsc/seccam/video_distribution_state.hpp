#ifndef INC_RSC_SECCAM_VIDEO_DISTRIBUTION_STATE_HPP
#define INC_RSC_SECCAM_VIDEO_DISTRIBUTION_STATE_HPP

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <boost/system/error_code.hpp>
#include "rsc/seccam/app_state.hpp"

namespace rsc {
namespace seccam {
	
class capture_worker;
class raw_frame_protocol;

template<class protocol_t>
class send_frame_worker;

class video_distribution_state : public app_state
{
public:
	video_distribution_state(
		std::shared_ptr<capture_worker>& capture_worker,
		std::shared_ptr<send_frame_worker<raw_frame_protocol>>& send_frame_worker);

	void on_entry() override;

private:
	void on_error(const boost::system::error_code& error);

private:
	std::shared_ptr<capture_worker> capture_worker_;
	std::shared_ptr<send_frame_worker<raw_frame_protocol>> send_frame_worker_;
	std::mutex mutex_;
	std::condition_variable error_condition_;
};

} // namespace seccam
} // namespace rsc
#endif
