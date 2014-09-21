#===============================================================================
# project settings
#===============================================================================
SET(TARGET rasp-sec-cam-server-test)

#===============================================================================
# build settings
#===============================================================================
SET(CMAKE_CXX_COMPILER "g++")

INCLUDE_DIRECTORIES(
	"../${INCLUDE_DIR}/"
	"./stub/"
	"../${THIRDPARTY_DIR}/google/"
	"/usr/local/include/")
LINK_DIRECTORIES(
	"/usr/local/lib/boost/")

FILE(GLOB_RECURSE SOURCES "../${SOURCE_DIR}/*.cpp" "./*.cpp")
LIST(APPEND SOURCES
	"../${THIRDPARTY_DIR}/google/gmock-gtest-all.cc"
	"../${THIRDPARTY_DIR}/google/gmock_main.cc")

# remove a file contains main funciton.
FOREACH(src ${SOURCES})
	IF(src MATCHES ".?/${SOURCE_DIR}/main.cpp")
		LIST(REMOVE_ITEM SOURCES ${src})
	ENDIF()
ENDFOREACH()

ADD_EXECUTABLE(${TARGET} ${SOURCES})

TARGET_LINK_LIBRARIES(${TARGET}
	boost_system
	pthread)

#===============================================================================
# install settings
#===============================================================================
INSTALL(TARGETS ${TARGET} DESTINATION bin)
