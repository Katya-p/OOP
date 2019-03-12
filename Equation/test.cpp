#include "pch.h"
#include "Equation.h"
#include "Parser.h"
TEST(TestCaseName, TestName) {
	
	double b, s, n;
	BisectionMethod bm("x^2+2*x-15", 0, 4);
	Solver solver;
	solver.setStrategy(&bm);
	std::string res1 = solver.useStrategy(b);
	SecantMethod sm("x^2+2*x-15", 0, 4);
	solver.setStrategy(&sm);
	std::string res2 = solver.useStrategy(s);
	NewtonsMethod nm("x^2+2*x-15", "2*x-2", 0, 4, 2);
	solver.setStrategy(&nm);
	std::string res3 = solver.useStrategy(n);
	EXPECT_EQ(round(b), 3);
	EXPECT_EQ(round(s), 3);
	EXPECT_EQ(round(n), 3);

}