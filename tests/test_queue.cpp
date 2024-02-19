#include "gtest.h"
#include "../Queue/Queue.h"
#include "../QueueOnList/QueueOnList.h"

TEST(test_TQueue, can_create) {
	ASSERT_NO_THROW(TQueue<int> t(7));
}

TEST(test_TQueue, cant_create_negative_size) {
	ASSERT_ANY_THROW(TQueue<int> t(-7));
}

TEST(test_TQueue, can_push_elem) {
	TQueue<int> st(1);
	ASSERT_NO_THROW(st.push(8));
}

TEST(test_TQueue, correct_isEmpty) {
	TQueue<int> st1(2);
	TQueue<int> st2(2);
	st2.push(8);
	TQueue<int> st3(2);
	st3.push(7);
	st3.pop();
	EXPECT_EQ(st1.empty(), true);
	EXPECT_EQ(st2.empty(), false);
	EXPECT_EQ(st3.empty(), true);
}

TEST(test_TQueue, can_push_elem_notempty) {
	TQueue<int> st(8);
	ASSERT_NO_THROW(st.push(8));
}

TEST(test_TQueue, can_return_front) {
	TQueue<int> st(2);
	st.push(8);
	st.push(9);
	EXPECT_EQ(st.front(), 8);
}

TEST(test_TQueue, cant_return_front_empty) {
	TQueue<int> st(3);
	ASSERT_ANY_THROW(st.front());
}

TEST(test_TQueue, can_return_back) {
	TQueue<int> st(2);
	st.push(8);
	st.push(9);
	EXPECT_EQ(st.back(), 9);
}

TEST(test_TQueue, cant_return_back_empty) {
	TQueue<int> st(3);
	ASSERT_ANY_THROW(st.front());
}

TEST(test_TQueue, can_pop) {
	TQueue<int> st(3);
	st.push(8);
	ASSERT_NO_THROW(st.pop());
}

TEST(test_TQueue, cant_pop_empty) {
	TQueue<int> st(3);
	ASSERT_ANY_THROW(st.pop());
}

TEST(test_TQueue, correct_pop) {
	TQueue<int> st(3);
	st.push(8);
	st.push(7);
	st.push(6);
	st.pop();
	EXPECT_EQ(st.front(), 7);
	EXPECT_EQ(st.back(), 6);
}

TEST(test_TQueueOnList, can_create) {
	ASSERT_NO_THROW(TQueueOnList<int> t);
}

TEST(test_TQueueOnList, can_push_elem) {
	TQueueOnList<int> st;
	ASSERT_NO_THROW(st.push(8));
}

TEST(test_TQueueOnList, correct_isEmpty) {
	TQueueOnList<int> st1;
	TQueueOnList<int> st2;
	st2.push(8);
	TQueueOnList<int> st3;
	st3.push(7);
	st3.pop();
	EXPECT_EQ(st1.empty(), true);
	EXPECT_EQ(st2.empty(), false);
	EXPECT_EQ(st3.empty(), true);
}

TEST(test_TQueueOnList, can_return_top) {
	TQueueOnList<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(8);
	EXPECT_EQ(st.back(), 8);
}

TEST(test_TQueueOnList, cant_return_top_empty) {
	TQueueOnList<int> st;
	ASSERT_ANY_THROW(st.front());
}

TEST(test_TQueueOnList, can_pop) {
	TQueueOnList<int> st;
	st.push(8);
	ASSERT_NO_THROW(st.pop());
}

TEST(test_TQueueOnList, cant_pop_empty) {
	TQueueOnList<int> st;
	ASSERT_ANY_THROW(st.pop());
}

TEST(test_TQueueOnList, correct_pop) {
	TQueueOnList<int> st;
	st.push(8);
	st.push(7);
	st.pop();
	EXPECT_EQ(st.back(), 7);
	EXPECT_EQ(st.size(), 1);
}
