#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "intersect.h"
using namespace std;

int main(int argc, char** argv) {
	string infile, outfile;
	if (strcmp(argv[1], "-i") == 0 && strcmp(argv[3], "-o") == 0) {
		infile = string(argv[2]);
		outfile = string(argv[4]);
	}
	else if (strcmp(argv[1], "-o") == 0 && strcmp(argv[3], "-i") == 0){
		infile = string(argv[4]);
		outfile = string(argv[2]);
	}
	ifstream fin(infile);
	clock_t tic = clock();
	CIntersect ins;
	ins.inputShapes(fin);
	int cnt = ins.cntTotalInsPoint();
	ofstream fout(outfile);
	fout << cnt;
	clock_t toc = clock();
	cout << "time: " << ((double)toc - tic) * 1.0 / CLOCKS_PER_SEC << endl;
	exit(0);
	return 0;
}