#include "Equation.h"

namespace {
	const double epsilon = 0.01;
}

std::string Solver::useStrategy(double & result) {
	Error err = operation->solve(result);
	if (err == Error::SameSignsAtTheEndsOfInterval) {
		return "Bisection Method requires different signs of function at the ends of interval\n";
	}
	else if (err == Error::DivisionByZero) {
		return "Division by zero\n";
	}
	return "Ok\n";
}

void Solver::setStrategy(SolutionStrategy * op) {
	operation = op;
}

Error BisectionMethod::solve(double & result) {
	if (func(a)*func(b) > 0) {
		return Error::SameSignsAtTheEndsOfInterval;
	}
	double left = a;
	double right = b;
	double x = 0;
	while ((right - left) > 2 * epsilon) {
		x = (left + right) / 2;
		if (func(x) == 0)
			break;
		if (func(a)*func(x) < 0)
			right = x;
		else
			left = x;
	}
	result = x;
	return Error::NoError;
}

Error SecantMethod::solve(double & result) {
	double left = a;
	double right = b;
	while (fabs(right - left) > epsilon) {
		if (func(right) == func(left)) {
			return Error::DivisionByZero;
		}
		left = right - (right - left) * func(right) / (func(right) - func(left));
		if (func(right) == func(left)) {
			return Error::DivisionByZero;
		}
		right = left + (left - right) * func(left) / (func(left) - func(right));
	}
	result = right;
	return Error::NoError;
}

Error NewtonsMethod::solve(double & result) {
	if (derivative(x0) == 0) {
		return Error::DivisionByZero;
	}
	double x = x0 - func(x0) / derivative(x0);
	while (fabs(x - x0) > epsilon) {
		x0 = x;
		if (derivative(x) == 0) {
			return Error::DivisionByZero;
		}
		x = x - func(x) / derivative(x);
	}
	result = x;
	return Error::NoError;
}