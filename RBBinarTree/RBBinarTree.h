#include <iostream>

enum Color {Black /*[ ]*/, Red /*( )*/, BlackBlack };


template <class T>
class RBTree;


template <class T>
class RBNode {
	RBNode* _parent, * _left, * _right;
	T _val;
	Color _col;

public:
	RBNode(const T& val,
		Color col = Red,
		RBNode* par = nullptr,
		RBNode* l = nullptr,
		RBNode* r = nullptr) :
		_parent(par), _left(l), _right(r), _col(col), _val(val) {}
	RBNode() = default;
	RBNode(const RBNode& n):
		_parent(n._parent), _left(n._left), _right(n._right), _col(n._col), _val(n._val) {}
	~RBNode() { 
		_parent = nullptr;
		_left = nullptr;
		_right = nullptr;
	}
	RBNode& operator=(const RBNode& n) {
		_right = n._right;
		_left = n._left;
		_col = n._col;
		_val = n._val;
		_parent = n._parent;
	}
	bool operator==(const RBNode& n) const noexcept {
		return 
			(_col == n._col &&
			_left == n._left &&
				_right = n._right &&
				_parent == n._parent &
				_val == n._val)
	}

	void Recolor() {
		if (_col == Black) _col = Red;
		else _col = Black;
	}
	void SwapData(RBNode<T>* n){
		T tmp = n->_val;
		n->_val = _val;
		_val = tmp;
	}

	RBNode* Left() { return _left; }
	RBNode* Right() { return _right; }
	RBNode* Parent() { return _parent; }
	T Data() { return _val; }
	Color Color() { return _col; }

	friend class RBTree<T>;
};

template <class T>
class RBTree {
	RBNode<T>* root;

	RBNode<T>* Find(const T& val, RBNode<T>* cur, bool* exit_flag, RBNode<T>* res);

	RBNode<T>* FindInsPos(const T& val, RBNode<T>* cur, bool* exit_flag, RBNode<T>* res);
	
	void BalanceInsert(RBNode<T>* X);

	void BalanceErase(RBNode<T>* X);

	void RecolorTree(RBNode<T>* X);

	void LLeftRotate(RBNode<T>* X);

	void RRightRotate(RBNode<T>* X);

	void RLeftRotate(RBNode<T>* X);

	void LRightRotate(RBNode<T>* X);

	size_t FindHeigth(RBNode<T>* n);

	void Print(RBNode<T>* n, int* tabs);

	RBNode<T>* Find(const T& data);

	RBNode<T>* FindMax(RBNode<T>* val);

public:

	RBTree() : root(nullptr) {}

	/*bool Find(const T& data);*/

	void Insert(const T& data);

	void Erase(const T& data);

	void Print();

	size_t TreeHeigth();

	size_t TreeWidth();
};

template <class T>
RBNode<T>* RBTree<T>::Find(const T& val, RBNode<T>* cur, bool* exit_flag, RBNode<T>* res) {
	if (cur == nullptr) { return res; }
	if (cur->Data() == val) { *exit_flag = true; res = cur; return res; }
	if (!*exit_flag && val < cur->Data()) { res = Find(val, cur->_left, exit_flag, res); }
	else if (!*exit_flag && val > cur->Data()) { res = Find(val, cur->_right, exit_flag, res); }
	return res;
}

template <class T>
RBNode<T>* RBTree<T>::FindInsPos(const T& val, RBNode<T>* cur, bool* exit_flag, RBNode<T>* res) {
	if (cur == nullptr) { return res; }
	if ((val < cur->Data() && cur->_left == nullptr) || (val > cur->Data() && cur->_right == nullptr)) { *exit_flag = true; res = cur; return res; }
	if (!*exit_flag && val < cur->Data()) { res = FindInsPos(val, cur->_left, exit_flag, res); }
	else if (!*exit_flag && val > cur->Data()) { res = FindInsPos(val, cur->_right, exit_flag, res); }
	return res;
}

