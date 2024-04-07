#include <iostream>

template <class T>
class TQueue {
	size_t _size;
	size_t end;
	T* pMem;
public:
	TQueue(int sz) : _size(sz), end(0) {
		if (sz <= 0) { throw std::length_error("Size must be more zero"); }
		pMem = new T[sz];
	}
	TQueue(const TQueue& que) : _size(que._size), end(que.end) {
		pMem = new T[_size];
		for (int i = 0; i < end; i++) {
			pMem[i] = que.pMem[i];
		}
	}
	size_t size() { return _size; }
	bool empty() { return end == 0; }
	bool full() { return end == _size; }
	T front() {
		if (empty()) { throw std::logic_error("Queue is empty"); }
		return *pMem;
	}
	T back() {
		if (empty()) { throw std::logic_error("Queue is empty"); }
		return pMem[end - 1];
	}
	void push(const T& elem) {
		if (full()) { throw std::logic_error("Queue is full"); }
		pMem[end] = elem;
		end++;
	}
	void pop() {
		if(empty()){ throw std::logic_error("Queue is empty"); }
		for (int i = 0; i < end - 1; i++) {
			pMem[i] = pMem[i + 1];
		}
		end--;
	}
};