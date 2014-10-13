#include "rsc/seccam/app_state_factory.hpp"
#include "rsc/seccam/app_state_machine_builder.hpp"
#include "rsc/seccam/capture_worker.hpp"
#include "rsc/seccam/connector.hpp"
#include "rsc/seccam/raspi_camera.hpp"
#include "rsc/seccam/send_frame_worker.hpp"
#include "rsc/seccam/security_camera.hpp"
#include "rsc/seccam/task_mediator.hpp"

void rsc::seccam::security_camera::run()
{
	camera_ = std::static_pointer_cast<rsc::seccam::camera>(std::make_shared<raspi_camera>());
	connector_ = std::make_shared<rsc::seccam::connector>();
	auto task_mediator = std::make_shared<rsc::seccam::task_mediator>();
	auto capture_worker = std::make_shared<rsc::seccam::capture_worker>(camera_, task_mediator);
	auto send_frame_worker = std::make_shared<rsc::seccam::send_frame_worker>(task_mediator, connector_);

	auto state_factory = std::unique_ptr<rsc::seccam::app_state_factory>(
		new app_state_factory(
			camera_,
			connector_,
			capture_worker,
			send_frame_worker));
	rsc::seccam::app_state_machine_builder state_machine_builder;
	state_machine_ = state_machine_builder.build(std::move(state_factory));

	state_machine_->run();

	capture_worker->stop();
	send_frame_worker->stop();
}
