#include "Equation.h"
#include <exception>
#include <iostream>

int main() {
	double b, s, n;
	BisectionMethod bm("sin(sin(x))", 2, 4);
	Solver solver;
	solver.setStrategy(&bm);
	std::string res1 = solver.useStrategy(b);
	SecantMethod sm("sin(sin(x))", 2, 4);
	solver.setStrategy(&sm);
	std::string res2 = solver.useStrategy(s);

	NewtonsMethod nm("sin(sin(x))", "cos(x)*cos(sin(x))", 2, 4, 1);
	solver.setStrategy(&nm);
	std::string res3 = solver.useStrategy(n);
	
	
	return 0;
}
