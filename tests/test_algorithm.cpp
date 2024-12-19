#pragma once
#include "ParsAlgorithm.h"
#include "../Polinoms/Polinoms.h"
#include <BinarTree.h>
#include <RBBinarTree.h>
#include <Table.h>
#include <time.h>
#include <gtest.h>

//TEST(Algorithm, can_brackets_true) {
//	// Arrange
//	std::string st = "{}";
//
//		// Act & Assert
//	EXPECT_EQ(CorrectBrackets(st), true);
//}
//
//TEST(Algorithm, can_brackets_false) {
//	// Arrange
//	std::string st = "{}}";
//
//	// Act & Assert
//	EXPECT_EQ(CorrectBrackets(st), false);
//}
//
//TEST(Algorithm, can_brackets_true_difficult) {
//	// Arrange
//	std::string st = "{{{{{{(((a)))}}}}}}[a][]{[]}()()";
//
//	// Act & Assert
//	EXPECT_EQ(CorrectBrackets(st), true);
//}
//
//TEST(Algorithm, can_brackets_false_difficult) {
//	// Arrange
//	std::string st = "{{{{{{{((()))}}}}}}[][]{[]}({)(})}";
//	std::string st2 = "";
//
//	// Act & Assert
//	EXPECT_EQ(CorrectBrackets(st), false);
//	EXPECT_EQ(true, CorrectBrackets(st2));
//}
//
//TEST(Algorithm, can_string_to_double) {
//	std::string st1 = "0.0000056";
//	std::string st2 = "23.03402";
//	std::string st3 = "   345 56. 234 123";
//	std::string st4 = "   345 56.907 234 123";
//	std::string st5 = "   345 56.907.0908 234 123";
//	int pos = 0;
//	double x = 0.0000056;
//	EXPECT_FLOAT_EQ(x, GetNumberFloat(st1, pos));
//	EXPECT_EQ(pos, 8);
//	pos = 0;
//	x = 23.03402;
//	EXPECT_FLOAT_EQ(x, GetNumberFloat(st2, pos));
//	pos = 0;
//	EXPECT_ANY_THROW(GetNumberFloat(st3, pos));
//	pos = 7;
//	x = 56.907;
//	EXPECT_FLOAT_EQ(x, GetNumberFloat(st4, pos));
//	pos = 7;
//	x = 56.907;
//	EXPECT_FLOAT_EQ(x, GetNumberFloat(st5, pos));
//}
//
//TEST(Algorithm, can_lexem) {
//	std::string st1 = "0.056";
//	std::string st2 = "x";
//	std::string st3 = "+";
//	std::string st4 = "arcsin";
//	std::string st5 = "arsin";
//	std::string st6 = " arcsin";
//	std::string st7 = "(";
//	std::string st8 = ")";
//	int pos = 0;
//	Lexem lex(st1, pos);
//	EXPECT_EQ(Number, lex.type());
//	EXPECT_EQ(4, pos);
//	EXPECT_FLOAT_EQ(0.056, lex.val());
//	EXPECT_EQ("0.056", lex.name());
//	pos = 0;
//	Lexem lex2(st2, pos);
//	EXPECT_EQ(Varieble, lex2.type());
//	EXPECT_EQ(0, pos);
//	EXPECT_FLOAT_EQ(0, lex2.val());
//	EXPECT_EQ("x", lex2.name());
//	pos = 0;
//	Lexem lex3(st3, pos);
//	EXPECT_EQ(Operator, lex3.type());
//	EXPECT_EQ(0, pos);
//	EXPECT_FLOAT_EQ(1, lex3.val());
//	EXPECT_EQ("+", lex3.name());
//	pos = 0;
//	Lexem lex4(st4, pos);
//	EXPECT_EQ(Func, lex4.type());
//	EXPECT_EQ(5, pos);
//	EXPECT_FLOAT_EQ(4, lex4.val());
//	EXPECT_EQ("arcsin", lex4.name());
//	pos = 0;
//	Lexem lex5(st5, pos);
//	EXPECT_EQ(Varieble, lex5.type());
//	EXPECT_EQ(0, pos);
//	EXPECT_FLOAT_EQ(0, lex5.val());
//	EXPECT_EQ("a", lex5.name());
//	pos = 0;
//	EXPECT_ANY_THROW(Lexem lex6(st6, pos));
//	pos = 0;
//	Lexem lex7(st7, pos);
//	EXPECT_EQ(OpenBracket, lex7.type());
//	EXPECT_EQ(0, pos);
//	EXPECT_FLOAT_EQ(0, lex7.val());
//	EXPECT_EQ("(", lex7.name());
//	pos = 0;
//	Lexem lex8(st8, pos);
//	EXPECT_EQ(CloseBracket, lex8.type());
//	EXPECT_EQ(0, pos);
//	EXPECT_FLOAT_EQ(0, lex8.val());
//	EXPECT_EQ(")", lex8.name());
//}
//
//TEST(Algorithm, can_get_lex) {
//	std::string st1 = "0.056+x";
//	TVector<Lexem> q(GetLexems(st1));
//	EXPECT_EQ(Number, q[0].type());
//	EXPECT_FLOAT_EQ(0.056, q[0].val());
//	EXPECT_EQ("0.056", q[0].name());
//
//	EXPECT_EQ(Operator, q[1].type());
//	EXPECT_FLOAT_EQ(1, q[1].val());
//	EXPECT_EQ("+", q[1].name());
//
//	EXPECT_EQ(Varieble, q[2].type());
//	EXPECT_FLOAT_EQ(0, q[2].val());
//	EXPECT_EQ("x", q[2].name());
//
//	std::string st2 = "arcth+";
//	EXPECT_ANY_THROW(GetLexems(st2));
//}
//
//TEST(Algorithm, can_RPN) {
//	std::string st1 = "12+3*4-2";
//	TList<Lexem> res(toRPN(st1));
//	TNode<Lexem>* cur = res.front_node();
//	EXPECT_EQ(cur->data().name(), "12");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "3");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "4");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "*");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "+");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "2");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "-");
//	std::string st2 = "12+sin3*4-2";
//	TList<Lexem> res2(toRPN(st2));
//	cur = res2.front_node();
//	EXPECT_EQ(cur->data().name(), "12");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "3");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "sin");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "4");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "*");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "+");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "2");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "-");
//	std::string st3 = "4(x^3)(y^2)";
//	TList<Lexem> res3(toRPN(st3));
//	cur = res3.front_node();
//	EXPECT_EQ(cur->data().name(), "4");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "x");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "3");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "^");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "*");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "y");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "2");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "^");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "*");
//	std::string st4 = "4(x^3)(y^2)(z^(-4))";
//	TList<Lexem> res4(toRPN(st4));
//	cur = res4.front_node();
//	EXPECT_EQ(cur->data().name(), "4");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "x");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "3");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "^");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "*");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "y");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "2");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "^");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "*");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "z");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "4");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "~");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "^");
//	cur = cur->next();
//	EXPECT_EQ(cur->data().name(), "*");
//}
//
//TEST(test_Polinom, can_create) {
//	Polinom pol;
//	Polinom pol2(std::string("12x1^4x2^5x3^-2"));
//	Polinom pol3(std::string("-x2^3x2^4+ + 5 + x1^4x3^-2+x3^-2+x4^6 +5x2^7 + 8"));
//	Polinom res;
//	std::cout << pol3 << std::endl;
//}
//
//TEST(test_Polinom, can_summ) {
//	std::string tmp = "x1 x2 x3 x4 x5 x6 x7 x8";
//	TVector<Lexem> vars = GetVars(tmp);
//	Polinom pol2(std::string("12x1^4x2^5x3^-2 - 5x1^4x3^-2"), vars);
//	Polinom pol3(std::string("-x2^3x2^4 + 5 + x1^4x3^-2 + x3^-2 + x4^6 + 5x2^7 + 8"), vars);
//	Polinom res = pol2 + pol3;
//	std::cout << res << std::endl;
//}
//
//TEST(test_Polinom, can_mult) {
//	std::string tmp = "x1 x2 x3";
//	TVector<Lexem> vars = GetVars(tmp);
//	Polinom pol2(std::string("x1^2x2^3"), vars);
//	Polinom pol3(std::string("-x1^2 + x2^-3"), vars);
//	Polinom res = pol2 * pol3;
//	std::cout << res << std::endl;
//}

