#include <thread>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "rsc/seccam/camera.hpp"
#include "rsc/seccam/capture_worker.hpp"
#include "rsc/seccam/concurrent_queue.hpp"

using ::testing::AtLeast;
using ::testing::Ge;
using ::testing::Return;
using namespace rsc::server;

class camera_mock : public camera
{
public:
	~camera_mock() = default;

	MOCK_METHOD0(open, bool());

	MOCK_CONST_METHOD0(is_opened, bool());

	MOCK_CONST_METHOD0(get_frame_size, size_t());

	MOCK_METHOD0(retrieve, std::shared_ptr<camera_frame>());
};

TEST(capture_worker_test, CanStartAndStop)
{
	camera_mock cam;
	EXPECT_CALL(cam, is_opened())
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(cam, retrieve())
		.WillRepeatedly(Return(std::shared_ptr<camera_frame>()));

	auto frame_queue = std::make_shared<concurrent_queue<camera_frame::ptr>>();
	capture_worker worker(cam, frame_queue);

	worker.start();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	worker.stop();
}

TEST(capture_worker_test, CaptureFrame)
{
	camera_mock cam;
	EXPECT_CALL(cam, is_opened())
		.WillRepeatedly(Return(true));
	EXPECT_CALL(cam, retrieve())
		.Times(AtLeast(1))
		.WillRepeatedly(Return(std::shared_ptr<camera_frame>()));

	auto frame_queue = std::make_shared<concurrent_queue<camera_frame::ptr>>();
	capture_worker worker(cam, frame_queue);

	worker.start();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	worker.stop();

	EXPECT_GE(frame_queue->size(), 1);
}
