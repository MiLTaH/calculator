#pragma once
#include "iostream"
#include "string"
#include "vector"
#include "arithmeticAndLogicOperators.h"
void input(std::string&);
long double toDouble(std::string );
std::string findNumbers(std::string, size_t, bool);
std::string stringCopy(std::string, size_t, size_t);
void UnaryOperation(std::string&, std::string, long double (*) (long double),bool);
void binaryOperation(std::string&, std::string, long double (*) (long double,long double));
void binaryOperationWithPriorities(std::string&, std::vector<std::string>,
	std::vector<long double (*) (long double, long double)>);
void brackets(std::string&, std::string, std::string);
void calculate(std::string&);
void UnaryPlus(std::string&);
void checkRounding(std::string&);
void doublePi(std::string&);
template <class T>
T power(T, size_t);
