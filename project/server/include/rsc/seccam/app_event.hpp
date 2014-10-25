#ifndef INC_RSC_SECCAM_APP_EVENT_HPP
#define INC_RSC_SECCAM_APP_EVENT_HPP

namespace rsc {
namespace seccam {
	
enum class app_event
{
	connection_established,
	signaling_succeeded,
	error_occurred
};

} // namespace seccam
} // namespace rsc
#endif
