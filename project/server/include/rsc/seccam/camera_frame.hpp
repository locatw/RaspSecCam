#ifndef INC_RSC_SECCAM_CAMERA_FRAME_HPP
#define INC_RSC_SECCAM_CAMERA_FRAME_HPP

#include <cstddef>
#include <memory>
#include <vector>
#include "rsc/seccam/camera_format.hpp"

namespace rsc {
namespace seccam {

class camera_frame
{
public:
	typedef std::shared_ptr<camera_frame> ptr;

public:
	camera_frame() = default;

	~camera_frame() = default;

	camera_frame(
		const camera_format& format,
		size_t width,
		size_t height,
		const std::vector<unsigned char>& frame_data);

	size_t size() const;

	size_t width() const;

	size_t height() const;

	camera_format format() const;

	unsigned char* data();

	const unsigned char* data() const;

private:
	camera_format format_;
	size_t width_;
	size_t height_;
	std::vector<unsigned char> frame_data_;
};

}}

#endif
