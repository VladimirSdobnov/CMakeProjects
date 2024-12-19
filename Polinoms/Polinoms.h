#include <iostream>
#include "../ParsAlgorithm/ParsAlgorithm.h"
#include "../TVectore/TVector.h"

template<class T>
int BinarSearchPos(TVector<T> data, const T& elem) {
	int left = 0;
	int right = data.size() - 1;
	int mid = 0;
	while (left <= right) {
		mid = (left + right) * 0.5;
		if (elem == data[mid]) return mid;
		if (elem > data[mid]) left = mid + 1;
		else if (elem < data[mid]) right = mid - 1;
	}
	return mid;
}

template<class T>
void prior_insert(TVector<T>& vec, T elem) {
	int pos = BinarSearchPos<T>(vec, elem);
	if (vec.size() == 0) { vec.append(elem); }
	else if (vec[pos] == elem) {
		vec[pos] = vec[pos] + elem;
	}
	else if (elem > vec[vec.size() - 1])
		vec.append(elem);
	else if (elem < vec[0])
		vec.insert(elem, 0);
	else if (elem > vec[pos]) {
		vec.insert(elem, pos + 1);
	}
	else {
		vec.insert(elem, pos);
	}
}



class Monom {
public:
	TVector<float> powers;
	float coefficient;

	Monom(int x = 0) : powers(x, x), coefficient(0) {
		for (int i = 0; i < x; i++) {
			powers[i] = 0;
		}
	}

	Monom(float coef, TVector<float> pows) {
		powers = pows;
		coefficient = coef;
	}

	Monom(const Monom& m): powers(m.powers), coefficient(m.coefficient) {};

	Monom& operator=(const Monom& m) {
		powers = m.powers;
		coefficient = m.coefficient;
		return *this;
	}
	Monom operator+(const Monom& m) {
		if (powers == m.powers) {
			Monom res(coefficient + m.coefficient, powers);
			return res;
		}
		throw std::logic_error("Different powers");
	}
	Monom operator-(const Monom& m) {
		if (powers == m.powers) {
			Monom res(coefficient - m.coefficient, powers);
			return res;
		}
		throw std::logic_error("Different powers");
	}
	Monom operator*(const Monom& m) {
		Monom res(coefficient * m.coefficient, powers + m.powers);
		return res;
	}
	Monom operator*(const float& x) {
		Monom res(coefficient * x, powers);
		return res;
	}
	Monom operator/(const Monom& m) {
		Monom res(coefficient / m.coefficient, powers - m.powers);
		return res;
	}
	Monom operator/(const float& x) {
		Monom res(coefficient / x, powers);
		return res;
	}

	bool operator==(const Monom& m) const noexcept {
		return powers == m.powers;// && coefficient == m.coefficient;
	}
	bool operator!=(const Monom& m) const noexcept {
		return !(*this == m);
	}
	bool operator>(const Monom& m) const noexcept {
		if (powers == m.powers) { throw std::logic_error("Different powers"); }
		if (m.powers == 0 && powers == 0) { return false; }
		else if (m.powers == 0) { return true; }
		for (int i = 0; i < powers.size(); i++) {
			if (powers[i] > m.powers[i]) { return true; }
			if (powers[i] < m.powers[i]) { return false; }
		}
		return false;
	}
	bool operator<(const Monom& m) const noexcept {
		if (powers == m.powers) { throw std::logic_error("Different powers"); }
		if (m.powers == 0) { return false; }
		for (int i = 0; i < powers.size(); i++) {
			if (powers[i] > m.powers[i]) { return false; }
			if (powers[i] < m.powers[i]) { return true; }
		}
		return false;
	}

};

