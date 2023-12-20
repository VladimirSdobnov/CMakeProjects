#include "../StackOnList/StackOnList.h"
#include <string>
#include <map>
#include <math.h>

std::map<std::string, int> Dict{
		{std::string("("), 0},
		{std::string("{"), 0},
		{std::string("["), 0},
		{std::string("+"), 1},
		{std::string("-"), 1},
		{std::string("*"), 2},
		{std::string("/"), 2},
		{std::string("^"), 3},
		{std::string("~"), 4},
		{std::string("!!"), 4},
		{std::string("!"), 4},
		{std::string("arcsh"), 4},
		{std::string("arcch"), 4},
		{std::string("arcth"), 4},
		{std::string("arccth"), 4},
		{std::string("arcsin"), 4},
		{std::string("arccos"), 4},
		{std::string("arctg"), 4},
		{std::string("arcctg"), 4},
		{std::string("sqrt"), 4},
		{std::string("sqr"), 4},
		{std::string("sin"), 4},
		{std::string("cos"), 4},
		{std::string("tg"), 4},
		{std::string("ctg"), 4},
		{std::string("sh"), 4},
		{std::string("ch"), 4},
		{std::string("ln"), 4},
		{std::string("th"), 4},
		{std::string("cth"), 4},
		
};

//float logarifm(StackOnList<float>& stack) {
//	if (stack.top() <= 0) { throw std::logic_error("Can't claculate logaritm non-positive number"); }
//	float x = (stack.top() - 1) / (stack.top() + 1);
//	stack.top();
//	return (2 * (x + (x * x * x / 3) + (x * x * x * x * x / 5) + (x * x * x * x * x * x * x / 7) +
//		(x * x * x * x * x * x * x * x * x / 9) + (x * x * x * x * x * x * x * x * x * x * x / 11) +
//		(x * x * x * x * x * x * x * x * x * x * x * x * x / 13) + (x * x * x * x * x * x * x * x * x * x * x * x * x * x * x / 15)));
//}
//
//float degree(StackOnList<float>& stack) {
//	float m = stack.top();
//	stack.pop();
//	float x = stack.top() - 1;
//	stack.top();
//	return (1 + (m * x) + (m * (m - 1) * x * x / 2) + (m * (m - 1) * (m - 2) * x * x * x / 6) +
//		(m * (m - 1) * (m - 2) * (m - 3) * x * x * x * x / 24));
//}
//
//float factorial(StackOnList<float>& stack) {
//	float x = stack.top();
//	stack.top();
//	float res = 1;
//	for (int i = x; i > 0; i--) {
//		res *= i;
//	}
//	return res;
//}
//
//float DoubleFactorial(StackOnList<float>& stack) {
//	float x = stack.top();
//	stack.top();
//	float res = 1;
//	for (int i = x; i > 0; i-=2) {
//		res *= i;
//	}
//	return res;
//}
//
//float sinus(StackOnList<float>& stack) {
//	float x = stack.top();
//	stack.top();
//	return (x - (x * x * x / 6) + (x * x * x * x * x / 120) - (x * x * x * x * x * x * x / 5040));
//}
//
//float cosinus(StackOnList<float>& stack) {
//	float x = stack.top();
//	stack.top();
//	return (1 - (x * x / 2) + (x * x * x * x / 24) - (x * x * x * x * x * x / 720));
//}
//
//float tangens(StackOnList<float>& stack) {
//	float x = stack.top();
//	stack.top();
//	return (1 - (x * x / 2) + (x * x * x * x / 24) - (x * x * x * x * x * x / 720));
//}
//
//float cotangens(StackOnList<float>& stack) {
//	return 1 / tangens(stack);
//}
//



std::map<std::string, int> DifFunc{
		{std::string("arcsh"), 4},
		{std::string("arcch"), 4},
		{std::string("arcth"), 4},
		{std::string("arccth"), 4},
		{std::string("arcsin"), 4},
		{std::string("arccos"), 4},
		{std::string("arctg"), 4},
		{std::string("arcctg"), 4},
		{std::string("sqrt"), 4},
		{std::string("sqr"), 4},
		{std::string("sin"), 4},
		{std::string("cos"), 4},
		{std::string("tg"), 4},
		{std::string("ctg"), 4},
		{std::string("sh"), 4},
		{std::string("ch"), 4},
		{std::string("ln"), 4},
		{std::string("th"), 4},
		{std::string("cth"), 4}
};

bool isLetter(char elem) {
	return elem <= 'Z' && elem >= 'A' ||
		elem <= 'z' && elem >= 'a';
}

bool isNumber(char elem) {
	return elem <= '9' &&
		elem >= '0';
}

bool isOperator(std::string elem) {
	return Dict.find(elem) != Dict.end();
}

