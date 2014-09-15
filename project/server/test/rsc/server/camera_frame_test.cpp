#include <gtest/gtest.h>
#include "rsc/server/camera_frame.hpp"

using namespace rsc::server;

TEST(camera_frame_test, ConstructDefault)
{
	camera_frame frame;

	EXPECT_EQ(0, frame.size());
}
