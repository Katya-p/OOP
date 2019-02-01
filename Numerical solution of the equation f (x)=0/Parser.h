#ifndef PARSER
#define PARSER
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <cstring>
#include <stdexcept>

struct Expression {
	Expression(std::string token) : token(token) {} 
	Expression(std::string token, Expression a) : token(token), args{ a } {} 
	Expression(std::string token, Expression a, Expression b) : token(token), args{ a, b } {}
	double operator()(double x);
	std::string token;
	std::vector<Expression> args;
};

int get_priority(const std::string& binary_op);

struct Parser {
	explicit Parser(std::string input) : input(input) {}
	Expression parse(); 
private:
	std::string parse_token(); 
	Expression parse_simple_expression(); 
	Expression parse_binary_expression(int min_priority); 

	std::string input; // Кусок строки, который еще не распарсили
};


#endif