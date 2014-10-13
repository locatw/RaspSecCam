#include <memory>
#include <stdexcept>
#include <boost/format.hpp>
#include "rsc/seccam/camera_format.hpp"
#include "rsc/seccam/camera_frame.hpp"
#include "rsc/seccam/raspi_camera.hpp"

namespace {
	std::string to_string(rsc::seccam::camera_format format)
	{
		switch (format) {
			case rsc::seccam::camera_format::BGR:
				return "BGR";
			default:
				const std::string message = (boost::format("unknown camera_format [%1%]") % static_cast<int>(format)).str();
				throw std::logic_error(message);
		}
	}

	std::string to_string(raspicam::RASPICAM_FORMAT format)
	{
		switch (format) {
			case raspicam::RASPICAM_FORMAT_BGR:
				return "RASPICAM_FORMAT_BGR";
			default:
				const std::string message = (boost::format("unknown raspicam::RASPICAM_FORMAT [%1%]") % format).str();
				throw std::logic_error(message);
		}
	}
}

namespace rsc {
namespace seccam { 

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
	return camera_.getImageTypeSize(camera_.getFormat());
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

size_t raspi_camera::get_width() const
{
	return camera_.getWidth();
}

size_t raspi_camera::get_height() const
{
	return camera_.getHeight();
}

camera_format raspi_camera::get_format() const
{
	raspicam::RASPICAM_FORMAT raspi_format = camera_.getFormat();

	switch (raspi_format) {
		case raspicam::RASPICAM_FORMAT_BGR:
			return camera_format::BGR;
		default:
			const std::string message = (boost::format("unknown raspicam format [%1%]") % ::to_string(raspi_format)).str();
			throw std::logic_error(message);
	}
}

void raspi_camera::set_width(size_t width)
{
	camera_.setWidth(width);
}

void raspi_camera::set_height(size_t height)
{
	camera_.setHeight(height);
}

void raspi_camera::set_format(camera_format format)
{
	raspicam::RASPICAM_FORMAT raspi_format;

	switch (format) {
		case camera_format::BGR:
			raspi_format = raspicam::RASPICAM_FORMAT_BGR;
			break;
		default:
			const std::string message = (boost::format("unknown camera format [%1%]") % ::to_string(format)).str();
			throw std::logic_error(message);
	}

	camera_.setFormat(raspi_format);
}

}}
