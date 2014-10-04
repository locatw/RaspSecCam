#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>
#include "rsc/server/capture_worker.hpp"
#include "rsc/server/camera_frame.hpp"
#include "rsc/server/concurrent_queue.hpp"
#include "rsc/server/raspi_camera.hpp"
#include "rsc/server/send_frame_worker.hpp"

int main(int argc, char* argv[])
{
	try {
		rsc::server::raspi_camera camera;
		rsc::server::concurrent_queue<rsc::server::camera_frame::ptr>::ptr frame_queue = 
			std::make_shared<rsc::server::concurrent_queue<rsc::server::camera_frame::ptr>>();
		rsc::server::send_frame_worker send_frame_worker(frame_queue);
		rsc::server::capture_worker capture_worker(camera, frame_queue);

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
	catch (const std::runtime_error& e) {
		std::cout << "error occurred : " << e.what() << std::endl;
		std::cout << "finish." << std::endl;
	}

	return 0;
}
