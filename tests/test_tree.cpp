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

//TEST(RBTree_test, can_insert) {
//	RBTree<int> tree;
//	for (int i = 6; i > -1; i--) {
//		tree.Insert(i * 5);
//	}
//
//	RBTree<int> tree2;
//	for (int i = 0; i < 7; i++) {
//		tree2.Insert(i * 5);
//	}
//	srand(time(0));
//	RBTree<int> tree3;
//	TVector<int> elem(15);
//	for (int i = 0; i < 15; i++) {
//		int x = rand() % 100;
//		std::cout << x << " ";
//		elem.append(x);
//		tree3.Insert(x);
//	}
//	std::cout << std::endl;
//	              
//	/*tree3.Print();
//	tree3.Insert(81);
//	tree3.Insert(5);
//	tree3.Insert(41);
//	tree3.Insert(12);
//	tree3.Insert(71);
//	tree3.Insert(3);
//	tree3.Insert(71);
//	tree3.Insert(66);
//	tree3.Insert(90);
//	tree3.Insert(13);
//	tree3.Insert(88);
//	tree3.Insert(15);
//	tree3.Insert(29);
//	tree3.Insert(46);
//	tree3.Insert(69);
//	std::cout << std::endl;
//	tree3.Print();
//	tree3.Erase(5);
//	std::cout << std::endl;
//	tree3.Print();
//	tree3.Erase(41);
//	tree3.Erase(12);
//	tree3.Print();
//	tree3.Erase(71);
//	tree3.Erase(3);
//	std::cout << std::endl;*/
//	tree3.Print();
//	for (int i = 0; i < 15 / 2; i++) {
//		std::cout << elem[i + 1] << std::endl;
//		tree3.Erase(elem[i + 1]);
//		std::cout << std::endl;
//		tree3.Print();
//	}
//}
//https://habr.com/ru/companies/otus/articles/521034/

