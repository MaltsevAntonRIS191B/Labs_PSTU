#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <cstring>
#include<Windows.h>
#include <sstream>
#include<exception>
//перевод из double в string
std::string toString(double a) {
	std::stringstream ss;
	ss << a;
	std::string str = ss.str();
	return str;
}
//структура для работы с токенами
struct Expression {
	std::string token;
	std::vector<Expression> args;
	Expression(std::string token) : token(token) {}
	Expression(std::string token, Expression a) : token(token), args{ a } {}
	Expression(std::string token, Expression a, Expression b) : token(token), args{ a, b } {}
};
//парсер выражений
class Parser {
	double x; //переменная x
	std::string parse_token();
	Expression parse_simple_expression();
	Expression parse_binary_expression(const int&);
	const char* input;
public:
	explicit Parser(const char* input, const double& x) : input(input), x(x) {} //инициализация строки с уравнением
	void parse_x();
	Expression parse();
};
void Parser::parse_x() {
	std::string inp = input;
	for (auto h : inp) {
		if (h == 'x') {
			return;
		}
	}
	throw std::runtime_error("В выражении отсутствует x");
}
std::string Parser::parse_token() {
	while (std::isspace(*input)) ++input; //двигаем дальше, пока не найдём начало выражения
	if (std::isdigit(*input)) {
		std::string number;
		while (std::isdigit(*input) || *input == '.') number.push_back(*input++);
		return number;
	}
	//массив доступных операций
	static const std::string tokens[] =
	{ "+", "-", "**", "*", "/", "mod", "abs", "sin", "cos", "(", ")","arccos","sqrt","x","ln","arcsin","arctg","exp","tg" };
	for (auto& a : tokens) {
		if (std::strncmp(input, a.c_str(), a.size()) == 0) {
			input += a.size();
			return a;
		}
	}
	return "";
}
//парсер простых выражений
Expression Parser::parse_simple_expression() {
	auto token = parse_token();
	if (token.empty()) throw std::runtime_error("Неправильный ввод");
	if (token == "x") {
		return Expression(toString(x));
	}
	//если token является (, то парсим, пока не найдём вторую скобку. Если скобку не нашли, то вызываем исключение
	if (token == "(") {
		auto result = parse();
		if (parse_token() != ")") throw std::runtime_error("Отсутствует')'");
		return result;
	}
	if (std::isdigit(token[0]))
		return Expression(token);

	return Expression(token, parse_simple_expression());
}
//получить приоритет операции
int get_priority(const std::string& binary_op) {
	if (binary_op == "+") return 1;
	if (binary_op == "-") return 1;
	if (binary_op == "*") return 2;
	if (binary_op == "/") return 2;
	if (binary_op == "mod") return 2;
	if (binary_op == "**") return 3;
	return 0;
}
//парсер бинарных выражений
Expression Parser::parse_binary_expression(const int& min_priority) {
	auto left = parse_simple_expression();
	for (;;) {
		auto operation = parse_token();
		auto priority = get_priority(operation);
		if (priority <= min_priority) {
			input -= operation.size();
			return left;
		}
		auto right = parse_binary_expression(priority);
		left = Expression(operation, left, right);
	}
}
//вызывает парсер бинарных выражений
Expression Parser::parse() {
	return parse_binary_expression(0);
}
//вычисление значения выражения
double eval(const Expression& e) {
	switch (e.args.size()) {
	case 2: {
		auto a = eval(e.args[0]);
		auto b = eval(e.args[1]);
		if (e.token == "+") return a + b;
		if (e.token == "-") return a - b;
		if (e.token == "*") return a * b;
		if (e.token == "/") return a / b;
		if (e.token == "**") return pow(a, b);
		if (e.token == "mod") return (int)a % (int)b;
		throw std::runtime_error("Неизвестаня бинарная операция");
	}
	case 1: {
		auto a = eval(e.args[0]);
		if (e.token == "+") return +a;
		if (e.token == "-") return -a;
		if (e.token == "abs") return abs(a);
		if (e.token == "sin") return sin(a);
		if (e.token == "arcsin") return asin(a);
		if (e.token == "cos") return cos(a);
		if (e.token == "arccos")return acos(a);
		if (e.token == "sqrt")return sqrt(a);
		if (e.token == "ln")return log(a);
		if (e.token == "arctg")return atan(a);
		if (e.token == "tg")return tan(a);
		throw std::runtime_error("Неизвестный тип выражения");
	}
		  //число
	case 0:
		return strtod(e.token.c_str(), nullptr); //перевод string в double
	}
	throw std::runtime_error("Неизвестный тип выражения");
}
//поиск корня нелинейного уравнения методом половинного деления 
double findroot(double (*f)(double), double a, double b, double eps) {
	double c;
	while ((b - a) / 2 > eps) {
		c = (a + b) / 2;
		if ((f(a) * f(c)) > 0) a = c;
		else b = c;
	}
	return c;
}
// итераций
double FindRoot(double (*f)(double), double x0, int n) {

	double x = x0, df, h = 0.00001;

	df = (f(x + h) - f(x)) / h;

	std::cout << "df = " << df << std::endl;

	for (int i = 1; i <= n; i++)

		x = x - f(x) / df;

	return x;

}


const double h = 0.1;

double testf11(const char* input, double x) {

	try {

		Parser p(input, x);

		auto result = eval(p.parse()); //вычисление значения функции при заданном x

		return result;

	}

	catch (std::exception& e) {

		std::cout << input << " : исключение: " << e.what() << '\n';

	}

}
std::string  equation; //строка для ввода уравнения
double testf2(double x) {
	return testf11(equation.c_str(), x);
}

/*
double testf22(double x) {

	return testf11(equation1.c_str(), x);

}*/



double f1(double x) {

	return (testf2(x) - testf2(x - h)) / h;

}

double f2(double x) {

	return (testf2(x + h) - 2 * testf2(x) + testf2(x - h)) / (h * h);

}

double koren(double (*f)(double), double (*f1)(double), double (*f2)(double), double a, double b, double e, int k)

{

	double x, x1;

	if (f(a) * f2(a) > 0)

		x = a;

	else

		x = b - 0.00001;//так как в точке 1.0 первая и вторые производные неопределенны.

	while (1)

	{

		x1 = x;

		k = k + 1;

		x = x - f(x) / f1(x);

		if (fabs(x1 - x) <= e)

			break;

	}

	x = trunc(x * 10000) / 10000;

	return x;

}














double testf1(const char* input, double x) {
	try {
		Parser p(input, x);
		auto result = eval(p.parse()); //вычисление значения функции при заданном x
		return result;
	}
	catch (std::exception& e) {
		std::cout << input << " : исключение: " << e.what() << '\n';
	}
}
