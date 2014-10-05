#ifndef INC_RSC_SECCAM_TASK_MEDIATOR_MOCK_HPP
#define INC_RSC_SECCAM_TASK_MEDIATOR_MOCK_HPP

#include "rsc/seccam/task_mediator.hpp"

namespace rsc {
namespace seccam {
	
class task_mediator_mock : public task_mediator
{
public:
	~task_mediator_mock() = default;

	MOCK_METHOD0(request_capturing_permission, void());

	MOCK_METHOD1(put_camera_frame, void(const std::shared_ptr<camera_frame>&));

	MOCK_METHOD0(get_camera_frame, std::shared_ptr<camera_frame>());
};

} // namespace seccam
} // namespace rsc

#endif
