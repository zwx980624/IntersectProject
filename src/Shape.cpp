#include "Shape.h"

int dcmp(double d1, double d2) {
	if (d1 - d2 > EPS) {
		return 1;
	}
	else if (d2 - d1 > EPS) {
		return -1;
	}
	else {
		return 0;
	}
}

bool CPoint::operator < (const CPoint & rhs) const 
{
	if (rhs._x - _x > EPS) {
		return true;
	}
	else if (_x - rhs._x > EPS) {
		return false;
	}
	else {
		if (rhs._y - _y > EPS) {
			return true;
		}
		else {
			return false;
		}
	}
}

bool CPoint::operator==(const CPoint & rhs) const
{
	return !(this->operator<(rhs)) && !(rhs.operator<(*this));
}

int CShape::_nextId = 0;

CShape::CShape(std::string type):_type(type)
{
	_id = _nextId++;
}

bool CShape::operator<(const CShape & rhs) const
{
	return _id < rhs._id;
}

bool CSlope::operator<(const CSlope & rhs) const
{
	if (_isInf) {
		return false;
	}
	else {
		if (rhs._isInf) {
			return true;
		}
		else {
			if (rhs._k - _k > EPS) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}

bool CSlope::operator==(const CSlope & rhs) const
{
	return !(this->operator<(rhs)) && !(rhs.operator<(*this));
}

CLine::CLine(int x1, int y1, int x2, int y2, std::string type): CShape(type)
{
	_x1 = (double)x1;
	_x2 = (double)x2;
	_y1 = (double)y1;
	_y2 = (double)y2;
	_A = (double)y2 - y1;
	_B = (double)x1 - x2;
	_C = (double)y1 * x2 - (double)x1 * y2;
	if (x1 - x2 == 0) {
		_k = CSlope(true);
		_b = CBias(true);
	}
	else {
		_k = CSlope(-_A / _B);
		_b = CBias(-_C / _B);
	}
}

CLine::CLine(double A, double B, double C):CShape("Line"),_A(A),_B(B),_C(C)
{
	if (abs(B - 0) < EPS) {
		_k = CSlope(true);
		_b = CBias(true);
	}
	else {
		_k = CSlope(-_A / _B);
		_b = CBias(-_C / _B);
	}
}

bool CLine::operator==(const CLine & rhs) const
{
	return (abs(_A - rhs._A) < EPS && abs(_B - rhs._B) < EPS &&
		abs(_C - rhs._C) < EPS && _k == rhs._k);
}

CCircle::CCircle(int x0, int y0, int r) : CShape("Circle"), _x0(x0), _y0(y0), _r(r) 
{
	_D = -2 * _x0;
	_E = -2 * _y0;
	_F = _x0 * _x0 + _y0 * _y0 - _r * _r;
}

bool CLine::crossInRange(double cx, double cy) const
{
	if (type() == "Line") {
		return true;
	}
	else if (type() == "Ray") {
		if (k().isInf()) {
			if (dcmp(cy, y1())*dcmp(y2(), y1()) != -1) {
				return true;
			}
		}
		else {
			if (dcmp(cx, x1())*dcmp(x2(), x1()) != -1) {
				return true;
			}
		}
		return false;
	}
	else {
		if (k().isInf()) {
			if (dcmp(cy, y1())*dcmp(y2(), y1()) != -1 &&
				dcmp(cy, y2())*dcmp(y1(), y2()) != -1) {
				return true;
			}
		}
		else {
			if (dcmp(cx, x1())*dcmp(x2(), x1()) != -1 &&
				dcmp(cx, x2())*dcmp(x1(), x2()) != -1) {
				return true;
			}
		}
		return false;
	}
}



