#include <chrono>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>
#include <boost/log/trivial.hpp>
#include "rsc/seccam/capture_worker.hpp"
#include "rsc/seccam/camera_format.hpp"
#include "rsc/seccam/camera_frame.hpp"
#include "rsc/seccam/concurrent_queue.hpp"
#include "rsc/seccam/raspi_camera.hpp"
#include "rsc/seccam/send_frame_worker.hpp"
#include "rsc/seccam/task_mediator.hpp"

#include "rsc/seccam/security_camera.hpp"

int main(int argc, char* argv[])
{
	try {
		rsc::seccam::security_camera sec_cam;

		sec_cam.run();
	}
	catch (const std::exception& e) {
		BOOST_LOG_TRIVIAL(error) << e.what();
	}

	BOOST_LOG_TRIVIAL(info) << "end" << std::endl;

	return 0;
}
