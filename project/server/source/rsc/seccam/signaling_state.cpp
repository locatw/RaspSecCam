#include <boost/log/trivial.hpp>
#include "rsc/seccam/camera.hpp"
#include "rsc/seccam/capture_worker.hpp"
#include "rsc/seccam/connector.hpp"
#include "rsc/seccam/signaling_state.hpp"

namespace rsc {
namespace seccam {
	
signaling_state::signaling_state(
	std::shared_ptr<camera>& camera,
	std::shared_ptr<connector>& connector)
	: state(app_state_id::signaling), camera_(camera), connector_(connector)
{}

void signaling_state::on_entry()
{
	try {
		if (!camera_->is_opened()) {
			throw std::runtime_error("camera is not opened");
		}

		const camera_format format = camera_->get_format();
		const size_t width = camera_->get_width();
		const size_t height = camera_->get_height();
		
		write_camera_format(format);
		write_camera_width(width);
		write_camera_height(height);

		notify_event(app_event::signaling_succeeded);
	}
	catch (const std::exception& e) {
		BOOST_LOG_TRIVIAL(error) << e.what();
		notify_event(app_event::error_occurred);
	}
}

void signaling_state::write_camera_format(const camera_format& format)
{
	const std::string format_str = to_string(format);
	boost::system::error_code error;

	BOOST_LOG_TRIVIAL(info) << "send camera format";
	connector_->write(format_str.c_str(), format_str.size(), error);
	if (error) {
		throw std::runtime_error(error.message());
	}
}

void signaling_state::write_camera_width(size_t width)
{
	BOOST_LOG_TRIVIAL(info) << "send camera width";
	write_size(width);
}

void signaling_state::write_camera_height(size_t height)
{
	BOOST_LOG_TRIVIAL(info) << "send camera height";
	write_size(height);
}

void signaling_state::write_size(size_t size)
{
	boost::system::error_code error;
	connector_->write(&size, sizeof(size_t), error);
	if (error) {
		throw std::runtime_error(error.message());
	}
}

} // namespace seccam
} // namespace rsc
