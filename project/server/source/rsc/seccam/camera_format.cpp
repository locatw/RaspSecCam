#include <stdexcept>
#include <boost/format.hpp>
#include "rsc/seccam/camera_format.hpp"

namespace rsc {
namespace seccam {
	
std::string to_string(const camera_format& format)
{
	switch (format) {
		case rsc::seccam::camera_format::BGR:
			return "BGR";
		default:
			const std::string message = (boost::format("unknown camera_format [%1%]") % static_cast<int>(format)).str();
			throw std::logic_error(message);
	}
}

} // namespace seccam
} // namespace rsc
