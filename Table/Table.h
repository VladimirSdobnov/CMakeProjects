#include "../TVectore/TVector.h"
#include "../List/list.h"
#include <iostream>

enum Status {Full, Empty};

#define SIZE 50 
#define STEP 3 


template<class TKey, class TValue>
class TPair {
	TKey _key;
	TValue _val;
public:
	TPair() = default;
	TPair(TKey key, TValue val) :_key(key), _val(val) {}
	TValue& val() { return _val; }
	TKey key() { return _key; }
	bool operator==(const TPair& other) const { return _key == other._key; }
	bool operator==(const TKey& k) const { return _key == k; }
	bool operator!=(const TPair& other) const { return !(_key == other._key); }
	bool operator!=(const TKey& k) const { return !(_key == k); }
};

template <class TKey, class TValue>
class ITable {
public:
	virtual TValue* search(const TKey& key) = 0;
	virtual void insert(const TKey& key, const TValue& val) = 0;
	virtual void erase(const TKey& key) = 0;
	virtual void replace(const TKey& key, const TValue& val) = 0;
};

template <class TKey, class TValue>
class UnorderedTableVec : public ITable<TKey, TValue> {
	TVector<TPair<TKey, TValue>> data;
public:
	UnorderedTableVec() = default;
	TValue* search(const TKey& key) override {
		for (auto i = data.begin(); i != data.end(); ++i) {
			if (*i == key) { return &((*i).val()); }
		}
		return nullptr;
	}
	void insert(const TKey& key, const TValue& val) override {
		for (auto elem : data) {
			if (elem == key) {
				return;
			}
		}
		data.append(TPair<TKey, TValue>(key, val));
	}
	void erase(const TKey& key) override {
		int i = 0;
		for (; data[i] != key; i++);
		data.erase(i);
	}
	void replace(const TKey& key, const TValue& val) override {
		for (auto elem : data) {
			if (elem == key) {
				elem.val() = val;
				return;
			}
		}
	}
	size_t size() { return data.size(); }
};

template <class TKey, class TValue>
class UnorderedTableList : public ITable<TKey, TValue> {
	TList<TPair<TKey, TValue>> data;
public:
	UnorderedTableList() = default;
	TValue* search(const TKey& key) override {
		for (auto i = data.begin();
			i != data.end();
			++i) {
			if ((*i).data() == key) { return &((*i).data().val()); }
		}
		return nullptr;
	}
	void insert(const TKey& key, const TValue& val) override {
		for (auto elem : data) {
			if (elem.data() == key) {
				return;
			}
		}
		data.push_back(TPair<TKey, TValue>(key, val));
	}
	void erase(const TKey& key) override {
		for (auto elem : data) {
			if (elem.data() == key) { data.erase(elem); return; }
		}
	}
	void replace(const TKey& key, const TValue& val) override {
		for (auto elem : data) {
			if (elem.data() == key) { elem.data().val() = val; return; }
		}
	}
	size_t size() { return data.size(); }
};

template <class TKey, class TValue>
class HashTableNode : public ITable<TKey, TValue> {
	TVector<TList<TPair<TKey, TValue>>> data;
	size_t(*HashFunc) (const TKey&);
	size_t count;
public:
	size_t HashInd(size_t x) {
		return x % data.size();
	}
	HashTableNode(size_t(*func)(const TKey&)) : data(SIZE, SIZE), HashFunc(func), count(0) {}
	TValue* search(const TKey& key) override {
		size_t ind = HashInd(HashFunc(key));
		if (data[ind].empty()) { return nullptr; }
		for (auto i = data[ind].begin(); i != data[ind].end(); i++) {
			if ((*i).data() == key) { return &((*i).data().val()); }
		}
		return nullptr;
	}
	void insert(const TKey& key, const TValue& val) override {
		size_t ind = HashInd(HashFunc(key));
		TPair<TKey, TValue> tmp(key, val);
		for (auto i = data[ind].begin(); i != data[ind].end(); i++) {
			if ((*i).data() == key) { throw std::logic_error("Object with this key exists"); }
		}
		if (data[ind].empty()) { count++; }
		data[ind].push_back(tmp);
	}
	void erase(const TKey& key) override {
		size_t ind = HashInd(HashFunc(key));
		for (auto i = data[ind].front_node(); i != nullptr; i = i->next()) {
			if (i->data() == key) { 
				data[ind].erase(i);
				if (data[ind].empty()) { count--; }
				return;
			}
		}
	}
	void replace(const TKey& key, const TValue& val) override {
		size_t ind = HashInd(HashFunc(key));
		for (auto i = data[ind].front_node(); i != nullptr; i = i->next()) {
			if (i->data() == key) {
				i->data().val() = val;
				return;
			}
		}
	}

	size_t size() { return count; }
};

template <class TKey, class TValue>
class HashTableStep : public ITable<TKey, TValue> {
	TVector<TPair<TKey, TValue>> data;
	TVector<Status> statuses;
	size_t(*HashFunc) (const TKey&);
	size_t count;
public:
	size_t HashInd(size_t x) {
		return x % data.size();
	}
	size_t DoubleHashInd(size_t x) {
		return (x + STEP) % data.size();
	}
	HashTableStep(size_t(*func)(const TKey&)) : data(SIZE, SIZE), statuses(SIZE, SIZE), HashFunc(func), count(0) {
		for (int i = 0; i < SIZE; i++) statuses[i] = Empty;
	}
	TValue* search(const TKey& key) override {
		size_t ind = HashInd(HashFunc(key));
		if (statuses[ind] == Empty) { return nullptr; }
		for (int i = 0; i < SIZE; i++) {
			if (statuses[ind] == Empty) { return nullptr; }
			if (data[ind] == key) { return &(data[ind].val()); }
			ind = DoubleHashInd(ind);
		}
		return nullptr;
	}
	void insert(const TKey& key, const TValue& val) override {
		size_t ind = HashInd(HashFunc(key));
		TPair<TKey, TValue> tmp(key, val);
		for (int i = 0; i < SIZE; i++) {
			if (statuses[ind] == Empty) { 
				data[ind] = tmp;
				statuses[ind] = Full;
				count++;
				return; }
			if (statuses[ind] == Full && data[ind] == key) { throw std::logic_error("Object with this key exists"); }
			ind = DoubleHashInd(ind);
		}
		throw std::logic_error("Table is full");
	}
	void erase(const TKey& key) override {
		size_t ind = HashInd(HashFunc(key));
		for (int i = 0; i < SIZE; i++) {
			if (statuses[ind] == Full && data[ind] == key) { statuses[ind] = Empty; count--; return; }
			ind = DoubleHashInd(ind);
		}
	}
	void replace(const TKey& key, const TValue& val) override {
		size_t ind = HashInd(HashFunc(key));
		for (int i = 0; i < SIZE; i++) {
			if (statuses[ind] == Full && data[ind] == key) { data[ind].val() = val; return; }
			ind = DoubleHashInd(ind);
		}
	}

	size_t size() { return count; }
};