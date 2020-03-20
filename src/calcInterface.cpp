#include "calcInterface.h"  
#include <sstream> 
using namespace std;

int guiProcess(vector<pair<double, double>>* points, string msg)
{
	int cnt = 0;
	try {
		CIntersect ins;
		istringstream in(msg);
		ins.inputShapes(in);
		cnt = ins.cntTotalInsPoint();
		std::unordered_set<CPoint, PointHash> pointsSet = ins.getInsPoints();
		for (auto sit = pointsSet.begin(); sit != pointsSet.end(); ++sit) {
			CPoint tmp = *sit;
			points->push_back(make_pair(tmp.x(), tmp.y()));
		}
	}
	catch (std::exception ex) {
		throw ex;
	}
	return cnt;
}

void cmdProcess(int argc, char* argv[]) {
	if (argc != 5) {
		cout << "Usage: intersect.exe -i input.txt -o output.txt\n";
		return;
	}
	string infile, outfile;
	if (strcmp(argv[1], "-i") == 0 && strcmp(argv[3], "-o") == 0) {
		infile = string(argv[2]);
		outfile = string(argv[4]);
	}
	else if (strcmp(argv[1], "-o") == 0 && strcmp(argv[3], "-i") == 0) {
		infile = string(argv[4]);
		outfile = string(argv[2]);
	}
	else {
		cout << "Usage: intersect.exe -i input.txt -o output.txt\n";
		return;
	}
	ifstream fin(infile);
	if (!fin) {
		cout << "input file cannot open\n";
		return;
	}
	CIntersect ins;
	ins.inputShapes(fin);
	int cnt = ins.cntTotalInsPoint();
	ofstream fout(outfile);
	fout << cnt;
	return;
}
