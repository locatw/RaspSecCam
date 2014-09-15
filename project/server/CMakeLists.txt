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

IF(NOT BUILD_TYPE)
	SET(BUILD_TYPE "app")
ENDIF()

IF(${BUILD_TYPE} STREQUAL "app")
	add_subdirectory(${SOURCE_DIR})
ELSEIF(${BUILD_TYPE} STREQUAL "test")
	add_subdirectory(${TEST_DIR})
ELSE()
	MESSAGE(FATAL_ERROR "unknown BUILD_TYPE:${BUILD_TYPE}")
ENDIF()
