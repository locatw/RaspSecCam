#ifndef INC_RSC_SECCAM_WAITING_FOR_CONNECTION_STATE_HPP
#define INC_RSC_SECCAM_WAITING_FOR_CONNECTION_STATE_HPP

#include <memory>
#include "rsc/seccam/app_state.hpp"

namespace rsc {
namespace seccam {

class connector;
	
class waiting_for_connection_state : public app_state
{
public:
	waiting_for_connection_state(std::shared_ptr<connector>& connector);

	void on_entry() override;

private:
	std::shared_ptr<connector> connector_;
};

} // namespace seccam
} // namespace rsc
#endif