//TEST(test_Polinom, can_generate_rand) {
//	srand(time(0));
//	Polinom p1 = RandPolinom(3, 5);
//	Polinom p2 = RandPolinom(3, 5);
//	Polinom res = p1 * p2;
//	std::cout << p1 << "\n\n" << p2 << "\n\n" << res << std::endl;
//}

void shuffle(TVector<std::string>& v) {
	for (int i = 0; i < v.size() / 2; i++) {
		srand(i);
		int x = rand() % v.size();
		std::swap(v[i], v[x]);
	}
}
TVector<std::string> name(110000, 0);

TEST(test_Polinom, create_vec_name) {
	for (int i = 0; i < 110000; i++) {
		std::string x = std::string("pos") + std::to_string(i);
		name.append(x);
	}
	shuffle(name);
}
//
//TEST(test_Polinom, additional) {
//	for (int i = 100; i < 1000000; i *= 10) {
//		srand(i);
//		Polinom p1 = RandPolinom(3, i);
//		srand(i + 2);
//		Polinom p2 = RandPolinom(3, i);
//		clock_t StartAdd = clock();
//		Polinom res = p1 + p2;
//		clock_t FinishAdd = clock() - StartAdd;
//		std::cout << "Time for additional polinoms with " << i << " monoms " << FinishAdd << std::endl;
//	}
//}
//
//TEST(test_Polinom, mult) {
//	for (int i = 10; i < 300; i *= 2) {
//		srand(i);
//		Polinom p1 = RandPolinom(3, i);
//		srand(i + 2);
//		Polinom p2 = RandPolinom(3, i);
//		clock_t StartAdd = clock();
//		Polinom res = p1 * p2;
//		clock_t FinishAdd = clock() - StartAdd;
//		std::cout << "Time for mult polinoms with " << i << " monoms " << FinishAdd << std::endl;
//	}
//}
//
//TEST(test_Polinom, SearchBinarTree) {
//	srand(time(0));
//	int n = 100;
//	int i = 0;
//	TSearchTree<TPair<std::string, Polinom>> tree;
//	do {
//		for (i; i < n; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			TPair<std::string, Polinom> elem(name[i], p1);
//			tree.insert(elem);
//		}
//		
//		clock_t StartIns = clock();
//		for (int i = n; i < n  + n / 10; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			TPair<std::string, Polinom> elem(name[i], p1);
//			tree.insert(elem);
//
//		}
//		clock_t FinishIns = clock() - StartIns;
//
//		clock_t StartFind = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			TPair<std::string, Polinom> elem(name[i], p1);
//			tree.find(elem);
//			
//		}
//		clock_t FinishFind = clock() - StartFind;
//
//		clock_t StartErase = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			TPair<std::string, Polinom> elem(name[i], p1);
//			tree.erase(elem);
//
//		}
//		clock_t FinishErase = clock() - StartErase;
//		
//		
//		
//		
//
//		std::cout << "Average time for insert in search tree with " << n << " elems " << (float)FinishIns / (n / 10) << std::endl;
//		std::cout << "Average time for found polinoms in search tree with " << n << " elems " << (float)FinishFind / (n / 10) << std::endl;
//		std::cout << "Average time for erase polinom from search Tree with " << n << " elems " << (float)FinishErase / (n / 10) << std::endl;
//
//
//		n *= 10;
//
//	} while (n < 1000000);
//
//}
//
//TEST(test_Polinom, BinarTree) {
//
//	srand(time(0));
//	int n = 100;
//	int i = 0;
//	TBinarTree<TPair<std::string, Polinom>> tree;
//
//	do {
//		for (i; i < n; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			TPair<std::string, Polinom> elem(name[i], p1);
//			tree.insert(elem);
//		}
//
//		clock_t StartIns = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			TPair<std::string, Polinom> elem(name[i], p1);
//			tree.insert(elem);
//
//		}
//		clock_t FinishIns = clock() - StartIns;
//
//		clock_t StartFind = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			TPair<std::string, Polinom> elem(name[i], p1);
//			tree.find(elem);
//
//		}
//		clock_t FinishFind = clock() - StartFind;
//
//		clock_t StartErase = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			TPair<std::string, Polinom> elem(name[i], p1);
//			tree.erase(tree.find(elem));
//
//		}
//		clock_t FinishErase = clock() - StartErase;
//
//		std::cout << "Average time for insert in binar tree with " << n << " elems " << (float)FinishIns / (n / 10) << std::endl;
//		std::cout << "Average time for found polinoms in binar tree with " << n << " elems " << (float)FinishFind / (n / 10) << std::endl;
//		std::cout << "Average time for erase polinom from binar Tree with " << n << " elems " << (float)FinishErase / (n / 10) << std::endl;
//
//		n *= 10;
//
//	} while (n < 1000000);
//}
//
//TEST(test_Polinom, RBTree) {
//	srand(time(0));
//	int n = 100;
//	int i = 0;
//	RBTree<TPair<std::string, Polinom>> tree;
//
//	do {
//		for (i; i < n; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			TPair<std::string, Polinom> elem(name[i], p1);
//			tree.Insert(elem);
//		}
//
//		clock_t StartIns = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			TPair<std::string, Polinom> elem(name[i], p1);
//			tree.Insert(elem);
//
//		}
//		clock_t FinishIns = clock() - StartIns;
//
//		clock_t StartFind = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			TPair<std::string, Polinom> elem(name[i], p1);
//			tree.Find(elem);
//
//		}
//		clock_t FinishFind = clock() - StartFind;
//
//		clock_t StartErase = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			TPair<std::string, Polinom> elem(name[i], p1);
//			tree.Erase(elem);
//
//		}
//		clock_t FinishErase = clock() - StartErase;
//
//		std::cout << "Average time for insert in RB tree with " << n << " elems " << (float)FinishIns / (n / 10) << std::endl;
//		std::cout << "Average time for found polinoms in RB tree with " << n << " elems " << (float)FinishFind / (n / 10) << std::endl;
//		std::cout << "Average time for erase polinom from RB Tree with " << n << " elems " << (float)FinishErase / (n / 10) << std::endl;
//
//		n *= 10;
//
//	} while (n < 1000000);
//}

