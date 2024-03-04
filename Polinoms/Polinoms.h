#include <iostream>
#include "../ParsAlgorithm/ParsAlgorithm.h"
#include "../TVectore/TVector.h"

class Monom {
public:
	TVector<float> powers;
	float coefficient;

	Monom(int x = 0) : powers(x), coefficient(0) {
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
			return Monom(coefficient + m.coefficient, powers);
		}
		throw std::logic_error("Different powers");
	}

	Monom operator-(const Monom& m) {
		if (powers == m.powers) {
			return Monom(coefficient - m.coefficient, powers);
		}
		throw std::logic_error("Different powers");
	}

	Monom operator*(const Monom& m) {
		return Monom(coefficient * m.coefficient, powers + m.powers);
	}

	Monom operator*(const float& x) {
		return Monom(coefficient * x, powers);
	}

	Monom operator/(const Monom& m) {
		return Monom(coefficient / m.coefficient, powers - m.powers);
	}

	Monom operator/(const float& x) {
		return Monom(coefficient / x, powers);
	}

	bool operator==(const Monom& m) const noexcept {
		return powers == m.powers && coefficient == m.coefficient;
	}

	bool operator!=(const Monom& m) const noexcept {
		return !(*this == m);
	}

};

TList<Monom> GetMonom(TList<Lexem> input, TVector<Lexem> variebles) {
	TList<Monom> res;
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
			else {
				if (find_pos<Lexem>(variebles.begin(), variebles.end(), lex) == nullptr) {
					throw std::logic_error("Unknow variebl");
				}
				VarPos = *find_pos<Lexem>(variebles.begin(), variebles.end(), lex);
				curMonom->powers[VarPos] += 1;
			}
			VarFlag = false;
			NumFlag = true;
			OpFlag = false;
		}
		else if (lex.type() == Operator && lex.name() == "~" && (OpFlag || StartFlag)) {
			bool VarFlag = false;
			bool NumFlag = false;
			bool OpFlag = false;
			bool MinFlag = true;
		}
		else if (lex.type() == Operator && lex.name() == "^" && VarFlag) {
			bool VarFlag = false;
			bool NumFlag = false;
			bool OpFlag = true;
			bool MinFlag = false;
		}
		else if (lex.type() == Operator && (lex.name() == "-" || lex.name() == "+")) {
			res.push_back(*curMonom);
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
	return res;
}



class Polinom {
	TList<Monom> monoms;
	TVector<Lexem> variebles;

public:
	Polinom() = default;
	Polinom(std::string& input) {
		TList<Lexem> expression = GetLexems(input);
		for (auto node : expression) {
			Lexem lex = node.data();
			if (lex.type() == Varieble) variebles.append(lex);
		}
		monoms = GetMonom(expression, variebles);
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
		for (TNode<Monom>* cur = res.monoms.front_node(); cur != nullptr; cur = cur->next()) {
			if (cur->data().powers == m.powers) {
				cur->data() = cur->data() + m;
				return res;
			}
		}
		res.monoms.push_back(m);
		return res;
	}

	Polinom operator-(const Monom& m) {
		if (variebles.size() != m.powers.size()) {
			throw std::logic_error("Different powers");
		}
		Polinom res(*this);
		for (TNode<Monom>* cur = res.monoms.front_node(); cur != nullptr; cur = cur->next()) {
			if (cur->data().powers == m.powers) {
				cur->data() = cur->data() - m;
				return res;
			}
		}
		res.monoms.push_back(m);
		return res;
	}

	Polinom operator*(const Monom& m) {
		if (variebles.size() != m.powers.size()) {
			throw std::logic_error("Different powers");
		}
		Polinom res(*this);
		for (TNode<Monom>* cur = res.monoms.front_node(); cur != nullptr; cur = cur->next()) {
				cur->data() = cur->data() * m;
		}
		return res;
	}

	Polinom operator*(const float& x) {
		Polinom res(*this);
		for (TNode<Monom>* cur = res.monoms.front_node(); cur != nullptr; cur = cur->next()) {
				cur->data() = cur->data() * x;
		}
		return res;
	}

	Polinom operator/(const Monom& m) {
		if (variebles.size() != m.powers.size()) {
			throw std::logic_error("Different powers");
		}
		Polinom res(*this);
		for (TNode<Monom>* cur = res.monoms.front_node(); cur != nullptr; cur = cur->next()) {
			cur->data() = cur->data() / m;
		}
		return res;
	}

	Polinom operator/(const float& x) {
		Polinom res(*this);
		for (TNode<Monom>* cur = res.monoms.front_node(); cur != nullptr; cur = cur->next()) {
			cur->data() = cur->data() / x;
		}
		return res;
	}
};

//4x^4y^3