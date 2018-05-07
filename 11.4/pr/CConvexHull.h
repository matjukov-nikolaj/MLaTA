#pragma once
#include "CPoint.h"

class CConvexHull
{
public:
	CConvexHull(std::vector<CPoint> &points, const size_t & size);
	void CreateConvexHull();
	std::vector<CPoint> GetPoints();
	double GetPerimeter();
private:
	bool IsRightTurn(const CPoint & p1, const CPoint & p2, const CPoint & p3);
	void CreateLowerPoints();
	void CreateUpperPoints();
	void CreateResultPoints();

	std::vector<CPoint> m_result;
	std::vector<CPoint> m_uppers;
	std::vector<CPoint> m_lowers;
	size_t m_size;
	std::vector<CPoint> m_points;
};

