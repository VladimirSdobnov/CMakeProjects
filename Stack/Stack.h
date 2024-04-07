#include <iostream>

template <class T>
class TStack {
private:
	T* data;
	size_t count;
	size_t pos_top;
public:
	TStack(int sz) :count(sz), pos_top(-1) {
		if (sz <= 0) { throw std::logic_error("size must be more than 0"); }
		data = new T[sz];
	}
	TStack(const TStack& st) :count(st.count) {
		data = new T[count];
		pos_top = st.pos_top;
		for (size_t i = 0; i < count; i++) { data[i] = st.data[i]; }
	}
	TStack(T* _mass, int sz) :count(sz), pos_top(sz) {
		if (sz <= 0) { throw std::logic_error("size must be more than 0"); }
		data = new T[sz];
		for (size_t i = 0; i < sz; i++) { data[i] = _mass[i]; }
	}
	~TStack() { 
		delete[] data;
		data = nullptr;
	}

	bool isEmpty() {
		return pos_top == -1;
	}

	bool isFull() {
		return pos_top == count;
	}

	T top() {
		if (isEmpty()) { throw std::logic_error("stack is empty"); }
		return data[pos_top];
	}

	void pop() {
		if (isEmpty()) { throw std::logic_error("stack is empty"); }
		pos_top -= 1;
	}

	void push(const T& elem) {
		if(isFull()){ throw std::logic_error("stack over flow"); }
		pos_top++;
		data[pos_top] = elem;
	}

	size_t size() { return count; }
};