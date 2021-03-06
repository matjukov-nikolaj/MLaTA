/*
10.1. Последовательность 1 (6)
В последовательности чисел a 1 , a 2 , a 3 , ... задан первый член, а остальные вычисляются по
формуле a i  = (a i - 1 ) 2  mod M. Найти N-й член последовательности.
Ограничения: 1 ≤ M ≤ 10000, 2 ≤ N ≤ 2×10 9 , 0 ≤ a 1 ≤ M, время 1 с.
Ввод из файла INPUT.TXT. В первой строке находятся числа M, N и a 1 , разделённые пробелом.
Вывод в файл OUTPUT.TXT. Вывести одно число - a N .

Матюков Николай Юрьевич

*/


#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

struct Sequence
{
	int m = -1;
	size_t n = -1;
	int a1 = -1;
	vector<int> firstNumbers;
	vector<int> cycleNumbers;
};

bool ValidInputData(Sequence &sequence)
{
	if (sequence.m <= 0 || sequence.m > 10000 ||
		sequence.a1 < 0 || sequence.a1 > sequence.m ||
		sequence.n < 2 || sequence.n > 2 * pow(10, 9))
	{
		return false;
	}
	return true;
}

bool ReadInput(Sequence &sequence, string &errorDescription)
{
	ifstream fileIn("input.txt");
	if (!fileIn.is_open())
	{
		errorDescription = "File input.txt has not opened for reading.";
		return false;
	}
	fileIn >> sequence.m;
	fileIn >> sequence.n;
	fileIn >> sequence.a1;
	if (!ValidInputData(sequence))
	{
		errorDescription = "Invalid input data.";
		return false;
	}
	return true;
}

void CreateCyclesOfSequence(Sequence &sequence)
{
	vector<int> temp;
	temp.push_back(sequence.a1);
	int ai = static_cast<int>(pow(sequence.a1, 2)) % sequence.m;
	while (find(temp.begin(), temp.end(), ai) == temp.end())
	{
		temp.push_back(ai);
		ai = static_cast<int>(pow(ai, 2)) % sequence.m;
	}
	vector<int>::iterator it = find(temp.begin(), temp.end(), ai);
	int firstNumberOfCycle = static_cast<int>(std::distance(temp.begin(), it));
	for (size_t i = firstNumberOfCycle; i < temp.size(); i++)
	{
		sequence.cycleNumbers.push_back(temp[i]);
	}
	for (int i = 0; i < firstNumberOfCycle; ++i)
	{
		sequence.firstNumbers.push_back(temp[i]);
	}
	temp.clear();
}

bool PrintElement(int Element, string &errorDescription)
{
	ofstream fileOut("output.txt");
	if (!fileOut.is_open())
	{
		errorDescription = "File output.txt has not opened for writing.";
		return false;
	}
	fileOut << Element << endl;
	cout << Element << endl;
	if (!fileOut.flush())
	{
		errorDescription = "Failed to save data on disk\n";
		return 1;
	}
	return true;
}

size_t GetElementPosition(size_t numberOfCycles, size_t vecSize, size_t n)
{
	return n - numberOfCycles * vecSize;
}

int GetElementAtNumberN(Sequence &sequence)
{
	size_t pos = 0;
	if (sequence.n < sequence.firstNumbers.size())
	{
		return sequence.firstNumbers[sequence.n - 1];
	}
	if (sequence.n < sequence.firstNumbers.size() + sequence.cycleNumbers.size())
	{
		return sequence.cycleNumbers[sequence.n - sequence.firstNumbers.size() - 1];
	}
	size_t expectPos = sequence.n - sequence.firstNumbers.size();
	size_t numberOfCycles = static_cast<int>(expectPos / sequence.cycleNumbers.size());
	if (numberOfCycles == 0)
	{
		return sequence.cycleNumbers[expectPos - 1];
	}
	pos = GetElementPosition(numberOfCycles, sequence.cycleNumbers.size(), expectPos);
	if (pos == 0)
	{
		pos = GetElementPosition(numberOfCycles - 1, sequence.cycleNumbers.size(), expectPos);
		return sequence.cycleNumbers[pos- 1];
	}
	return sequence.cycleNumbers[pos - 1];
}

int main()
{
	Sequence sequence;
	string errorDescription = "";
	if (!ReadInput(sequence, errorDescription))
	{
		cout << errorDescription << endl;
		return 1;
	}
	int Element = -1;
	if (sequence.a1 == 0 || sequence.a1 == 1)
	{
		Element = sequence.a1;
	}
	else
	{
		CreateCyclesOfSequence(sequence);
		Element = GetElementAtNumberN(sequence);
	}
	if (!PrintElement(Element, errorDescription))
	{
		cout << errorDescription << endl;
		return 1;
	}
	return 0;
}
