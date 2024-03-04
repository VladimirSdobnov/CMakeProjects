//#include "../Table/Table.h"
//#include "gtest.h"
//
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