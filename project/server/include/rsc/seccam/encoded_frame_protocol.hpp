#ifndef INC_RSC_SECCAM_ENCODED_FRAME_PROTOCOL_HPP
#define INC_RSC_SECCAM_ENCODED_FRAME_PROTOCOL_HPP

#include <memory>
#include <boost/system/error_code.hpp>

namespace rsc {
namespace seccam {

class camera_frame;
class connector;

/**
 * this class is a communication protocol that sends camera frame data after encoding.
 */
class encoded_frame_protocol
{
public:
	explicit encoded_frame_protocol(std::shared_ptr<connector>& connector);

	void send(const std::shared_ptr<camera_frame>& frame, boost::system::error_code& error);

private:
	std::shared_ptr<connector> connector_;
};

} // namespace seccam
} // namespace rsc

#endif
