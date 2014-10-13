#ifndef INC_RSC_SECCAM_SECURITY_CAMERA_HPP
#define INC_RSC_SECCAM_SECURITY_CAMERA_HPP

#include <memory>
#include "rsc/seccam/fsm/state_machine.hpp"
#include "rsc/seccam/app_event.hpp"
#include "rsc/seccam/app_state_id.hpp"

namespace rsc {
namespace seccam {

class camera;
class connector;

class security_camera
{
public:
	security_camera() = default;

	void run();

private:
	typedef fsm::state_machine<app_state_id, app_event> state_machine_type;

private:
	std::unique_ptr<state_machine_type> state_machine_;
	std::shared_ptr<camera> camera_;
	std::shared_ptr<connector> connector_;
};

} // namespace seccam
} // namespace rsc
#endif
