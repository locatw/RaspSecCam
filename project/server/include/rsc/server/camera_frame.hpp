#ifndef INC_RSC_SERVER_CAMERA_FRAME_HPP
#define INC_RSC_SERVER_CAMERA_FRAME_HPP

#include <cstddef>
#include <vector>

namespace rsc {
namespace server {

class camera_frame
{
public:
	camera_frame() = default;

	~camera_frame() = default;

	explicit camera_frame(const std::vector<unsigned char>& frame);

	size_t size() const;

	unsigned char* data();

	const unsigned char* data() const;

private:
	std::vector<unsigned char> frame_;
};

}}

#endif
