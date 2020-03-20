#include "calcInterface.h"  
#include <sstream> 
using namespace std;

int guiProcess(vector<pair<double, double>>* points, string msg)
{
	int cnt = 0;
	try {
		CIntersect ins;
		istringstream in(msg);
		try
		{
			ins.inputShapes(in);
		}
		catch (InputHandlerException e)
		{
			exception stde = exception(e.what());
			throw stde;
		}
		cnt = ins.cntTotalInsPoint();
		std::unordered_set<CPoint, PointHash> pointsSet = ins.getInsPoints();
		for (auto sit = pointsSet.begin(); sit != pointsSet.end(); ++sit) {
			CPoint tmp = *sit;
			points->push_back(make_pair(tmp.x(), tmp.y()));
		}
	}
	catch (exception e) {
		throw e;
	}
	return cnt;
}



void cmdProcess(int argc, char* argv[]) {
	try {
		if (argc != 5) {
			cout << "Usage: intersect.exe -i input.txt -o output.txt\n";
			exception stde = exception("Usage: intersect.exe -i input.txt -o output.txt\n");
			throw stde;
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
			exception stde = exception("Usage: intersect.exe -i input.txt -o output.txt\n");
			throw stde;
		}
		ifstream fin(infile);
		if (!fin) {
			cout << "input file cannot open\n";
			exception stde = exception("input file cannot open\n");
			throw stde;
		}
		CIntersect ins;
		try {
			ins.inputShapes(fin);
		}
		catch (InputHandlerException e) {
			exception stde = exception(e.what());
			throw stde;
		}
		int cnt = ins.cntTotalInsPoint();
		ofstream fout(outfile);
		fout << cnt;
		return;
	}
	catch (exception se) {
		throw se;
	}
	return;
}
