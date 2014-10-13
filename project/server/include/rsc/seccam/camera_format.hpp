#ifndef INC_RSC_SECCAM_CAMERA_FORMAT_HPP
#define INC_RSC_SECCAM_CAMERA_FORMAT_HPP

#include <string>

namespace rsc {
namespace seccam {
	
enum class camera_format {
	BGR
};

std::string to_string(const camera_format& format);

} // namespace seccam
} // namespace rsc

#endif
