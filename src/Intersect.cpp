#include "Intersect.h"

using namespace std;

inline int dround(double x) {
	if (x < 0) {
		return (int)(x - 0.5);
	}
	else {
		return (int)(x + 0.5);
	}
}

void CIntersect::inputShapes(std::istream& in) {
	int N;
	in >> N;
	while (N--) {
		string shape;
		in >> shape;
		if (shape == "L") {
			int x1, y1, x2, y2;
			in >> x1 >> y1 >> x2 >> y2;
			CLine line(x1, y1, x2, y2);
			_k2lines[line.k()].push_back(line);
			_lines.push_back(line);
		}
		else if (shape == "R") {
			int x1, y1, x2, y2;
			in >> x1 >> y1 >> x2 >> y2;
			CLine ray(x1, y1, x2, y2, "Ray");
			pair<CSlope, CBias> kb = make_pair(ray.k(), ray.b());
			if (ray.k().isInf()) {
				kb = make_pair(ray.k(), CBias((double)x1));
			}
			vector<CLine> lines = _kb2lines[kb];
			for (int j = 0; j < lines.size(); j++) {
				CLine coverl = lines[j];
				int cx1 = dround(coverl.x1());
				int cy1 = dround(coverl.y1());
				int cx2 = dround(coverl.x2());
				int cy2 = dround(coverl.y2());
				if (coverl.type() == "Ray") {
					if (dcmp(cx1, x1) == 0 && dcmp(cy1, y1) == 0) {
						_insp2shapesId[CPoint(cx1, cy1)].push_back(coverl.id());
						_insp2shapesId[CPoint(cx1, cy1)].push_back(ray.id());
					}
				}
				else {
					if (dcmp(cx1, x1) == 0 && dcmp(cy1, y1) == 0) {
						_insp2shapesId[CPoint(cx1, cy1)].push_back(coverl.id());
						_insp2shapesId[CPoint(cx1, cy1)].push_back(ray.id());
					}
					if (dcmp(cx2, x1) == 0 && dcmp(cy2, y1) == 0) {
						_insp2shapesId[CPoint(cx2, cy2)].push_back(coverl.id());
						_insp2shapesId[CPoint(cx2, cy2)].push_back(ray.id());
					}
				}
			}
			_kb2lines[kb].push_back(ray);
			_k2lines[ray.k()].push_back(ray);
			_lines.push_back(ray);
		}
		else if (shape == "S") {
			int x1, y1, x2, y2;
			in >> x1 >> y1 >> x2 >> y2;
			CLine seg(x1, y1, x2, y2, "Seg");
			pair<CSlope, CBias> kb = make_pair(seg.k(), seg.b());
			if (seg.k().isInf()) {
				kb = make_pair(seg.k(), CBias((double)x1));
			}
			vector<CLine> lines = _kb2lines[kb];
			for (int j = 0; j < lines.size(); j++) {
				CLine coverl = lines[j];
				int cx1 = dround(coverl.x1());
				int cy1 = dround(coverl.y1());
				int cx2 = dround(coverl.x2());
				int cy2 = dround(coverl.y2());
				if (coverl.type() == "Ray") {
					if (dcmp(cx1, x1) == 0 && dcmp(cy1, y1) == 0) {
						_insp2shapesId[CPoint(cx1, cy1)].push_back(coverl.id());
						_insp2shapesId[CPoint(cx1, cy1)].push_back(seg.id());
					}
					if (dcmp(cx1, x2) == 0 && dcmp(cy1, y2) == 0) {
						_insp2shapesId[CPoint(cx1, cy1)].push_back(coverl.id());
						_insp2shapesId[CPoint(cx1, cy1)].push_back(seg.id());
					}
				}
				else {
					if (dcmp(cx1, x1) == 0 && dcmp(cy1, y1) == 0) {
						_insp2shapesId[CPoint(cx1, cy1)].push_back(coverl.id());
						_insp2shapesId[CPoint(cx1, cy1)].push_back(seg.id());
					}
					if (dcmp(cx1, x2) == 0 && dcmp(cy1, y2) == 0) {
						_insp2shapesId[CPoint(cx1, cy1)].push_back(coverl.id());
						_insp2shapesId[CPoint(cx1, cy1)].push_back(seg.id());
					}
					if (dcmp(cx2, x1) == 0 && dcmp(cy2, y1) == 0) {
						_insp2shapesId[CPoint(cx2, cy2)].push_back(coverl.id());
						_insp2shapesId[CPoint(cx2, cy2)].push_back(seg.id());
					}
					if (dcmp(cx2, x2) == 0 && dcmp(cy2, y2) == 0) {
						_insp2shapesId[CPoint(cx2, cy2)].push_back(coverl.id());
						_insp2shapesId[CPoint(cx2, cy2)].push_back(seg.id());
					}
				}
			}
			_kb2lines[kb].push_back(seg);
			_k2lines[seg.k()].push_back(seg);
			_lines.push_back(seg);
		}
		else {
			int x0, y0, r;
			in >> x0 >> y0 >> r;
			CCircle circ(x0, y0, r);
			_circles.push_back(circ);
		}
	}
}

