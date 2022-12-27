#include "arithmeticAndLogicOperators.h"
#include <cmath>
bool isZero(long double num) { return -0.0000000000001 < num && num < 0.0000000000001; }
bool isInt(long double num) {
	long int numint= num;
	return isZero(num - numint);
}
bool isLogic(long double num) {
	long int numint = num;
	return (isZero(num - numint) && (numint == 1 || numint == 0));
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
	return num1-num2*divided; }
long double root(long double num) {
	return sqrt(num);
}
long double doublePower(long double num1, long double num2) {
	if (isInt(num2) == 0) throw "Error: power is not int\n";
	return pow(num1, num2);
}
long double doubleOr(long double num1, long double num2) {
	if (isInt(num1) == 0 || isInt(num2) == 0) throw "Error: for operation | one of operand isn't int\n";
	int l1 = num1, l2 = num2;
	return l1 | l2;
}
long double doubleAnd(long double num1, long double num2) {
	if (isInt(num1) == 0 || isInt(num2) == 0) throw "Error: for operation & one of operand isn't int\n";
	int l1 = num1, l2 = num2;
	return l1 & l2;
}
long double doubleXor(long double num1, long double num2) {
	if (isInt(num1) == 0 || isInt(num2) == 0) throw "Error: for operation ^ one of operand isn't int\n";
	int l1 = num1, l2 = num2;
	return l1 ^ l2;
}
long double doubleNand(long double num1, long double num2) {
	if (isInt(num1) == 0 || isInt(num2) == 0) throw "Error: for operation NAND one of operand isn't int\n";
	int l1 = num1, l2 = num2;
	return ~(l1 & l2);
}
long double doubleNor(long double num1, long double num2) {
	if (isInt(num1) == 0 || isInt(num2) == 0) throw "Error: for operation NOR one of operand isn't int\n";
	int l1 = num1, l2 = num2;
	return ~(l1 | l2);
}
long double doubleSin(long double num) {
	return sin(num);
}
long double doubleCos(long double num) {
	return cos(num);
}
long double doubleTan(long double num) {
	return tan(num);
}