template <class T>
void RBTree<T>::BalanceInsert(RBNode<T>* X) {

	//Если дошли до некого нулевого указателя выходим
	//Чисто на всякий случай
	if (X == nullptr) { return; }


	//Задаем родителя
	RBNode<T>* P = X->Parent();

	//Если родитель НУЛЕВОЙ, значит дошли до КОРНЯ
	//Корень должен быть ЧЕРНЫМ
	if (P == nullptr) {
		root = X;
		X->_col = Black; return;
	}


	//Если родитель просто ЧЕРНЫЙ, то никаких проблем с балансом нет
	if (P->Color() == Black) { return; }
	if (X->Color() == Black && P->Color() == Red) { return; }

	//Задаем деда и дядю
	RBNode<T>* G = P->Parent();
	RBNode<T>* U = G->Right() != P ? G->Right() : G->Left();



	if (U == nullptr || U->Color() == Black) {

		//Когда дядя ЧЕРНЫЙ нужна проверка доп условий
		if (G->Left() == P && P->Left() == X) {
			LLeftRotate(X);
			BalanceInsert(P);
			return;
		}
		if (G->Right() == P && P->Right() == X) {
			RRightRotate(X);
			BalanceInsert(P);
			return;
		}
		if (G->Left() == P && P->Right() == X) {
			LRightRotate(X);
			BalanceInsert(X);
			return;
		}
		if (G->Right() == P && P->Left() == X) {
			RLeftRotate(X);
			BalanceInsert(X);
			return;
		}
	}
	else {

		//Когда дядя КРАСНЫЙ достаточно перекрасить участок дерева относительно Х
		RecolorTree(X);

		//И заново вызвать балансировку уже для деда,
		//потому что при перекраске он становится КРАСНЫМ и возможен конфликт
		BalanceInsert(G);
		return;
	}
}

