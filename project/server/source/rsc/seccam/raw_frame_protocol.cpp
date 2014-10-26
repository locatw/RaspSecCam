#include "rsc/seccam/camera_frame.hpp"
#include "rsc/seccam/connector.hpp"
#include "rsc/seccam/raw_frame_protocol.hpp"

namespace rsc {
namespace seccam {
	
raw_frame_protocol::raw_frame_protocol(std::shared_ptr<connector>& connector)
	: connector_(connector)
{}

void raw_frame_protocol::send(const std::shared_ptr<camera_frame>& frame, boost::system::error_code& error)
{
	const size_t data_size = frame->size();

	connector_->write(&data_size, sizeof(size_t), error);
	if (error) {
		return;
	}

	connector_->write(frame->data(), data_size, error);
	if (error) {
		return;
	}
}

} // namespace seccam
} // namespace rsc
