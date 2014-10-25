#ifndef RSC_SECCAM_APP_STATE_HPP
#define RSC_SECCAM_APP_STATE_HPP

#include "rsc/seccam/fsm/state.hpp"
#include "rsc/seccam/app_state_id.hpp"
#include "rsc/seccam/app_event.hpp"

namespace rsc {
namespace seccam {

class app_state : public fsm::state<app_state_id, app_event>
{
public:
	app_state(const app_state_id& state_id);

	virtual ~app_state() = default;

	/**
	 * derived class must call app_state::on_entry. 
	 */
	virtual void on_entry() override;

	/**
	 * derived class must call app_state::on_exit. 
	 */
	virtual void on_exit() override;

	void on_event_occurred(const app_event& event);
};

} // namespace seccam
} // namespace rsc
#endif
