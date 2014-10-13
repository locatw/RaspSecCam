#include <memory>
#include <thread>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "rsc/seccam/camera.hpp"
#include "rsc/seccam/camera_frame.hpp"
#include "rsc/seccam/capture_worker.hpp"
#include "rsc/seccam/task_mediator_mock.hpp"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Ge;
using ::testing::Return;
using namespace rsc::seccam;

class camera_mock : public camera
{
public:
	~camera_mock() = default;

	MOCK_METHOD0(open, bool());

	MOCK_CONST_METHOD0(is_opened, bool());

	MOCK_CONST_METHOD0(get_frame_size, size_t());

	MOCK_METHOD0(retrieve, std::shared_ptr<camera_frame>());

	MOCK_CONST_METHOD0(get_width, size_t());

	MOCK_CONST_METHOD0(get_height, size_t());

	MOCK_CONST_METHOD0(get_format, camera_format());

	MOCK_METHOD1(set_width, void(size_t));

	MOCK_METHOD1(set_height, void(size_t));

	MOCK_METHOD1(set_format, void(camera_format));
};

TEST(capture_worker_test, CanStartAndStop)
{
	auto cam_mock = std::make_shared<camera_mock>();
	EXPECT_CALL(*cam_mock, is_opened())
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(*cam_mock, retrieve())
		.WillRepeatedly(Return(std::shared_ptr<camera_frame>()));

	auto mediator_mock = std::make_shared<task_mediator_mock>();
	EXPECT_CALL(*mediator_mock, request_capturing_permission())
		.Times(AtLeast(1));
	EXPECT_CALL(*mediator_mock, put_camera_frame(_))
		.Times(AtLeast(1));

	auto mediator = std::static_pointer_cast<task_mediator>(mediator_mock);
	auto cam = std::static_pointer_cast<camera>(cam_mock);
	capture_worker worker(cam, mediator);

	worker.start();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	worker.stop();
}

TEST(capture_worker_test, CaptureFrame)
{
	auto cam_mock = std::make_shared<camera_mock>();
	EXPECT_CALL(*cam_mock, is_opened())
		.WillRepeatedly(Return(true));
	EXPECT_CALL(*cam_mock, retrieve())
		.Times(AtLeast(1))
		.WillRepeatedly(Return(std::shared_ptr<camera_frame>()));

	auto mediator_mock = std::make_shared<task_mediator_mock>();
	EXPECT_CALL(*mediator_mock, request_capturing_permission())
		.Times(AtLeast(1));
	EXPECT_CALL(*mediator_mock, put_camera_frame(_))
		.Times(AtLeast(1));

	auto mediator = std::static_pointer_cast<task_mediator>(mediator_mock);
	auto cam = std::static_pointer_cast<camera>(cam_mock);
	capture_worker worker(cam, mediator);

	worker.start();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	worker.stop();
}
