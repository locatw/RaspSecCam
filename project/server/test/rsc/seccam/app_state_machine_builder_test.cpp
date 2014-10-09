#include <functional>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "rsc/seccam/app_state_machine_builder.hpp"

using namespace rsc::seccam;
using namespace rsc::seccam::fsm;

class camera_setting_state_mock : public state<app_state_id, app_event>
{
public:
	camera_setting_state_mock() : state(app_state_id::camera_setting) {}

	MOCK_METHOD0(on_entry, void());

	MOCK_METHOD0(on_exit, void());
};

class waiting_for_connection_state_mock : public state<app_state_id, app_event>
{
public:
	waiting_for_connection_state_mock() : state(app_state_id::waiting_for_connection) {}

	MOCK_METHOD0(on_entry, void());

	MOCK_METHOD0(on_exit, void());
};

class signaling_state_mock : public state<app_state_id, app_event>
{
public:
	signaling_state_mock() : state(app_state_id::signaling) {}

	MOCK_METHOD0(on_entry, void());

	MOCK_METHOD0(on_exit, void());
};

class video_distribution_state_mock: public state<app_state_id, app_event>
{
public:
	video_distribution_state_mock() : state(app_state_id::video_distribution) {}

	MOCK_METHOD0(on_entry, void());

	MOCK_METHOD0(on_exit, void());
};

class state_factory_mock : public state_factory<app_state_id, app_event>
{
public:
	MOCK_METHOD1(create_mock, state_type*(app_state_id));

	std::unique_ptr<state_type> create(app_state_id id) override
	{
		return std::unique_ptr<state_type>(create_mock(id));
	}
};

using ::testing::InSequence;
using ::testing::Invoke;
using ::testing::NiceMock;

typedef fsm::state_factory<app_state_id, app_event> state_factory_type;

class app_state_machine_builder_test : public ::testing::Test
{
protected:
	virtual void SetUp() override
	{
		mocked_camera_setting_state = create_mocked_state<camera_setting_state_mock>();
		mocked_waiting_for_connection_state = create_mocked_state<waiting_for_connection_state_mock>();
		mocked_signaling_state = create_mocked_state<signaling_state_mock>();
		mocked_video_distribution_state = create_mocked_state<video_distribution_state_mock>();
	}

	void setup_state_factory()
	{
		mocked_factory = create_mocked_state<state_factory_mock>();
		ON_CALL(*mocked_factory, create_mock(app_state_id::camera_setting))
			.WillByDefault(Return(mocked_camera_setting_state.release()));
		ON_CALL(*mocked_factory, create_mock(app_state_id::waiting_for_connection))
			.WillByDefault(Return(mocked_waiting_for_connection_state.release()));
		ON_CALL(*mocked_factory, create_mock(app_state_id::signaling))
			.WillByDefault(Return(mocked_signaling_state.release()));
		ON_CALL(*mocked_factory, create_mock(app_state_id::video_distribution))
			.WillByDefault(Return(mocked_video_distribution_state.release()));

		factory = std::unique_ptr<state_factory_type>(static_cast<state_factory_type*>(mocked_factory.release()));
	}

	std::unique_ptr<NiceMock<camera_setting_state_mock>> mocked_camera_setting_state;
	std::unique_ptr<NiceMock<waiting_for_connection_state_mock>> mocked_waiting_for_connection_state;
	std::unique_ptr<NiceMock<signaling_state_mock>> mocked_signaling_state;
	std::unique_ptr<NiceMock<video_distribution_state_mock>> mocked_video_distribution_state;
	std::unique_ptr<state_factory_mock> mocked_factory;
	std::unique_ptr<state_factory_type> factory;

private:
	template<class state_type>
	std::unique_ptr<NiceMock<state_type>> create_mocked_state()
	{
		return std::unique_ptr<NiceMock<state_type>>(new NiceMock<state_type>());
	}
};

TEST_F(app_state_machine_builder_test, TransitToWaitingForConnectionStateFromCameraSettingStateTest)
{
	InSequence seq;

	EXPECT_CALL(*mocked_camera_setting_state, on_entry())
		.Times(1);
	EXPECT_CALL(*mocked_camera_setting_state, on_exit())
		.Times(1);
	EXPECT_CALL(*mocked_waiting_for_connection_state, on_entry())
		.Times(1);

	setup_state_factory();

	app_state_machine_builder builder;
	auto app_state_machine = builder.build(std::move(factory));

	app_state_machine->run();
}

TEST_F(app_state_machine_builder_test, TransitToSignalingStateFromWaitingForConnectionStateTest)
{
	InSequence seq;

	EXPECT_CALL(*mocked_waiting_for_connection_state, on_entry())
		.Times(1)
		.WillOnce(Invoke(std::bind(
			&waiting_for_connection_state_mock::notify_event,
			mocked_waiting_for_connection_state.get(),
			app_event::connection_established)));
	EXPECT_CALL(*mocked_waiting_for_connection_state, on_exit())
		.Times(1);
	EXPECT_CALL(*mocked_signaling_state, on_entry())
		.Times(1);

	setup_state_factory();

	app_state_machine_builder builder;
	auto app_state_machine = builder.build(std::move(factory));

	app_state_machine->run();
}

TEST_F(app_state_machine_builder_test, TransitToImageDistributionLoopStateFromSignalingStateStateTest)
{
	InSequence seq;

	EXPECT_CALL(*mocked_waiting_for_connection_state, on_entry())
		.Times(1)
		.WillOnce(Invoke(std::bind(
			&waiting_for_connection_state_mock::notify_event,
			mocked_waiting_for_connection_state.get(),
			app_event::connection_established)));
	EXPECT_CALL(*mocked_signaling_state, on_entry())
		.Times(1)
		.WillOnce(Invoke(std::bind(
			&signaling_state_mock::notify_event,
			mocked_signaling_state.get(),
			app_event::signaling_succeeded)));
	EXPECT_CALL(*mocked_signaling_state, on_exit())
		.Times(1);
	EXPECT_CALL(*mocked_video_distribution_state, on_entry())
		.Times(1);

	setup_state_factory();

	app_state_machine_builder builder;
	auto app_state_machine = builder.build(std::move(factory));

	app_state_machine->run();
}