// calculate Intersections of one circ and one line
// need: para1 is CCirc, para2 is CLine
// return a vector of intersections. size can be 0,1,2.
std::vector<CPoint> calcInsCircLine(const CShape& circ, const CShape& line)
{
	if (line.k().isInf()) {
		vector<CPoint> ret;
		double xc = -line.C() / line.A();
		double x0 = circ.x0();
		double y0 = circ.y0();
		double d = abs(xc - x0);
		double r = circ.r();
		if (d - r > EPS) { // not intersect 
			return ret;
		}
		else if (d - r > -EPS) { // tangent 
			ret.push_back(CPoint(xc, y0));
			return ret;
		}
		else {
			double n = sqrt(r * r - d * d);
			ret.push_back(CPoint(xc, y0 + n));
			ret.push_back(CPoint(xc, y0 - n));
			return ret;
		}
	}
	else if (abs(line.k().val() - 0.0) < EPS) {
		vector<CPoint> ret;
		double yc = -line.C() / line.B();
		double x0 = circ.x0();
		double y0 = circ.y0();
		double d = abs(yc - y0);
		double r = circ.r();
		if (d - r > EPS) { // not intersect 
			return ret;
		}
		else if (d - r > -EPS) { // tangent 
			ret.push_back(CPoint(x0, yc));
			return ret;
		}
		else {
			double n = sqrt(r * r - d * d);
			ret.push_back(CPoint(x0 + n, yc));
			ret.push_back(CPoint(x0 - n, yc));
			return ret;
		}
	}
	else {
		vector<CPoint> ret;
		double k = line.k().val();
		double x0 = circ.x0();
		double y0 = circ.y0();
		double b1 = line.b().val();
		double d_2 = (k * x0 - y0 + b1) * (k * x0 - y0 + b1) / (1 + k * k);
		double d = sqrt(d_2);
		double n;
		if (d - circ.r() > EPS) { // not intersect
			return ret;
		}
		else if (circ.r() - d < EPS){ // tangent
			n = 0.0;
		}
		else { // intersect 
			n = sqrt(circ.r() * circ.r() - d_2);
		}
		double b2 = x0 / k + y0;
		double xc = (b2 - b1) / (k + 1 / k);
		double yc = (k * b2 + b1 / k) / (k + 1 / k);
		double x1 = xc + n  / sqrt(1 + k * k);
		double x2 = xc - n  / sqrt(1 + k * k);
		double y1 = yc + n * k / sqrt(1 + k * k);
		double y2 = yc - n * k / sqrt(1 + k * k);
		ret.push_back(CPoint(x1, y1));
		ret.push_back(CPoint(x2, y2));
		return ret;
	}
}

