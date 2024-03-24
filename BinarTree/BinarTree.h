#pragma once
#include <iostream>
#include "../QueueOnList/QueueOnList.h"

template <class T>
class TBinarTree;
template <class T>
class TSearchTree;


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
	friend class TSearchTree<T>;
};

template <class T>
class TBinarTree {
private:
	TNodeTree<T>* find(const T& val, TNodeTree<T>* cur, bool* exit_flag, TNodeTree<T>* res) {
		if (cur == nullptr) { return res; }
		if (cur->data() == val) { *exit_flag = true; res = cur; return res; }
		if (!*exit_flag) { res = find(val, cur->_left, exit_flag, res); }
		if (!*exit_flag) { res = find(val, cur->_right, exit_flag, res); }
		return res;
	}
	TNodeTree<T>* find_pred(TNodeTree<T>* val, TNodeTree<T>* cur, bool* exit_flag, TNodeTree<T>* res) {
		if (cur == nullptr) { return res; }
		if (cur->_left == val || cur->_right == val) { *exit_flag = true; res = cur; return res; }
		if (!*exit_flag) { res = find_pred(val, cur->_left, exit_flag, res); }
		if (!*exit_flag) { res = find_pred(val, cur->_right, exit_flag, res); }
		return res;
	}
	
public:
	TNodeTree<T>* root;
	TBinarTree() { root = nullptr; }
	TBinarTree(const TBinarTree& tree) {
		if (tree.root == nullptr) { root = nullptr; return; }
		root = new TNodeTree<T>(tree.root->data());
		TQueueOnList<TNodeTree<T>*> verts;
		TQueueOnList<TNodeTree<T>*> verts2;
		verts.push(tree.root);
		verts2.push(root);
		TNodeTree<T>* tmp = tree.root;
		TNodeTree<T>* cur = root;
		while (!verts.empty()) {
			if (tmp->_left != nullptr) {
				verts.push(tmp->_left);
				cur->_left = new TNodeTree<T>(tmp->_left->data());
				verts2.push(cur->_left);
			}
			if (tmp->_right != nullptr) {
				verts.push(tmp->_right);
				cur->_right = new TNodeTree<T>(tmp->_right->data());
				verts2.push(cur->_right);
			}
			verts.pop();
			verts2.pop();
			if (!verts.empty()) {
				tmp = verts.front();
				cur = verts2.front();
			}
		}
	}