template<class T>
void RBTree<T>::BalanceErase(RBNode<T>* X) {

	if (X == root) { return; }

	RBNode<T>* P = X->Parent();

	RBNode<T>* S = P->Right() != X ? P->Right() : P->Left();
	if (P->Color() == Red) {
		if ((S->Left() == nullptr || S->Left()->Color() == Black) &&
			(S->Right() == nullptr || S->Right()->Color() == Black)) {
			P->Recolor();
			S->Recolor();
		}
		else if (P->Left() == S && S->Left() != nullptr && S->Left()->Color() == Red) {
			LLeftRotate(S->Left());
			S->_col = Red;
			P->_col = Black;
			S->Left()->_col = Black;
			if (S->Parent() == nullptr) { root = S; }
		}
		else if (P->Right() == S && S->Right() != nullptr && S->Right()->Color() == Red) {
			RRightRotate(S->Right());
			S->_col = Red;
			P->_col = Black;
			S->Right()->_col = Black;
			if (S->Parent() == nullptr) { root = S; }
		}
		else if (P->Left() == S && S->Left() == nullptr && S->Right()->Color() == Red) {
			LRightRotate(S->Right());
			S->Parent()->Recolor();
			P->Recolor();
		}
		else if (P->Right() == S && S->Right() == nullptr && S->Left()->Color() == Red) {
			RLeftRotate(S->Left());
			S->Parent()->Recolor();
			P->Recolor();

		}
	}
	else if (P->Color() == Black) {
		if (S->Color() == Red &&
			S->Left()->Color() == Black &&
			S->Right()->Color() == Black) {
			if (S == P->Left() &&
				(S->Right()->Right() == nullptr || S->Right()->Right()->Color() == Black) &&
				(S->Right()->Left() == nullptr || S->Right()->Left()->Color() == Black)) {
				LLeftRotate(S->Left());
				S->_col = Black;
				S->Right()->Left()->Recolor();
				if (S->Parent() == nullptr) { root = S; }
			}
			else if (S == P->Right() &&
				(S->Left()->Right() == nullptr || S->Left()->Right()->Color() == Black) &&
				(S->Left()->Left() == nullptr || S->Left()->Left()->Color() == Black)) {
				RRightRotate(S->Right());
				S->_col = Black;
				S->Left()->Right()->Recolor();
				if (S->Parent() == nullptr) { root = S; }
			}
			else if (S == P->Left() &&
				(S->Right()->Left() == nullptr ||
				 S->Right()->Left()->Color() == Black)) {
				LRightRotate(S->Right());
				P->_col = Black;
				S->Recolor();
				if (S->Left() != nullptr)S->Left()->Recolor();
				if (S->Parent()->Parent() == nullptr) { root = S->Parent(); }
			}
			else if (S == P->Right() &&
				S->Left()->Right()->Color() == Red) {
				RLeftRotate(S->Left());
				P->_col = Black;
				S->Recolor();
				if (S->Right() != nullptr) S->Right()->Recolor();
				if (S->Parent()->Parent() == nullptr) { root = S->Parent(); }
			}
			else if (S == P->Left() &&
				S->Right()->Left()->Color() == Red) {
				LRightRotate(S->Right());
				P->_col = Black;
				if (S->Right() != nullptr)S->Right()->Recolor();
				if (S->Parent()->Parent() == nullptr) { root = S->Parent(); }
			}
			else if (S == P->Right() &&
				S->Left()->Right()->Color() == Red) {
				RLeftRotate(S->Left());
				P->_col = Black;
				if(S->Left() != nullptr) S->Left()->Recolor();
				if (S->Parent()->Parent() == nullptr) { root = S->Parent(); }
			}
		}
		else if (S->Color() == Black) {
			if (S == P->Left() &&
				S->Right() != nullptr &&
				S->Right()->Color() == Red) {
				LRightRotate(S->Right());
				P->Recolor();
				if (S->Parent() == nullptr) { root = S; }
				else if (S->Parent()->Parent() == nullptr) { root = S->Parent(); }
			}
			else if (S == P->Right() &&
				S->Left() != nullptr &&
				S->Left()->Color() == Red) {
				RLeftRotate(S->Left());
				P->Recolor();
				if (S->Parent() == nullptr) { root = S; }
				else if (S->Parent()->Parent() == nullptr) { root = S->Parent(); }
			}
			else if ((S->Left() == nullptr || S->Left()->Color() == Black) &&
				(S->Right() == nullptr || S->Right()->Color() == Black)) {
				S->Recolor();
				BalanceErase(P);
			}
			if (S == P->Left() &&
				S->Left() != nullptr &&
				S->Left()->Color() == Red) {
				LLeftRotate(S->Left());
				if (S->Parent() == nullptr) { root = S; }
				else if (S->Parent()->Parent() == nullptr) { root = S->Parent(); }
			}
			else if (S == P->Right() &&
				S->Right() != nullptr &&
				S->Right()->Color() == Red) {
				RRightRotate(S->Right());
				if (S->Parent() == nullptr) { root = S; }
				else if (S->Parent()->Parent() == nullptr) { root = S->Parent(); }
			}
		}
	}

	if (root->Color() == Red) { root->_col = Black; }
	
}

template <class T>
void RBTree<T>::RecolorTree(RBNode<T>* X) {
	RBNode<T>* P = X->Parent();
	RBNode<T>* G = P->Parent();
	RBNode<T>* U = G->Right() != P ? G->Right() : G->Left();

	/*
			  [G]                      (G)
		   /      \     recolor      /     \
		 (P)      (U)    ---->     [P]     [U]
		/   \    /   \   ---->    /   \   /   \
	  (X)   T3  T4   T5  ---->  (X)   T3 T4   T5
	 /   \                     /   \
	T1   T2                   T1   T2
	*/


	P->_col = Black;
	G->_col = Red;
	U->_col = Black;
}

template <class T>
void RBTree<T>::LLeftRotate(RBNode<T>* X) {
	RBNode<T>* P = X->Parent();
	RBNode<T>* G = P->Parent();
	RBNode<T>* U = G->Left();

	/*
			 [G]                          (P)
		   /     \     RRightRotate     /     \
		 (P)     [U]     ---->        [X]     [G]
		/   \   /   \    ---->       /   \   /   \
	  (X)   T3 T4   T5   ---->      T1   T2 T3   [U]
	 /   \                                      /   \
	T1   T2                                    T4   T5
	*/

	//Подвешиваем P к отцу G
	if (G->Parent() != nullptr) {
		if (G == G->_parent->_left) {
			G->_parent->_left = P;
		}
		else {
			G->_parent->_right = P;
		}
	}
	P->_parent = G->_parent;


	//Подвешиваем ветку T3 к G
	G->_left = P->_right;
	if (P->Right() != nullptr) P->_right->_parent = G;

	//Подвешиваем G к P
	P->_right = G;
	G->_parent = P;

	//Перекрашиваем U и X
	X->_col = Black;
}

