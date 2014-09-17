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
	"../${THIRDPARTY_DIR}/")

FILE(GLOB_RECURSE SOURCES "../${SOURCE_DIR}/*.cpp" "./*.cpp")
LIST(APPEND SOURCES
	"../${THIRDPARTY_DIR}/gtest/gtest-all.cc"
	"../${THIRDPARTY_DIR}/gtest/gtest_main.cc")

# remove a file contains main funciton.
FOREACH(src ${SOURCES})
	IF(src MATCHES ".?/${SOURCE_DIR}/main.cpp")
		LIST(REMOVE_ITEM SOURCES ${src})
	ENDIF()
ENDFOREACH()

ADD_EXECUTABLE(${TARGET} ${SOURCES})

TARGET_LINK_LIBRARIES(${TARGET}
	pthread)

#===============================================================================
# install settings
#===============================================================================
INSTALL(TARGETS ${TARGET} DESTINATION bin)
