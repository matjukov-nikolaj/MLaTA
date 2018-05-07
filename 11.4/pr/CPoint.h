#pragma once
class CPoint
{
public:
	CPoint();
	CPoint(int x, int y);
	bool operator != (const CPoint &point);
	double GetDistanceToPoint(const CPoint & point) const;
	int x;
	int y;
	~CPoint();
};
