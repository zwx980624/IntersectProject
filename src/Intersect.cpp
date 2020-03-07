#include "Intersect.h"

using namespace std;

void CIntersect::inputShapes(std::istream& in) {
	int N;
	in >> N;
	while (N--) {
		string shape;
		int x1, y1, x2, y2;
		in >> shape >> x1 >> y1 >> x2 >> y2;
		if (shape == "L") {
			CLine line(x1, y1, x2, y2);
			_k2lines[line.k()].insert(line);
			_lines.push_back(line);
		}
	}
}

// calculate all intersect points of s1 and s2
// return the points as vector
// need: s1, s2 should be CLine or CCircle
std::vector<CPoint> CIntersect::calcShapeInsPoint(const CShape& s1, const CShape& s2) const
{
	if (s1.type() == "Line" && s2.type() == "Line") {
		if (s1.A()*s2.B() - s2.A()*s1.B() == 0) {
			return vector<CPoint>();
		}
		double x = (s2.C()*s1.B() - s1.C()*s2.B()) / (s1.A()*s2.B() - s2.A()*s1.B());
		double y = (s2.C()*s1.A() - s1.C()*s2.A()) / (s1.B()*s2.A() - s2.B()*s1.A());
		vector<CPoint> ret;
		ret.push_back(CPoint(x, y));
		return ret;
	}
}

// the main pipeline: loop the inputs and fill in _insp2shapes
// return the total count of intersect points
// need: _k2lines and _circles have been filled
int CIntersect::cntTotalInsPoint()
{
	vector<CLine> over;
	for (auto mit = _k2lines.begin(); mit != _k2lines.end(); ++mit) {
		set<CLine>& s = mit->second;
		for (set<CLine>::iterator sit = s.begin(); sit != s.end(); ++sit) {
			for (auto oit = over.begin(); oit != over.end(); ++oit) {
				CPoint point = calcShapeInsPoint(*sit, *oit)[0]; // must intersect
				_insp2shapes[point].insert(*sit);
			}
		}
		for (set<CLine>::iterator sit = s.begin(); sit != s.end(); ++sit) {
			over.push_back(*sit);
		}
	}
	return _insp2shapes.size();
}

