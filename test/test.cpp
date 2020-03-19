#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Intersect.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace test
{
	/*TEST_CLASS(test_input)
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
*/
		/*TEST_METHOD(TestMethod4)
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
		}*/
//	};

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
			// zonghe
			// 5
			// L - 14 - 4 20 2
			// L - 2 0 - 2 4
			// L - 12 0 4 0
			// L - 6 - 2 14 8
			// L - 14 - 2 20 4

			ifstream fin("../test/test5.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(7, cnt);
		}

		TEST_METHOD(TestMethod6)
		{
			// limit slope
			// 5
			// L - 99999 99999 - 99999 - 99999
			// L 99998 99999 99999 - 99999
			// L - 99998 99999 - 99999 - 99999
			// L 99999 99999 - 99999 99999
			// L 99999 - 99999 - 99999 - 99998
			ifstream fin("../test/test6.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(10, cnt);
		}
		
		TEST_METHOD(TestMethod7)
		{
			// line + circ, eazy
			// 2
			// L 0 0 1 1
			// C 0 0 1
			ifstream fin("../test/test7.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(2, cnt);
		}

		TEST_METHOD(TestMethod8)
		{
			// medium line + circ
			// 4
			// C 1 0 2
			// C 2 2 1
			// C 3 - 2 6
			// L - 1 4 4 - 1
			ifstream fin("../test/test8.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(6, cnt);
		}
		TEST_METHOD(TestMethod9)
		{
			// tangetn
			// 6
			// C 0 0 10
			// C 4 3 5
			// C - 5 0 5
			// L 2 14 14 - 2
			// L 0 0 0 1
			// L - 10 0 - 10 1

			ifstream fin("../test/test9.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(9, cnt);
		}
		TEST_METHOD(TestMethod10)
		{
			//1000cases
			ifstream fin("../test/test10.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(433579, cnt);
		}
		TEST_METHOD(TestMethod11)
		{
			// circles
			ifstream fin("../test/test11.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(10, cnt);
		}

		TEST_METHOD(TestMethod14)
		{
			// circles
			ifstream fin("../test/test14.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(1, cnt);
		}
		TEST_METHOD(TestMethod15)
		{
			// circles
			ifstream fin("../test/test15.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(5, cnt);
		}

		TEST_METHOD(TestMethod16)
		{
			CLine t1 = CLine(0, 0, 0, 1, "Ray");
			CCircle c = CCircle(0, 0, 2);
			CIntersect ins;
			std::vector<CPoint> ans;
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(0, 2) == ans[0]);

			t1 = CLine(0, 0, 1, 0, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);

			t1 = CLine(0, 0, 1, 1, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(sqrt(2), sqrt(2)) == ans[0]);


			t1 = CLine(0, 0, 0, -1, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(0, -2) == ans[0]);


			t1 = CLine(0, 0, -1, 0, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(-2, 0) == ans[0]);

			t1 = CLine(0, 0, -1, -1, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(-sqrt(2), -sqrt(2)) == ans[0]);

		}

		TEST_METHOD(TestMethod17)
		{

			CCircle c = CCircle(0, 0, 2);
			CIntersect ins;
			std::vector<CPoint> ans;

			CLine t1 = CLine(0, 3, 0, 0, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(2, (int)ans.size());
			Assert::AreEqual(true, CPoint(0, 2) == ans[0]);
			Assert::AreEqual(true, CPoint(0, -2) == ans[1]);

			t1 = CLine(3, 0, 0, 0, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(2, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);
			Assert::AreEqual(true, CPoint(-2, 0) == ans[1]);

			t1 = CLine(2, 2, 0, 0, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(2, (int)ans.size());
			Assert::AreEqual(true, CPoint(sqrt(2), sqrt(2)) == ans[0]);
			Assert::AreEqual(true, CPoint(-sqrt(2), -sqrt(2)) == ans[1]);
		}

		TEST_METHOD(TestMethod18)
		{

			CCircle c = CCircle(0, 0, 2);
			CIntersect ins;
			std::vector<CPoint> ans;

			CLine t1 = CLine(2, 2, -2, 2, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(0, 2) == ans[0]);

			t1 = CLine(2, 2, 2, -2, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);

			t1 = CLine(2, 2, 3, 3, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(0, (int)ans.size());

			t1 = CLine(2, 0, 0, 0, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(2, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);
			Assert::AreEqual(true, CPoint(-2, 0) == ans[1]);

			t1 = CLine(2, 0, 3, 0, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);

			t1 = CLine(2, 0, 2, 2, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);
		}

		TEST_METHOD(TestMethod19)
		{
			CLine t1 = CLine(0, 0, 0, 1, "Ray");
			CCircle c = CCircle(0, 0, 2);
			CIntersect ins;
			std::vector<CPoint> ans;
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(0, 2) == ans[0]);

			t1 = CLine(0, 0, 1, 0, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);

			t1 = CLine(0, 0, 1, 1, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(sqrt(2), sqrt(2)) == ans[0]);


			t1 = CLine(0, 0, 0, -1, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(0, -2) == ans[0]);


			t1 = CLine(0, 0, -1, 0, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(-2, 0) == ans[0]);

			t1 = CLine(0, 0, -1, -1, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(-sqrt(2), -sqrt(2)) == ans[0]);

		}

		TEST_METHOD(TestMethod20)
		{

			CCircle c = CCircle(0, 0, 2);
			CIntersect ins;
			std::vector<CPoint> ans;

			CLine t1 = CLine(0, 3, 0, 0, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(2, (int)ans.size());
			Assert::AreEqual(true, CPoint(0, 2) == ans[0]);
			Assert::AreEqual(true, CPoint(0, -2) == ans[1]);

			t1 = CLine(3, 0, 0, 0, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(2, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);
			Assert::AreEqual(true, CPoint(-2, 0) == ans[1]);

			t1 = CLine(2, 2, 0, 0, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(2, (int)ans.size());
			Assert::AreEqual(true, CPoint(sqrt(2), sqrt(2)) == ans[0]);
			Assert::AreEqual(true, CPoint(-sqrt(2), -sqrt(2)) == ans[1]);
		}

		TEST_METHOD(TestMethod21)
		{

			CCircle c = CCircle(0, 0, 2);
			CIntersect ins;
			std::vector<CPoint> ans;

			CLine t1 = CLine(2, 2, -2, 2, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(0, 2) == ans[0]);

			t1 = CLine(2, 2, 2, -2, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);

			t1 = CLine(2, 2, 3, 3, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(0, (int)ans.size());

			t1 = CLine(2, 0, 0, 0, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(2, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);
			Assert::AreEqual(true, CPoint(-2, 0) == ans[1]);

			t1 = CLine(2, 0, 3, 0, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);

			t1 = CLine(2, 0, 2, 2, "Ray");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);
		}

		TEST_METHOD(TestMethod22)
		{

			CCircle c = CCircle(0, 0, 2);
			CIntersect ins;
			std::vector<CPoint> ans;

			CLine t1 = CLine(0, 0, 1, 1, "Seg");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(0, (int)ans.size());

			t1 = CLine(0, 3, 0, 4, "Seg");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(0, (int)ans.size());

			t1 = CLine(0, 3, 1, 3, "Seg");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(0, (int)ans.size());

		}

		TEST_METHOD(TestMethod23)
		{
			CCircle c = CCircle(0, 0, 2);
			CIntersect ins;
			std::vector<CPoint> ans;

			CLine t1 = CLine(0, 2, 0, 0, "Seg");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(0, 2) == ans[0]);

			t1 = CLine(0, 2, 0, 3, "Seg");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(0, 2) == ans[0]);

			t1 = CLine(0, 2, 2, 2, "Seg");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(0, 2) == ans[0]);


			t1 = CLine(-2, 2, 2, 2, "Seg");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(0, 2) == ans[0]);

			t1 = CLine(2, 2, 2, -2, "Seg");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);

			t1 = CLine(2, 2, 2, -2, "Seg");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);

			t1 = CLine(0, 0, 3, 3, "Seg");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(1, (int)ans.size());
			Assert::AreEqual(true, CPoint(sqrt(2), sqrt(2)) == ans[0]);

		}

		TEST_METHOD(TestMethod24)
		{

			CCircle c = CCircle(0, 0, 2);
			CIntersect ins;
			std::vector<CPoint> ans;

			CLine t1 = CLine(0, 2, 0, -2, "Seg");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(2, (int)ans.size());
			Assert::AreEqual(true, CPoint(0, 2) == ans[0]);
			Assert::AreEqual(true, CPoint(0, -2) == ans[1]);

			t1 = CLine(2, 0, -2, 0, "Seg");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(2, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);
			Assert::AreEqual(true, CPoint(-2, 0) == ans[1]);


			t1 = CLine(2, 0, 0, 2, "Seg");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(2, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);
			Assert::AreEqual(true, CPoint(0, 2) == ans[1]);

			t1 = CLine(0, 3, 0, -3, "Seg");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(2, (int)ans.size());
			Assert::AreEqual(true, CPoint(0, 2) == ans[0]);
			Assert::AreEqual(true, CPoint(0, -2) == ans[1]);

			t1 = CLine(3, 0, -3, 0, "Seg");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(2, (int)ans.size());
			Assert::AreEqual(true, CPoint(2, 0) == ans[0]);
			Assert::AreEqual(true, CPoint(-2, 0) == ans[1]);

			t1 = CLine(3, 3, -3, -3, "Seg");
			ans = ins.calcShapeInsPoint(c, t1);
			Assert::AreEqual(2, (int)ans.size());
			Assert::AreEqual(true, CPoint(sqrt(2), sqrt(2)) == ans[0]);
			Assert::AreEqual(true, CPoint(-sqrt(2), -sqrt(2)) == ans[1]);
		}

		TEST_METHOD(TestMethod25)
		{
			// paralile
			// 4
			// L 0 0 0 1
			// L 0 0 1 1
			// L 1 0 1 2
			// L 1 0 2 1
			ifstream fin("../test/test19.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(1, cnt);
		}

		TEST_METHOD(TestMethod26)
		{
			// paralile
			// 4
			// L 0 0 0 1
			// L 0 0 1 1
			// L 1 0 1 2
			// L 1 0 2 1
			ifstream fin("../test/test20.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(1, cnt);
		}

		TEST_METHOD(TestMethod27)
		{
			// paralile
			// 4
			// L 0 0 0 1
			// L 0 0 1 1
			// L 1 0 1 2
			// L 1 0 2 1
			ifstream fin("../test/test21.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(1, cnt);
		}

		TEST_METHOD(TestMethod28)
		{
			// paralile
			// 4
			// L 0 0 0 1
			// L 0 0 1 1
			// L 1 0 1 2
			// L 1 0 2 1
			ifstream fin("../test/test22.txt");
			if (!fin) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			ins.inputShapes(fin);
			int cnt = ins.cntTotalInsPoint();
			Assert::AreEqual(10, cnt);
		}
	};

	TEST_CLASS(test_exception) {
		TEST_METHOD(TestMethod_RR1)
		{
			string strin = "2\nR 0 0 5 5\nR 6 6 -1 -1\n";
			ShapeCoverException s(2, "R 6 6 -1 -1", "R 0 0 5 5");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_RR2)
		{
			string strin = "2\nR 0 0 1 1\nR 2 2 6 6\n";
			ShapeCoverException s(2, "R 2 2 6 6", "R 0 0 1 1");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_RR4)
		{
			string strin = "2\nR 0 0 0 1\nR 0 -2 0 1\n";
			ShapeCoverException s(2, "R 0 -2 0 1", "R 0 0 0 1");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_RR5)
		{
			string strin = "2\nR 0 0 1 0\nR -2 0 -1 0\n";
			ShapeCoverException s(2, "R -2 0 -1 0", "R 0 0 1 0");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_SS1)
		{
			string strin = "3\nS 0 -1 0 1\nS 0 3 0 6\nS 0 0 0 2\n";
			ShapeCoverException s(3, "S 0 0 0 2", "S 0 -1 0 1");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_SS2)
		{
			string strin = "3\nS 0 -1 0 1\nS 0 3 0 6\nS 0 0 0 -2\n";
			ShapeCoverException s(3, "S 0 0 0 -2", "S 0 -1 0 1");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_SS3)
		{
			string strin = "3\nS 0 -1 0 1\nS 0 3 0 6\nS 0 4 0 5\n";
			ShapeCoverException s(3, "S 0 4 0 5", "S 0 3 0 6");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_SS4)
		{
			string strin = "3\nS 0 -1 0 1\nS 0 3 0 6\nS 0 8 0 2\n";
			ShapeCoverException s(3, "S 0 8 0 2", "S 0 3 0 6");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_SS5)
		{
			string strin = "3\nS -1 0 1 0\nS 3 0 6 0\nS 0 0 2 0\n";
			ShapeCoverException s(3, "S 0 0 2 0", "S -1 0 1 0");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_SS6)
		{
			string strin = "3\nS -1 0 1 0\nS 3 0 6 0\nS 0 0 -2 0\n";
			ShapeCoverException s(3, "S 0 0 -2 0", "S -1 0 1 0");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_SS7)
		{
			string strin = "3\nS -1 0 1 0\nS 3 0 6 0\nS 4 0 5 0\n";
			ShapeCoverException s(3, "S 4 0 5 0", "S 3 0 6 0");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_SS8)
		{
			string strin = "3\nS -1 0 1 0\nS 3 0 6 0\nS 8 0 2 0\n";
			ShapeCoverException s(3, "S 8 0 2 0", "S 3 0 6 0");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_SR1)
		{
			string strin = "3\nS 0 0 0 4\nS 0 0 4 0\nR 0 -2 0 -1";
			ShapeCoverException s(3, "R 0 -2 0 -1", "S 0 0 0 4");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_SR2)
		{
			string strin = "3\nS 0 0 0 4\nS 0 0 4 0\nR 0 0 0 1";
			ShapeCoverException s(3, "R 0 0 0 1", "S 0 0 0 4");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_SR3)
		{
			string strin = "3\nS 0 0 0 4\nS 0 0 4 0\nR 0 0 1 0";
			ShapeCoverException s(3, "R 0 0 1 0", "S 0 0 4 0");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_SR4)
		{
			string strin = "3\nS 0 0 0 4\nS 0 0 4 0\nR -2 0 -1 0";
			ShapeCoverException s(3, "R -2 0 -1 0", "S 0 0 4 0");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_RS1)
		{
			string strin = "3\nS 0 0 4 0\nR 0 -2 0 -1\nS 0 0 0 4";
			ShapeCoverException s(3, "S 0 0 0 4", "R 0 -2 0 -1");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_RS2)
		{
			string strin = "3\nS 0 0 4 0\nR 0 0 0 1\nS 0 0 0 4";
			ShapeCoverException s(3, "S 0 0 0 4", "R 0 0 0 1");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_RS3)
		{
			string strin = "3\nS 0 0 0 4\nR 0 0 1 0\nS 0 0 4 0";
			ShapeCoverException s(3, "S 0 0 4 0", "R 0 0 1 0");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_RS4)
		{
			string strin = "3\nR -2 0 -1 0\nS 0 0 0 4\nS 0 0 4 0";
			ShapeCoverException s(3, "S 0 0 4 0", "R -2 0 -1 0");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_N0)
		{
			string strin = "";
			ShapeNumberException s("Can't read Correct N. The fisrt line should be an Integer in [1, 500000]");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_N1)
		{
			string strin = "C 1 2 3\nL 1 2 3";
			ShapeNumberException s("Can't read Correct N. The fisrt line should be an Integer in [1, 500000]");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_N2)
		{
			string strin = "100000000000000000";
			ShapeNumberException s("Can't read Correct N. The fisrt line should be an Integer in [1, 500000]");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_N3)
		{
			string strin = "10000000";
			ShapeNumberException s("N is out of range. The fisrt line should be an Integer in [1, 500000]");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_N4)
		{
			string strin = "0";
			ShapeNumberException s("N is out of range. The fisrt line should be an Integer in [1, 500000]");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_N5)
		{
			string strin = "3";
			ShapeNumberException s("The number of graphics is less than N.");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}

		TEST_METHOD(TestMethod_N6)
		{
			string strin = "1\nL 1 2 3 4\nC 1 1 2";
			ShapeNumberException s("The number of graphics is larger than N.");
			InputHandlerException std = s;
			istringstream in(strin);
			if (!in) {
				Assert::AreEqual(132, 0);
			}
			CIntersect ins;
			try {
				ins.inputShapes(in);
				Assert::AreEqual(132, 0);
			}
			catch (InputHandlerException e) {
				Assert::AreEqual(true, strcmp(std.what(), e.what()) == 0);
				//Assert::AreEqual(true, std.what() == t2);
			}
		}
	};
}
