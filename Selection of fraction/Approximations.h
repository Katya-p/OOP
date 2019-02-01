#ifndef APPROXIMATIONS
#define APPROXIMATIONS
#include <utility>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
struct Fraction {
	Fraction(int numerator, int denominator) 
		: numerator(numerator), denominator(denominator)
	{}

	Fraction(int numerator, int denominator, double epsilon)
		: numerator(numerator), denominator(denominator), epsilon(epsilon)
	{}
	Fraction()
		: numerator(-1), denominator(-1)
	{}

	void swap(Fraction & other);
	bool print_and_mark_as_completed(double value, double error, std::vector<Fraction> & fractions);
	int get_numerator();
	int get_denominator();
	void set_numerator(int num);
	void set_denominator(int den);
	double get_epsilon();
private:
	int numerator, denominator;
	double epsilon;
};

struct Approximations {
	Approximations(double value)
		: value(value), res(Fraction((int)value, 1)), current(Fraction((int)value + 1, 1))
	{}
	void print();
	void operator()(double error);
	std::vector<Fraction> get_fractions();
private:
	double value;
	Fraction res;
	Fraction current;
	std::vector<Fraction> fractions;
};

#endif