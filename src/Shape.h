#pragma once
#include <string>
#define EPS 1e-6

class CPoint {
private:
	double _x;
	double _y;

public:
	CPoint(double x, double y) :_x(x), _y(y) {}
	bool operator < (const CPoint & rhs) const;
	bool operator == (const CPoint & rhs) const;
	double x() { return _x; }
	double y() { return _y; }
};

class CShape {
private:
	int _id;
	static int _nextId;
	std::string _type;

public:
	CShape(std::string type);
	bool operator < (const CShape & rhs) const;
	std::string type() const { return _type; }
	virtual double A() const { return 0; }
	virtual double B() const { return 0; }
	virtual double C() const { return 0; }
};

class CSlope {
private:
	bool _isInf;
	double _k;

public:
	CSlope() :_isInf(false), _k(0.0) {}
	CSlope(double k) :_isInf(false), _k(k) {}
	CSlope(bool inf) :_isInf(inf), _k(0.0){}
	bool operator < (const CSlope & rhs) const;
	bool operator == (const CSlope & rhs) const;
};

class CLine: public CShape {
private:
	double _A;
	double _B;
	double _C;
	CSlope _k;
public:
	CLine(int x1, int y1, int x2, int y2);
	CLine(double A, double B, double C);
	CSlope k() { return _k; }
	bool operator == (const CLine & rhs) const; // A, B, C all equal
	virtual double A() const { return _A; }
	virtual double B() const  { return _B; }
	virtual double C() const  { return _C; }
};