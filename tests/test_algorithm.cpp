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
	EXPECT_EQ(pos, 9);
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

TEST(Algorithm, can_coorect_form) {
	std::string st1 = "6ar";
	std::string res;
	std::string st2 = "arcsinst";
	std::string st3 = "arcthqe";
	std::string st4 = "aarcsin";
	std::string st5 = "aarcsincostgcthxert";
	std::string st6 = "a(arcsin(costgc)thxert)";
	std::string st7 = "a+arcsincos(tgc+thx)ert";
	std::string st8 = "a.arcsin,cos(tgc+thx)ert";
	CorrectForm(st1);
	res = "6*a*r";
	EXPECT_EQ(res, st1);
	CorrectForm(st2);
	res = "arcsins*t";
	EXPECT_EQ(res, st2);
	CorrectForm(st3);
	res = "arcthq*2.718";
	EXPECT_EQ(res, st3);
	CorrectForm(st4);
	res = "a*arcsin";
	EXPECT_EQ(res, st4);
	res = "a*arcsincostgcthx*2.718*r*t";
	CorrectForm(st5);
	EXPECT_EQ(res, st5);
	res = "a*(arcsin(costgc)*thx*2.718*r*t)";
	CorrectForm(st6);
	EXPECT_EQ(res, st6);
	res = "a+arcsincos(tgc+thx)*2.718*r*t";
	CorrectForm(st7);
	EXPECT_EQ(res, st7);
	EXPECT_ANY_THROW(CorrectForm(st8));

}

TEST(Algorithm, can_coorect_form2) {
	std::string st1 = "-6ar";
	std::string res;
	std::string st2 = "arcsin{st}";
	std::string st3 = "5 + 6 ( -4 + 3)";
	std::string st4 = "a\rcsin";
	std::string st5 = "5+6(-4+3arcsinx)-34^yx";
	CorrectForm(st1);
	res = "~6*a*r";
	EXPECT_EQ(res, st1);
	CorrectForm(st2);
	res = "arcsin{s*t}";
	EXPECT_EQ(res, st2);
	delspace(st3);
	CorrectForm(st3);
	res = "5+6*(~4+3)";
	EXPECT_EQ(res, st3);
	EXPECT_ANY_THROW(CorrectForm(st4));
	res = "5+6*(~4+3*arcsinx)-34^y*x";
	CorrectForm(st5);
	EXPECT_EQ(res, st5);
	res = "arcsin";
}

TEST(Algorithm, can_get_string) {
	std::string st1 = "arcsin";
	std::string st2 = "cosxert";
	std::string st3 = "erty";
	std::string st4 = "qwe+";
	std::string st5 = "s4";
	std::string st6 = "sinarcsin";
	int pos = 0;
	std::string res("arcsin");
	EXPECT_EQ(res, GetOperator(st1, pos));
	EXPECT_EQ(pos, 5);
	pos = 0;
	res = "cos";
	EXPECT_EQ(res, GetOperator(st2, pos));
	EXPECT_EQ(pos, 2);
	pos = 0;
	res = "Not";
	EXPECT_EQ(res, GetOperator(st3, pos));
	EXPECT_EQ(0, pos);
	pos = 0;
	res = "Not";
	EXPECT_EQ(res, GetOperator(st4, pos));
	EXPECT_EQ(0, pos);
	pos = 0;
	res = "Not";
	EXPECT_EQ(res, GetOperator(st5, pos));
	pos = 0;
	res = "sin";
	EXPECT_EQ(res, GetOperator(st6, pos));
}

TEST(Algorithm, can_get_RPN) {
	std::string res;
	std::string st = "3 + 4";
	res = "3 4 + ";
	EXPECT_EQ(res, toRPN(st));
	st = "arcsin5";
	res = "5 arcsin ";
	EXPECT_EQ(res, toRPN(st));
	st = "(arcsin(6 * 7))^5 - 5 + xy";
	res = "6 7 * arcsin 5 ^ 5 - x y * + ";
	EXPECT_EQ(res, toRPN(st));
	std::cout << st;
}

TEST(Algorithm, can_replace) {
	std::string st1 = "pi*e*e*34";
	ReplaceConstant(st1);
	EXPECT_EQ("3.142*2.718*2.718*34", st1);
}

TEST(Algorithm, can_calculate) {
	std::string st1 = "3 * 2 + (34 - 2) / 2 ^ 3";
	float res = Calculate(st1);
	EXPECT_FLOAT_EQ(10, res);
	std::string st2;
	std::cin >> st2;
	float x;
	x = Calculate(st2);
	std::cout << "\n" << x;
}
