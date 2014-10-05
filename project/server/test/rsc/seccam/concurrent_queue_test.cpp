#include <gtest/gtest.h>
#include "rsc/seccam/concurrent_queue.hpp"

using namespace rsc::seccam;

TEST(concurrent_queue_test, ConstructDefault)
{
	concurrent_queue<int> queue;

	EXPECT_EQ(0, queue.size());
}

TEST(concurrent_queue_test, EmptyReturnsTrueIfQueueIsEmpty)
{
	concurrent_queue<int> queue;

	EXPECT_EQ(0, queue.size());
	EXPECT_TRUE(queue.empty());
}

TEST(concurrent_queue_test, SizeIncreasedAfterPushingValue)
{
	concurrent_queue<int> queue;
	
	EXPECT_EQ(0, queue.size());

	queue.push(1);

	EXPECT_EQ(1, queue.size());
}

TEST(concurrent_queue_test, SizeDecreasedAfterPopingValue)
{
	concurrent_queue<int> queue;
	queue.push(1);

	EXPECT_EQ(1, queue.size());

	queue.pop();

	EXPECT_EQ(0, queue.size());
}

TEST(concurrent_queue_test, FrontReturnsFirstPushedValue)
{
	concurrent_queue<int> queue;

	queue.push(1);
	queue.push(2);

	EXPECT_EQ(1, queue.front());
}

TEST(concurrent_queue_test, SizeNotChangedAfterCallingFront)
{
	concurrent_queue<int> queue;
	queue.push(1);
	queue.front();

	EXPECT_EQ(1, queue.size());
}

TEST(concurrent_queue_test, ConstFrontReturnsFirstPushedValue)
{
	concurrent_queue<int> queue;

	queue.push(1);
	queue.push(2);

	EXPECT_EQ(1, static_cast<const concurrent_queue<int>*>(&queue)->front());
}
