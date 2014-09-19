#include "rsc/server/camera_frame.hpp"
#include "rsc/server/raspi_camera.hpp"

namespace rsc {
namespace server { 

bool raspi_camera::open()
{
	return camera_.open();
}

bool raspi_camera::is_opened() const
{
	return camera_.isOpened();
}

size_t raspi_camera::get_frame_size() const
{
	return camera_.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB);
}

std::shared_ptr<camera_frame> raspi_camera::retrieve()
{
	auto frame = std::make_shared<camera_frame>();

	camera_.retrieve(frame->data(), raspicam::RASPICAM_FORMAT_IGNORE);

	return frame;
}


}}
