#include <iostream>
#include "../TVectore/TVector.h"
#include "../ParsAlgorithm/ParsAlgorithm.h"

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

class Polinom {
	TVector<Monom> monoms;
	TVector<Lexem> variebles;

public:
	Polinom(std::string input) {
		TVector<Lexem> lex = toRPN(input);
		for (Lexem elem : lex) {
			if (elem.type() == "Varieble") 
			{
				if (find<Lexem>(variebles.begin(), variebles.end(), elem) == nullptr) {
					variebles.append(elem);
				}
			}
		
		}
	}
};

//4x^4*y^3