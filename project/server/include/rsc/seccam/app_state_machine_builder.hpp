#ifndef INC_RSC_SECCAM_APP_STATE_MACHINE_BUILDER_HPP
#define INC_RSC_SECCAM_APP_STATE_MACHINE_BUILDER_HPP

#include <memory>
#include "rsc/seccam/app_state_id.hpp"
#include "rsc/seccam/app_event.hpp"
#include "rsc/seccam/fsm/state_machine.hpp"

namespace rsc {
namespace seccam {

class app_state_machine_builder
{
public:
	virtual ~app_state_machine_builder() = default;

	std::unique_ptr<fsm::state_machine<app_state_id, app_event>> build(
			std::unique_ptr<fsm::state_factory<app_state_id, app_event>> state_factory);
};

} // namespace seccam
} // namespace rsc

#endif
