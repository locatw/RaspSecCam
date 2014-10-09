#include "rsc/seccam/waiting_for_connection_state.hpp"

namespace rsc {
namespace seccam {
	
waiting_for_connection_state::waiting_for_connection_state()
	: state(app_state_id::waiting_for_connection)
{}

void waiting_for_connection_state::on_entry()
{

}

} // namespace seccam
} // namespace rsc
