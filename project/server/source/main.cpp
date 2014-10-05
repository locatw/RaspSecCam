#include <chrono>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>
#include "rsc/seccam/capture_worker.hpp"
#include "rsc/seccam/camera_format.hpp"
#include "rsc/seccam/camera_frame.hpp"
#include "rsc/seccam/concurrent_queue.hpp"
#include "rsc/seccam/raspi_camera.hpp"
#include "rsc/seccam/send_frame_worker.hpp"
#include "rsc/seccam/task_mediator.hpp"

int main(int argc, char* argv[])
{
	try {
		rsc::seccam::raspi_camera camera;
		auto task_mediator = std::make_shared<rsc::seccam::task_mediator>();
		rsc::seccam::send_frame_worker send_frame_worker(task_mediator);
		rsc::seccam::capture_worker capture_worker(camera, task_mediator);

		camera.set_format(rsc::seccam::camera_format::BGR);
		camera.set_width(480);
		camera.set_height(320);

		if (!camera.open()) {
			throw std::runtime_error("cannot open camera");
		}

		std::this_thread::sleep_for(std::chrono::seconds(3));

		send_frame_worker.accept(31400);

		capture_worker.start();
		send_frame_worker.start();

		while (true) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		capture_worker.stop();
		send_frame_worker.stop();
	}
	catch (const std::exception& e) {
		std::cout << "error occurred : " << e.what() << std::endl;
		std::cout << "finish." << std::endl;
	}

	return 0;
}
