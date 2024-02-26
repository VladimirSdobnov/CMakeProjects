//#include "Stack.h"
//#include <gtest.h>
//#include "StackOnList.h"
//
//TEST(test_TStack, can_create) {
//	ASSERT_NO_THROW(TStack<int> t(7));
//}
//
//TEST(test_TStack, can_create_mass) {
//	int data[7];
//	ASSERT_NO_THROW(TStack<int> t(data, 7));
//}
//
//TEST(test_TStack, cant_create_negative_size) {
//	ASSERT_ANY_THROW(TStack<int> t(-7));
//}
//
//TEST(test_TStack, can_push_elem) {
//	TStack<int> st(1);
//	ASSERT_NO_THROW(st.push(8));
//}
//
//TEST(test_TStack, correct_isEmpty) {
//	TStack<int> st1(2);
//	TStack<int> st2(2);
//	st2.push(8);
//	TStack<int> st3(2);
//	st3.push(7);
//	st3.pop();
//	EXPECT_EQ(st1.isEmpty(), true);
//	EXPECT_EQ(st2.isEmpty(), false);
//	EXPECT_EQ(st3.isEmpty(), true);
//}
//
//TEST(test_TStack, can_push_elem_notempty) {
//	TStack<int> st(8);
//	ASSERT_NO_THROW(st.push(8));
//}
//
//TEST(test_TStack, can_return_top) {
//	TStack<int> st(1);
//	st.push(8);
//	EXPECT_EQ(st.top(), 8);
//}
//
//TEST(test_TStack, cant_return_top_empty) {
//	TStack<int> st(3);
//	ASSERT_ANY_THROW(st.top());
//}
//
//TEST(test_TStack, can_pop) {
//	TStack<int> st(3);
//	st.push(8);
//	ASSERT_NO_THROW(st.pop());
//}
//
//TEST(test_TStack, cant_pop_empty) {
//	TStack<int> st(3);
//	ASSERT_ANY_THROW(st.pop());
//}
//
//TEST(test_TStack, correct_pop) {
//	TStack<int> st(3);
//	st.push(8);
//	st.push(7);
//	st.pop();
//	EXPECT_EQ(st.top(), 8);
//}
//
//TEST(test_StackOnList, can_create) {
//	ASSERT_NO_THROW(StackOnList<int> t);
//}
//
//TEST(test_StackOnList, can_create_mass) {
//	int data[7];
//	ASSERT_NO_THROW(StackOnList<int> t(data, 7));
//}
//
//TEST(test_StackOnList, can_push_elem) {
//	StackOnList<int> st;
//	ASSERT_NO_THROW(st.push(8));
//}
//
//TEST(test_StackOnList, correct_isEmpty) {
//	StackOnList<int> st1;
//	StackOnList<int> st2;
//	st2.push(8);
//	StackOnList<int> st3;
//	st3.push(7);
//	st3.pop();
//	EXPECT_EQ(st1.empty(), true);
//	EXPECT_EQ(st2.empty(), false);
//	EXPECT_EQ(st3.empty(), true);
//}
//
//TEST(test_StackOnList, can_return_top) {
//	StackOnList<int> st;
//	st.push(1);
//	st.push(2);
//	st.push(3);
//	st.push(8);
//	EXPECT_EQ(st.top(), 8);
//}
//
//TEST(test_StackOnList, cant_return_top_empty) {
//	StackOnList<int> st;
//	ASSERT_ANY_THROW(st.top());
//}
//
//TEST(test_StackOnList, can_pop) {
//	StackOnList<int> st;
//	st.push(8);
//	ASSERT_NO_THROW(st.pop());
//}
//
//TEST(test_StackOnList, can_pop_empty) {
//	StackOnList<int> st;
//	ASSERT_NO_THROW(st.pop());
//}
//
//TEST(test_StackOnList, correct_pop) {
//	StackOnList<int> st;
//	st.push(8);
//	st.push(7);
//	st.pop();
//	EXPECT_EQ(st.top(), 8);
//	EXPECT_EQ(st.size(), 1);
//}