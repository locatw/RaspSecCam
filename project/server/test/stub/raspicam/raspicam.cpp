#include "raspicam.h"

namespace raspicam {

RaspiCam::RaspiCam()
{}

RaspiCam::~RaspiCam()
{}

bool RaspiCam::open(bool start_capture)
{
	return true;
}

bool RaspiCam::isOpened() const
{
	return true;
}

void RaspiCam::retrieve(unsigned char* data, RASPICAM_FORMAT type)
{}

size_t RaspiCam::getImageTypeSize(RASPICAM_FORMAT type) const
{
	return RASPICAM_FORMAT_RGB;
}

}
