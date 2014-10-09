#ifndef INC_RSC_SECCAM_APP_STATE_ID_HPP
#define INC_RSC_SECCAM_APP_STATE_ID_HPP

namespace rsc {
namespace seccam {

enum class app_state_id
{
	camera_setting,
	waiting_for_connection,
	signaling,
	video_distribution
};

} // namespace seccam
} // namespace rsc
#endif
