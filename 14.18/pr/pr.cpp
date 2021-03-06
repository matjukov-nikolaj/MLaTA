/*14.18.Вычисление выражения(7)
Во входной строке записано арифметическое выражение, состоящее из целых чисел и знаков
операций « + », « - », «*», « / », «(», «)», «^».Пробелы в выражении отсутствуют.Требуется написать
программу, которая вычислит значение данного выражения.
Ввод.Входной файл INPUT.TXT содержит одну строку, состоящую не более чем из 255
символов.Числа в выражении не превышают по модулю 2×10 9.Гарантируется, что в процессе
вычислений получаемые значения не превышают по модулю 2×10 9 .
Вывод.В единственной строке файла OUTPUT.TXT требуется вывести значение выражения с
точностью 4 знака после запятой.

Матюков Николай Юрьевич ПС - 21

*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <limits>
#include <iomanip>
#include <cmath>
using namespace std;

const short MAX_SIZE = 255;

namespace Sign
{
	constexpr char add = '+';
	constexpr char sub = '-';
	constexpr char mul = '*';
	constexpr char div = '/';
	constexpr char degree = '^';
	constexpr char openBracket = '(';
	constexpr char closeBracket = ')';
}

string GetExpression(ifstream &fIn)
{
	string str;
	getline(fIn, str);
	return str;
}

void CheckTopCharOnOpenBracket(stack <char> &stack)
{
	if ((!stack.empty()) && (stack.top() == Sign::openBracket))
	{
		stack.pop();
	}
}

void GetFromStackBeforeEndOrOpenBracket(stack <char> &stack, string &str, bool fromCloseBracket)
{
	while (!stack.empty() && (stack.top() != Sign::openBracket))
	{
		str += ' ';
		str += stack.top();
		stack.pop();
	}
	if (fromCloseBracket)
	{
		CheckTopCharOnOpenBracket(stack);
	}
}

void PushInStackAddOrSub(stack <char> &stack, char ch, string &str)
{
	if ((!stack.empty()) &&
		((stack.top() != Sign::mul) &&
		(stack.top() != Sign::div) &&
		(stack.top() != Sign::degree) &&
		(stack.top() != Sign::add) &&
		(stack.top() != Sign::sub)))
	{
		stack.push(ch);
	} 
	else
	{
		GetFromStackBeforeEndOrOpenBracket(stack, str, false);
		stack.push(ch);
	}
}

bool ChIsDigit(char ch)
{
	string digitStr = "0123456789";
	if (digitStr.find(ch) != string::npos)
	{
		return true;
	}
	return false;
}

bool ChIsSign(char ch)
{
	string SignStr = "+-*/^";
	if (SignStr.find(ch) != string::npos)
	{
		return true;
	}
	return false;
}

void CheckUnaryMinus(stack <char> &stack, string &str, string inputStr, short &i)
{
	if ((!stack.empty() && (stack.top() == Sign::openBracket))
		&& (!ChIsDigit(inputStr[i - 1])) || (str.empty()))
	{
		str += '0';
	}
}

void PushInStackMulOrDiv(stack <char> &stack, char ch, string &str)
{
	if ((!stack.empty()) &&
		((stack.top() != Sign::degree) &&
		(stack.top() != Sign::div) &&
		(stack.top() != Sign::mul)))
	{
		stack.push(ch);
	}
	else
	{
		while ((!stack.empty()) &&
			(stack.top() != Sign::openBracket) &&
			(stack.top() != Sign::add) &&
			(stack.top() != Sign::sub) &&
			(stack.top() != Sign::div))
		{
			str += ' ';
			str += stack.top();
			stack.pop();
		}
		CheckTopCharOnOpenBracket(stack);
		stack.push(ch);
	}
}

void WriteFromStack(stack <char> &stack, string &str)
{
	while (!stack.empty())
	{
		str += ' ';
		str += stack.top();
		stack.pop();
	}
}

