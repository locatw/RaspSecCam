#ifndef INC_RSC_SERVER_CAMERA_HPP
#define INC_RSC_SERVER_CAMERA_HPP

#include <memory>

namespace rsc {
namespace server {

class camera_frame;

class camera
{
public:
	camera() = default;

	virtual ~camera() = default;

	virtual bool open() = 0;

	virtual bool is_opened() const = 0;

	virtual size_t get_frame_size() const = 0;

	virtual std::shared_ptr<camera_frame> retrieve() = 0;

private:
	camera(const camera&) = default;
	camera& operator=(const camera&) = default;
};

}}

#endif
