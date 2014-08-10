#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <raspicam/raspicam.h>

int main(int argc, char* argv[])
{
	raspicam::RaspiCam camera;

	if (!camera.open()) {
		std::cout << "cannot open camera." << std::endl;
		return 1;
	}

	std::this_thread::sleep_for(std::chrono::seconds(3));

	const size_t frameSize = camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB);
	std::vector<unsigned char> frameData(frameSize);

	auto term = std::chrono::system_clock::now() + std::chrono::seconds(5);
	while (std::chrono::system_clock::now() <= term) {
		camera.grab();

		const size_t frameSize = camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB);
		std::vector<unsigned char> frameData(frameSize);

		camera.retrieve(frameData.data(), raspicam::RASPICAM_FORMAT_IGNORE);
	}

	return 0;
}
