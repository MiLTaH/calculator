#include "arithmeticAndLogicOperators.h"
#include <cmath>
bool isZero(long double num) { return -0.0000000000001 < num && num < 0.0000000000001; }
bool isInt(long double num) {
	long int numint = num;
	return isZero(num - numint);
}
long double summary(long double num1, long double num2) { return num1 + num2; }
long double subtract(long double num1, long double num2) { return num1 - num2; }
long double multiplication(long double num1, long double num2) { return num1 * num2; }
long double division(long double num1, long double num2) {
	if (isZero(num2)) throw "Error: number is too similar with 0\n";
	return num1 / num2;
}
long double divisionWithRemainder(long double num1, long double num2) {
	if (isZero(num2)) throw "Error: number is too similar with 0\n";
	if (isInt(num1) == 0 || isInt(num2) == 0) throw "Error: for operation % one of operand isn't int\n";
	long int divided = num1 / num2;
	return num1 - num2 * divided;
}
