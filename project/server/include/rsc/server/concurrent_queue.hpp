#ifndef INC_RSC_SERVER_CONCURRENT_QUEUE_HPP
#define INC_RSC_SERVER_CONCURRENT_QUEUE_HPP

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

namespace rsc {
namespace server {

/**
 * This class is a queue with concurrency.
 * 
 * @attention Not all member functions and non member functions are implemented.
 */
template<class T, class Container = std::deque<T>>
class concurrent_queue
{
private:
	typedef std::queue<T, Container> queue_type;

public:
	typedef std::shared_ptr<concurrent_queue<T>> ptr;

public:
	typedef typename queue_type::value_type value_type;
	typedef typename queue_type::reference reference;
	typedef typename queue_type::const_reference const_reference;
	typedef typename queue_type::size_type size_type;
	typedef	Container container_type;

public:
	explicit concurrent_queue(const Container& other = Container())
		: mutex_(), condition_(), queue_(other)
	{}

	bool empty() const
	{
		return queue_.empty();
	}

	size_type size() const
	{
		std::lock_guard<std::mutex> lock(mutex_);
		return queue_.size();
	}

	value_type& front()
	{
		return const_cast<value_type&>(static_cast<const concurrent_queue*>(this)->front());
	}

	const value_type& front() const
	{
		std::unique_lock<std::mutex> lock(mutex_);

		while (queue_.empty()) {
			condition_.wait(lock);
		}

		const T& value = queue_.front();

		lock.unlock();

		return value;
	}

	void push(const value_type& x)
	{
		std::unique_lock<std::mutex> lock(mutex_);

		queue_.push(x);

		lock.unlock();
		condition_.notify_one();
	}

	void pop()
	{
		std::unique_lock<std::mutex> lock(mutex_);

		while (queue_.empty()) {
			condition_.wait(lock);
		}

		queue_.pop();
	}

private:
	mutable std::mutex mutex_;
	mutable std::condition_variable condition_;
	std::queue<T, Container> queue_;
};

}}

#endif