	void insert(const T& data) {
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

	TNodeTree<T>* find_last(){
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

	TNodeTree<T>* find(const T& val) {
		TNodeTree<T>* cur = root;
		bool* exit_flag = new bool(false);
		TNodeTree<T>* res = nullptr;
		return find(val, cur, exit_flag, res);
	}
	
	TNodeTree<T>* find_pred(TNodeTree<T>* val) {
		TNodeTree<T>* cur = root;
		bool* exit_flag = new bool(false);
		TNodeTree<T>* res = nullptr;
		return find_pred(val, cur, exit_flag, res);
	}
	void erase(TNodeTree<T>* Node) {
		if (root == nullptr) { return; }
		TNodeTree<T>* replacement = find_last();
		TNodeTree<T>* pred;
		if (Node == root) {
			if (Node == replacement) { root == nullptr; return; }
			else { root->_data = replacement->data(); }
		}
		else {
			pred = find_pred(Node);
			if (Node == replacement) {
				if (pred->_left == Node) pred->_left = nullptr;
				else if (pred->_right == Node) pred->_right = nullptr;
				return;
			}
			else if (pred->_left == Node) { pred->_left->_data = replacement->data(); }
			else { pred->_right->_data = replacement->data(); }
		}
		pred = find_pred(replacement);
		if (pred->left() == Node) { pred->_left = nullptr; }
		else { pred->_right = nullptr; }
	}
};

template<class T>
void printtreeBFS(const TBinarTree<T>& tree) {
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

template <class T>
class TSearchTree {
private:
	TNodeTree<T>* find(const T& val, TNodeTree<T>* cur, bool* exit_flag, TNodeTree<T>* res) {
		if (cur == nullptr) { return res; }
		if (cur->data() == val) { *exit_flag = true; res = cur; return res; }
		if (!*exit_flag && val < cur->data()) { res = find(val, cur->_left, exit_flag, res); }
		else if (!*exit_flag && val > cur->data()) { res = find(val, cur->_right, exit_flag, res); }
		return res;
	}
	TNodeTree<T>* find_pred(TNodeTree<T>* val, TNodeTree<T>* cur, bool* exit_flag, TNodeTree<T>* res) {
		if (cur == nullptr) { return res; }
		if (cur->_left == val || cur->_right == val) { *exit_flag = true; res = cur; return res; }
		if (!*exit_flag && val->data() < cur->data()) { res = find_pred(val, cur->_left, exit_flag, res); }
		else if (!*exit_flag && val->data() > cur->data()) { res = find_pred(val, cur->_right, exit_flag, res); }
		return res;
	}
	TNodeTree<T>* find_ins_pos(const T& val, TNodeTree<T>* cur, bool* exit_flag, TNodeTree<T>* res) {
		if (cur == nullptr) { return res; }
		if ((val < cur->data() && cur->_left == nullptr) || (val > cur->data() && cur->_right == nullptr)) { *exit_flag = true; res = cur; return res; }
		if (!*exit_flag && val < cur->data()) { res = find_ins_pos(val, cur->_left, exit_flag, res); }
		else if (!*exit_flag && val > cur->data()) { res = find_ins_pos(val, cur->_right, exit_flag, res); }
		return res;
	}
	TNodeTree<T>* find_max(TNodeTree<T>* val) {
		TNodeTree<T>* res = val;
		while (res->_right != nullptr) {
			res = res->_right;
		}
		return res;
	}
	TNodeTree<T>* find_min(TNodeTree<T>* val) {
		TNodeTree<T>* res = val;
		while (res->_left != nullptr) {
			res = res->_left;
		}
		return res;
	}
public:
	TNodeTree<T>* root;
	TSearchTree() : root(nullptr) {}
	TSearchTree(const TSearchTree& tree) {
		if (tree.root == nullptr) { root = nullptr; return; }
		root = new TNodeTree<T>(tree.root->data());
		TQueueOnList<TNodeTree<T>*> verts;
		TQueueOnList<TNodeTree<T>*> verts2;
		verts.push(tree.root);
		verts2.push(root);
		TNodeTree<T>* tmp = tree.root;
		TNodeTree<T>* cur = root;
		while (!verts.empty()) {
			if (tmp->_left != nullptr) {
				verts.push(tmp->_left);
				cur->_left = new TNodeTree<T>(tmp->_left->data());
				verts2.push(cur->_left);
			}
			if (tmp->_right != nullptr) {
				verts.push(tmp->_right);
				cur->_right = new TNodeTree<T>(tmp->_right->data());
				verts2.push(cur->_right);
			}
			verts.pop();
			verts2.pop();
			if (!verts.empty()) {
				tmp = verts.front();
				cur = verts2.front();
			}
		}
	}
	void insert(const T& data) {
		if (root == nullptr) { root = new TNodeTree<T>(data); return; }
		bool* exit_flag = new bool(false);
		TNodeTree<T>* cur = root;
		TNodeTree<T>* res = nullptr;
		res = find_ins_pos(data, cur, exit_flag, res);
		if (res == nullptr) { return; }
		if (data < res->data()) { res->_left = new TNodeTree<T>(data); }
		else if(data > res->data()) { res->_right = new TNodeTree<T>(data); }
	}
	TNodeTree<T>* find(const T& val) {
		TNodeTree<T>* cur = root;
		bool* exit_flag = new bool(false);
		TNodeTree<T>* res = nullptr;
		return find(val, cur, exit_flag, res);
	}
	TNodeTree<T>* find_pred(TNodeTree<T>* val) {
		TNodeTree<T>* cur = root;
		bool* exit_flag = new bool(false);
		TNodeTree<T>* res = nullptr;
		return find_pred(val, cur, exit_flag, res);
	}
	void erase(const T& val) {
		TNodeTree<T>* tmp = find(val);
		if (tmp == nullptr) { return; }
		if (tmp->_left == nullptr && tmp->_right == nullptr) {
			TNodeTree<T>* pred = find_pred(tmp);
			if (tmp == pred->_left) { pred->_left = nullptr; return; }
			if (tmp == pred->_right) { pred->_right = nullptr; return; }
		}
		if (tmp->_left == nullptr) {
			TNodeTree<T>* pred = find_pred(tmp);
			if (tmp == pred->_left) { pred->_left = tmp->_right; return; }
			if (tmp == pred->_right) { pred->_right = tmp->_right; return; }
		}
		if (tmp->_right == nullptr) {
			TNodeTree<T>* pred = find_pred(tmp);
			if (tmp == pred->_left) { pred->_left = tmp->_left; return; }
			if (tmp == pred->_right) { pred->_right = tmp->_left; return; }
		}
		TNodeTree<T>* replacement = find_max(tmp->_left);
		TNodeTree<T>* pred = find_pred(replacement);
		tmp->_data = replacement->data();
		if (replacement == pred->_left) { pred->_left = nullptr; return; }
		if (replacement == pred->_right) { pred->_right = nullptr; return; }
	}
};