string GetPostfixFormOfExpression(string &str)
{
	stack <char> stack;
	string postfixStr = "";
	char ch = ' ';
	for (short i = 0; i < str.size(); i++)
	{
		ch = str[i];
		switch (ch)
		{
		case Sign::openBracket:
			stack.push(ch);
			break;
		case Sign::closeBracket:
			GetFromStackBeforeEndOrOpenBracket(stack, postfixStr, true);
			break;
		case Sign::add:
			PushInStackAddOrSub(stack, ch, postfixStr);
			break;
		case Sign::sub:
			CheckUnaryMinus(stack, postfixStr, str, i);
			PushInStackAddOrSub(stack, ch, postfixStr);
			break;
		case Sign::mul:
			PushInStackMulOrDiv(stack, ch, postfixStr);
			break;
		case Sign::div:
			PushInStackMulOrDiv(stack, ch, postfixStr);
			break;
		case Sign::degree:
			stack.push(ch);
			break;
		default:
			postfixStr += ch;
			break;
		}
		if (ChIsSign(ch))
		{
			postfixStr += ' ';
		}
	}
	WriteFromStack(stack, postfixStr);
	return postfixStr;
}

void SetErrorDescription(double currResult, string &errDescription, double firstNum, double secondNum, string opp)
{
	if ((static_cast<long long>(currResult) > INT_MAX) || 
		(static_cast<long long>(currResult) == _I64_MIN) ||
		(static_cast<long long>(currResult) == _I64_MAX) ||
		(static_cast<long long>(currResult) < INT_MIN))
	{
		errDescription = opp + " is " + to_string(firstNum) + " and " + to_string(secondNum) + " is more than INT_MAX.";
	}
}

double GetResultOfCalculationTwoOperands(stack <double> &stack, const char ch, string &errDescription)
{
	double currResult = 1E-12;
	double secondNum = stack.top();
	stack.pop();
	double firstNum = stack.top();
	stack.pop();
	switch (ch)
	{
	case Sign::add:
		currResult = firstNum + secondNum;
		SetErrorDescription(currResult, errDescription, firstNum, secondNum, "Sum");
		break;
	case Sign::sub:
		currResult = firstNum - secondNum;
		break;
	case Sign::mul:
		currResult = firstNum * secondNum;
		SetErrorDescription(currResult, errDescription, firstNum, secondNum, "Multiplication");
		break;
	case Sign::div:
		currResult = firstNum / secondNum;
		break;
	case Sign::degree:
		currResult = pow(firstNum, secondNum);
		if (errno == EDOM)
		{
			errDescription = "Incorrect exponentiation";
		}
		if ((errno == ERANGE && currResult == HUGE_VAL) || 
			(static_cast<long long>(currResult) == _I64_MIN) ||
			(static_cast<long long>(currResult) > INT_MAX))
		{
			errDescription = "Degree is " + to_string(firstNum) + " and " + to_string(secondNum) + " is more than INT_MAX.";
		}
		break;
	default:
		break;
	}
	return currResult;
}

double GetResultOfExpression(string str, string &errDescription)
{
	char ch = ' ';
	string numberStr = "";
	long long number;
	stack <double> stack;
	double result = 0;
	for (short i = 0; i < str.size(); i++)
	{
		ch = str[i];
		if (ChIsDigit(ch))
		{
			numberStr += ch;
		}
		if ((ch == ' ') && (numberStr != ""))
		{
			number = stoll(numberStr.c_str());
			if (number > INT_MAX)
			{
				errDescription = "Incorrect input data. Number: " + numberStr + " is more than INT_MAX.";
				return result;
			}
			stack.push(static_cast<double>(number));
			numberStr = "";
		}
		if (ChIsSign(ch))
		{
			double currResult = GetResultOfCalculationTwoOperands(stack, ch, errDescription);
			if (errDescription != "")
			{
				return result;
			}
			stack.push(currResult);
			currResult = 1E-12;
		}
	}
	result = stack.top();
	stack.pop();
	return result;
}

int main()
{
	ifstream fileIn("input.txt");
	if (!fileIn.is_open())
	{
		cout << "File input.txt has not opened for reading.";
		return 1;
	}
	ofstream fileOut("output.txt");
	if (!fileOut.is_open())
	{
		cout << "File output.txt has not opened for writing.";
		return 1;
	}
	string currString = GetExpression(fileIn);
	if (currString.empty())
	{
		cout << "Empty input data" << endl;
		return 1;
	}
	if (currString.size() > 255)
	{
		cout << "It is long expressions more than 255." << endl;
		return 1;
	}
	string postfixStr = GetPostfixFormOfExpression(currString);
	//cout << postfixStr << endl;
	string errDescription = "";
	fileOut << fixed << setprecision(4);
	double result = GetResultOfExpression(postfixStr, errDescription);
	if (errDescription != "")
	{
		fileOut << errDescription << endl;
		return 1;
	}
	//cout << postfixStr << endl;
	//cout << result << endl;
	fileOut << result << endl;
    return 0;
}
