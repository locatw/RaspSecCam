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

bool RaspiCam::grab()
{
	return true;
}

void RaspiCam::retrieve(unsigned char* data, RASPICAM_FORMAT type)
{}

size_t RaspiCam::getImageTypeSize(RASPICAM_FORMAT type) const
{
	return RASPICAM_FORMAT_RGB;
}

unsigned int RaspiCam::getWidth() const
{
	return 0;
}

unsigned int RaspiCam::getHeight() const
{
	return 0;
}

RASPICAM_FORMAT RaspiCam::getFormat() const
{
	return RASPICAM_FORMAT_RGB;
}

void RaspiCam::setWidth(unsigned int width)
{}

void RaspiCam::setHeight(unsigned int height)
{}

void RaspiCam::setFormat(RASPICAM_FORMAT fmt)
{}

}
