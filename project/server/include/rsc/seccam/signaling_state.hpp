#ifndef INC_RSC_SECCAM_SIGNALING_STATE_HPP
#define INC_RSC_SECCAM_SIGNALING_STATE_HPP

#include <memory>
#include <boost/optional.hpp>
#include "rsc/seccam/app_state_id.hpp"
#include "rsc/seccam/app_event.hpp"
#include "rsc/seccam/camera_format.hpp"
#include "rsc/seccam/fsm/state.hpp"

namespace rsc {
namespace seccam {

class camera;
class connector;
	
class signaling_state : public fsm::state<app_state_id, app_event>
{
public:
	signaling_state(
		std::shared_ptr<camera>& camera,
		std::shared_ptr<connector>& connector);

	void on_entry() override;

private:
	void write_camera_format(const camera_format& format);

	void write_camera_width(size_t width);

	void write_camera_height(size_t height);

	void write_size(size_t size);

private:
	std::shared_ptr<camera> camera_;
	std::shared_ptr<connector>& connector_;
};

} // namespace seccam
} // namespace rsc
#endif