TEST(test_Polinom, UnorderedVec) {
	srand(time(0));
	int n = 100;
	int i = 0;
	UnorderedTableVec<std::string, Polinom> tree;

	do {
		for (i; i < n; i++) {
			Polinom p1 = RandPolinom(3, 5);
			tree.insert(name[i], p1);
		}

		clock_t StartIns = clock();
		for (int i = n; i < n + n / 10; i++) {
			Polinom p1 = RandPolinom(3, 5);
			tree.insert(name[i], p1);

		}
		clock_t FinishIns = clock() - StartIns;

		clock_t StartFind = clock();
		for (int i = n; i < n + n / 10; i++) {
			tree.search(name[i]);

		}
		clock_t FinishFind = clock() - StartFind;

		clock_t StartErase = clock();
		for (int i = n; i < n + n / 10; i++) {
			tree.erase(name[i]);
		}
		clock_t FinishErase = clock() - StartErase;

		std::cout << "Average time for insert in unnordered vec table with " << n << " elems " << (float)FinishIns / (n / 10) << std::endl;
		std::cout << "Average time for found polinoms in unnordered vec table with " << n << " elems " << (float)FinishFind / (n / 10) << std::endl;
		std::cout << "Average time for erase polinom from unnordered vec table with " << n << " elems " << (float)FinishErase / (n / 10) << std::endl;

		n *= 10;

	} while (n < 1000000);
}

