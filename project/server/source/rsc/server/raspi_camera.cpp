#include <memory>
#include <stdexcept>
#include "rsc/server/camera_frame.hpp"
#include "rsc/server/raspi_camera.hpp"

namespace rsc {
namespace server { 

bool raspi_camera::open()
{
	camera_.setFormat(raspicam::RASPICAM_FORMAT_BGR);

	return camera_.open();
}

bool raspi_camera::is_opened() const
{
	return camera_.isOpened();
}

size_t raspi_camera::get_frame_size() const
{
	return camera_.getImageTypeSize(raspicam::RASPICAM_FORMAT_BGR);
}

std::shared_ptr<camera_frame> raspi_camera::retrieve()
{
	if (!camera_.grab()) {
		throw std::runtime_error("cannot grab");
	}

	std::vector<unsigned char> buffer(this->get_frame_size());
	camera_.retrieve(buffer.data());

	return std::make_shared<camera_frame>(buffer);
}

void raspi_camera::set_width(size_t width)
{
	camera_.setWidth(width);
}

void raspi_camera::set_height(size_t height)
{
	camera_.setHeight(height);
}

}}
