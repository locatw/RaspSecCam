#include "rsc/seccam/signaling_state.hpp"

namespace rsc {
namespace seccam {
	
signaling_state::signaling_state()
	: state(app_state_id::signaling)
{}

void signaling_state::on_entry()
{

}

} // namespace seccam
} // namespace rsc
