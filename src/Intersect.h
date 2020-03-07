#pragma once
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include "Shape.h"

class CIntersect {
private:
	std::vector<CLine> _lines;
	std::map<CSlope, std::set<CLine> > _k2lines;
	std::set<CCircle> _circles;
	std::map<CPoint, std::set<CShape> > _insp2shapes;

public:
	void inputShapes(std::istream& in);
	std::vector<CPoint> calcShapeInsPoint(const CShape&, const CShape&) const;
	int cntTotalInsPoint();
	std::map<CSlope, std::set<CLine> > getK2Lines() { return _k2lines; }
	std::map<CPoint, std::set<CShape> > getInsp2shapes() { return _insp2shapes; }
	std::vector<CLine> getLines() { return _lines; }
};