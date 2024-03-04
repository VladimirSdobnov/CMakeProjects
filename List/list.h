#pragma once
#include<iostream>

template <class T>
class TNode;
template <class T>
class TList;

#include <iterator>
template<class T>
class InIteratorList : public std::iterator<std::input_iterator_tag, T> {
	friend class TList<T>;
	friend class TNode<T>;
protected:
	TNode<T>* p;
	InIteratorList(TNode<T>* _p) : p(_p) {};
public:
	InIteratorList& operator=(const InIteratorList& it) {
		if (this != it) {
			p = it.p;
		}
		return *this;
	}
	bool operator!=(InIteratorList const& other) const { return p != other.p; }
	bool operator==(InIteratorList const& other) const { return p == other.p; }
	TNode<T>& operator*() const { return *p; } //typename Iterator<T>::reference operator*() const;
	InIteratorList& operator++() { p = p->next(); return *this; }
};

template<class T>
class OutIteratorList : public InIteratorList<T>,
	public std::iterator<std::output_iterator_tag, T> {
	friend class TList<T>;
	friend class TNode<T>;
protected:
	using InIteratorList<T>::p;
	OutIteratorList(TNode<T>* _p) : InIteratorList<T>(_p) {};
public:
	using InIteratorList<T>::operator*;
	using InIteratorList<T>::operator++;
	using InIteratorList<T>::operator==;
	using InIteratorList<T>::operator!=;
	OutIteratorList& operator++(int) {
		OutIteratorList tmp = *this;
		p++;
		return tmp;
	}
};

template <class T>
class ForwardIteratorList : public OutIteratorList<T>,
	public std::iterator<std::forward_iterator_tag, T> {
	friend class TList<T>;
	friend class TNode<T>;
protected:
	using OutIteratorList<T>::p;
	ForwardIteratorList(TNode<T>* _p) : OutIteratorList<T>(_p) {};
public:
	ForwardIteratorList(const ForwardIteratorList& it) : OutIteratorList<T>(it.p) {};
	using OutIteratorList<T>::operator*;
	using OutIteratorList<T>::operator++;
	using OutIteratorList<T>::operator==;
	using OutIteratorList<T>::operator!=;
};

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
	T& data() { return _data; }
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
	TList(const TList& list) {
		head = new TNode<T>(list.head->data());
		TNode<T>* cur1 = head;
		TNode<T>* cur2 = list.head;
		while (cur2->_next != nullptr)
		{
			cur1->_next = new TNode<T>(cur2->_next->data());
			cur1 = cur1->_next;
			cur2 = cur2->_next;
		}
		tail = cur1;
		count = list.count;
	}
	~TList() {
		TNode<T>* currentNode = head;
		while (currentNode != nullptr) {
			TNode<T>* nextNode = currentNode->next();
			delete currentNode;
			currentNode = nextNode;
		}
	}

	InIteratorList<T> begin_in() { return InIteratorList<T>(head); }
	InIteratorList<T> end_in() { return InIteratorList<T>(nullptr); }
	InIteratorList<T> begin_in() const { return InIteratorList<const T>(head); }
	InIteratorList<T> end_in() const { return InIteratorList<const T>(nullptr); }

	OutIteratorList<T> begin_out() { return OutIteratorList<T>(head); }
	OutIteratorList<T> end_out() { return OutIteratorList<T>(nullptr); }
	OutIteratorList<T> begin_out() const { return OutIteratorList<const T>(head); }
	OutIteratorList<T> end_out() const { return OutIteratorList<const T>(nullptr); }

	ForwardIteratorList<T> begin() { return ForwardIteratorList<T>(head); }
	ForwardIteratorList<T> end() { return ForwardIteratorList<T>(nullptr); }
	ForwardIteratorList<T> begin() const { return ForwardIteratorList<const T>(head); }
	ForwardIteratorList<T> end() const { return ForwardIteratorList<const T>(nullptr); }

	void insert(TNode<T>* p, const T& data) {
		if (p == nullptr) { throw std::logic_error("Wrong pointer"); }
		p->_next = new TNode<T>(data, p->_next);
		count++;
		if (p->_next == nullptr) { tail = p; return; }
		if (p->_next->_next == nullptr) { tail = p->_next; return; }
		
	}
	void insert(TNode<T> node, const T& data) {
		TNode<T>* tmp = head;
		while (tmp != nullptr && !(*tmp == node)) {
			tmp = tmp->_next;
		}
		if (tmp == nullptr) { throw std::logic_error("Wrong node"); }
		tmp->_next = new TNode<T>(data, tmp->_next);
		count++;
		if (node._next == nullptr) { return; }
		if (node._next->_next == nullptr) { tail = node._next; return; }

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

	void erase(TNode<T> node) {
		if (node == *head) { head = node._next; }
		else
		{
			TNode<T>* tmp = head;
			while (!(*(tmp->_next) == node) && tmp->_next != nullptr) {
				tmp = tmp->_next;
			}
			if (tmp->_next == nullptr) { throw std::logic_error("node is missing"); }
			delete tmp->_next;
			tmp->_next = node._next;
			if (tmp->_next == nullptr) { tail = tmp; }
		}
		count--;
		if (head == nullptr) { tail = nullptr; }
	}

	void push_back(const T& data) {
		TNode<T>* p = new TNode<T>(data);
		if (head == nullptr) { head = p; tail = p; }
		else { tail->_next = p; tail = p; }
		count++;
	}
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

template <class T>
ForwardIteratorList<T>* find(ForwardIteratorList<T> begin, ForwardIteratorList<T> end, const T& elem) {
	while (begin != end) {
		if ((*begin).data() == elem) return &begin;
		++begin;
	}
	return nullptr;
}
