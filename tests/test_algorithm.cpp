#pragma once
#include "ParsAlgorithm.h"
#include <gtest.h>

TEST(Algorithm, can_brackets_true) {
	// Arrange
	std::string st = "{}";

		// Act & Assert
	EXPECT_EQ(CorrectBrackets(st), true);
}

TEST(Algorithm, can_brackets_false) {
	// Arrange
	std::string st = "{}}";

	// Act & Assert
	EXPECT_EQ(CorrectBrackets(st), false);
}

TEST(Algorithm, can_brackets_true_difficult) {
	// Arrange
	std::string st = "{{{{{{(((a)))}}}}}}[a][]{[]}()()";

	// Act & Assert
	EXPECT_EQ(CorrectBrackets(st), true);
}

TEST(Algorithm, can_brackets_false_difficult) {
	// Arrange
	std::string st = "{{{{{{{((()))}}}}}}[][]{[]}({)(})}";
	std::string st2 = "";

	// Act & Assert
	EXPECT_EQ(CorrectBrackets(st), false);
	EXPECT_EQ(true, CorrectBrackets(st2));
}

TEST(Algorithm, can_string_to_double) {
	std::string st1 = "0.0000056";
	std::string st2 = "23.03402";
	std::string st3 = "   345 56. 234 123";
	std::string st4 = "   345 56.907 234 123";
	std::string st5 = "   345 56.907.0908 234 123";
	int pos = 0;
	double x = 0.0000056;
	EXPECT_FLOAT_EQ(x, GetNumberFloat(st1, pos));
	EXPECT_EQ(pos, 8);
	pos = 0;
	x = 23.03402;
	EXPECT_FLOAT_EQ(x, GetNumberFloat(st2, pos));
	pos = 0;
	EXPECT_ANY_THROW(GetNumberFloat(st3, pos));
	pos = 7;
	x = 56.907;
	EXPECT_FLOAT_EQ(x, GetNumberFloat(st4, pos));
	pos = 7;
	x = 56.907;
	EXPECT_FLOAT_EQ(x, GetNumberFloat(st5, pos));
}

TEST(Algorithm, can_lexem) {
	std::string st1 = "0.056";
	std::string st2 = "x";
	std::string st3 = "+";
	std::string st4 = "arcsin";
	std::string st5 = "arsin";
	std::string st6 = " arcsin";
	std::string st7 = "(";
	std::string st8 = ")";
	int pos = 0;
	Lexem lex(st1, pos);
	EXPECT_EQ("Number", lex.type());
	EXPECT_EQ(4, pos);
	EXPECT_FLOAT_EQ(0.056, lex.val());
	EXPECT_EQ("0.056", lex.name());
	pos = 0;
	Lexem lex2(st2, pos);
	EXPECT_EQ("Varieble", lex2.type());
	EXPECT_EQ(0, pos);
	EXPECT_FLOAT_EQ(0, lex2.val());
	EXPECT_EQ("x", lex2.name());
	pos = 0;
	Lexem lex3(st3, pos);
	EXPECT_EQ("Operator", lex3.type());
	EXPECT_EQ(0, pos);
	EXPECT_FLOAT_EQ(1, lex3.val());
	EXPECT_EQ("+", lex3.name());
	pos = 0;
	Lexem lex4(st4, pos);
	EXPECT_EQ("Func", lex4.type());
	EXPECT_EQ(5, pos);
	EXPECT_FLOAT_EQ(4, lex4.val());
	EXPECT_EQ("arcsin", lex4.name());
	pos = 0;
	Lexem lex5(st5, pos);
	EXPECT_EQ("Varieble", lex5.type());
	EXPECT_EQ(0, pos);
	EXPECT_FLOAT_EQ(0, lex5.val());
	EXPECT_EQ("a", lex5.name());
	pos = 0;
	EXPECT_ANY_THROW(Lexem lex6(st6, pos));
	pos = 0;
	Lexem lex7(st7, pos);
	EXPECT_EQ("OpenBracket", lex7.type());
	EXPECT_EQ(0, pos);
	EXPECT_FLOAT_EQ(0, lex7.val());
	EXPECT_EQ("(", lex7.name());
	pos = 0;
	Lexem lex8(st8, pos);
	EXPECT_EQ("CloseBracket", lex8.type());
	EXPECT_EQ(0, pos);
	EXPECT_FLOAT_EQ(0, lex8.val());
	EXPECT_EQ(")", lex8.name());
}

