#pragma once
#include "../StackOnList/StackOnList.h"
#include "../QueueOnList/QueueOnList.h"
#include"../TVectore/TVector.h"
#include <string>
#include <map>
#include <math.h>


bool isLetter(char elem) {
	return elem <= 'Z' && elem >= 'A' ||
		elem <= 'z' && elem >= 'a';
}

bool isNumber(char elem) {
	return elem <= '9' &&
		elem >= '0';
}

bool isOpenBracket(char elem) {
	return elem == '{' || elem == '(' || elem == '[';
}

bool isCloseBracket(char elem) {
	return elem == '}' || elem == ')' || elem == ']';
}

bool CorrectBrackets(std::string input) {
	StackOnList<char> st;
	for (auto elem : input) {
		if (!isOpenBracket(elem) && !isCloseBracket(elem)) { continue; }
		if (isOpenBracket(elem)) {
			st.push(elem);
		}
		else if (!st.empty() && ((elem == ')' && st.top() == '(') || (elem == '}' && st.top() == '{')
			|| (elem == ']' && st.top() == '['))) {
			st.pop();
		}
		else {
			return false;
		}
	}
	return st.empty();
}

void delspace(std::string& st) {
	while (st.find(' ') != std::string::npos) {
		st.erase(st.find(' '), 1);
	}
}

void toUnarMinus(std::string& st){
	if (st[0] == '-') { st[0] = '~'; }
	while (st.find("(-") != std::string::npos) {
		st[st.find("(-") + 1] = '~';
	}
}

float GetNumberFloat(std::string& st, int& pos) {
	std::string tmp;
	while (pos < st.length() &&
		(isNumber(st[pos]) ||
		(st[pos] == '.' &&
		tmp.find('.') == std::string::npos))) {
		tmp += st[pos];
		pos++;
	}
	if (pos + 1 < st.length() && st[pos + 1] == '.') { throw std::logic_error("wrong number"); }
	pos--;
	return std::stof(tmp);
}

std::string GetNumberString(std::string& st, int& pos) {
	std::string tmp;
	while (pos < st.length() &&
		(isNumber(st[pos]) ||
		(st[pos] == '.' &&
		tmp.find('.') == std::string::npos))) {
		tmp += st[pos];
		pos++;
	}
	if (pos < st.length() && st[pos] == '.') { throw std::logic_error("wrong number"); }
	pos--;
	return tmp;
}

void ReplaceConstant(std::string& input) {
	while (input.find('e') != std::string::npos) {
		input.replace(input.find('e'), 1, "2.718");
	}
	while (input.find("pi") != std::string::npos) {
		input.replace(input.find("pi"), 2, "3.142");
	}
}
 
template<class T1, class T2>
class TPair {
	T1 _key;
	T2 _val;
public:
	TPair(T1 key, T2 val):_key(key), _val(val) {}
	T2 val() { return val; }
	T1 key() { return key; }
	bool operator==(TPair const& other) const { return _key == other._key; }
};

class Lexem {
	std::string _type;
	float _value;
	std::string _name;
public:
	Lexem() :_type(""), _value(0), _name("") {};
	Lexem(std::string& input, int& pos) {
		if (isNumber(input[pos])) {
			_type = "Number";
			int tmppos = pos;
			_value = GetNumberFloat(input, tmppos);
			_name = GetNumberString(input, pos);
			return;
		}
		else if (isOpenBracket(input[pos])) {
			_type = "OpenBracket";
			_value = 0;
			_name = input[pos];
			return;
		}
		else if (isCloseBracket(input[pos])) {
			_type = "CloseBracket";
			_value = 0;
			_name = input[pos];
			return;
		}
		else if (input[pos] == '+' || input[pos] == '-') {
			_type = "Operator";
			_name = input[pos];
			_value = 1;
			return;
		}
		else if (input[pos] == '*' || input[pos] == '/') {
			_type = "Operator";
			_name = input[pos];
			_value = 2;
			return;
		}
		else if (input[pos] == '^') {
			_type = "Operator";
			_name = input[pos];
			_value = 3;
			return;
		}
		else if (input[pos] == '~') {
			_type = "Operator";
			_name = input[pos];
			_value = 4;
			return;
		}
		else if (input[pos] == '!') {
			_type = "Factorial";
			_name = input[pos];
			_value = 4;
			if (input.substr(pos, 2) == "!!") {
				_name = "!!";
			}
			return;
		}
		std::string tmpstr = input.substr(pos, 2);
		if (tmpstr == "tg" || tmpstr == "ln" || tmpstr == "sh" || tmpstr == "ch" || tmpstr == "th") {
			_type = "Func";
			_name = tmpstr;
			_value = 4;
			pos++;
			return;
		}
		else {
			tmpstr = input.substr(pos, 3);
		}
		if (tmpstr == "cos" || tmpstr == "sin" || tmpstr == "sqr" || tmpstr == "ctg" || tmpstr == "cth") {
			_type = "Func";
			_name = tmpstr;
			_value = 4;
			pos += 2;
			return;
		}
		else {
			tmpstr = input.substr(pos, 4);
		}
		if (tmpstr == "sqrt") {
			_type = "Func";
			_name = tmpstr;
			_value = 4;
			pos += 3;
			return;
		}
		else {
			tmpstr = input.substr(pos, 5);
		}
		if (tmpstr == "arctg" || tmpstr == "arcth" || tmpstr == "arcsh" || tmpstr == "arcsh") {
			_type = "Func";
			_name = tmpstr;
			_value = 4;
			pos += 4;
			return;
		}
		else {
			tmpstr = input.substr(pos, 6);
		}
		if (tmpstr == "arccos" || tmpstr == "arcsin" || tmpstr == "arcctg" || tmpstr == "arccth") {
			_type = "Func";
			_name = tmpstr;
			_value = 4;
			pos += 5;
			return;
		}
		else if (isLetter(input[pos])) {
			_type = "Varieble";
			_name = input[pos];
			_value = 0;
			return;
		}
		throw std::logic_error("Not Lexem");
	}
	Lexem(float x) {
		_type = "Number";
		_name = x;
		_value = x;
	}
	Lexem& operator=(const Lexem& l) {
		_type = l._type;
		_value = l._value;
		_name = l._name;
		return *this;
	}
	std::string type() { return _type; }
	std::string name() { return _name; }
	void val(float x) { _value = x; }
	float val() { return _value; }
};

