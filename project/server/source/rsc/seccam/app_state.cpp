#include <functional>
#include <stdexcept>
#include <string>
#include <boost/format.hpp>
#include <boost/log/trivial.hpp>
#include "rsc/seccam/app_state.hpp"

namespace {
	std::string to_state_name(const rsc::seccam::app_state_id& state_id)
	{
		switch (state_id) {
			case rsc::seccam::app_state_id::camera_setting:
				return "camera setting";
			case rsc::seccam::app_state_id::signaling:
				return "signaling";
			case rsc::seccam::app_state_id::video_distribution:
				return "video distribution";
			case rsc::seccam::app_state_id::waiting_for_connection:
				return "waiting for connection";
			default:
				throw std::logic_error("unknown app state id");
		}
	}

	std::string to_event_name(const rsc::seccam::app_event& event)
	{
		using rsc::seccam::app_event;

		switch (event) {
			case app_event::connection_established:
				return "connection established";
			case app_event::error_occurred:
				return "error occurred";
			case app_event::signaling_succeeded:
				return "signaling succeeded";
			default:
				throw std::logic_error("unknown app event");
		}
	}
}

namespace rsc {
namespace seccam {

app_state::app_state(const app_state_id& state_id)
	: state(state_id)
{
	using std::placeholders::_1;
	event_occurred.connect(std::bind(&app_state::on_event_occurred, this, _1));
}
	
void app_state::on_entry()
{
	BOOST_LOG_TRIVIAL(info) << (boost::format("entered into %1% state") % ::to_state_name(id())).str();
}

void app_state::on_exit()
{
	BOOST_LOG_TRIVIAL(info) << (boost::format("exit from %1% state") % ::to_state_name(id())).str();
}

void app_state::on_event_occurred(const app_event& event)
{
	const std::string event_name = ::to_event_name(event) + " event";
	BOOST_LOG_TRIVIAL(info) << (boost::format("%1% event occurred") % ::to_event_name(event)).str();
}

} // namespace seccam
} // namespace rsc
