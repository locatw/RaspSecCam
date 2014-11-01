#include "rsc/seccam/camera_frame.hpp"

namespace rsc {
namespace seccam {

	camera_frame::camera_frame(
		const camera_format& format,
		size_t width,
		size_t height,
	   	const std::vector<unsigned char>& frame_data)
		: format_(format), width_(width), height_(height), frame_data_(frame_data.begin(), frame_data.end())
	{}

	size_t camera_frame::size() const
	{
		return frame_data_.size();
	}

	size_t camera_frame::width() const
	{
		return width_;
	}

	size_t camera_frame::height() const
	{
		return height_;
	}

	camera_format camera_frame::format() const
	{
		return format_;
	}

	unsigned char* camera_frame::data()
	{
		return frame_data_.data();
	}

	const unsigned char* camera_frame::data() const
	{
		return static_cast<const unsigned char*>(const_cast<camera_frame*>(this)->data());
	}
}
}