//TEST(test_Polinom, UnorderedList) {
//	srand(time(0));
//	int n = 100;
//	int i = 0;
//	UnorderedTableList<std::string, Polinom> tree;
//
//	do {
//		for (i; i < n; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			tree.insert(name[i], p1);
//		}
//
//		clock_t StartIns = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			tree.insert(name[i], p1);
//
//		}
//		clock_t FinishIns = clock() - StartIns;
//
//		clock_t StartFind = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			tree.search(name[i]);
//
//		}
//		clock_t FinishFind = clock() - StartFind;
//
//		clock_t StartErase = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			tree.erase(name[i]);
//		}
//		clock_t FinishErase = clock() - StartErase;
//
//		std::cout << "Average time for insert in unnordered list table with " << n << " elems " << (float)FinishIns / (n / 10) << std::endl;
//		std::cout << "Average time for found polinoms in unnordered list table with " << n << " elems " << (float)FinishFind / (n / 10) << std::endl;
//		std::cout << "Average time for erase polinom from unnordered list table with " << n << " elems " << (float)FinishErase / (n / 10) << std::endl;
//
//		n *= 10;
//
//	} while (n < 1000000);
//}
//
//size_t func(const std::string& str) {
//	size_t res = 0;
//	for (auto elem : str) { res += elem; }
//	return res;
//}
//
//TEST(test_Polinom, HashTableStep) {
//	srand(time(0));
//	int n = 100;
//	int i = 0;
//	HashTableStep<std::string, Polinom> tree(func);
//
//	do {
//		for (i; i < n; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			tree.insert(name[i], p1);
//		}
//
//		clock_t StartIns = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			tree.insert(name[i], p1);
//
//		}
//		clock_t FinishIns = clock() - StartIns;
//
//		clock_t StartFind = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			tree.search(name[i]);
//
//		}
//		clock_t FinishFind = clock() - StartFind;
//
//		clock_t StartErase = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			tree.erase(name[i]);
//		}
//		clock_t FinishErase = clock() - StartErase;
//
//		std::cout << "Average time for insert in hash step table with " << n << " elems " << (float)FinishIns / (n / 10) << std::endl;
//		std::cout << "Average time for found polinoms in hash step table with " << n << " elems " << (float)FinishFind / (n / 10) << std::endl;
//		std::cout << "Average time for erase polinom from hash step table with " << n << " elems " << (float)FinishErase / (n / 10) << std::endl;
//
//		n *= 10;
//
//	} while (n < 1000000);
//}
//
//TEST(test_Polinom, HashTableNode) {
//	srand(time(0));
//	int n = 100;
//	int i = 0;
//	HashTableNode<std::string, Polinom> tree(func);
//
//	do {
//		for (i; i < n; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			tree.insert(name[i], p1);
//		}
//
//		clock_t StartIns = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			Polinom p1 = RandPolinom(3, 5);
//			tree.insert(name[i], p1);
//
//		}
//		clock_t FinishIns = clock() - StartIns;
//
//		clock_t StartFind = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			tree.search(name[i]);
//
//		}
//		clock_t FinishFind = clock() - StartFind;
//
//		clock_t StartErase = clock();
//		for (int i = n; i < n + n / 10; i++) {
//			tree.erase(name[i]);
//		}
//		clock_t FinishErase = clock() - StartErase;
//
//		std::cout << "Average time for insert in hash step table with " << n << " elems " << (float)FinishIns / (n / 10) << std::endl;
//		std::cout << "Average time for found polinoms in hash step table with " << n << " elems " << (float)FinishFind / (n / 10) << std::endl;
//		std::cout << "Average time for erase polinom from hash step table with " << n << " elems " << (float)FinishErase / (n / 10) << std::endl;
//
//		n *= 10;
//
//	} while (n < 1000000);
//}
