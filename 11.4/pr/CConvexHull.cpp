#include "stdafx.h"
#include "CConvexHull.h"
#include "CPoint.h"

CConvexHull::CConvexHull(std::vector<CPoint>& points, const size_t &size)
	:m_points(points)
	,m_size(size)
{
}

bool CConvexHull::IsRightTurn(const CPoint &p1, const CPoint &p2, const CPoint &p3)
{
	return ((p3.x - p1.x)*(p2.y - p1.y) - (p3.y - p1.y)*(p2.x - p1.x)) > 0;
}

void CConvexHull::CreateLowerPoints()
{
	m_lowers.push_back(m_points[m_size - 1]);
	m_lowers.push_back(m_points[m_size - 2]);

	for (size_t i = 2; i< m_size; i++)
	{
		while (m_lowers.size() > 1 and (!IsRightTurn(m_lowers[m_lowers.size() - 2], m_lowers[m_lowers.size() - 1], m_points[m_size - i - 1])))
		{
			m_lowers.pop_back();
		}
		m_lowers.push_back(m_points[m_size - i - 1]);
	}
}

void CConvexHull::CreateUpperPoints()
{
	m_uppers.push_back(m_points[0]);
	m_uppers.push_back(m_points[1]);

	for (size_t i = 2; i < m_size; i++)
	{
		while (m_uppers.size() > 1 and (!IsRightTurn(m_uppers[m_uppers.size() - 2], m_uppers[m_uppers.size() - 1], m_points[i])))
		{
			m_uppers.pop_back();
		}
		m_uppers.push_back(m_points[i]);
	}
}

void CConvexHull::CreateConvexHull()
{
	sort(m_points.begin(), m_points.end(), [](const CPoint &p1, const CPoint &p2){ return (p1.x < p2.x) || (p1.x == p2.x && p1.y < p2.y); });
	CreateUpperPoints();
	CreateLowerPoints();
	CreateResultPoints();
}

void CConvexHull::CreateResultPoints()
{
	for (size_t i = 0; i < m_uppers.size(); ++i)
	{
		m_result.push_back(m_uppers[i]);
	}
	for (size_t i = 0; i < m_lowers.size(); ++i)
	{
		if (std::find_if(m_result.begin(), m_result.end(), [&](const CPoint & point) { return m_lowers[i].x == point.x && m_lowers[i].y == point.y; }) == m_result.end())
		{
			m_result.push_back(m_lowers[i]);
		}
	}
}

double CConvexHull::GetPerimeter()
{
	double result = 1E-12;
	CPoint point1 = m_result[0];
	CPoint point2;
	for (size_t i = 1; i < m_result.size(); ++i)
	{
		point2 = m_result[i];
		result += point1.GetDistanceToPoint(point2);
		point1 = point2;
	}
	result += point1.GetDistanceToPoint(m_result[0]);
	return result;
}

std::vector<CPoint> CConvexHull::GetPoints()
{
	return m_result;
}