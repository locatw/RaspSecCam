#include <chrono>
#include <thread>
#include <boost/log/trivial.hpp>
#include "rsc/seccam/camera_format.hpp"
#include "rsc/seccam/camera.hpp"
#include "rsc/seccam/camera_setting_state.hpp"

namespace rsc {
namespace seccam {
	
camera_setting_state::camera_setting_state(std::shared_ptr<camera>& camera)
	: app_state(app_state_id::camera_setting), camera_(camera)
{}

void camera_setting_state::on_entry()
{
	app_state::on_entry();

	camera_->set_format(rsc::seccam::camera_format::BGR);
	camera_->set_width(480);
	camera_->set_height(320);

	if (!camera_->open()) {
		throw std::runtime_error("cannot open camera");
	}

	// wait until camera device calibration finished.
	std::this_thread::sleep_for(std::chrono::seconds(3));

	BOOST_LOG_TRIVIAL(info) << "finish camera setting";
}

} // namespace seccam
} // namespace rsc
