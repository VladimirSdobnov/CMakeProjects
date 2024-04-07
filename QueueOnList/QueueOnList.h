#pragma once
#include "../List/list.h">

template <class T>
class TQueueOnList {
	TList<T> list;
public:
	TQueueOnList() {};
	TQueueOnList(const TQueueOnList& que) : list(que.list) {};
	size_t size() { return list.size(); }
	bool empty() { return list.empty(); }
	T front() {
		if (empty()) { throw std::logic_error("Queue is empty"); }
		return list.front();
	}
	T back() {
		if (empty()) { throw std::logic_error("Queue is empty"); }
		return list.back();
	}
	void push(const T& elem) {
		list.push_back(elem);
	}
	T pop() {
		if (empty()) { throw std::logic_error("Queue is empty"); }
		T res = list.front();
		list.pop_front();
		return res;
	}
};