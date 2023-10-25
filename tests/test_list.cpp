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
	EXPECT_EQ(list.front(), p);
	EXPECT_EQ(list.back(), p);

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
	TNode<int>* p = list.front();
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
	TNode<int>* p = list.front();
	for (int i = 0; i < 5; i++) {
		p = p->next();
	}
	list.insert(p, 25);
	p = list.front();
	std::string res;
	std::string s1 = "01234525678910111213141516171819";
	for (int i = 0; i < list.size(); i++) {
		res = res + std::to_string(p->data());
		p = p->next();
	}
	EXPECT_EQ(res, s1);
}