TVector<Lexem> GetLexems(std::string& input) {
	delspace(input);
	toUnarMinus(input);
	ReplaceConstant(input);
	if (!CorrectBrackets(input)) { throw std::logic_error("wrong brackets"); }
	TVector<Lexem> lexems;
	bool OpenBrFlag = true;
	bool CloseBrFlag = false;
	bool OperatorFlag = false;
	bool DifFuncFlag = false;
	bool OperandFlag = false;
	bool FactFlag = false;
	int i = 0;
	do {
		Lexem lex(input, i);
		if (lex.type() == "OpenBracket") {
			if (CloseBrFlag || OperandFlag || FactFlag) {
				int pos = 0;
				Lexem tmp(std::string("*"), pos);
				lexems.append(tmp);
			}
			OpenBrFlag = true;
			CloseBrFlag = false;
			OperatorFlag = false;
			DifFuncFlag = false;
			OperandFlag = false;
			FactFlag = false;
		}
		else if (lex.type() == "CloseBracket" && (FactFlag || OperandFlag || CloseBrFlag)) {
			OpenBrFlag = false;
			CloseBrFlag = true;
			OperatorFlag = false;
			DifFuncFlag = false;
			OperandFlag = false;
			FactFlag = false;
		}
		else if (lex.type() == "Operator" && (FactFlag || OperandFlag || CloseBrFlag || (lex.name()=="~" && OpenBrFlag))) {
			OpenBrFlag = false;
			CloseBrFlag = false;
			OperatorFlag = true;
			DifFuncFlag = false;
			OperandFlag = false;
			FactFlag = false;
		}
		else if (lex.type() == "Factorial" && (OperandFlag || CloseBrFlag)) {
			OpenBrFlag = false;
			CloseBrFlag = false;
			OperatorFlag = false;
			DifFuncFlag = false;
			OperandFlag = false;
			FactFlag = true;
		}
		else if (lex.type() == "Func") {
			if (CloseBrFlag || OperandFlag || FactFlag) {
				int pos = 0;
				Lexem tmp(std::string("*"), pos);
				lexems.append(tmp);
			}
			OpenBrFlag = false;
			CloseBrFlag = false;
			OperatorFlag = false;
			DifFuncFlag = true;
			OperandFlag = false;
			FactFlag = false;
		}
		else if (lex.type() == "Varieble" || lex.type() == "Number") {
			if (CloseBrFlag || FactFlag || OperandFlag) {
				int pos = 0;
				Lexem tmp(std::string("*"), pos);
				lexems.append(tmp);
			}
			OpenBrFlag = false;
			CloseBrFlag = false;
			OperatorFlag = false;
			DifFuncFlag = false;
			OperandFlag = true;
			FactFlag = false;
		}
		else { throw std::logic_error("Invalid syntax pos: " + i); }
		lexems.append(lex);
		i++;
	} while (i != input.length());
	return lexems;
}

