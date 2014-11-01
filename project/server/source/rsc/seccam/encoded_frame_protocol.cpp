#include <stdexcept>
#include <vector>
#include <opencv2/opencv.hpp>
#include "rsc/seccam/camera_frame.hpp"
#include "rsc/seccam/connector.hpp"
#include "rsc/seccam/encoded_frame_protocol.hpp"

namespace {
	using rsc::seccam::camera_format;
	
	int to_opencv_array_type(const camera_format& format)
	{
		switch (format) {
			case camera_format::BGR:
				return CV_8UC3;
			default:
				throw std::domain_error("unknown camera format");
		}
	}
}

namespace rsc {
namespace seccam {

encoded_frame_protocol::encoded_frame_protocol(std::shared_ptr<connector>& connector)
	: connector_(connector)
{}

void encoded_frame_protocol::send(const std::shared_ptr<camera_frame>& frame, boost::system::error_code& error)
{
	std::vector<unsigned char> encoded_frame;
	const cv::Mat inputMat(
		frame->height(),
		frame->width(),
		::to_opencv_array_type(frame->format()),
		frame->data());
	cv::imencode(".jpg", inputMat, encoded_frame, { CV_IMWRITE_JPEG_QUALITY, 90 });

	const size_t data_size = encoded_frame.size();

	connector_->write(&data_size, sizeof(size_t), error);
	if (error) {
		return;
	}

	connector_->write(encoded_frame.data(), data_size, error);
	if (error) {
		return;
	}
}

} // namespace seccam
} // namespace rsc