bool isDifFunc(std::string elem) {
	return DifFunc.find(elem) != DifFunc.end();
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

std::string GetOperator(std::string& input, int& pos) {
	std::string res = "Not";
	if (isOperator(input.substr(pos, 6))) {
		res = input.substr(pos, 6);
		pos += 5;
	}
	else if (isOperator(input.substr(pos, 5))) {
		res = input.substr(pos, 5);
		pos += 4;
	}
	else if (isOperator(input.substr(pos, 4))) {
		res = input.substr(pos, 4);
		pos += 3;
	}
	else if (isOperator(input.substr(pos, 3))) {
		res = input.substr(pos, 3);
		pos += 2;
	}
	else if (isOperator(input.substr(pos, 2))) {
		res = input.substr(pos, 2);
		pos += 1;
	}
	else if (isOperator(input.substr(pos, 1))) {
		res = input.substr(pos, 1);
	}
	return res;
}

void ReplaceConstant(std::string& input) {
	while (input.find('e') != std::string::npos) {
		input.replace(input.find('e'), 1, "2.718");
	}
	while (input.find("pi") != std::string::npos) {
		input.replace(input.find("pi"), 2, "3.142");
	}
}

void ReplaceVar(std::string& input, std::string var, std::string val) {
	while (input.find(var) != std::string::npos) {
		input.replace(input.find(var), 1, val);
	}
}

void CorrectForm(std::string& input) {
	delspace(input);
	toUnarMinus(input);
	ReplaceConstant(input);
	if (!CorrectBrackets(input)) { throw std::logic_error("wrong brackets"); }
	if(!isLetter(input[0]) && !isNumber(input[0]) && !isOpenBracket(input[0]) && input[0] != '~') { throw std::logic_error("wrong first element"); }
	bool OpenBrFlag = true;
	bool CloseBrFlag = false;
	bool OperatorFlag = false;
	bool DifFuncFlag = false;
	bool OperandFlag = false;
	bool FactFlag = false;
	int pos = 0;
	do {
		if (isOpenBracket(input[pos])) {
			if (CloseBrFlag || OperandFlag || FactFlag) {
				input.insert(pos, "*");
				pos++;
			}
			OpenBrFlag = true;
			CloseBrFlag = false;
			OperatorFlag = false;
			DifFuncFlag = false;
			OperandFlag = false;
			FactFlag = false;
		}
		else if (isCloseBracket(input[pos])) {
			OpenBrFlag = false;
			CloseBrFlag = true;
			OperatorFlag = false;
			DifFuncFlag = false;
			OperandFlag = false;
			FactFlag = false;
		}
		else if (isOperator(std::string(1, input[pos]))) {
			if (input[pos] == '!') {
				OpenBrFlag = false;
				CloseBrFlag = false;
				OperatorFlag = false;
				DifFuncFlag = false;
				OperandFlag = false;
				FactFlag = true;
			}
			else {
				OpenBrFlag = false;
				CloseBrFlag = false;
				OperatorFlag = true;
				DifFuncFlag = false;
				OperandFlag = false;
				FactFlag = false;
			}
			
		}
		else if (isLetter(input[pos])) {
			if(CloseBrFlag || FactFlag || OperandFlag) {
				input.insert(pos, "*");
				pos++;
			}
			if (isDifFunc(GetOperator(input, pos))) {
				OpenBrFlag = false;
				CloseBrFlag = false;
				OperatorFlag = false;
				DifFuncFlag = true;
				OperandFlag = false;
				FactFlag = false;
			}
			else {
				OpenBrFlag = false;
				CloseBrFlag = false;
				OperatorFlag = false;
				DifFuncFlag = false;
				OperandFlag = true;
				FactFlag = false;
			}
			
		}
		else if (isNumber(input[pos])) {
			if (CloseBrFlag || FactFlag || OperandFlag) {
				input.insert(pos, "*");
				pos++;
			}
			OpenBrFlag = false;
			CloseBrFlag = false;
			OperatorFlag = false;
			DifFuncFlag = false;
			OperandFlag = true;
			FactFlag = false;
			GetNumberString(input, pos);
		}
		else { throw std::logic_error("Invalid syntax pos: " + pos); }
		pos++;
	} while (pos != input.length());
}

std::string toRPN(std::string& input) {
	CorrectForm(input);
	std::string res;
	StackOnList<std::string> operators;
	for (int pos = 0; pos < input.length(); pos++) {
		if (isNumber(input[pos])) { res = res + GetNumberString(input, pos) + ' '; }
		else if (isOpenBracket(input[pos])) { operators.push(std::string(1, input[pos])); }
		else if (isCloseBracket(input[pos])) {
			while (!isOpenBracket(operators.top()[0])) {
				res = res + operators.top() + ' ';
				operators.pop();
			}
			operators.pop();
		}
		else if (isLetter(input[pos])) {
			std::string tmp = GetOperator(input, pos);
			if (tmp == "Not") { res = res + input[pos] + ' '; }
			else { 
				while (!operators.empty() && Dict[operators.top()] >= Dict[tmp])
				{
					res = res + operators.top() + ' ';
					operators.pop();
				}
				operators.push(tmp);
			}
		}
		else if (isOperator(std::string(1, input[pos]))) {
			while (!operators.empty() && Dict[operators.top()] >= Dict[std::string(1, input[pos])])
			{
				res = res + operators.top() + ' ';
				operators.pop();
			}
			operators.push(std::string(1, input[pos]));
		}
	}
	while (!operators.empty()) {
		res = res + operators.top() + ' ';
		operators.pop();
	}
	return res;
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

std::string GetVar() {
	std::string res;
	std::cin >> res;
	return res;
}

float Calculate(std::string _input) {
	std::string input = toRPN(_input);
	StackOnList<float> numbers;
	while (input.find(' ') != std::string::npos) {
		int pos = 0;
		std::string tmp = input.substr(0, input.find(' '));
		input.erase(0, input.find(' ') + 1);
		if (isNumber(tmp[0])) {
			numbers.push(GetNumberFloat(tmp, pos));
		}
		else {
			std::string operation = GetOperator(tmp, pos);
			if (operation == "Not") {
				std::string var = GetVar();
				ReplaceVar(input, tmp, var);
				numbers.push(GetNumberFloat(var, pos));
			}
			else {
				funcdef(numbers, operation);
			}
		}
	}
	return numbers.top();
}