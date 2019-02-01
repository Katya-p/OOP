#include "Approximations.h"

namespace {
	const double MAX = 4.0e+10;
	const double MIN = 3.0e-10;
}

void Approximations::operator()(double error) {
	if (value < MIN || value > MAX || error < 0.0)
		return;
	
	double r = (current.get_numerator() - value * current.get_denominator()) / (value * res.get_denominator() - res.get_numerator());
	if (!((r > 1.0) || (value * res.get_denominator() == (double)res.get_numerator()))) {
		res.swap(current);
	}	
	if (res.print_and_mark_as_completed(value, error, fractions)) {
		return;
	}
	while (r != 0.0) {
		if (r <= 1.0) {
			r = 1.0 / r;
		}
		
		current.set_numerator(current.get_numerator() + res.get_numerator() * (int)r);
		current.set_denominator(current.get_denominator() + res.get_denominator() * (int)r);
		res.set_numerator(res.get_numerator() + current.get_numerator());
		res.set_denominator(res.get_denominator() + current.get_denominator());

		r = (current.get_numerator() - value * current.get_denominator()) / (value * res.get_denominator() - res.get_numerator());
		if (!((r > 1.0) || (value * res.get_denominator() == (double)res.get_numerator()))) {
			res.swap(current);
		}		
		if (res.print_and_mark_as_completed(value, error, fractions)) {
			return;
		}
	} 
}

void Approximations::print() {
	for (auto it : fractions) {
		std::cout << it.get_numerator() << '/' << it.get_denominator() << "	epsilon = " << it.get_epsilon() << std::endl;
	}
}
std::vector<Fraction> Approximations::get_fractions() {
	return fractions;
}

void Fraction::swap(Fraction & other) {
	std::swap(numerator, other.numerator);
	std::swap(denominator, other.denominator);
}
void Fraction::set_denominator(int den) {
	denominator = den;
}
double Fraction::get_epsilon() {
	return epsilon;
}

void Fraction::set_numerator(int num) {
	numerator = num;
}
int Fraction::get_denominator() {
	return denominator;
}

int Fraction::get_numerator() {
	return numerator;
}
bool Fraction::print_and_mark_as_completed(double value, double error, std::vector<Fraction> & fractions) {
	epsilon = fabs(1.0 - numerator / (value*denominator));
	if (epsilon <= error) {
		fractions.push_back(*this);
		return true;
	}
	double m = 1.0;
	do {
		m *= 10.0;
	} while (m * epsilon < 1.0);
	epsilon = 1.0 / m * ((int)(0.5 + m * epsilon));
	fractions.push_back(*this);
	return false;
}