TVector<Monom> GetMonom(TList<Lexem> input, TVector<Lexem> variebles) {
	TVector<Monom> res;
	bool StartFlag = true;
	bool VarFlag = false;
	bool NumFlag = false;
	bool OpFlag = false;
	bool MinFlag = false;
	int VarPos = 0;
	Monom* curMonom = new Monom(variebles.size());
	for (auto node : input) {
		auto lex = node.data();
		if (lex.type() == Number && (OpFlag || StartFlag || MinFlag)) {
			if (MinFlag) { lex.val(-lex.val()); MinFlag = false; }
			if (StartFlag) { curMonom->coefficient = lex.val(); StartFlag = false; }
			else { curMonom->powers[VarPos] += lex.val() - 1; }
			VarFlag = false;
			NumFlag = true;
			OpFlag = false;
		}
		else if (lex.type() == Varieble && (NumFlag || StartFlag || (StartFlag && MinFlag) || VarFlag)) {
			if (StartFlag && MinFlag) { curMonom->coefficient = -1; StartFlag = false; MinFlag = false; }
			if (StartFlag) { curMonom->coefficient = 1; StartFlag = false; }
			if (find_pos<Lexem>(variebles.begin(), variebles.end(), lex) == nullptr) {
				throw std::logic_error("Unknow variebl");
			}
			VarPos = *find_pos<Lexem>(variebles.begin(), variebles.end(), lex);
			curMonom->powers[VarPos] += 1;
			VarFlag = true;
			NumFlag = false;
			OpFlag = false;
		}
		else if (lex.type() == Operator && lex.name() == "~" && (OpFlag || StartFlag) && !MinFlag) {
			VarFlag = false;
			NumFlag = false;
			OpFlag = false;
			MinFlag = true;
		}
		else if (lex.type() == Operator && lex.name() == "^" && VarFlag) {
			VarFlag = false;
			NumFlag = false;
			OpFlag = true;
			MinFlag = false;
		}
		else if (lex.type() == Operator && (lex.name() == "-" || lex.name() == "+")) {
			prior_insert(res, *curMonom);
			delete curMonom;
			curMonom = new Monom(variebles.size());
			StartFlag = true;
			VarFlag = false;
			NumFlag = false;
			OpFlag = false;
			if (lex.name() == "-") MinFlag = true;
			else MinFlag = false;
			VarPos = 0;
		}
		else { throw std::logic_error("Invalid syntax in monom"); }
	}
	prior_insert(res, *curMonom);
	delete curMonom;
	return res;
}
TVector<Lexem> GetVars(std::string input) {
	TList<Lexem> expression = GetLexems(input);
	TVector<Lexem> variebles;
	for (auto node : expression) {
		Lexem lex = node.data();
		if (lex.type() == Varieble && find_pos<Lexem>(variebles.begin(), variebles.end(), lex) == nullptr) variebles.append(lex);
	}
	return variebles;
}

//�� ��������� ���������� �� ������� �����
Monom RandMonom(int var_count, float max_pow = 100, float min_pow = 0, float max_coef = 1000, float min_coef = 1) {
	Monom res(var_count);
	res.coefficient = min_coef + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max_coef - min_coef)));
	for (int i = 0; i < var_count; i++) {
		res.powers[i] = rand() % int((max_pow - min_pow)) + min_pow;
	}
	return res;
}

class Polinom {
	TVector<Monom> monoms;
	TVector<Lexem> variebles;

public:
	Polinom() = default;
	Polinom(TVector<Lexem> vars) : monoms() {
		for (auto lex : vars) {

			if (lex.type() != Varieble) throw std::logic_error("In vars vec non varieble");
		}
		variebles = vars;
	}
	Polinom(std::string& input) {
		TList<Lexem> expression = GetLexems(input);
		variebles = GetVars(input);
		monoms = GetMonom(expression, variebles);
	}
	Polinom(std::string& input, TVector<Lexem> vars) {
		TList<Lexem> expression = GetLexems(input);
		for (auto lex : vars) {
			
			if (lex.type() != Varieble) throw std::logic_error("In vars vec non varieble");
		}
		variebles = vars;
		monoms = GetMonom(expression, vars);
	}
	Polinom(const Polinom& p) : monoms(p.monoms), variebles(p.variebles) {};

