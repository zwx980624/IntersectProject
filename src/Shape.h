#pragma once
#include <string>
#define EPS 1e-8

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
	bool isInf() const { return _isInf; }
	double val() const { return _k; }
};

class CBias {
private:
	bool _isNan;
	double _b;
public:
	CBias() :_isNan(false), _b(0.0) {}
	CBias(double b) :_isNan(false), _b(b) {}
	CBias(bool nan) :_isNan(nan), _b(0.0) {}
	bool isNan() const { return _isNan; }
	double val() const { return _b; }
};

class CShape {
private:
	int _id;
	static int _nextId;
	std::string _type;

public:
	CShape(std::string type);
	bool operator < (const CShape & rhs) const;
	inline std::string type() const { return _type; }
	inline virtual double A() const { return 0; }
	inline virtual double B() const { return 0; }
	inline virtual double C() const { return 0; }
	inline virtual double x0() const { return 0; }
	inline virtual double y0() const { return 0; }
	inline virtual double r() const { return 0; }
	inline virtual double D() const { return 0; }
	inline virtual double E() const { return 0; }
	inline virtual double F() const { return 0; }
	inline virtual CSlope k() const { return CSlope(0.0); }
	inline virtual CBias b() const { return CBias(0.0); }
	inline int id() const { return _id; }
};

class CLine: public CShape {
private:
	double _A;
	double _B;
	double _C;
	CSlope _k;
	CBias  _b;
public:
	CLine(int x1, int y1, int x2, int y2);
	CLine(double A, double B, double C);
	inline virtual CSlope k() const { return _k; }
	inline virtual CBias b() const { return _b; }
	bool operator == (const CLine & rhs) const; // A, B, C all equal
	inline virtual double A() const { return _A; }
	inline virtual double B() const  { return _B; }
	inline virtual double C() const  { return _C; }
};

class CCircle : public CShape {
private:
	double _x0;
	double _y0;
	double _r;
	double _D;
	double _E;
	double _F;
public:
	CCircle(int x0, int y0, int r);
	inline virtual double x0() const { return _x0; }
	inline virtual double y0() const { return _y0; }
	inline virtual double r() const { return _r; }
	inline virtual double D() const { return _D; }
	inline virtual double E() const { return _E; }
	inline virtual double F() const { return _F; }
};