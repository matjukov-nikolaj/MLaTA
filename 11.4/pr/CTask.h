#pragma once
#include "CPoint.h"

class CTask
{
public:
	CTask(std::istream & input, std::ostream & output);
	void PrintCoords();
	void GetSolution();
private:
	void ReadInput();

	int m_distance;
	std::vector<CPoint> m_castleCoords;
	std::istream &m_input;
	std::ostream &m_output;

};

