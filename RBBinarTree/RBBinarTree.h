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

	void recolor() {
		if (_col == Black) _col = Red;
		else _col == Black;
	}

	RBNode* left() { return _left; }
	RBNode* right() { return _right; }
	RBNode* parent() { return _parent; }
	T data() { return _val; }
	Color color() { return _col; }

	friend class RBTree<T>;
};

template <class T>
class RBTree {
	RBNode<T>* root;
	RBNode<T>* find(const T& val, RBNode<T>* cur, bool* exit_flag, RBNode<T>* res) {
		if (cur == nullptr) { return res; }
		if (cur->data() == val) { *exit_flag = true; res = cur; return res; }
		if (!*exit_flag && val < cur->data()) { res = find(val, cur->_left, exit_flag, res); }
		else if (!*exit_flag && val > cur->data()) { res = find(val, cur->_right, exit_flag, res); }
		return res;
	}
	RBNode<T>* find_ins_pos(const T& val, RBNode<T>* cur, bool* exit_flag, RBNode<T>* res) {
		if (cur == nullptr) { return res; }
		if ((val < cur->data() && cur->_left == nullptr) || (val > cur->data() && cur->_right == nullptr)) { *exit_flag = true; res = cur; return res; }
		if (!*exit_flag && val < cur->data()) { res = find_ins_pos(val, cur->_left, exit_flag, res); }
		else if (!*exit_flag && val > cur->data()) { res = find_ins_pos(val, cur->_right, exit_flag, res); }
		return res;
	}
	

	void balance(RBNode<T>* X) {

		//Если дошли до некого нулевого указателя выходим
		//Чисто на всякий случай
		if (X == nullptr) { return; }


		//Задаем родителя
		RBNode<T>* P = X->parent();

		//Если родитель НУЛЕВОЙ, значит дошли до КОРНЯ
		//Корень должен быть ЧЕРНЫМ
		if (P == nullptr) {
			root = X;
			X->_col = Black; return; 
		}


		//Если родитель просто ЧЕРНЫЙ, то никаких проблем с балансом нет
		if (P->color() == Black) { return; }


		//Задаем деда и дядю
		RBNode<T>* G = P->parent();
		RBNode<T>* U = G->right() != P ? G->right() : G->left();



		if (U == nullptr || U->color() == Black) {

			//Когда дядя ЧЕРНЫЙ нужна проверка доп условий
			if (G->left() == P && P->left() == X) {
				LLeftRotate(X);
				balance(P);
				return;
			}
			if (G->right() == P && P->right() == X) {
				RRightRotate(X);
				balance(P);
				return;
			}
			if (G->left() == P && P->right() == X) {
				LRightRotate(X);
				balance(X);
				return;
			}
			if (G->right() == P && P->left() == X) {
				RLeftRotate(X);
				balance(X);
				return;
			}
		}
		else {

			//Когда дядя КРАСНЫЙ достаточно перекрасить участок дерева относительно Х
			recolorTree(X);

			//И заново вызвать балансировку уже для деда,
			//потому что при перекраске он становится КРАСНЫМ и возможен конфликт
			balance(G);
			return;
		}
	}

	void recolorTree(RBNode<T>* X) {
		RBNode<T>* P = X->parent();
		RBNode<T>* G = P->parent();
		RBNode<T>* U = G->right() != P ? G->right() : G->left();

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

	void LLeftRotate(RBNode<T>* X) {
		RBNode<T>* P = X->parent();
		RBNode<T>* G = P->parent();
		RBNode<T>* U = G->left();

		/*
				 [G]                          (P)
			   /     \     RRightRotate     /     \
			 (P)     [U]     ---->        [X]     [G]
			/   \   /   \    ---->       /   \   /   \
		  (X)   T3 T4   T5   ---->      T1   T2 T3   (U)
		 /   \                                      /   \
		T1   T2                                    T4   T5
		*/

		//Подвешиваем P к отцу G
		if (G->parent() != nullptr) {
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
		if (P->right() != nullptr) P->_right->_parent = G;

		//Подвешиваем G к P
		P->_right = G;
		G->_parent = P;

		//Перекрашиваем U и X
		U->_col = Red;
		X->_col = Black;
	}

	void RRightRotate(RBNode<T>* X) {
		RBNode<T>* P = X->parent();
		RBNode<T>* G = P->parent();
		RBNode<T>* U = G->right();
		/*
				[G]                          (P)
			  /     \     LLeftRotate      /     \
			[U]     (P)     ---->        [G]     [X]
		   /   \   /   \    ---->       /   \   /   \
		  T1   T2 T3   (X)  ---->     (U)   T3 T4   T5
					  /   \          /   \
					 T4   T5        T1   T2
		*/
		//Подвешиваем P к отцу G
		if (G->parent() != nullptr) {
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
		if (P->left() != nullptr) P->_left->_parent = G;

		//Подвешиваем G к P
		P->_left = G;
		G->_parent = P;

		//Перекрашиваем U и X
		U->_col = Red;
		X->_col = Black;
	}

	void RLeftRotate(RBNode<T>* X) {
		RBNode<T>* P = X->parent();
		RBNode<T>* G = P->parent();
		RBNode<T>* U = G->right();

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
		if (G->parent() != nullptr) {
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
		if (X->left() != nullptr) X->_left->_parent = G;

		//Подвешиваем ветку T4 к P
		P->_left = X->_right;
		if (X->right() != nullptr) X->_right->_parent = P;

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

	void LRightRotate(RBNode<T>* X) {
		RBNode<T>* P = X->parent();
		RBNode<T>* G = P->parent();
		RBNode<T>* U = G->left();

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
		if (G->parent() != nullptr) {
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
		if (X->right() != nullptr) X->_right->_parent = G;

		//Подвешиваем T2 к P
		P->_right = X->_left;
		if (X->left() != nullptr) X->_left->_parent = P;

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

public:
	RBTree() : root(nullptr) {}
	void insert(const T& data) {
		if (root == nullptr) { root = new RBNode<T>(data, Black); return; }
		bool* exit_flag = new bool(false);
		RBNode<T>* cur = root;
		RBNode<T>* res = nullptr;
		res = find_ins_pos(data, cur, exit_flag, res);
		if (res == nullptr) { return; }
		RBNode<T>* X = new RBNode<T>(data, Red, res);
		if (data < res->data()) { res->_left = X; }
		else if (data > res->data()) { res->_right = X; }
		balance(X);
	}

};