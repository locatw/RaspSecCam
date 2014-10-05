#ifndef INC_RSC_SECCAM_CAMERA_FRAME_HPP
#define INC_RSC_SECCAM_CAMERA_FRAME_HPP

#include <cstddef>
#include <memory>
#include <vector>

namespace rsc {
namespace seccam {

class camera_frame
{
public:
	typedef std::shared_ptr<camera_frame> ptr;

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
