CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#===============================================================================
# project settings
#===============================================================================
PROJECT(RaspSecCam-Server CXX)

SET(INCLUDE_DIR "include")
SET(SOURCE_DIR "source")
SET(TEST_DIR "test")
SET(THIRDPARTY_DIR "../../thirdparty")

#===============================================================================
# build settings
#===============================================================================
SET(CMAKE_CXX_FLAGS_RELEASE "-std=c++11")
SET(CMAKE_CXX_FLAGS_DEBUG "-std=c++11")
SET(CMAKE_BUILD_TYPE Release)

add_subdirectory(${SOURCE_DIR})
add_subdirectory(${TEST_DIR})
