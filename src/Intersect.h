#pragma once
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "Shape.h"
#include "myException.h"
#define lrange -100000
#define rrange 100000


class CIntersect {
private:
	std::vector<CLine> _lines;
	std::unordered_map<CSlope, std::vector<CLine>, SlopeHash> _k2lines;
	std::vector<CCircle> _circles;
	//std::map<CPoint, std::vector<int>> _insp2shapesId;
	std::unordered_map<CPoint, std::vector<int>, PointHash > _insp2shapesId;
	std::unordered_set<CPoint, PointHash> _insPoints;
	std::unordered_map<std::string, int> _shapes;
	std::unordered_map<std::pair<CSlope, CBias>, std::vector<CLine>, KbHash> _kb2lines;

public:
	void inputShapes(std::istream& in);
	std::vector<CPoint> calcShapeInsPoint(const CShape&, const CShape&) const;
	int cntTotalInsPoint();
	//std::map<CSlope, std::set<CLine>> getK2Lines() { return _k2lines; }
	//std::map<CPoint, std::set<CShape>> getInsp2shapes() { return _insp2shapes; }
	std::vector<CLine> getLines() { return _lines; }
	std::unordered_set<CPoint, PointHash> getInsPoints() { return _insPoints; }
	bool addShapes(string shape);
};
