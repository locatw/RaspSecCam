#ifndef INC_RSC_SERVER_CAMERA_HPP
#define INC_RSC_SERVER_CAMERA_HPP

#include <memory>

namespace rsc {
namespace seccam {

class camera_frame;
enum class camera_format;

class camera
{
public:
	camera() = default;

	virtual ~camera() = default;

	virtual bool open() = 0;

	virtual bool is_opened() const = 0;

	virtual size_t get_frame_size() const = 0;

	virtual std::shared_ptr<camera_frame> retrieve() = 0;

	virtual camera_format get_format() const = 0;

	virtual void set_width(size_t width) = 0;

	virtual void set_height(size_t height) = 0;

	virtual void set_format(camera_format format) = 0;

private:
	camera(const camera&) = default;
	camera& operator=(const camera&) = default;
};

}}

#endif
