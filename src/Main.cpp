#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "intersect.h"
using namespace std;

int main(int argc, char** argv) {
	if (argc != 5) {
		cout << "Usage: intersect.exe -i input.txt -o output.txt\n";
		exit(0);
	}
	string infile, outfile;
	if (strcmp(argv[1], "-i") == 0 && strcmp(argv[3], "-o") == 0) {
		infile = string(argv[2]);
		outfile = string(argv[4]);
	}
	else if (strcmp(argv[1], "-o") == 0 && strcmp(argv[3], "-i") == 0){
		infile = string(argv[4]);
		outfile = string(argv[2]);
	}
	else {
		cout << "Usage: intersect.exe -i input.txt -o output.txt\n";
		exit(0);
	}
	
	ifstream fin(infile);

	if (!fin) {
		cout << "input file cannot open\n";
		exit(0);
	}
	clock_t tic = clock();
	CIntersect ins;
	try {
		ins.inputShapes(fin);
	}
	catch (InputHandlerException e) {
		cout << e.what() <<endl;
		exit(0);
	}

	int cnt = 0;
	try {
		cnt = ins.cntTotalInsPoint();
	}
	catch (exception e) {
		cout << e.what() <<endl;
	}
	ofstream fout(outfile);
	fout << cnt;
	cout << cnt << endl;
	clock_t toc = clock();
	cout << "time: " << ((double)toc - tic) * 1.0 / CLOCKS_PER_SEC << endl;
	exit(0);
	return 0;
}