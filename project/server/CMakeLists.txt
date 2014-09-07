CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#===============================================================================
# project settings
#===============================================================================
PROJECT(RaspSecCam-Server CXX)

SET(TARGET rasp-sec-cam-server)
SET(SOURCE_DIR "source")

#===============================================================================
# build settings
#===============================================================================
SET(CMAKE_CXX_COMPILER
	"$ENV{HOME}/raspi-dev/opt/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-g++")

SET(CMAKE_CXX_FLAGS_RELEASE "-std=c++11")
SET(CMAKE_CXX_FLAGS_DEBUG "-std=c++11")
SET(CMAKE_BUILD_TYPE Release)

INCLUDE_DIRECTORIES(
	"$ENV{HOME}/raspi-dev/opt/rootfs/usr/local/include/")
LINK_DIRECTORIES(
	"$ENV{HOME}/raspi-dev/opt/rootfs/usr/local/lib/raspicam/"
	"$ENV{HOME}/raspi-dev/opt/userland/build/lib/")

FILE(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

ADD_EXECUTABLE(${TARGET} ${SOURCES})

TARGET_LINK_LIBRARIES(${TARGET}
	raspicam
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
