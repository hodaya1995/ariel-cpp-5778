/**
 * A minimal Fraction class for demonstrating
 * type-conversion operators and the ambiguity they cause.
 * 
 * @author Erel Segal-Halevi
 * @since 2018
 */

#include<iostream>
#include<cmath>
using namespace std;


class Fraction {
	int 	nom;
	int 	den;

public:
	Fraction(int nn, int dn): nom(nn), den(dn) { }

	// Add "explicit" in one of the lines below to allow compilation of last line.
	// See	https://stackoverflow.com/a/49092822/827927
	explicit Fraction(int nn): Fraction(nn, 1) { }
	operator double() const { 
		cout << "converting Fraction to double" << endl;
		return double(nom) / double(den); 
	}

	friend ostream& operator<<(ostream& os, const Fraction& frac);
	friend Fraction sqrt(const Fraction& f);
	friend const Fraction operator+ (const Fraction& a, const Fraction& other);
	//operator char() const { return 'a'; }
};

const Fraction operator+ (const Fraction& a, const Fraction& other) {
	int nn = a.nom * other.den +
		a.den * other.nom;
	int dd = a.den * other.den;
	return Fraction(nn, dd);
}

ostream& operator<<(ostream& os, const Fraction& frac) {
	return os << frac.nom << '/' << frac.den;
}

Fraction sqrt(const Fraction& f) {
	return Fraction(
		int(sqrt(f.nom)),
		int(sqrt(f.den))
	);
}

int main() {
	Fraction f1 {1, 4};
	cout << "f1 = " << f1 << endl;
	double d1 {f1};
	// equivalent to: 
	// double d1 = f1;
	cout << "d1 = " << d1 << endl;
	cout << "sqrt(f1) = " << sqrt(f1) << endl;
	cout << "std::sqrt(f1) = " << std::sqrt(f1) << endl;
	cout << "sin(f1) = " << sin(f1) << endl;

	Fraction f2 {2};
	cout << "f2 = " << f2 << endl;
	cout << ((Fraction)2) << endl;
	cout << "f1+2 = " << (f1 + Fraction{2}) << endl;   // OK!
	cout << "f1+2 = " << (double{f1} + 2) << endl;    // OK!
	cout << "f1+2 = " << (f1 + 2) << endl;   // ambiguous!
	cout << "2+f1 = " << (2 + f1) << endl;   // ambiguous!

	return 0;
}
