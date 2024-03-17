#include "../Table/Table.h"
#include "gtest.h"
#include <time.h>

//size_t func(const std::string& str) {
//	size_t res = 0;
//	for (auto elem : str) { res += elem; }
//	return res;
//}
//
//TEST(HashTableNode, can_create) {
//	HashTableNode<int, int> table(nullptr);
//	//EXPECT_NO_THROW(UnorderedTableVec<int, int> table);//???????????????????????????????????????????
//}
//
//TEST(HashTableNode, can_insert) {
//	HashTableNode<std::string, int> table(func);
//	std::string tmp = "pol";
//	EXPECT_NO_THROW(table.insert(tmp, 5));
//	EXPECT_EQ(*table.search(tmp), 5);
//	EXPECT_ANY_THROW(table.insert(tmp, 5));
//}
//
//TEST(HashTableNode, can_erase) {
//	HashTableNode<std::string, int> table(func);
//	std::string tmp = "pol";
//	table.insert(tmp, 5);
//	tmp = "pol2";
//	table.insert(tmp, 5);
//	tmp = "pol3";
//	table.insert(tmp, 5);
//	EXPECT_NO_THROW(table.erase(tmp));
//	EXPECT_EQ(table.search(tmp), nullptr);
//}
//
//TEST(HashTableStep, can_create) {
//	HashTableNode<int, int> table(nullptr);
//	//EXPECT_NO_THROW(UnorderedTableVec<int, int> table);//???????????????????????????????????????????
//}
//
//TEST(HashTableStep, can_insert) {
//	HashTableStep<std::string, int> table(func);
//	std::string tmp = "pol";
//	EXPECT_NO_THROW(table.insert(tmp, 5));
//	EXPECT_EQ(*table.search(tmp), 5);
//	EXPECT_ANY_THROW(table.insert(tmp, 5));
//}
//
//TEST(HashTableStep, can_erase) {
//	HashTableStep<std::string, int> table(func);
//	std::string tmp = "pol";
//	table.insert(tmp, 5);
//	tmp = "pol2";
//	table.insert(tmp, 5);
//	tmp = "pol3";
//	table.insert(tmp, 5);
//	EXPECT_NO_THROW(table.erase(tmp));
//	EXPECT_EQ(table.search(tmp), nullptr);
//}


//TEST(TableVec, can_create) {
//	UnorderedTableVec<int, int> table;
//	//EXPECT_NO_THROW(UnorderedTableVec<int, int> table);//???????????????????????????????????????????
//}
//
//TEST(TableVec, can_insert) {
//	UnorderedTableVec<int, int> table;
//	EXPECT_NO_THROW(table.insert(5, 5));
//	EXPECT_EQ(*table.search(5), 5);
//}
//
//TEST(TableVec, can_erase) {
//	UnorderedTableVec<int, int> table;
//	table.insert(5, 5);
//	table.insert(6, 6);
//	EXPECT_NO_THROW(table.erase(6));
//	EXPECT_EQ(table.size(), 1);
//}
//
//TEST(TableList, can_create) {
//	UnorderedTableList<int, int> table;
//	//EXPECT_NO_THROW(UnorderedTableVec<int, int> table);//???????????????????????????????????????????
//}
//
//TEST(TableList, can_insert) {
//	UnorderedTableList<int, int> table;
//	EXPECT_NO_THROW(table.insert(5, 5));
//	EXPECT_EQ(*table.search(5), 5);
//}
//
//TEST(TableList, can_erase) {
//	UnorderedTableList<int, int> table;
//	table.insert(5, 5);
//	table.insert(6, 6);
//	EXPECT_NO_THROW(table.erase(6));
//	EXPECT_EQ(table.size(), 1);
//}

//TEST(Table_Effect, insert_time) {
//	UnorderedTableList<int, int> list;
//	UnorderedTableVec<int, int> vec;
//	clock_t tStartlist = clock();
//	for (int i = 0; i < 30000; i++) {
//		list.insert(i, i);
//	}
//	clock_t tFinishlist = clock() - tStartlist;
//	clock_t tStartvec = clock();
//	for (int i = 0; i < 30000; i++) {
//		vec.insert(i, i);
//	}
//	clock_t tFinishvec = clock() - tStartvec;
//	std::cout << "List: " << tFinishlist << std::endl;
//	std::cout << "Vector: " << tFinishvec << std::endl;
//}

//TEST(Table_Effect, search_time) {
//	UnorderedTableList<int, int> list;
//	UnorderedTableVec<int, int> vec;
//	for (int i = 0; i < 30000; i++) {
//		list.insert(i, i);
//	}
//	for (int i = 0; i < 30000; i++) {
//		vec.insert(i, i);
//	}
//	clock_t tStartlist = clock();
//	clock_t tFinishlist = clock() - tStartlist;
//	clock_t tStartvec = clock();
//	clock_t tFinishvec = clock() - tStartvec;
//	std::cout << "List: " << tFinishlist << std::endl;
//	std::cout << "Vector: " << tFinishvec << std::endl;
//	clock_t tStartlist = clock();
//	clock_t tFinishlist = clock() - tStartlist;
//}