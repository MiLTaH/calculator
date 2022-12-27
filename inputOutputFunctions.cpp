#include "inputOutputFunctions.h"
template <class T>
T power(T number, size_t pow) {
	T powNumber = 1;
	for (size_t i = 0; i < pow; i++)
	{
		powNumber *= number;
	}
	return powNumber;
}
void input(std::string &str) 
{
	std::cout << "Input expression:\n";
	std::cin >> str;
}
std::string stringCopy(std::string _string,size_t startPosition,size_t endPosition) 
{
	if (endPosition < startPosition) throw "Error: string copy is failed\n";
	_string.erase(0, startPosition);
	_string.erase(endPosition - startPosition + 1, _string.size() - (endPosition - startPosition));
	return _string;
}
long double toDouble(std::string number) {
	long double doubleNumber=0;
	if (number.size() == 0) throw "Error:Empty string to number\n";
	bool isNegative = 0;
	size_t position = 0;
	if (number[0] == '-') {
		isNegative = 1;
		position++;
	}
	size_t t=0;
	size_t positionOfDot = number.size();
	if (number.find('.', 0) != -1) positionOfDot = number.find('.', 0);
	if (positionOfDot == number.size() - 1) throw "Error: there are no numbers after dot\n";
	for (size_t i = position; i < positionOfDot; i++)
	{
		t = t * 10 + (number[i]-'0');
	}
	size_t p = 0,count=0;
	doubleNumber = t;
	for (size_t i = positionOfDot+1; i < number.size(); i++)
	{
		doubleNumber += (static_cast<long double>(number[i] - '0') / power(10, count+1));
		count++;
	}
	if (isNegative) doubleNumber = -doubleNumber;
	return doubleNumber;
}
std::string findNumbers(std::string expression,size_t positionOfOperation,bool isForward) 
{
	std::string number;
	size_t numberOfDots = 0;
	int position= positionOfOperation;
	if (isForward == 1) 
	{
		if (position + 1 == expression.size()) throw "Error: find number after operator is failed\n";
		if (expression[position + 1] == '-') {
			position++;
			if (position+1==expression.size()) throw "Error: no number after -\n";
			if (expression[position + 1] - '0' >= 0 && expression[position + 1] - '0' < 10); else throw "Error: no number after -\n";
		}
		while(true) 
		{
			if (position == expression.size()-1) break;
			if (expression[position + 1] - '0' >= 0 && expression[position + 1] - '0' < 10) {
				position++;
				continue;
			}
			if (expression[position + 1] == '.') if (numberOfDots == 0) {
				position++;
				numberOfDots++;
				continue;
			}
			else throw "Error:Two dots in number\n";
			break;
		}
	}
	else 
	{
		if (position == 0) throw "Error: find number before operator is failed\n";
		while (true)
		{
			if (position == 0) break;
			if (expression[position - 1] - '0' >= 0 && expression[position - 1] - '0' < 10 ) {
				position--;
				continue;
			}
			if (expression[position - 1] == '.') if (numberOfDots == 0) {
				position--;
				numberOfDots++;
				continue;
			}
			else throw "Error: Two dots in number\n";
			if (expression[position - 1] == '-') {
				position--;
				break;
			}
			break;
		}
	}
	if (isForward == 1) return stringCopy(expression, positionOfOperation + 1, position);
	else return stringCopy(expression, position, positionOfOperation - 1);
}
void binaryOperation(std::string &expression,std::string operationChar, long double (*functionOfOperation) (long double,long double)) 
{
	int position=expression.find(operationChar, 1);
	int positionOfEnd = position + operationChar.size()-1;
	while (position != -1) {
		long double number1 = toDouble(findNumbers(expression, position, 0));
		long double number2 = toDouble(findNumbers(expression, positionOfEnd, 1));
		long double result=functionOfOperation(number1, number2);
		size_t insertPos = position - findNumbers(expression, position, 0).size();
		expression.erase(insertPos,
			operationChar.size() + findNumbers(expression, positionOfEnd, 1).size() + findNumbers(expression, position, 0).size());
		expression.insert(insertPos, std::to_string(result));
		position = expression.find(operationChar, 1);
		positionOfEnd = position + operationChar.size() - 1;
	}
}
void binaryOperationWithPriorities(std::string& expression, std::vector<std::string> operationChars, std::vector<long double (*) (long double, long double)> functions)
{
	while(true){
	int minPosition,minElement;
	minPosition = expression.size();
	minElement = 0;
	for (size_t i = 0; i < operationChars.size(); i++)
	{
		int position = expression.find(operationChars[i], 1);
		if (position != -1 && position < minPosition) {
			minPosition = position;
			minElement = i;
		}
	}
	if (minPosition == expression.size()) break;
	int position = minPosition;
	int positionOfEnd = position + operationChars[minElement].size() - 1;
		long double number1 = toDouble(findNumbers(expression, position, 0));
		long double number2 = toDouble(findNumbers(expression, positionOfEnd, 1));
		long double result = functions[minElement](number1, number2);
		size_t insertPos = position - findNumbers(expression, position, 0).size();
		expression.erase(insertPos,
			operationChars[minElement].size() + findNumbers(expression, positionOfEnd, 1).size() + findNumbers(expression, position, 0).size());
		expression.insert(insertPos, std::to_string(result));
	}
}
void calculate(std::string& expression) {
	brackets(expression, "(", ")");
	doublePi(expression);
	UnaryPlus(expression);
	UnaryOperation(expression, "sqrt", root, 1);
	UnaryOperation(expression, "sin", doubleSin, 1);
	UnaryOperation(expression, "cos", doubleCos, 1);
	UnaryOperation(expression, "tan", doubleTan, 1);
	binaryOperation(expression, "^", doublePower);
	std::vector<std::string> mult = { "*","/","%" };
	std::vector<long double (*) (long double, long double)> multFunctions = { multiplication,division,divisionWithRemainder };
	binaryOperationWithPriorities(expression, mult, multFunctions);
	std::vector <std::string> add = {"+", "-"};
	std::vector<long double (*) (long double, long double)> addFunctions = { summary,subtract };
	binaryOperationWithPriorities(expression, add, addFunctions);
	binaryOperation(expression, "&", doubleAnd);
	std::vector<std::string> byte = { "|","XOR","NAND","NOR" };
	std::vector<long double (*) (long double, long double)> byteFunctions = { doubleOr,doubleXor,doubleNand,doubleNor };
	binaryOperationWithPriorities(expression, byte, byteFunctions);
	checkRounding(expression);
}
void UnaryOperation(std::string& expression, std::string operationChar, long double (*functionOfOperation) (long double),bool isPost)
{
	int position = expression.find(operationChar, 0);
	int positionOfEnd = position + operationChar.size() - 1;
	while (position != -1) {
		long double number = toDouble(findNumbers(expression, (isPost) ? positionOfEnd : position, isPost));
		long double result = functionOfOperation(number);
		size_t insertPos = (isPost)? position:position- findNumbers(expression, (isPost) ? positionOfEnd : position, isPost).size();
		expression.erase(insertPos,
			operationChar.size() + findNumbers(expression, (isPost)?positionOfEnd:position, isPost).size());
		expression.insert(insertPos, std::to_string(result));
		position = expression.find(operationChar, 0);
		positionOfEnd = position + operationChar.size() - 1;
	}
}
void brackets(std::string& expression, std::string firstBrackets, std::string secondBrackets) {
	int isBrackets = expression.find(firstBrackets, 0);
	while (isBrackets != -1) {
		int firstPosition = expression.find(firstBrackets, 0);
		int firstPositionSearch = expression.find(firstBrackets, firstPosition + 1);
		int secondPosition = expression.find(secondBrackets, 0);
		while (firstPositionSearch < secondPosition && firstPositionSearch != -1) {
			firstPositionSearch = expression.find(firstBrackets, firstPositionSearch + 1);
			secondPosition = expression.find(secondBrackets, secondPosition + 1);
		}
		if (firstPosition == -1 || secondPosition == -1) throw "Error: can't find some brackets\n";
		if (firstPosition + 1 == secondPosition) throw "Error: empty brackets\n";
		std::string subexpression = stringCopy(expression, firstPosition + 1, secondPosition - 1);
		calculate(subexpression);
		expression.erase(firstPosition, secondPosition - firstPosition + 1);
		expression.insert(firstPosition, subexpression);
		isBrackets = expression.find(firstBrackets, 0);
	}
}
void UnaryPlus(std::string& expression) {
	int position = expression.find("+", 0);
	int positionOfSearch = position;
	while (position != -1) {
		if (position!=expression.size()-1 && expression[position + 1] == '+') throw "Error: ++ is not available\n";
		if (position == 0) {
			expression.erase(position, 1);
			position = expression.find("+", positionOfSearch);
			continue;
		}
		if (expression[position - 1] - '0' >= 0 && expression[position - 1] - '0' < 10) {
			positionOfSearch = position + 1;
			position = expression.find("+", positionOfSearch);
		}
		else {
			expression.erase(position, 1);
			position = expression.find("+", positionOfSearch);
		}
	}
}
void checkRounding(std::string& expression) {
	std::string num1 = findNumbers(expression, -1, 1);
	if (num1.size() != expression.size()) throw "Error: check failed, different sizes\n";
	int numberNine = 0;
	int positionOfDot = expression.find(".", 0);
	if (positionOfDot == -1) return;
	for (size_t i = expression.size() - 1; i >= positionOfDot; i--) {
		if (expression[i] == '0' && i == expression.size() - 1) {
			expression.erase(i, 1);
			continue;
		}
		if (expression[i] == '.') {
			expression.erase(i, 1);
			break;
		}
		break;
	}
}
void doublePi(std::string& expression) {
	int position = expression.find("pi", 0);
	while (position != -1) {
		expression.erase(position, 2);
		expression.insert(position, "3.141592653589");
		position = expression.find("pi", 0);
	}
}
