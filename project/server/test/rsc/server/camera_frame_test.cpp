#include <gtest/gtest.h>
#include "rsc/server/camera_frame.hpp"

using namespace rsc::server;

TEST(camera_frame_test, ConstructDefault)
{
	camera_frame frame;

	EXPECT_EQ(0, frame.size());
}

TEST(camera_frame_test, CopyConstruct)
{
	std::vector<unsigned char> frameData = {1};
	camera_frame frame(frameData);

	EXPECT_NE(frameData.data(), frame.data());
}

TEST(camera_frame_test, ConstructWithFrameData)
{
	std::vector<unsigned char> frameData = {1, 2, 3};
	camera_frame frame(frameData);

	EXPECT_EQ(3, frame.size());
}

TEST(camera_frame_test, AccessFrameData)
{
	std::vector<unsigned char> frameData = {1, 2, 3};
	camera_frame frame(frameData);

	EXPECT_EQ(1, frame.data()[0]);
	EXPECT_EQ(2, frame.data()[1]);
	EXPECT_EQ(3, frame.data()[2]);
}
