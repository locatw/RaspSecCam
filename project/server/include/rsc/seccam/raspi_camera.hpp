#ifndef INC_RSC_SECCAM_RASPI_CAMERA_HPP
#define INC_RSC_SECCAM_RASPI_CAMERA_HPP

#include <raspicam/raspicam.h>
#include "camera.hpp"

namespace rsc {
namespace seccam {

class raspi_camera : public camera
{
public:
	raspi_camera() = default;

	virtual ~raspi_camera() = default;

	bool open() override;

	bool is_opened() const override;

	size_t get_frame_size() const override;

	std::shared_ptr<camera_frame> retrieve() override;

	camera_format get_format() const override;

	virtual void set_width(size_t width) override;

	virtual void set_height(size_t height) override;

	void set_format(camera_format format) override;

private:
	raspicam::RaspiCam camera_;

private:
	raspi_camera(const camera&);
	camera& operator=(const camera&);
};

}}

#endif