// calculate all intersect points of s1 and s2
// return the points as vector
// need: s1, s2 should be CLine or CCircle.
// special need: if s1, s2 are CLine. They cannot be parallel.
std::vector<CPoint> CIntersect::calcShapeInsPoint(const CShape& s1, const CShape& s2) const
{
	if (s1.typeLine() && s2.typeLine()) {
		//if (s1.A()*s2.B() - s2.A()*s1.B() == 0) {
		//	return vector<CPoint>();
		//}
		double x = (s2.C()*s1.B() - s1.C()*s2.B()) / (s1.A()*s2.B() - s2.A()*s1.B());
		double y = (s2.C()*s1.A() - s1.C()*s2.A()) / (s1.B()*s2.A() - s2.B()*s1.A());
		vector<CPoint> ret;
		if (s1.crossInRange(x, y) && s2.crossInRange(x, y)) {
			ret.push_back(CPoint(x, y));
		}
		return ret;
	}
	else {
		if (s1.type() == "Circle" && s2.typeLine()) {
			std::vector<CPoint> ret;
			std::vector<CPoint> get = calcInsCircLine(s1, s2);
			for (int i = 0; i < get.size(); ++i) {
				if (s2.crossInRange(get[i].x(), get[i].y())) {
					ret.push_back(get[i]);
				}
			}
			return ret;
		}
		else if (s1.typeLine() && s2.type() == "Circle") {
			std::vector<CPoint> ret;
			std::vector<CPoint> get = calcInsCircLine(s2, s1);
			for (int i = 0; i < get.size(); ++i) {
				if (s1.crossInRange(get[i].x(), get[i].y())) {
					ret.push_back(get[i]);
				}
			}
			return ret;
		}
		else { // 2 circles
			CLine line(s1.D() - s2.D(), s1.E() - s2.E(), s1.F() - s2.F());
			return calcInsCircLine(s1, line);
		}
	}
}

// the main pipeline: loop the inputs and fill in _insp2shapes or _insPoints
// return the total count of intersect points
// need: _k2lines and _circles have been filled
int CIntersect::cntTotalInsPoint()
{
	// lines first
	vector<CLine> over;
	vector<CCircle> circ_over;
	for (auto mit = _k2lines.begin(); mit != _k2lines.end(); ++mit) {
		vector<CLine>& s = mit->second;
		for (auto sit = s.begin(); sit != s.end(); ++sit) {
			// trick: If the cross point already exists, 
			//        we can cut calculation with other lines crossing this point.
			set<int> can_skip_id; // use this to record which line do not need calculate.
			for (auto oit = over.begin(); oit != over.end(); ++oit) {
				if (can_skip_id.find(oit->id()) == can_skip_id.end()) { // cannot skip
					auto vpoint = calcShapeInsPoint(*sit, *oit);
					if (vpoint.size() != 0) {
						CPoint point = calcShapeInsPoint(*sit, *oit)[0]; 
						if (_insp2shapesId.find(point) == _insp2shapesId.end()) { // new cross point
							_insp2shapesId[point].push_back(sit->id());
							_insp2shapesId[point].push_back(oit->id());
						}
						else { // cross point already exists
							vector<int>& sl = _insp2shapesId[point];
							can_skip_id.insert(sl.begin(), sl.end());
							_insp2shapesId[point].push_back(sit->id());
						}
					}
				}
			}
		}
		over.insert(over.end(), s.begin(), s.end());
	}


	for (auto mit = _insp2shapesId.begin(); mit != _insp2shapesId.end(); ++mit) {
		_insPoints.insert(mit->first);
	}

	// circles violent loop
	for (auto sit = _circles.begin(); sit != _circles.end(); ++sit) {
		for (auto oit = over.begin(); oit != over.end(); ++oit) {
			vector<CPoint> points = calcShapeInsPoint(*sit, *oit);
			for (auto pit = points.begin(); pit != points.end(); ++pit) {
				_insPoints.insert(*pit);
			}
		}
		for (auto oit = circ_over.begin(); oit != circ_over.end(); ++oit) {
			vector<CPoint> points = calcShapeInsPoint(*sit, *oit);
			for (auto pit = points.begin(); pit != points.end(); ++pit) {
				_insPoints.insert(*pit);
			}
		}
		circ_over.push_back(*sit);
	}

	if (_circles.size() != 0) {
		return _insPoints.size();
	}
	else {
		return _insp2shapesId.size();
	}
}

