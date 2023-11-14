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
		TNode<T>* currentNode = head;
		while (currentNode != nullptr) {
			TNode<T>* nextNode = currentNode->next();
			delete currentNode;
			currentNode = nextNode;
		}
	}
	void insert(TNode<T>* p, const T& data) {
		if (p == nullptr) { throw std::logic_error("Wrong pointer"); }
		p->_next = new TNode<T>(data, p->_next);
		count++;
		if (p->_next == nullptr) { tail = p; return; }
		if (p->_next->_next == nullptr) { tail = p->_next; return; }
		
	}
	void erase(TNode<T>* p) {
		if (p == nullptr) { throw std::logic_error("Wrong pointer"); }
		if (p == head) { head = p->_next; }
		else
		{
			TNode<T>* tmp = head;
			while (tmp->_next != p && tmp->_next != nullptr) {
				tmp = tmp->_next;
			}
			if (tmp->_next == nullptr) { throw std::logic_error("node is missing"); }
			tmp->_next = p->_next;
			if (tmp->_next == nullptr) { tail = tmp; }
		}
		delete p;
		count--;
		if (head == nullptr) { tail = nullptr; }
	}
	void push_back(const T& data) { insert(tail, data); }
	void push_front(const T& data) {
		TNode<T>* p = new TNode<T>(data, head);
		head = p;
		count++;
		if (p->_next == nullptr) { tail = p; }
	}
	void pop_back() { erase(tail); }
	void pop_front() { erase(head); }
	T front() { return head->data(); }
	T back() { return tail->data(); }

	bool empty() { return count == 0; }


	TNode<T>* front_node() { return head; }
	TNode<T>* back_node() { return tail; }
	size_t size() { return count; }
};