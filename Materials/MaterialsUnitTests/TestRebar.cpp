#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Materials;

namespace MaterialsUnitTest
{
	TEST_CLASS(TestRebar)
	{
	public:
		
		TEST_METHOD(Test)
		{
			Rebar bar(_T("BarName"), Rebar::Grade::Grade60, Rebar::Type::A615, Rebar::Size::bs3);
			Assert::AreEqual(_T("BarName"), bar.GetName().c_str());
			Assert::IsTrue(Rebar::Grade::Grade60 == bar.GetGrade());
			Assert::IsTrue(Rebar::Type::A615 == bar.GetType());
			Assert::IsTrue(Rebar::Size::bs3 == bar.GetSize());

			Assert::AreEqual(0.0095249999999999987, bar.GetNominalDimension());
			Assert::AreEqual(7.0967600000000001e-05, bar.GetNominalArea());
			Assert::AreEqual(620528156.38530004, bar.GetUltimateStrength());
			Assert::AreEqual(413685437.59020001, bar.GetYieldStrength());
			Assert::AreEqual(199947961501.93002, bar.GetE());
			Assert::AreEqual(0.09, bar.GetElongation(), 0.00001);
		}

		TEST_METHOD(UltimateStrength)
		{
			Assert::AreEqual(-1.0, Rebar::GetUltimateStrength(Rebar::Type::A1035, Rebar::Grade::Grade40));
			Assert::AreEqual(-1.0, Rebar::GetUltimateStrength(Rebar::Type::A1035, Rebar::Grade::Grade60));
			Assert::AreEqual(-1.0, Rebar::GetUltimateStrength(Rebar::Type::A1035, Rebar::Grade::Grade75));
			Assert::AreEqual(-1.0, Rebar::GetUltimateStrength(Rebar::Type::A1035, Rebar::Grade::Grade80));
			Assert::AreEqual(1034213593.9755001, Rebar::GetUltimateStrength(Rebar::Type::A1035, Rebar::Grade::Grade100));
			Assert::AreEqual(1034213593.9755001, Rebar::GetUltimateStrength(Rebar::Type::A1035, Rebar::Grade::Grade120));

			Assert::AreEqual(413685437.59020001, Rebar::GetUltimateStrength(Rebar::Type::A615, Rebar::Grade::Grade40));
			Assert::AreEqual(620528156.38530004, Rebar::GetUltimateStrength(Rebar::Type::A615, Rebar::Grade::Grade60));
			Assert::AreEqual(689475729.31700003, Rebar::GetUltimateStrength(Rebar::Type::A615, Rebar::Grade::Grade75));
			Assert::AreEqual(723949515.78285003, Rebar::GetUltimateStrength(Rebar::Type::A615, Rebar::Grade::Grade80));
			Assert::AreEqual(-1.0, Rebar::GetUltimateStrength(Rebar::Type::A615, Rebar::Grade::Grade100));
			Assert::AreEqual(-1.0, Rebar::GetUltimateStrength(Rebar::Type::A615, Rebar::Grade::Grade120));

			Assert::AreEqual(-1.0, Rebar::GetUltimateStrength(Rebar::Type::A706, Rebar::Grade::Grade40));
			Assert::AreEqual(551580583.45360005, Rebar::GetUltimateStrength(Rebar::Type::A706, Rebar::Grade::Grade60));
			Assert::AreEqual(-1.0, Rebar::GetUltimateStrength(Rebar::Type::A706, Rebar::Grade::Grade75));
			Assert::AreEqual(689475729.31700003, Rebar::GetUltimateStrength(Rebar::Type::A706, Rebar::Grade::Grade80));
			Assert::AreEqual(-1.0, Rebar::GetUltimateStrength(Rebar::Type::A706, Rebar::Grade::Grade100));
			Assert::AreEqual(-1.0, Rebar::GetUltimateStrength(Rebar::Type::A706, Rebar::Grade::Grade120));
		}

		TEST_METHOD(YieldStrength)
		{
			Assert::AreEqual(-1.0, Rebar::GetYieldStrength(Rebar::Type::A1035, Rebar::Grade::Grade40));
			Assert::AreEqual(-1.0, Rebar::GetYieldStrength(Rebar::Type::A1035, Rebar::Grade::Grade60));
			Assert::AreEqual(-1.0, Rebar::GetYieldStrength(Rebar::Type::A1035, Rebar::Grade::Grade75));
			Assert::AreEqual(-1.0, Rebar::GetYieldStrength(Rebar::Type::A1035, Rebar::Grade::Grade80));
			Assert::AreEqual(689475729.31700003, Rebar::GetYieldStrength(Rebar::Type::A1035, Rebar::Grade::Grade100));
			Assert::AreEqual(827370875.18040001, Rebar::GetYieldStrength(Rebar::Type::A1035, Rebar::Grade::Grade120));
			
			Assert::AreEqual(275790291.72680002, Rebar::GetYieldStrength(Rebar::Type::A615, Rebar::Grade::Grade40));
			Assert::AreEqual(413685437.59020001, Rebar::GetYieldStrength(Rebar::Type::A615, Rebar::Grade::Grade60));
			Assert::AreEqual(517106796.98775005, Rebar::GetYieldStrength(Rebar::Type::A615, Rebar::Grade::Grade75));
			Assert::AreEqual(551580583.45360005, Rebar::GetYieldStrength(Rebar::Type::A615, Rebar::Grade::Grade80));
			Assert::AreEqual(-1.0, Rebar::GetYieldStrength(Rebar::Type::A615, Rebar::Grade::Grade100));
			Assert::AreEqual(-1.0, Rebar::GetYieldStrength(Rebar::Type::A615, Rebar::Grade::Grade120));

			Assert::AreEqual(-1.0, Rebar::GetYieldStrength(Rebar::Type::A706, Rebar::Grade::Grade40));
			Assert::AreEqual(413685437.59020001, Rebar::GetYieldStrength(Rebar::Type::A706, Rebar::Grade::Grade60));
			Assert::AreEqual(-1.0, Rebar::GetYieldStrength(Rebar::Type::A706, Rebar::Grade::Grade75));
			Assert::AreEqual(551580583.45360005, Rebar::GetYieldStrength(Rebar::Type::A706, Rebar::Grade::Grade80));
			Assert::AreEqual(-1.0, Rebar::GetYieldStrength(Rebar::Type::A706, Rebar::Grade::Grade100));
			Assert::AreEqual(-1.0, Rebar::GetYieldStrength(Rebar::Type::A706, Rebar::Grade::Grade120));
		}

		TEST_METHOD(ModulusOfElasticity)
		{
			Assert::AreEqual(-1.0, Rebar::GetE(Rebar::Type::A1035, Rebar::Grade::Grade40));
			Assert::AreEqual(-1.0, Rebar::GetE(Rebar::Type::A1035, Rebar::Grade::Grade60));
			Assert::AreEqual(-1.0, Rebar::GetE(Rebar::Type::A1035, Rebar::Grade::Grade75));
			Assert::AreEqual(-1.0, Rebar::GetE(Rebar::Type::A1035, Rebar::Grade::Grade80));
			Assert::AreEqual(199947961501.93002, Rebar::GetE(Rebar::Type::A1035, Rebar::Grade::Grade100));
			Assert::AreEqual(199947961501.93002, Rebar::GetE(Rebar::Type::A1035, Rebar::Grade::Grade120));

			Assert::AreEqual(199947961501.93002, Rebar::GetE(Rebar::Type::A615, Rebar::Grade::Grade40));
			Assert::AreEqual(199947961501.93002, Rebar::GetE(Rebar::Type::A615, Rebar::Grade::Grade60));
			Assert::AreEqual(199947961501.93002, Rebar::GetE(Rebar::Type::A615, Rebar::Grade::Grade75));
			Assert::AreEqual(199947961501.93002, Rebar::GetE(Rebar::Type::A615, Rebar::Grade::Grade80));
			Assert::AreEqual(-1.0, Rebar::GetE(Rebar::Type::A615, Rebar::Grade::Grade100));
			Assert::AreEqual(-1.0, Rebar::GetE(Rebar::Type::A615, Rebar::Grade::Grade120));

			Assert::AreEqual(-1.0, Rebar::GetE(Rebar::Type::A706, Rebar::Grade::Grade40));
			Assert::AreEqual(199947961501.93002, Rebar::GetE(Rebar::Type::A706, Rebar::Grade::Grade60));
			Assert::AreEqual(-1.0, Rebar::GetE(Rebar::Type::A706, Rebar::Grade::Grade75));
			Assert::AreEqual(199947961501.93002, Rebar::GetE(Rebar::Type::A706, Rebar::Grade::Grade80));
			Assert::AreEqual(-1.0, Rebar::GetE(Rebar::Type::A706, Rebar::Grade::Grade100));
			Assert::AreEqual(-1.0, Rebar::GetE(Rebar::Type::A706, Rebar::Grade::Grade120));
		}

		TEST_METHOD(Elongation_A1035)
		{
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade40, Rebar::Size::bs3));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade40, Rebar::Size::bs4));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade40, Rebar::Size::bs5));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade40, Rebar::Size::bs6));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade40, Rebar::Size::bs7));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade40, Rebar::Size::bs8));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade40, Rebar::Size::bs9));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade40, Rebar::Size::bs10));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade40, Rebar::Size::bs11));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade40, Rebar::Size::bs14));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade40, Rebar::Size::bs18));

			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade60, Rebar::Size::bs3));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade60, Rebar::Size::bs4));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade60, Rebar::Size::bs5));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade60, Rebar::Size::bs6));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade60, Rebar::Size::bs7));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade60, Rebar::Size::bs8));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade60, Rebar::Size::bs9));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade60, Rebar::Size::bs10));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade60, Rebar::Size::bs11));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade60, Rebar::Size::bs14));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade60, Rebar::Size::bs18));

			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade75, Rebar::Size::bs3));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade75, Rebar::Size::bs4));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade75, Rebar::Size::bs5));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade75, Rebar::Size::bs6));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade75, Rebar::Size::bs7));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade75, Rebar::Size::bs8));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade75, Rebar::Size::bs9));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade75, Rebar::Size::bs10));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade75, Rebar::Size::bs11));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade75, Rebar::Size::bs14));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade75, Rebar::Size::bs18));

			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade80, Rebar::Size::bs3));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade80, Rebar::Size::bs4));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade80, Rebar::Size::bs5));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade80, Rebar::Size::bs6));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade80, Rebar::Size::bs7));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade80, Rebar::Size::bs8));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade80, Rebar::Size::bs9));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade80, Rebar::Size::bs10));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade80, Rebar::Size::bs11));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade80, Rebar::Size::bs14));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade80, Rebar::Size::bs18));

			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade100, Rebar::Size::bs3), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade100, Rebar::Size::bs4), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade100, Rebar::Size::bs5), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade100, Rebar::Size::bs6), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade100, Rebar::Size::bs7), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade100, Rebar::Size::bs8), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade100, Rebar::Size::bs9), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade100, Rebar::Size::bs10), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade100, Rebar::Size::bs11), 0.001);
			Assert::AreEqual(0.06, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade100, Rebar::Size::bs14), 0.001);
			Assert::AreEqual(0.06, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade100, Rebar::Size::bs18), 0.001);

			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade120, Rebar::Size::bs3), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade120, Rebar::Size::bs4), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade120, Rebar::Size::bs5), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade120, Rebar::Size::bs6), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade120, Rebar::Size::bs7), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade120, Rebar::Size::bs8), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade120, Rebar::Size::bs9), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade120, Rebar::Size::bs10), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade120, Rebar::Size::bs11), 0.001);
			Assert::AreEqual(0.06, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade120, Rebar::Size::bs14), 0.001);
			Assert::AreEqual(0.06, Rebar::GetElongation(Rebar::Type::A1035, Rebar::Grade::Grade120, Rebar::Size::bs18), 0.001);
		}

		TEST_METHOD(Elongation_A615)
		{
			Assert::AreEqual(0.11, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade40, Rebar::Size::bs3));
			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade40, Rebar::Size::bs4));
			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade40, Rebar::Size::bs5));
			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade40, Rebar::Size::bs6));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade40, Rebar::Size::bs7));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade40, Rebar::Size::bs8));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade40, Rebar::Size::bs9));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade40, Rebar::Size::bs10));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade40, Rebar::Size::bs11));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade40, Rebar::Size::bs14));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade40, Rebar::Size::bs18));

			Assert::AreEqual(0.09, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade60, Rebar::Size::bs3), 0.001);
			Assert::AreEqual(0.09, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade60, Rebar::Size::bs4), 0.001);
			Assert::AreEqual(0.09, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade60, Rebar::Size::bs5), 0.001);
			Assert::AreEqual(0.09, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade60, Rebar::Size::bs6), 0.001);
			Assert::AreEqual(0.08, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade60, Rebar::Size::bs7), 0.001);
			Assert::AreEqual(0.08, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade60, Rebar::Size::bs8), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade60, Rebar::Size::bs9), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade60, Rebar::Size::bs10), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade60, Rebar::Size::bs11), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade60, Rebar::Size::bs14), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade60, Rebar::Size::bs18), 0.001);

			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade75, Rebar::Size::bs3), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade75, Rebar::Size::bs4), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade75, Rebar::Size::bs5), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade75, Rebar::Size::bs6), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade75, Rebar::Size::bs7), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade75, Rebar::Size::bs8), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade75, Rebar::Size::bs9), 0.001);
			Assert::AreEqual(0.06, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade75, Rebar::Size::bs10), 0.001);
			Assert::AreEqual(0.06, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade75, Rebar::Size::bs11), 0.001);
			Assert::AreEqual(0.06, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade75, Rebar::Size::bs14), 0.001);
			Assert::AreEqual(0.06, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade75, Rebar::Size::bs18), 0.001);

			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade80, Rebar::Size::bs3), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade80, Rebar::Size::bs4), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade80, Rebar::Size::bs5), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade80, Rebar::Size::bs6), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade80, Rebar::Size::bs7), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade80, Rebar::Size::bs8), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade80, Rebar::Size::bs9), 0.001);
			Assert::AreEqual(0.06, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade80, Rebar::Size::bs10), 0.001);
			Assert::AreEqual(0.06, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade80, Rebar::Size::bs11), 0.001);
			Assert::AreEqual(0.06, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade80, Rebar::Size::bs14), 0.001);
			Assert::AreEqual(0.06, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade80, Rebar::Size::bs18), 0.001);

			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade100, Rebar::Size::bs3), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade100, Rebar::Size::bs4), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade100, Rebar::Size::bs5), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade100, Rebar::Size::bs6), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade100, Rebar::Size::bs7), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade100, Rebar::Size::bs8), 0.001);
			Assert::AreEqual(0.07, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade100, Rebar::Size::bs9), 0.001);
			Assert::AreEqual(0.06, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade100, Rebar::Size::bs10), 0.001);
			Assert::AreEqual(0.06, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade100, Rebar::Size::bs11), 0.001);
			Assert::AreEqual(0.06, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade100, Rebar::Size::bs14), 0.001);
			Assert::AreEqual(0.06, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade100, Rebar::Size::bs18), 0.001);

			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade120, Rebar::Size::bs3));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade120, Rebar::Size::bs4));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade120, Rebar::Size::bs5));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade120, Rebar::Size::bs6));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade120, Rebar::Size::bs7));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade120, Rebar::Size::bs8));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade120, Rebar::Size::bs9));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade120, Rebar::Size::bs10));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade120, Rebar::Size::bs11));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade120, Rebar::Size::bs14));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A615, Rebar::Grade::Grade120, Rebar::Size::bs18));
		}

		TEST_METHOD(Elongation_A706)
		{
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade40, Rebar::Size::bs3));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade40, Rebar::Size::bs4));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade40, Rebar::Size::bs5));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade40, Rebar::Size::bs6));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade40, Rebar::Size::bs7));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade40, Rebar::Size::bs8));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade40, Rebar::Size::bs9));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade40, Rebar::Size::bs10));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade40, Rebar::Size::bs11));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade40, Rebar::Size::bs14));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade40, Rebar::Size::bs18));

			Assert::AreEqual(0.14, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade60, Rebar::Size::bs3), 0.001);
			Assert::AreEqual(0.14, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade60, Rebar::Size::bs4), 0.001);
			Assert::AreEqual(0.14, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade60, Rebar::Size::bs5), 0.001);
			Assert::AreEqual(0.14, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade60, Rebar::Size::bs6), 0.001);
			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade60, Rebar::Size::bs7), 0.001);
			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade60, Rebar::Size::bs8), 0.001);
			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade60, Rebar::Size::bs9), 0.001);
			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade60, Rebar::Size::bs10), 0.001);
			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade60, Rebar::Size::bs11), 0.001);
			Assert::AreEqual(0.10, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade60, Rebar::Size::bs14), 0.001);
			Assert::AreEqual(0.10, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade60, Rebar::Size::bs18), 0.001);

			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade75, Rebar::Size::bs3));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade75, Rebar::Size::bs4));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade75, Rebar::Size::bs5));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade75, Rebar::Size::bs6));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade75, Rebar::Size::bs7));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade75, Rebar::Size::bs8));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade75, Rebar::Size::bs9));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade75, Rebar::Size::bs10));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade75, Rebar::Size::bs11));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade75, Rebar::Size::bs14));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade75, Rebar::Size::bs18));

			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade80, Rebar::Size::bs3), 0.001);
			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade80, Rebar::Size::bs4), 0.001);
			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade80, Rebar::Size::bs5), 0.001);
			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade80, Rebar::Size::bs6), 0.001);
			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade80, Rebar::Size::bs7), 0.001);
			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade80, Rebar::Size::bs8), 0.001);
			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade80, Rebar::Size::bs9), 0.001);
			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade80, Rebar::Size::bs10), 0.001);
			Assert::AreEqual(0.12, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade80, Rebar::Size::bs11), 0.001);
			Assert::AreEqual(0.10, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade80, Rebar::Size::bs14), 0.001);
			Assert::AreEqual(0.10, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade80, Rebar::Size::bs18), 0.001);

			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade100, Rebar::Size::bs3));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade100, Rebar::Size::bs4));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade100, Rebar::Size::bs5));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade100, Rebar::Size::bs6));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade100, Rebar::Size::bs7));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade100, Rebar::Size::bs8));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade100, Rebar::Size::bs9));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade100, Rebar::Size::bs10));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade100, Rebar::Size::bs11));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade100, Rebar::Size::bs14));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade100, Rebar::Size::bs18));

			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade120, Rebar::Size::bs3));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade120, Rebar::Size::bs4));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade120, Rebar::Size::bs5));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade120, Rebar::Size::bs6));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade120, Rebar::Size::bs7));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade120, Rebar::Size::bs8));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade120, Rebar::Size::bs9));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade120, Rebar::Size::bs10));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade120, Rebar::Size::bs11));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade120, Rebar::Size::bs14));
			Assert::AreEqual(-1.0, Rebar::GetElongation(Rebar::Type::A706, Rebar::Grade::Grade120, Rebar::Size::bs18));
		}
	};
}