template <class T>
void RBTree<T>::RRightRotate(RBNode<T>* X) {
	RBNode<T>* P = X->Parent();
	RBNode<T>* G = P->Parent();
	RBNode<T>* U = G->Right();
	/*
			[G]                          (P)
		  /     \     LLeftRotate      /     \
		[U]     (P)     ---->        [G]     [X]
	   /   \   /   \    ---->       /   \   /   \
	  T1   T2 T3   (X)  ---->     [U]   T3 T4   T5
				  /   \          /   \
				 T4   T5        T1   T2
	*/
	//Подвешиваем P к отцу G
	if (G->Parent() != nullptr) {
		if (G == G->_parent->_left) {
			G->_parent->_left = P;
		}
		else {
			G->_parent->_right = P;
		}
	}
	P->_parent = G->_parent;


	//Подвешиваем ветку T3 к G
	G->_right = P->_left;
	if (P->Left() != nullptr) P->_left->_parent = G;

	//Подвешиваем G к P
	P->_left = G;
	G->_parent = P;

	//Перекрашиваем U и X
	X->_col = Black;
}

template <class T>
void RBTree<T>::RLeftRotate(RBNode<T>* X) {
	RBNode<T>* P = X->Parent();
	RBNode<T>* G = P->Parent();
	RBNode<T>* U = G->Right();

	/*
			 [G]                          [X]
		   /     \    LRightRotate      /     \
		 [U]     (P)     ---->        (G)     (P)
		/   \   /   \    ---->       /   \   /   \
	  T1   T2 (X)   T5   ---->     [U]   T3 T4   T5
			 /   \                /   \
		   T3     T4             T1    T2
	*/

	//Подвешиваем X к отцу G
	if (G->Parent() != nullptr) {
		if (G == G->_parent->_left) {
			G->_parent->_left = X;
		}
		else {
			G->_parent->_right = X;
		}
	}
	X->_parent = G->_parent;


	//Подвешиваем ветку T3 к G
	G->_right = X->_left;
	if (X->Left() != nullptr) X->_left->_parent = G;

	//Подвешиваем ветку T4 к P
	P->_left = X->_right;
	if (X->Right() != nullptr) X->_right->_parent = P;

	//Подвешиваем G к X
	X->_left = G;
	G->_parent = X;

	//Подвешиваем P к X
	X->_right = P;
	P->_parent = X;

	//Перекрашиваем X и G
	X->_col = Black;
	G->_col = Red;
}

template <class T>
void RBTree<T>::LRightRotate(RBNode<T>* X) {
	RBNode<T>* P = X->Parent();
	RBNode<T>* G = P->Parent();
	RBNode<T>* U = G->Left();

	/*
			 [G]                          [X]
		   /     \    LRightRotate      /     \
		 (P)     [U]     ---->        (P)     (G)
		/   \   /   \    ---->       /   \   /   \
	  T1   (X) T4   T5   ---->      T1   T2 T3   [U]
		  /   \                                 /   \
		 T2   T3                               T4   T5
	*/

	//Подвешиваем X к отцу G
	if (G->Parent() != nullptr) {
		if (G == G->_parent->_left) {
			G->_parent->_left = X;
		}
		else {
			G->_parent->_right = X;
		}
	}
	X->_parent = G->_parent;


	//Подвешиваем ветку T3 к G
	G->_left = X->_right;
	if (X->Right() != nullptr) X->_right->_parent = G;

	//Подвешиваем T2 к P
	P->_right = X->_left;
	if (X->Left() != nullptr) X->_left->_parent = P;

	//Подвешиваем G к X
	X->_right = G;
	G->_parent = X;

	//Подвешиваем P к X
	X->_left = P;
	P->_parent = X;

	//Перекрашиваем X и G
	X->_col = Black;
	G->_col = Red;

}

