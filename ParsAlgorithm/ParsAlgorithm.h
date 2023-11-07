#include "../StackOnList/StackOnList.h"
#include <string>
#include <map>

std::map<std::string, int> dict{
		{std::string("("), 0},
		{std::string("{"), 0},
		{std::string("["), 0},
		{std::string("+"), 1},
		{std::string("-"), 1},
		{std::string("*"), 2},
		{std::string("/"), 2},
		{std::string("^"), 3},
		{std::string("~"), 4},
		{std::string("arcsh"), 4},
		{std::string("arcch"), 4},
		{std::string("arcth"), 4},
		{std::string("arccth"), 4},
		{std::string("arcsin"), 4},
		{std::string("arccos"), 4},
		{std::string("arctg"), 4},
		{std::string("arcctg"), 4},
		{std::string("sqr"), 4},
		{std::string("sqrt"), 4},
		{std::string("sin"), 4},
		{std::string("cos"), 4},
		{std::string("tg"), 4},
		{std::string("ctg"), 4},
		{std::string("sh"), 4},
		{std::string("ch"), 4},
		{std::string("th"), 4},
		{std::string("cth"), 4},
		
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
	return dict.find(elem) != dict.end();
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

double NumberDouble(std::string& st, int& pos) {
	std::string tmp;
	while (pos < st.length() &&
		(isNumber(st[pos]) ||
		(st[pos] == '.' &&
		tmp.find('.') == std::string::npos))) {
		tmp += st[pos];
		pos++;
	}
	if (pos + 1 < st.length() && st[pos + 1] == '.') { throw std::logic_error("wrong number"); }
	return std::stod(tmp);
}

std::string NumberString(std::string& st, int& pos) {
	std::string tmp;
	while (pos < st.length() &&
		(isNumber(st[pos]) ||
		(st[pos] == '.' &&
		tmp.find('.') == std::string::npos))) {
		tmp += st[pos];
		pos++;
	}
	if (pos + 1 < st.length() && st[pos + 1] == '.') { throw std::logic_error("wrong number"); }
	return tmp;
}

std::string GetOperator(std::string& input, int& pos) {
	std::string res = "Not";
	if (isOperator(input.substr(pos, 6))) {
		res = input.substr(pos, 6);
		pos += 5;
	}
	if (isOperator(input.substr(pos, 5))) {
		res = input.substr(pos, 5);
		pos += 4;
	}
	if (isOperator(input.substr(pos, 4))) {
		res = input.substr(pos, 4);
		pos += 3;
	}
	if (isOperator(input.substr(pos, 3))) {
		res = input.substr(pos, 3);
		pos += 2;
	}
	if (isOperator(input.substr(pos, 2))) {
		res = input.substr(pos, 2);
		pos += 1;
	}
	if (isOperator(input.substr(pos, 1))) {
		res = input.substr(pos, 1);
	}
	return res;
}

void CorrectForm(std::string& input) {
	if (input[0] == '-') { input[0] = '~'; }
	for (int i = 0; i < input.length(); i++) {
		if (!isNumber(input[i]) &&
			!isLetter(input[i]) &&
			!isOperator(std::string(1, input[i])) &&
			!isCloseBracket(input[i]) &&
			input[i] != '.') {
			throw std::logic_error("invalid syntex");
		}
		if (isOpenBracket(input[i]) && input[i + 1] == '-') { input[i + 1] = '~'; }
		if (GetOperator(input, i) != "Not") { continue; }
		if(isCloseBracket(input[i]) && 
			i + 1 < input.length() && !isOperator(std::string(1, input[i + 1]))){
			input.insert(++i, 1, '*');
		}
		
		if (isNumber(input[i]) &&
			i + 1 < input.length() &&
			(isLetter(input[i + 1]) ||
				isOpenBracket(input[i + 1]))) {
			input.insert(++i, 1, '*');
		}
		else if (i + 1 < input.length() && 
			isLetter(input[i]) &&
			(isLetter(input[i + 1]) ||
				isOpenBracket(input[i + 1]))) {
			input.insert(++i, 1, '*');
		}
		else if (i + 1 < input.length() &&
			isCloseBracket(input[i]) &&
			(isLetter(input[i + 1]) ||
				isOpenBracket(input[i + 1]) ||
				isNumber(input[i + 1]))) {
			input.insert(++i, 1, '*');
		}
	}
}

std::string toRPN(std::string& input) {
	if (!CorrectBrackets(input)) { throw std::logic_error("wrong brackets"); }
	std::string res;
	StackOnList<std::string> operators;
	delspace(input);
	CorrectForm(input);
	for (int pos = 0; pos < input.length();) {
		if (isNumber(input[pos])) { res = res + NumberString(input, pos) + ' '; }
		if (isOpenBracket(input[pos])) { operators.push(std::string(1, input[pos])); pos++;  }
		if (isCloseBracket(input[pos])) {
			while (!isOpenBracket(operators.top()[0])) {
				res = res + operators.top() + ' ';
				operators.pop();
			}
			operators.pop();
			pos++;
		}
		if (isLetter(input[pos])) {
			std::string tmp = GetOperator(input, pos);
			if (tmp == "Not") { res = res + input[pos] + ' '; pos++; }
			else { 
				while (!operators.empty() &&  dict[operators.top()] >= dict[tmp])
				{
					res = res + operators.top() + ' ';
					operators.pop();
				}
				operators.push(tmp); pos++; 
			}
		}
		if (isOperator(std::string(1, input[pos])) && !isOpenBracket(input[pos])) {
			while (!operators.empty() && dict[operators.top()] >= dict[std::string(1, input[pos])])
			{
				res = res + operators.top() + ' ';
				operators.pop();
			}
			operators.push(std::string(1, input[pos])); pos++;
		}
	}
	while (!operators.empty()) {
		res = res + operators.top() + ' ';
		operators.pop();
	}
	return res;
}
