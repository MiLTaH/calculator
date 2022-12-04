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
