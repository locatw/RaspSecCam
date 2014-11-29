#include <wiringPi/wiringPi.h>
#include "rsc/seccam/indicator.hpp"

namespace {
	static const int GPIO25 = 25;
}

namespace rsc {
namespace seccam {
	
bool indicator::initialize()
{
	if (wiringPiSetupGpio() == -1) {
		return false;
	}

	initialize_sending_video_indicator();
}

void indicator::set_sending_video_indicator(bool on)
{
	auto value = (on) ? HIGH : LOW;

	digitalWrite(GPIO25, value);
}

void indicator::initialize_sending_video_indicator()
{
	pinMode(GPIO25, OUTPUT);
	digitalWrite(GPIO25, LOW);
}

} // namespace seccam
} // namespace rsc
