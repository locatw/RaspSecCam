#include <iostream>
#include <boost/log/attributes.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include "rsc/seccam/app_state_factory.hpp"
#include "rsc/seccam/app_state_machine_builder.hpp"
#include "rsc/seccam/capture_worker.hpp"
#include "rsc/seccam/connector.hpp"
#include "rsc/seccam/raspi_camera.hpp"
#include "rsc/seccam/send_frame_worker.hpp"
#include "rsc/seccam/security_camera.hpp"
#include "rsc/seccam/task_mediator.hpp"

rsc::seccam::security_camera::security_camera()
	: state_machine_(), camera_(), connector_()
{
	initialize_logger();
}

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
}

void rsc::seccam::security_camera::initialize_logger()
{
	boost::log::add_file_log(
		boost::log::keywords::file_name = "log/%Y%m%d_%H%M%S_%5N.log",
		boost::log::keywords::rotation_size = 1024 * 1024,	// maximum file size is 1MB per file
		boost::log::keywords::format = "[%TimeStamp%]: %Message%",
		boost::log::keywords::auto_flush = true);

	auto logger = boost::log::core::get();
	logger->add_global_attribute("TimeStamp", boost::log::attributes::local_clock());
}
