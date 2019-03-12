#ifndef EQUATION
#define EQUATION
#include <string>
#include "Parser.h"


enum class Error {
	NoError,
	SameSignsAtTheEndsOfInterval,
	DivisionByZero
};

struct SolutionStrategy {
	virtual Error solve(double & result) = 0;
	virtual ~SolutionStrategy() {}
};

struct BisectionMethod : SolutionStrategy {
	BisectionMethod(const char* input, double a, double b)
		:func(Parser(input).parse()), a(a), b(b)
	{}
	Error solve(double & result);
private:
	Expression func;
	double a;
	double b;
};

struct SecantMethod : SolutionStrategy {
	SecantMethod(const char* input, double a, double b)
		:func(Parser(input).parse()), a(a), b(b)
	{}
	Error solve(double & result);
private:
	Expression func;
	double a;
	double b;
};

struct NewtonsMethod : SolutionStrategy {
	NewtonsMethod(const char* input_func, const char* input_derivative, double a, double b, double x0)
		:func(Parser(input_func).parse()), derivative(Parser(input_derivative).parse()), a(a), b(b), x0(x0)
	{}
	Error solve(double & result);
private:
	Expression func;
	Expression derivative;
	double a;
	double b;
	double x0;
};

struct Solver
{
	std::string useStrategy(double & result);
	void setStrategy(SolutionStrategy * op);
private:
	SolutionStrategy * operation;
};
#endif