	Polinom& operator=(const Polinom& p) {
		monoms = p.monoms;
		variebles = p.variebles;
		return *this;
	}

	Polinom operator+(const Monom& m) {
		if (variebles.size() != m.powers.size()) {
			throw std::logic_error("Different powers");
		}
		Polinom res(*this);
		prior_insert<Monom>(res.monoms, m);
		return res;
	}

	Polinom operator-(const Monom& m) {
		if (variebles.size() != m.powers.size()) {
			throw std::logic_error("Different powers");
		}
		Monom tmp(m);
		float x = -1;
		tmp = tmp * -1;
		Polinom res(*this);
		prior_insert<Monom>(res.monoms, tmp);
		return res;
	}

	Polinom operator*(const Monom& m) {
		if (variebles.size() != m.powers.size()) {
			throw std::logic_error("Different powers");
		}
		Polinom res(*this);
		res.monoms = res.monoms * m;
		return res;
	}

	Polinom operator*(const float& x) {
		Polinom res(*this);
		for (int i = 0; i < res.monoms.size(); i++) {
			res.monoms[i] = res.monoms[i] * x;
		}
		return res;
	}

	Polinom operator/(const Monom& m) {
		if (variebles.size() != m.powers.size()) {
			throw std::logic_error("Different powers");
		}
		Polinom res(*this);
		for(int i = 0; i < monoms.size(); i++) {
			res.monoms[i] = monoms[i] / m;
		}
		return res;
	}

	Polinom operator/(const float& x) {
		Polinom res(*this);
		for (int i = 0; i < monoms.size(); i++) {
			res.monoms[i] = monoms[i] / x;
		}
		return res;
	}

	Polinom operator+(const Polinom& p) {
		if (variebles != p.variebles) {
			throw std::logic_error("Different variebles");
		}
		Polinom res(*this);
		for (int i = 0; i < p.monoms.size(); i++) {
			prior_insert(res.monoms, p.monoms[i]);
		}
		return res;
	}

	Polinom operator-(const Polinom& p) {
		if (variebles != p.variebles) {
			throw std::logic_error("Different variebles");
		}
		Polinom tmp(p);
		float x = -1;
		tmp = tmp * -1;
		Polinom res(*this);
		for (int i = 0; i < tmp.monoms.size(); i++) {
			prior_insert(res.monoms, tmp.monoms[i]);
		}
		return res;
	}

	Polinom operator*(const Polinom& p) {
		if (variebles != p.variebles) {
			throw std::logic_error("Different variebles");
		}
		Polinom res(variebles);
		for (int i = 0; i < p.monoms.size(); i++) {
			Polinom tmp = (*this) * p.monoms[i];
			res = res + tmp;
		}
		return res;
	}

	friend std::ostream& operator<<(std::ostream& ostr, Polinom& p);
};

Polinom RandPolinom(int var_count = 3, int monom_count = 10) {
	TVector<Lexem> vars(var_count);
	for (int i = 1; i <= var_count; i++) {
		std::string var("x" + std::to_string(i));
		int pos = 0;
		vars.append(Lexem(var, pos));
	}
	Polinom res(vars);
	for (int i = 0; i < monom_count; i++) {
		Monom m = RandMonom(var_count);
		res = res + m;
	}
	return res;
}

std::ostream& operator<<(std::ostream& ostr, Polinom& p) {
	int k = 0;
	for (auto elem : p.monoms) {
		if (elem.coefficient != 0) {
			if (elem.coefficient > 0) {
				if (k != 0) ostr << " + ";
				if (elem.coefficient != 1) ostr << elem.coefficient;
			}
			else if (elem.coefficient < 0) {
				if (k != 0) ostr << " - ";
				if (elem.coefficient != -1) ostr << -elem.coefficient;
				
			}
			else { continue; }
			for (int i = 0; i < elem.powers.size(); i++) {
				if (elem.powers[i] != 0) ostr << p.variebles[i].name() << "^" << elem.powers[i];
			}
			k++;
		}
	}
	return ostr;
}

//4x^4y^3