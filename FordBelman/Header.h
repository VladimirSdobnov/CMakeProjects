#pragma once
#include <iostream>
#include <limits.h>
#include "TVector.h"
#include "../List/list.h"

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
	bool operator>(const TPair& other) const { return _key > other._key; }
	bool operator>(const TKey& k) const { return _key > k; }
	bool operator<(const TPair& other) const { return !(_key < other._key); }
	bool operator<(const TKey& k) const { return !(_key < k); }
};

struct Edge {
	int source, destination, weight;
};

void bellmanFord(TVector<int>& distance, TVector<int>& up, TVector<Edge>& graph, int vertices, int source);

void dijcstra_mark(TVector<int>& distance, TVector<int>& up, TVector<TList<Edge>>& ADJ, int vertices, int source);
