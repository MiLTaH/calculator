#include "inputOutputFunctions.h"
int main() {
	try {
		std::string expression;
		input(expression);
		calculate(expression);
		std::cout << expression;
	}
	catch (const char* error) { std::cout << error; }
	return 0;
}
