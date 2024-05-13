#pragma once
#include <../BinarTree/BinarTree.h>
#include <../gtest/gtest.h>
#include <../RBBinarTree/RBBinarTree.h>
#include <../TVectore/TVector.h>

//TEST(Tree_test, can_create) {
//	TBinarTree<int> tree;
//	/*void main() {
//		TBinarTree<int> tree;
//		tree.insert(5);
//		tree.insert(4);
//		tree.insert(3);
//		tree.insert(2);
//		tree.insert(1);
//		std::cout << tree.find(1, tree.root)->data();
//	}*/
//}
//
//TEST(Tree_test, can_insert) {
//	TBinarTree<int> tree;
//	tree.insert(5);
//	tree.insert(4);
//	tree.insert(3);
//	tree.insert(2);
//	tree.insert(1);
//	tree.insert(0);
//	tree.insert(-1);
//	tree.insert(-2);
//	tree.insert(-3);
//	tree.insert(-4);
//	tree.insert(-5);
//	std::cout << tree.find(1)->data();
//	std::cout << tree.find(2)->data();
//	std::cout << tree.find(3)->data();
//	std::cout << tree.find(4)->data();
//	std::cout << tree.find(5)->data() << std::endl;
//	printtreeBFS<int>(tree);
//	std::cout << std::endl;
//	printtreeDFSUP<int>(tree.root);
//	std::cout << std::endl;
//	printtreeDFSDOWNUP<int>(tree.root);
//	std::cout << std::endl;
//	printtreeDFSDOWNDOWN<int>(tree.root);
//	std::cout << std::endl;
//	tree.erase(tree.find(-5));
//	tree.erase(tree.find(-4));
//	tree.erase(tree.find(5));
//	tree.erase(tree.find(4));
//	tree.erase(tree.find(3));
//	printtreeBFS<int>(tree);
//	std::cout << std::endl;
//	TBinarTree<int> tree2(tree);
//	printtreeBFS<int>(tree2);
//	std::cout << std::endl;
//}
//
//TEST(SearchTree_test, can_create) {
//	TSearchTree<int> tree;
//}
//
//TEST(SearchTree_test, can_insert) {
//	TSearchTree<int> tree;
//	tree.insert(0);
//	tree.insert(1);
//	tree.insert(-1);
//	tree.insert(5);
//	tree.insert(4);
//	tree.insert(3);
//	tree.insert(2);
//	tree.insert(-2);
//	tree.insert(-3);
//	tree.insert(-4);
//	tree.insert(-5);
//	std::cout << tree.find(1)->data();
//	std::cout << tree.find(2)->data();
//	std::cout << tree.find(3)->data();
//	std::cout << tree.find(4)->data();
//	std::cout << tree.find(5)->data() << std::endl;
//	printtreeBFS<int>(tree);
//	std::cout << std::endl;
//	tree.erase(-5);
//	tree.erase(-4);
//	tree.erase(5);
//	tree.erase(0);
//	tree.erase(4);
//	tree.erase(3);
//	printtreeBFS<int>(tree);
//	std::cout << std::endl;
//}

TEST(RBTree_test, can_insert) {
	RBTree<int> tree;
	for (int i = 6; i > -1; i--) {
		tree.Insert(i * 5);
	}

	RBTree<int> tree2;
	for (int i = 0; i < 7; i++) {
		tree2.Insert(i * 5);
	}
	srand(time(0));
	RBTree<int> tree3;
	TVector<int> elem(15);
	/*for (int i = 0; i < 15; i++) {
		int x = rand() % 100;
		std::cout << x << " ";
		elem.append(x);
		tree3.Insert(x);
	}
	std::cout << std::endl;
	tree3.Print()*/;
	/*tree3.Insert(38);
	tree3.Insert(25);
	tree3.Insert(7);
	tree3.Insert(74);
	tree3.Insert(79);
	tree3.Insert(45);
	tree3.Insert(71);
	tree3.Insert(30);
	tree3.Insert(13);
	tree3.Insert(16);
	tree3.Insert(89);
	tree3.Insert(86);
	tree3.Insert(11);
	tree3.Insert(47);
	tree3.Insert(2);
	std::cout << std::endl;
	tree3.Print();
	tree3.Erase(25);
	std::cout << std::endl;
	tree3.Print();
	tree3.Erase(7);
	std::cout << std::endl;
	tree3.Print();*/
	tree3.Insert(59);
	tree3.Insert(5);
	tree3.Insert(90);
	tree3.Insert(99);
	tree3.Insert(90);
	tree3.Insert(83);
	tree3.Insert(72);
	tree3.Insert(8);
	tree3.Insert(83);
	tree3.Insert(35);
	tree3.Insert(48);
	tree3.Insert(38);
	tree3.Insert(10);
	tree3.Insert(95);
	tree3.Insert(49);
	std::cout << std::endl;
	tree3.Print();
	tree3.Erase(5);
	std::cout << std::endl;
	tree3.Print();
	/*for (int i = 0; i < 15 / 2; i++) {
		std::cout << elem[i + 1] << std::endl;
		tree3.Erase(elem[i + 1]);
		std::cout << std::endl;
		tree3.Print();
	}*/
}
//https://habr.com/ru/companies/otus/articles/521034/

