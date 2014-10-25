#ifndef INC_RSC_SECCAM_CAMERA_SETTING_STATE_HPP
#define INC_RSC_SECCAM_CAMERA_SETTING_STATE_HPP

#include "rsc/seccam/app_state.hpp"

namespace rsc {
namespace seccam {

class camera;

class camera_setting_state : public app_state
{
public:
	camera_setting_state(std::shared_ptr<camera>& camera);

	void on_entry() override;

private:
	std::shared_ptr<camera> camera_;
};

} // namespace seccam
} // namespace rsc
#endif
