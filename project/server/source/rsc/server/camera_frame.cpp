#include "rsc/server/camera_frame.hpp"

namespace rsc {
namespace server {

	camera_frame::camera_frame(const std::vector<unsigned char>& frame)
		: frame_(frame.begin(), frame.end())
	{}

	size_t camera_frame::size() const
	{
		return frame_.size();
	}

	unsigned char* camera_frame::data()
	{
		return frame_.data();
	}

	const unsigned char* camera_frame::data() const
	{
		return static_cast<const unsigned char*>(const_cast<camera_frame*>(this)->data());
	}
}
}
