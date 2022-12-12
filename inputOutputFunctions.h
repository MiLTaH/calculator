#pragma once
#include "iostream"
#include "string"
#include "vector"
#include "arithmeticAndLogicOperators.h"
void input(std::string&);
long double toDouble(std::string );
std::string findNumbers(std::string, size_t, bool);
template <class T>
T power(T, size_t);
void binaryOperation(std::string&, std::string, long double (*) (long double, long double));
void binaryOperationWithPriorities(std::string&, std::vector<std::string>,
	std::vector<long double (*) (long double, long double)>);
void calculate(std::string&);
