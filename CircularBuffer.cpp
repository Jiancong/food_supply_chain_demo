#include <CircularBuffer.hpp>
#include <lock_guard>

void CircularBuffer::Reset()
{
	lock_guard<mutex> lock(mutex_);
	head_ = tail_;
	full_ = false;
}

bool CircularBuffer::Empty() const
{
	//if head and tail are equal, we are empty
	return (!full_ && (head_ == tail_));
}

bool CircularBuffer::Full() const
{
	//If tail is ahead the head by 1, we are full
	return full_;
}

size_t CircularBuffer::Capacity() const
{
	return max_size_;
}

size_t CircularBuffer::Size() const
{
	size_t size = max_size_;

	if(!full_)
	{
		if(head_ >= tail_)
		{
			size = head_ - tail_;
		}
		else
		{
			size = max_size_ + head_ - tail_;
		}
	}

	return size;
}

void CircularBuffer::Put(T item)
{
	lock_guard<mutex> lock(mutex_);

	buf_[head_] = item;

	if(full_)
	{
		tail_ = (tail_ + 1) % max_size_;
	}

	head_ = (head_ + 1) % max_size_;

	full_ = head_ == tail_;
}

T CircularBuffer::get()
{
	lock_guard<mutex> lock(mutex_);

	if(empty())
	{
		return T();
	}

	//Read data and advance the tail (we now have a free space)
	auto val = buf_[tail_];
	full_ = false;
	tail_ = (tail_ + 1) % max_size_;

	return val;
}