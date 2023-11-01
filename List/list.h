#include<iostream>

template <class T>
class TNode;
template <class T>
class TList;

template <class T>
class TNode {
private:
	T _data;
	TNode* _next;
public:
	TNode( T data, TNode* p = nullptr) :_data(data), _next(p) {}
	TNode(const TNode& node) :_data(node._data), _next(node._next) {}
	~TNode() { _next = nullptr; }
	TNode& operator=(const TNode& node) {
		_data = node._data;
		_next = node._next;
		return *this;
	}
	bool operator==(const TNode node) const noexcept {
		return _data == node._data && _next == node._next;
	}
	TNode* next() { return _next; }
	T data() { return _data; }
	friend TList<T>;
};

template <class T>
class TList {
private:
	size_t count;
	TNode<T>* head;
	TNode<T>* tail;
public:
	TList() : head(nullptr), tail(nullptr), count(0) {}
	TList(T* data, int mass_size) {
		if (mass_size < 1) { throw std::logic_error("Mass is empty"); }
		count = mass_size;
		head = new TNode<T>(data[0]);
		TNode<T>* p = head;
		for (size_t i = 1; i < mass_size; i++) {
			p->_next = new TNode<T>(data[i]);
			p = p->_next;
		}
		tail = p;
	}
	~TList() {
		head = nullptr;
		tail = nullptr;
	}
	void insert(TNode<T>* p, const T& data) {
		p->_next = new TNode<T>(data, p->_next);
		if (p->_next == nullptr) { tail = p; }
		count++;
	}



	TNode<T>* front() { return head; }
	TNode<T>* back() { return tail; }
	size_t size() { return count; }
};