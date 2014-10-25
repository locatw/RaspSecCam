#include "rsc/seccam/connector.hpp"
#include "rsc/seccam/waiting_for_connection_state.hpp"

namespace rsc {
namespace seccam {
	
waiting_for_connection_state::waiting_for_connection_state(std::shared_ptr<connector>& connector)
	: app_state(app_state_id::waiting_for_connection), connector_(connector)
{}

void waiting_for_connection_state::on_entry()
{
	app_state::on_entry();

	connector_->accept(31400);

	notify_event(app_event::connection_established);
}

} // namespace seccam
} // namespace rsc
