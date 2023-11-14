#include "../List/list.h"

template<class T>
class StackOnList {
	TList<T> data;
public:
	StackOnList() :data() {}
	StackOnList(const StackOnList& st) :data(st.data) {}
	StackOnList(T* data, int mass_size) : data(data, mass_size) {}
	~StackOnList() {}

	bool empty() { return data.empty(); }
	T top() {
		if (data.empty()) { throw std::logic_error("stack is empty"); }
		return data.front();
	}
	void pop() { 
		if (data.empty()) { return; }
		data.pop_front();
	}
	void push(const T& elem) { data.push_front(elem); }
	size_t size() { return data.size(); }
};