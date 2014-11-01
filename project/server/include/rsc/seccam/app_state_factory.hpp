#ifndef INC_RSC_SECCAM_APP_STATE_FACTORY_HPP
#define INC_RSC_SECCAM_APP_STATE_FACTORY_HPP

#include "rsc/seccam/fsm/state_machine.hpp"
#include "rsc/seccam/app_event.hpp"
#include "rsc/seccam/app_state_id.hpp"

namespace rsc {
namespace seccam {

class camera;
class capture_worker;
class connector;
class encoded_frame_protocol;
class raw_frame_protocol;

template<class protocol_t>
class send_frame_worker;
	
class app_state_factory : public fsm::state_factory<app_state_id, app_event>
{
public:
	app_state_factory(
		std::shared_ptr<camera>& camera,
		std::shared_ptr<connector>& connector,
		std::shared_ptr<capture_worker>& capture_worker,
		std::shared_ptr<send_frame_worker<encoded_frame_protocol>>& send_frame_worker);

	std::unique_ptr<state_type> create(app_state_id id) override;

private:
	std::shared_ptr<camera> camera_;
	std::shared_ptr<connector> connector_;
	std::shared_ptr<capture_worker>& capture_worker_;
	std::shared_ptr<send_frame_worker<encoded_frame_protocol>>& send_frame_worker_;
};

} // namespace seccam
} // namespace rsc

#endif
