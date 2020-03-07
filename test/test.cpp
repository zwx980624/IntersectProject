#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Intersect.h"
#include <iostream>
#include <fstream>
#include <vector>



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace test
{
	TEST_CLASS(test_input)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// one single line
			// 1
			// L 0 0 1 1
			CLine ans(1, -1, 0);
			ifstream fin("../test/test1.txt");
			if (!fin) {
				Assert::AreEqual(132,0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			map<CSlope, set<CLine> > k2lines = ins.getK2Lines();
			Assert::AreEqual((int)k2lines.size(), 1);
			Assert::AreEqual((int)k2lines[1.0].size(), 1);
			set<CLine> lines = k2lines[1.0];
			for (set<CLine>::iterator sit = lines.begin(); sit != lines.end(); ++sit) {
				Assert::AreEqual(true, ans==*sit);
			}
		}

		TEST_METHOD(TestMethod2)
		{
			// normal 3 lines 3 points
			// 3
			// L 0 0 1 1
			// L 1 0 0 1
			// L 1 2 2 0
			vector<CLine> ans;
			ans.push_back(CLine(-2, -1, 4));
			ans.push_back(CLine(1, 1, -1));
			ans.push_back(CLine(1, -1, 0));
			vector<CSlope> ans_slope;
			ans_slope.push_back(CSlope(-2.0));
			ans_slope.push_back(CSlope(-1.0));
			ans_slope.push_back(CSlope(1.0));
			ifstream fin("../test/test2.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			map<CSlope, set<CLine> > k2lines = ins.getK2Lines();
			Assert::AreEqual((int)k2lines.size(), 3);
			int i = 0;
			for (map<CSlope, set<CLine> >::iterator mit = k2lines.begin();
					mit != k2lines.end(); ++mit, ++i) {
				Assert::AreEqual(true, mit->first == ans_slope[i]);
				Assert::AreEqual((int)(mit->second.size()), 1);
				set<CLine> lines = mit->second;
				for (set<CLine>::iterator sit = lines.begin(); sit != lines.end(); ++sit) {
					Assert::AreEqual(true, ans[i] == *sit);
				}
			}
		}

		TEST_METHOD(TestMethod3)
		{
			// normal 3 intersect in 1 point
			// 3
			// L 0 0 1 1
			// L 0 0 0 1
			// L 0 0 -1 0
			vector<CLine> ans;
			ans.push_back(CLine(0, 1, 0));
			ans.push_back(CLine(1, -1, 0));
			ans.push_back(CLine(1, 0, 0));
			vector<CSlope> ans_slope;
			ans_slope.push_back(CSlope(0.0));
			ans_slope.push_back(CSlope(1.0));
			ans_slope.push_back(CSlope(true));
			ifstream fin("../test/test3.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			map<CSlope, set<CLine> > k2lines = ins.getK2Lines();
			Assert::AreEqual((int)k2lines.size(), 3);
			int i = 0;
			for (map<CSlope, set<CLine> >::iterator mit = k2lines.begin();
				mit != k2lines.end(); ++mit, ++i) {
				Assert::AreEqual(true, mit->first == ans_slope[i]);
				Assert::AreEqual((int)(mit->second.size()), 1);
				set<CLine> lines = mit->second;
				for (set<CLine>::iterator sit = lines.begin(); sit != lines.end(); ++sit) {
					Assert::AreEqual(true, ans[i] == *sit);
				}
			}
		}

		TEST_METHOD(TestMethod4)
		{
			// paralile
			// 4
			// L 0 0 0 1
			// L 0 0 1 1
			// L 1 0 1 2
			// L 1 0 2 1
			vector<CLine> ans;
			ans.push_back(CLine(1, -1, 0));
			ans.push_back(CLine(1, -1, -1));
			ans.push_back(CLine(1, 0, 0));
			ans.push_back(CLine(2, 0, -2));
			vector<CSlope> ans_slope;
			ans_slope.push_back(CSlope(1.0));
			ans_slope.push_back(CSlope(true));
			ifstream fin("../test/test4.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			map<CSlope, set<CLine> > k2lines = ins.getK2Lines();
			Assert::AreEqual((int)k2lines.size(), 2);
			int i = 0;
			int j = 0;
			for (map<CSlope, set<CLine> >::iterator mit = k2lines.begin();
									mit != k2lines.end(); ++mit, ++i) {
				Assert::AreEqual(true, mit->first == ans_slope[i]);
				Assert::AreEqual((int)(mit->second.size()), 2);
				set<CLine> lines = mit->second;
				for (set<CLine>::iterator sit = lines.begin(); 
								sit != lines.end(); ++sit, ++j) {
					Assert::AreEqual(true, ans[j] == *sit);
				}
			}
		}
	};

	TEST_CLASS(test_line_intersect)
	{
	public:
		TEST_METHOD(TestMethod2)
		{
			// normal 3 lines 3 points
			// 3
			// L 0 0 1 1
			// L 1 0 0 1
			// L 1 2 2 0
			vector<CPoint> ans;
			ans.push_back(CPoint(0.5,0.5));
			ans.push_back(CPoint(4./3, 4./3));
			ans.push_back(CPoint(3, -2));
			ifstream fin("../test/test2.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			vector<CLine> lines = ins.getLines();
			int k = 0;
			for (int i = 0; i != lines.size(); ++i) {
				for (int j = i + 1; j != lines.size(); ++j) {
					CPoint p = ins.calcShapeInsPoint(lines[i], lines[j])[0];
					Assert::AreEqual(true, ans[k] == p);
					k++;
				}
			}
		}

		TEST_METHOD(TestMethod3)
		{
			// normal 3 intersect in 1 point
			// 3
			// L 0 0 1 1
			// L 0 0 0 1
			// L 0 0 -1 0
			vector<CPoint> ans;
			ans.push_back(CPoint(0, 0));
			ans.push_back(CPoint(0, 0));
			ans.push_back(CPoint(0, 0));
			ifstream fin("../test/test3.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			vector<CLine> lines = ins.getLines();
			int k = 0;
			for (int i = 0; i != lines.size(); ++i) {
				for (int j = i + 1; j != lines.size(); ++j) {
					CPoint p = ins.calcShapeInsPoint(lines[i], lines[j])[0];
					Assert::AreEqual(true, ans[k] == p);
					k++;
				}
			}
		}

		TEST_METHOD(TestMethod4)
		{
			// paralile
			// 4
			// L 0 0 0 1
			// L 0 0 1 1
			// L 1 0 1 2
			// L 1 0 2 1
			int isInf[] = { 0,1,0,0,1,0 };
			vector<CPoint> ans;
			ans.push_back(CPoint(0, 0));
			ans.push_back(CPoint(0, -1));
			ans.push_back(CPoint(1, 1));
			ans.push_back(CPoint(1, 0));
			ifstream fin("../test/test4.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			vector<CLine> lines = ins.getLines();
			int k = 0;
			int kk = 0;
			for (int i = 0; i != lines.size(); ++i) {
				for (int j = i + 1; j != lines.size(); ++j) {
					vector<CPoint> p = ins.calcShapeInsPoint(lines[i], lines[j]);
					if (isInf[k] == 1) {
						Assert::AreEqual((int)p.size(), 0);
					}
					else {
						Assert::AreEqual(true, ans[kk] == p[0]);
						kk++;
					}
					k++;
				}
			}
		}
	};

	TEST_CLASS(test_cnt_intersect)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			// one single line
			// 1
			// L 0 0 1 1
			ifstream fin("../test/test1.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(0, cnt);
		}

		TEST_METHOD(TestMethod2)
		{
			// normal 3 lines 3 points
			// 3
			// L 0 0 1 1
			// L 1 0 0 1
			// L 1 2 2 0
			ifstream fin("../test/test2.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(3, cnt);
		}

		TEST_METHOD(TestMethod3)
		{
			// normal 3 intersect in 1 point
			// 3
			// L 0 0 1 1
			// L 0 0 0 1
			// L 0 0 -1 0
			ifstream fin("../test/test3.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(1, cnt);
		}

		TEST_METHOD(TestMethod4)
		{
			// paralile
			// 4
			// L 0 0 0 1
			// L 0 0 1 1
			// L 1 0 1 2
			// L 1 0 2 1
			ifstream fin("../test/test4.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(4, cnt);
		}

		TEST_METHOD(TestMethod5)
		{
			// paralile
			// 4
			// L 0 0 0 1
			// L 0 0 1 1
			// L 1 0 1 2
			// L 1 0 2 1
			ifstream fin("../test/test5.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(7, cnt);
		}

	};
}
