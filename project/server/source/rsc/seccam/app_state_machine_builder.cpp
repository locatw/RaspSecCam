#include "rsc/seccam/app_state_machine_builder.hpp"
#include "rsc/seccam/camera_setting_state.hpp"
#include "rsc/seccam/video_distribution_state.hpp"
#include "rsc/seccam/signaling_state.hpp"
#include "rsc/seccam/waiting_for_connection_state.hpp"

namespace rsc {
namespace seccam {

class app_state_factory : public fsm::state_factory<app_state_id, app_event>
{
public:
	std::unique_ptr<state_type> create(app_state_id id) override
	{
		switch (id) {
			case app_state_id::camera_setting:
				return std::unique_ptr<state_type>(new camera_setting_state());
			case app_state_id::waiting_for_connection:
				return std::unique_ptr<state_type>(new waiting_for_connection_state());
			case app_state_id::signaling:
				return std::unique_ptr<state_type>(new signaling_state());
			case app_state_id::video_distribution:
				return std::unique_ptr<state_type>(new video_distribution_state());
			default:
				throw std::logic_error("unknown app state id");
		}
	}
};

std::unique_ptr<fsm::state_machine<app_state_id, app_event>> app_state_machine_builder::build(
		std::unique_ptr<fsm::state_factory<app_state_id, app_event>> state_factory)
{
	typedef fsm::transition_table_entry<app_state_id, app_event> table_entry_type;
	typedef fsm::state_machine<app_state_id, app_event> state_machine_type;

	fsm::transition_table<app_state_id, app_event> table = {
		table_entry_type(app_state_id::camera_setting, boost::none, app_state_id::waiting_for_connection),
		table_entry_type(app_state_id::waiting_for_connection, app_event::connection_established, app_state_id::signaling),
		table_entry_type(app_state_id::signaling, app_event::signaling_succeeded, app_state_id::video_distribution)
	};

	return std::unique_ptr<state_machine_type>(new state_machine_type(table, state_factory, app_state_id::camera_setting));
}

} // namespace seccam
} // namespace rsc
