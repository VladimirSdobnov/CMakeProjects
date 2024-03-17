#pragma once
#include <iostream>
#include "../QueueOnList/QueueOnList.h"

template <class T>
class TBinarTree;

template <class T>
class TNodeTree {
private:
	T _data;
	TNodeTree* _left;
	TNodeTree* _right;
public:
	TNodeTree(T data, TNodeTree* l = nullptr, TNodeTree* r = nullptr) :_data(data), _left(l), _right(r) {}
	TNodeTree(const TNodeTree& node) :_data(node._data), _left(node._left), _right(node._right) {}
	~TNodeTree() { _left = nullptr; _right = nullptr; }
	TNodeTree& operator=(const TNodeTree& node) {
		_data = node._data;
		_left = node._left;
		_right = node._right;
		return *this;
	}
	bool operator==(const TNodeTree node) const noexcept {
		return _data == node._data && _left == node._left && _right == node._right;
	}
	TNodeTree* left() { return _left; }
	TNodeTree* right() { return _right; }
	T data() { return _data; }

	friend class TBinarTree<T>;
};

template <class T>
class TBinarTree {
public:
	TNodeTree<T>* root;


	TBinarTree() { root = nullptr; }

	void insert(T data) {
		if (root == nullptr) { root = new TNodeTree<T>(data); return; }
		TQueueOnList<TNodeTree<T>*> verts;
		verts.push(root);
		TNodeTree<T>* tmp = root;
		while (tmp->_left != nullptr && tmp->_right != nullptr) {
			verts.push(tmp->_left);
			verts.push(tmp->_right);
			verts.pop();
			tmp = verts.front();
		}
		TNodeTree<T>* newnode = new TNodeTree<T>(data);
		if (tmp->_left == nullptr) { tmp->_left = newnode; }
		else { tmp->_right = newnode; }
	}


	TNodeTree<T>* find_last(TNodeTree<T>* root){
		TQueueOnList<TNodeTree<T>*> verts;
		verts.push(root);
		TNodeTree<T>* tmp = root;
		while (tmp->_left != nullptr && tmp->_right != nullptr) {
			verts.push(tmp->_left);
			verts.push(tmp->_right);
			verts.pop();
			tmp = verts.front();
		}
		while (!verts.empty()) {
			tmp = verts.pop();
		}
		return tmp;
	}

	TNodeTree<T>* find(T val, TNodeTree<T>* cur, bool* exit_flag = new bool(false), TNodeTree<T>* res = nullptr) {
		if (cur == nullptr) { return res; }
		if (cur->data() == val) { *exit_flag = true; res = cur; return res; }
		if (!*exit_flag) { res = find(val, cur->_left, exit_flag, res); }
		if (!*exit_flag) { res = find(val, cur->_right, exit_flag, res); }
		return res;
	}

	TNodeTree<T>* find_pred(TNodeTree<T>* val, TNodeTree<T>* cur, bool* exit_flag = new bool(false), TNodeTree<T>* res = nullptr) {
		if (cur == nullptr) { return res; }
		if (cur->_left == val || cur->_right == val) { *exit_flag = true; res = cur; return res; }
		if (!*exit_flag) { res = find_pred(val, cur->_left, exit_flag, res); }
		if (!*exit_flag) { res = find_pred(val, cur->_right, exit_flag, res); }
		return res;
	}

	void erase(TNodeTree<T>* Node) {
		TNodeTree<T>* replacement = find_last(Node);
		TNodeTree<T>* pred = find_pred(Node, root);
		if (Node == root) { root->_data = replacement->data(); }
		else if (pred->left() == Node) { pred->_left->_data = replacement->data(); }
		else { pred->_right->_data = replacement->data(); }
		pred = find_pred(replacement, Node);
		if (pred->left() == Node) { pred->_left = nullptr; }
		else { pred->_right = nullptr; }
	}
};

template<class T>
void printtreeBFS(TBinarTree<T> tree) {
	TQueueOnList<TNodeTree<T>*> verts;
	verts.push(tree.root);
	TNodeTree<T>* tmp = tree.root;
	while (!verts.empty()) {
		if (tmp->left() != nullptr) {
			verts.push(tmp->left());
		}
		if (tmp->right() != nullptr) {
			verts.push(tmp->right());
		}
		std::cout << verts.pop()->data() << " ";
		if (!verts.empty()) tmp = verts.front();
	}
}
template<class T>
void printtreeDFSUP(TNodeTree<T>* cur) {
	if (cur == nullptr) { return; }
	std::cout << cur->data() << " ";
	printtreeDFSUP(cur->left());
	printtreeDFSUP(cur->right());
	return;
}
template<class T>
void printtreeDFSDOWNUP(TNodeTree<T>* cur) {
	if (cur == nullptr) { return; }
	
	printtreeDFSDOWNUP(cur->left());
	std::cout << cur->data() << " ";
	printtreeDFSDOWNUP(cur->right());
	return;
}
template<class T>
void printtreeDFSDOWNDOWN(TNodeTree<T>* cur) {
	if (cur == nullptr) { return; }
	
	printtreeDFSDOWNDOWN(cur->left());
	printtreeDFSDOWNDOWN(cur->right());
	std::cout << cur->data() << " ";
	return;
}
