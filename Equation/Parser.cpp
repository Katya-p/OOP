#include "Parser.h"

int get_priority(const std::string& binary_op){
	if (binary_op == "+") return 1;
	if (binary_op == "-") return 1;
	if (binary_op == "*") return 2;
	if (binary_op == "/") return 2;
	if (binary_op == "^") return 3;
	return 0;
}

double Expression::operator()(double x){
	switch (args.size()) {
	case 2: { 
		auto a = args[0](x);
		auto b = args[1](x);
		if (token == "+") return a + b;
		if (token == "-") return a - b;
		if (token == "*") return a * b;
		if (token == "/") return a / b;
		if (token == "^") return pow(a, b);

		throw std::runtime_error("Unknown binary operator");
	}

	case 1: { 
		auto a = args[0](x);
		if (token == "+") return +a;
		if (token == "-") return -a;
		if (token == "abs") return abs(a);
		if (token == "sin") return sin(a);
		if (token == "cos") return cos(a);
		if (token == "tan") return tan(a);
		if (token == "exp") return exp(a);
		if (token == "log") return log(a);
		throw std::runtime_error("Unknown unary operator");
	}

	case 0: { 
		if (token == "x") {
			return x;
		}
		return strtod(token.c_str(), nullptr);
	}
	}

	throw std::runtime_error("Unknown expression type");
}

std::string Parser::parse_token() {
	auto it = input.begin();
	if (std::isdigit(*it)) {
		std::string number;
		while (std::isdigit(*it) || *it == '.')
		{
			number.push_back(*it);
			it++;
		}
		input.erase(input.begin(), it);
		return number;
	}
	if (*it == 'x') {
		input.erase(input.begin(), input.begin() + 1);
		return { 'x' };
	}
	static const std::string tokens[] = { "+", "-", "^", "*", "/", "abs", "sin", "cos", "tan", "(", ")", "exp", "log"/*, "x"*/ };
	for (auto& t : tokens) {
		if (std::strncmp(input.c_str(), t.c_str(), t.size()) == 0) {
			input.erase(input.begin(), input.begin() + t.size());
			return t;
		}
	}
	return { "" }; // Какой-то неизвестный токен, или символ '\0' - конец строки.
}

Expression Parser::parse_simple_expression() {
	auto token = parse_token();
	if (token.empty()) 
		throw std::runtime_error("Invalid input");

	if (std::isdigit(token[0]) || (token[0] == 'x')) // Если это цифра или x, возвращаем выражение без аргументов
		return Expression(token);

	if (token == "(") {
		auto result = parse();
		if (parse_token() != ")") throw std::runtime_error("Expected ')'");
		return result; // Если это скобки, парсим и возвращаем выражение в скобках
	}
	// Иначе, это унарная операция
	auto arg = parse_simple_expression(); 
	return Expression(token, arg);
}

Expression Parser::parse_binary_expression(int min_priority) {
	auto left_expr = parse_simple_expression(); 
	for (;;) {
		auto op = parse_token(); // Пробуем парсить бинарную операцию.
		int priority = get_priority(op);
		// Выходим из цикла если ее приоритет слишком низок (или это не бинарная операция).
		if (priority <= min_priority) {
			input = op + input; // Отдаем токен обратно
			return left_expr; // возвращаем выражение слева.
		}

		// Парсим выражение справа. Текущая операция задает минимальный приоритет.
		auto right_expr = parse_binary_expression(priority);
		left_expr = Expression(op, left_expr, right_expr); // Обновляем выражение слева.
	} 
}

//вызывает парсер бинарных выражений, передавая ему нулевой минимальный приоритет операций (любая бинарная операция):
Expression Parser::parse() {
	return parse_binary_expression(0);
}