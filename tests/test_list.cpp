#include <gtest.h>
#include "list.h"

TEST(test_TNode, can_create) {
	// Arrange
	TNode<int>* p = new TNode<int>(0);

	// Act & Assert
	ASSERT_NO_THROW(TNode<int>(13, p));
}

TEST(test_TNode, correct_create) {
	// Arrange
	TNode<int>* p = new TNode<int>(0);
	TNode<int> node(13, p);
	// Act & Assert
	EXPECT_EQ(node.data(), 13);
	EXPECT_EQ(node.next(), p);
}

TEST(test_TNode, correct_eq) {
	// Arrange
	TNode<int>* p = new TNode<int>(0);
	TNode<int> node1(13, p);
	TNode<int> node2(13, p);
	// Act & Assert
	EXPECT_EQ(node1, node2);
}

TEST(test_TNode, correct_copy) {
	// Arrange
	TNode<int>* p = new TNode<int>(0);
	TNode<int> node1(13, p);
	TNode<int> node2(node1);
	// Act & Assert
	EXPECT_EQ(node1, node2);
	EXPECT_NE(&node1, &node2);
}

TEST(test_TNode, correct_assign) {
	// Arrange
	TNode<int>* p = new TNode<int>(0);
	TNode<int> node1(13, p);
	TNode<int> node2 = node1;
	// Act & Assert
	EXPECT_EQ(node1, node2);
	EXPECT_NE(&node1, &node2);
}

TEST(test_TList, can_create_default) {
	// Arrange
	ASSERT_NO_THROW(TList<int> list());
}

TEST(test_TList, correct_create_default) {
	// Arrange
	TList<int> list;
	TNode<int>* p = nullptr;
	EXPECT_EQ(list.front_node(), p);
	EXPECT_EQ(list.back_node(), p);

}

TEST(test_TList, can_create_bymass) {
	// Arrange
	int* m = new int[20];
	for (int i = 0; i < 20; i++) {
		m[i] = i;
	}
	ASSERT_NO_THROW(TList<int> list(m, 20));
}

TEST(test_TList, correct_create_bymass) {
	// Arrange
	int* m = new int[20];
	std::string s1;
	for (int i = 0; i < 20; i++) {
		m[i] = i;
		s1 = s1 + std::to_string(i);
	}
	TList<int> list(m, 20);
	int* m2 = new int[20];
	std::string res;
	TNode<int>* p = list.front_node();
	for (int i = 0; i < list.size(); i++) {
		m2[i] = p->data();
		res = res + std::to_string(i);
		p = p->next();
	}
	EXPECT_EQ(s1, res);
}

TEST(test_TList, can_insert) {
	// Arrange
	int* m = new int[20];
	for (int i = 0; i < 20; i++) {
		m[i] = i;
	}
	TList<int> list(m, 20);
	TNode<int>* p = list.front_node();
	for (int i = 0; i < 5; i++) {
		p = p->next();
	}
	list.insert(p, 25);
	p = list.front_node();
	std::string res;
	std::string s1 = "01234525678910111213141516171819";
	for (int i = 0; i < list.size(); i++) {
		res = res + std::to_string(p->data());
		p = p->next();
	}
	EXPECT_EQ(res, s1);
}

TEST(test_TList, cant_insert_in_empty) {
	// Arrange
	TList<int> list;
	TNode<int>* p = list.front_node();
	EXPECT_ANY_THROW(list.insert(p, 25));
}

TEST(test_TList, can_erase) {
	// Arrange
	int* m = new int[20];
	for (int i = 0; i < 20; i++) {
		m[i] = i;
	}
	TList<int> list(m, 20);
	TNode<int>* p = list.front_node();
	for (int i = 0; i < 5; i++) {
		p = p->next();
	}
	list.erase(p);
	p = list.front_node();
	std::string res;
	std::string s1 = "01234678910111213141516171819";
	for (int i = 0; i < list.size(); i++) {
		res = res + std::to_string(p->data());
		p = p->next();
	}
	EXPECT_EQ(list.size(), 19);
	EXPECT_EQ(res, s1);
}

TEST(test_TList, cant_erese_in_empty) {
	// Arrange
	TList<int> list;
	TNode<int>* p = list.front_node();
	EXPECT_ANY_THROW(list.erase(p));
}

TEST(test_TList, can_erese_one_power) {
	// Arrange
	TList<int> list;
	list.push_front(25);
	list.erase(list.front_node());
	EXPECT_EQ(list.front_node(), nullptr);
	EXPECT_EQ(list.back_node(), nullptr);
	EXPECT_EQ(list.size(), 0);
}

TEST(test_TList, can_push_front) {
	// Arrange
	TList<int> list;
	ASSERT_NO_THROW(list.push_front(25));
	ASSERT_EQ(list.front(), 25);
}

TEST(test_TList, can_push_back) {
	// Arrange
	TList<int> list;
	list.push_front(25);
	list.push_front(26);
	list.push_front(27);
	list.push_front(28);
	ASSERT_NO_THROW(list.push_back(30));
	ASSERT_EQ(list.back(), 30);
}

TEST(test_TList, cant_pop_front_empty) {
	// Arrange
	TList<int> list;
	ASSERT_ANY_THROW(list.pop_front());
}

TEST(test_TList, cant_pop_back_empty) {
	// Arrange
	TList<int> list;
	ASSERT_ANY_THROW(list.pop_back());
}

TEST(test_TList, can_pop_back) {
	// Arrange
	TList<int> list;
	list.push_front(25);
	list.push_front(26);
	list.push_front(27);
	list.push_front(28);
	ASSERT_NO_THROW(list.pop_back());
	ASSERT_EQ(list.back(), 26);
	ASSERT_EQ(list.size(), 3);
}

TEST(test_TList, can_pop_front) {
	// Arrange
	TList<int> list;
	list.push_front(25);
	list.push_front(26);
	list.push_front(27);
	list.push_front(28);
	ASSERT_NO_THROW(list.pop_front());
	ASSERT_EQ(list.front(), 27);
	ASSERT_EQ(list.size(), 3);
}