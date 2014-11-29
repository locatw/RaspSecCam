#===============================================================================
# project settings
#===============================================================================
SET(TARGET rasp-sec-cam-server)

#===============================================================================
# build settings
#===============================================================================
SET(CMAKE_CXX_COMPILER
	"$ENV{HOME}/raspi-dev/opt/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-g++")

INCLUDE_DIRECTORIES(
	"../${INCLUDE_DIR}"
	"$ENV{HOME}/raspi-dev/opt/rootfs/usr/local/include")
LINK_DIRECTORIES(
	"$ENV{HOME}/raspi-dev/opt/rootfs/usr/lib/arm-linux-gnueabihf/"
	"$ENV{HOME}/raspi-dev/opt/rootfs/usr/local/lib/"
	"$ENV{HOME}/raspi-dev/opt/userland/build/lib/")

FILE(GLOB_RECURSE SOURCES "*.cpp")

# Boost.Log is static linked by default.
# So BOOST_LOG_DYN_LINK is needed for dynamic linking.
# See Boost.Log FAQ in document.
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

ADD_EXECUTABLE(${TARGET} ${SOURCES})

TARGET_LINK_LIBRARIES(${TARGET}
	boost_system
	boost_log
	boost_log_setup
	boost_thread
	opencv_core
	opencv_highgui
	pthread
	z
	raspicam
	wiringPi
	mmal
	mmal_core
	mmal_util
	mmal_vc_client
	vcos
	vchiq_arm)

#===============================================================================
# install settings
#===============================================================================
INSTALL(TARGETS ${TARGET} DESTINATION bin)
