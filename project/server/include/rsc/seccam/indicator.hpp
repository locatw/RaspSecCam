#ifndef RSC_SECCAM_INDICATOR_HPP
#define RSC_SECCAM_INDICATOR_HPP

namespace rsc {
namespace seccam {
	
class indicator
{
public:
	bool initialize();

	void set_sending_video_indicator(bool on);

private:
	void initialize_sending_video_indicator();
};

} // namespace seccam
} // namespace rsc

#endif
