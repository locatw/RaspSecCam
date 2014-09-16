#ifndef INC_RSC_SERVER_RASPI_CAMERA_HPP
#define INC_RSC_SERVER_RASPI_CAMERA_HPP

#include <raspicam/raspicam.h>
#include "camera.hpp"

namespace rsc {
namespace server {

class raspi_camera : public camera
{
public:
	virtual ~raspi_camera() = default;

	bool open() override;

	size_t getFrameSize() const override;

	std::shared_ptr<camera_frame> retrieve() override;

private:
	raspicam::RaspiCam camera_;

private:
	raspi_camera(const camera&);
	camera& operator=(const camera&);
};

}}

#endif
