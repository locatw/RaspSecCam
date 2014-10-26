#include <stdexcept>
#include "rsc/seccam/app_state_factory.hpp"
#include "rsc/seccam/camera.hpp"
#include "rsc/seccam/camera_setting_state.hpp"
#include "rsc/seccam/capture_worker.hpp"
#include "rsc/seccam/connector.hpp"
#include "rsc/seccam/send_frame_worker.hpp"
#include "rsc/seccam/signaling_state.hpp"
#include "rsc/seccam/video_distribution_state.hpp"
#include "rsc/seccam/waiting_for_connection_state.hpp"

namespace rsc {
namespace seccam {

app_state_factory::app_state_factory(
	std::shared_ptr<camera>& camera,
	std::shared_ptr<connector>& connector,
	std::shared_ptr<capture_worker>& capture_worker,
	std::shared_ptr<send_frame_worker<raw_frame_protocol>>& send_frame_worker)
	: camera_(camera),
	  connector_(connector),
	  capture_worker_(capture_worker),
	  send_frame_worker_(send_frame_worker) 
{}
	
std::unique_ptr<app_state_factory::state_type> app_state_factory::create(app_state_id id)
{
	switch (id) {
		case app_state_id::camera_setting:
			return std::unique_ptr<state_type>(new camera_setting_state(camera_));
		case app_state_id::waiting_for_connection:
			return std::unique_ptr<state_type>(new waiting_for_connection_state(connector_));
		case app_state_id::signaling:
			return std::unique_ptr<state_type>(new signaling_state(camera_, connector_));
		case app_state_id::video_distribution:
			return std::unique_ptr<state_type>(new video_distribution_state(capture_worker_, send_frame_worker_));
		default:
			throw std::logic_error("unknown app state id");
	}
}

} // namespace secc
} // namespace rsc
