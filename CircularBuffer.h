#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <mutex>
#include <unique_ptr>

using namespace std;

template <class T>
class CircularBuffer {
public:
	explicit CircularBuffer(size_t size) :
		buf_(unique_ptr<T[]>(new T[size])),
		max_size_(size){};

	void Put(T item);
	T Get();
	void Reset();
	bool Empty() const;
	bool Full() const;
	size_t Capacity() const;
	size_t Size() const;

private:
	mutex mutex_;
	unique_ptr<T[]> buf_;
	size_t head_ = 0;
	size_t tail_ = 0;
	const size_t max_size_;
	bool full_ = 0;
};
#endif