TVector<Lexem> toRPN(std::string& input) {
	TVector<Lexem> expression(GetLexems(input));
	TVector<Lexem> res;
	StackOnList<Lexem> operators;
	int i = 0;
	while (i < expression.size()) {
		Lexem lex(expression[i]);
		if (lex.type() == "Number" || lex.type() == "Varieble") { res.append(lex); }
		else if (lex.type() == "OpenBracket") { operators.push(lex); }
		else if (lex.type() == "CloseBracket") {
			while (!(operators.top().type() == "OpenBracket")) {
				res.append(operators.pop());
			}
			operators.pop();
		}
		else if (lex.type() == "Func" || lex.type() == "Factorial" || lex.type() == "Operator") {
			while (!operators.empty() && operators.top().val() >= lex.val())
			{
				res.append(operators.pop());
			}
			operators.push(lex);
		}
		i++;
	}
	while (!operators.empty()) {
		res.append(operators.pop());
	}
	return res;
}

//Переделать!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void ReplaceVar(std::string& input, std::string var, std::string val) {
	while (input.find(var) != std::string::npos) {
		input.replace(input.find(var), 1, val);
	}
}

void funcdef(StackOnList<float>& stack, std::string operation) {
	if (operation == "+") {
		float x = stack.pop();
		float y = stack.pop();
		stack.push(x + y);
	}
	else if (operation == "-") {
		float x = stack.pop();
		float y = stack.pop();
		stack.push(y - x);
	}
	else if (operation == "*") {
		float x = stack.pop();
		float y = stack.pop();
		stack.push(x * y);
	}
	else if (operation == "/") {
		float x = stack.pop();
		float y = stack.pop();
		stack.push(y / x);
	}
	else if (operation == "^") {
		float x = stack.pop();
		float y = stack.pop();
		stack.push(powf(y, x));
	}
	else if (operation == "~") {
		float x = stack.pop();
		stack.push(-x);
	}
	/*else if (operation == "!") {
		float x = stack.pop();
		stack.push(x);
	else if (operation == "!!") {
		float x = stack.pop();
		stack.push(x);
	}*/


}

void GetSetVar(TVector<Lexem> input) {
	for (Lexem lex : input) {
		if (lex.type() == "Varieble") {
			std::cout << lex.name() << " ";
			float x;
			std::cin >> x;
			lex.val(x);
		}
	}
}

float Calculate(std::string _input) {
	TVector<Lexem> expressions(toRPN(_input));
	StackOnList<float> numbers;
	//TVector<TPair<std::string, float>> vars;
	int i = 0;
	while (i < expressions.size()) {
		Lexem lex(expressions[i]);
		if (lex.type() == "Number" || lex.type() == "Varieble") {
			numbers.push(lex.val());
		}
		else {
			funcdef(numbers, lex.name());
		}
	}
	return numbers.top();
}

float logarifm(StackOnList<float>& stack) {
	if (stack.top() <= 0) { throw std::logic_error("Can't claculate logaritm non-positive number"); }
	float x = (stack.top() - 1) / (stack.top() + 1);
	stack.top();
	return (2 * (x + (x * x * x / 3) + (x * x * x * x * x / 5) + (x * x * x * x * x * x * x / 7) +
		(x * x * x * x * x * x * x * x * x / 9) + (x * x * x * x * x * x * x * x * x * x * x / 11) +
		(x * x * x * x * x * x * x * x * x * x * x * x * x / 13) + (x * x * x * x * x * x * x * x * x * x * x * x * x * x * x / 15)));
}

float degree(StackOnList<float>& stack) {
	float m = stack.top();
	stack.pop();
	float x = stack.top() - 1;
	stack.top();
	return (1 + (m * x) + (m * (m - 1) * x * x / 2) + (m * (m - 1) * (m - 2) * x * x * x / 6) +
		(m * (m - 1) * (m - 2) * (m - 3) * x * x * x * x / 24));
}

float factorial(StackOnList<float>& stack) {
	float x = stack.top();
	stack.top();
	float res = 1;
	for (int i = x; i > 0; i--) {
		res *= i;
	}
	return res;
}

float DoubleFactorial(StackOnList<float>& stack) {
	float x = stack.top();
	stack.top();
	float res = 1;
	for (int i = x; i > 0; i-=2) {
		res *= i;
	}
	return res;
}

float sinus(StackOnList<float>& stack) {
	float x = stack.top();
	stack.top();
	return (x - (x * x * x / 6) + (x * x * x * x * x / 120) - (x * x * x * x * x * x * x / 5040));
}

float cosinus(StackOnList<float>& stack) {
	float x = stack.top();
	stack.top();
	return (1 - (x * x / 2) + (x * x * x * x / 24) - (x * x * x * x * x * x / 720));
}

float tangens(StackOnList<float>& stack) {
	float x = stack.top();
	stack.top();
	return (1 - (x * x / 2) + (x * x * x * x / 24) - (x * x * x * x * x * x / 720));
}

float cotangens(StackOnList<float>& stack) {
	return 1 / tangens(stack);
}