TEST(Algorithm, can_get_lex) {
	std::string st1 = "0.056+x";
	TVector<Lexem> q(GetLexems(st1));
	EXPECT_EQ("Number", q[0].type());
	EXPECT_FLOAT_EQ(0.056, q[0].val());
	EXPECT_EQ("0.056", q[0].name());

	EXPECT_EQ("Operator", q[1].type());
	EXPECT_FLOAT_EQ(1, q[1].val());
	EXPECT_EQ("+", q[1].name());

	EXPECT_EQ("Varieble", q[2].type());
	EXPECT_FLOAT_EQ(0, q[2].val());
	EXPECT_EQ("x", q[2].name());

	std::string st2 = "arcth+";
	EXPECT_ANY_THROW(GetLexems(st2));
}

TEST(Algorithm, can_RPN) {
	std::string st1 = "12+3*4-2";
	TVector<Lexem> res(toRPN(st1));
	EXPECT_EQ(res[0].name(), "12");
	EXPECT_EQ(res[1].name(), "3");
	EXPECT_EQ(res[2].name(), "4");
	EXPECT_EQ(res[3].name(), "*");
	EXPECT_EQ(res[4].name(), "+");
	EXPECT_EQ(res[5].name(), "2");
	EXPECT_EQ(res[6].name(), "-");
	std::string st2 = "12+sin3*4-2";
	TVector<Lexem> res2(toRPN(st2));
	EXPECT_EQ(res2[0].name(), "12");
	EXPECT_EQ(res2[1].name(), "3");
	EXPECT_EQ(res2[2].name(), "sin");
	EXPECT_EQ(res2[3].name(), "4");
	EXPECT_EQ(res2[4].name(), "*");
	EXPECT_EQ(res2[5].name(), "+");
	EXPECT_EQ(res2[6].name(), "2");
	EXPECT_EQ(res2[7].name(), "-");
	std::string st3 = "4(x^3)(y^2)";
	TVector<Lexem> res3(toRPN(st3));
	EXPECT_EQ(res3[0].name(), "4");
	EXPECT_EQ(res3[1].name(), "x");
	EXPECT_EQ(res3[2].name(), "3");
	EXPECT_EQ(res3[3].name(), "^");
	EXPECT_EQ(res3[4].name(), "*");
	EXPECT_EQ(res3[5].name(), "y");
	EXPECT_EQ(res3[6].name(), "2");
	EXPECT_EQ(res3[7].name(), "^");
	EXPECT_EQ(res3[8].name(), "*");
	std::string st4 = "4(x^3)(y^2)(z^(-4))";
	TVector<Lexem> res4(toRPN(st4));
	EXPECT_EQ(res4[0].name(), "4");
	EXPECT_EQ(res4[1].name(), "x");
	EXPECT_EQ(res4[2].name(), "3");
	EXPECT_EQ(res4[3].name(), "^");
	EXPECT_EQ(res4[4].name(), "*");
	EXPECT_EQ(res4[5].name(), "y");
	EXPECT_EQ(res4[6].name(), "2");
	EXPECT_EQ(res4[7].name(), "^");
	EXPECT_EQ(res4[8].name(), "*");
	EXPECT_EQ(res4[9].name(), "z");
	EXPECT_EQ(res4[10].name(), "4");
	EXPECT_EQ(res4[11].name(), "~");
	EXPECT_EQ(res4[12].name(), "^");
	EXPECT_EQ(res4[13].name(), "*");
}