template <class T>
void RBTree<T>::Insert(const T& data) {
	if (root == nullptr) { root = new RBNode<T>(data, Black); return; }
	bool* exit_flag = new bool(false);
	RBNode<T>* cur = root;
	RBNode<T>* res = nullptr;
	res = FindInsPos(data, cur, exit_flag, res);
	if (res == nullptr) { return; }
	RBNode<T>* X = new RBNode<T>(data, Red, res);
	if (data < res->Data()) { res->_left = X; }
	else if (data > res->Data()) { res->_right = X; }
	BalanceInsert(X);
}

template<class T>
void RBTree<T>::Erase(const T& data) {
	RBNode<T>* X = Find(data);
	if (X == nullptr) { return; }
	if (X->Left() != nullptr && X->Right() != nullptr) {
		RBNode<T>* tmp = FindMax(X->Left());
		X->SwapData(tmp);
		X = tmp;
	}

	RBNode<T>* P = X->Parent();

	if (X->Left() == nullptr && X->Right() == nullptr && X->Color() == Red) {
		if (X == P->Left()) {
			P->_left = nullptr;
		}
		else {
			P->_right = nullptr;
		}
		return;
	}

	if (X->Color() == Black) {
		if (X->Left() != nullptr && X->Right() == nullptr) {
			X->SwapData(X->Left());
			X->_left = nullptr;
			return;
		}
		else if(X->Left() == nullptr && X->Right() != nullptr) {
			X->SwapData(X->Right());
			X->_right = nullptr;
			return;
		}
	}

	BalanceErase(X);

	P = X->Parent();
	if (X == root) { root = nullptr; return; }

	if (X == P->Left()) {
		P->_left = nullptr;
	}
	else {
		P->_right = nullptr;
	}
}

template <class T>
size_t RBTree<T>::FindHeigth(RBNode<T>* n) {
	if (n->Left() == nullptr && n->Right() == nullptr) { return 0; }
	size_t h1 = 0, h2 = 0;
	if (n->Left() != nullptr) h1 = FindHeigth(n->Left());
	if (n->Right() != nullptr) h2 = FindHeigth(n->Right());
	return std::max(h1, h2) + 1;
}

template <class T>
size_t RBTree<T>::TreeHeigth() {
	return FindHeigth(root);
}

template <class T>
size_t RBTree<T>::TreeWidth() {
	return std::pow(2, TreeHeigth());
}

template <class T>
void RBTree<T>::Print(RBNode<T>* n, int* tabs) {
	if (n == nullptr) return; // Если ветки не существует — выходим, выводить нечего
	(*tabs) += 6; // Иначе увеличим счётчик рекурсивно вызванных процедур, который будет считать отступы для красивого вывода
	Print(n->Left(), tabs); // Выведем ветку и её подветки слева
	for (int i = 0; i < *tabs; i++) std::cout << " "; // Потом отступы
	if (n->Parent() != nullptr) {
		if (n == n->Parent()->Left()) std::cout << "/";
		else std::cout << "\\";
	}
	if (n->Color() == Red) std::cout << "(" << n->Data() << ")" << std::endl;
	if (n->Color() == Black) std::cout << "[" << n->Data() << "]" << std::endl;
	// Данные этой ветки
	Print(n->Right(), tabs); // И ветки, что справа
	(*tabs) -= 6; // После уменьшим количество отступов
	return;
}

template<class T>
RBNode<T>* RBTree<T>::Find(const T& data) {
	RBNode<T>* cur = root;
	bool* exit_flag = new bool(false);
	RBNode<T>* res = nullptr;
	return Find(data, cur, exit_flag, res);
}

template<class T>
RBNode<T>* RBTree<T>::FindMax(RBNode<T>* val) {
	RBNode<T>* res = val;
	while (res->_right != nullptr) {
		res = res->_right;
	}
	return res;
}

template <class T>
void RBTree<T>::Print() {
	int* tabs = new int(0);
	Print(root, tabs);
}

/*
			  [G]                      (G)
		   /      \     recolor      /     \
		 (P)      (U)    ---->     [P]     [U]
		/   \    /   \   ---->    /   \   /   \
	  (X)   T3  T4   T5  ---->  (X)   T3 T4   T5
	 /   \                     /   \            
	T1   T2                   T1   T2           
	*/