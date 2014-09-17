#ifndef INC_RASPICAM_RASPICAM_H
#define INC_RASPICAM_RASPICAM_H

#include <cstring>
#include "raspicamtypes.h"

namespace raspicam {

class RaspiCam
{
public:
	RaspiCam();

	virtual ~RaspiCam();

	virtual bool open(bool start_capture = true);

	virtual void retrieve(unsigned char* data, RASPICAM_FORMAT type = RASPICAM_FORMAT_IGNORE);

	virtual size_t getImageTypeSize(RASPICAM_FORMAT type) const;
		
};

}

#endif
