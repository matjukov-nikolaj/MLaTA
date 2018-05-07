#include "stdafx.h"
#include "CPoint.h"

CPoint::CPoint()
{
}

CPoint::CPoint(int x, int y)
	:x(x)
	,y(y)
{
}

bool CPoint::operator!=(const CPoint & point)
{
	return (this->x != point.x && this->y != point.y);
}

double CPoint::GetDistanceToPoint(const CPoint &point) const
{
	return sqrt(pow((point.x - x), 2) + pow((point.y - y), 2));
}

CPoint::~CPoint()
{
}
