#include "stdafx.h"
#include "CTask.h"
#include "CConvexHull.h"

CTask::CTask(std::istream & input, std::ostream & output)
	:m_input(input)
	,m_output(output)
{
}

void CTask::PrintCoords()
{
	CPoint point;
	for (size_t i = 0; i < m_castleCoords.size(); ++i)
	{
		point = m_castleCoords[i];
		m_output << point.x << " " << point.y << "\n";
	}
}

void CTask::GetSolution()
{
	ReadInput();
	CConvexHull convexHull(m_castleCoords, m_castleCoords.size());
	convexHull.CreateConvexHull();
	double perimeter = convexHull.GetPerimeter();
	double circleSize = 2 * M_PI * m_distance;
	m_output << static_cast<int>(perimeter + circleSize) << "\n";
}

void CTask::ReadInput()
{
	int numberOfAngels;
	m_input >> numberOfAngels >> m_distance;
	if (numberOfAngels < 3 || numberOfAngels > 1000)
	{
		throw std::invalid_argument("Invalid number of angles.");
	}
	if (m_distance < 1 || m_distance > 1000)
	{
		throw std::invalid_argument("Invalid distance.");
	}
	CPoint point;
	for (int i = 0; i < numberOfAngels; ++i)
	{
		m_input >> point.x >> point.y;
		if ((point.x < -10000 || point.x > 10000) || (point.y < -10000 || point.y > 10000))
		{
			throw std::invalid_argument("Invalid point.");
		}
		m_castleCoords.push_back(point);
	}
}
