#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Materials;

namespace MaterialsUnitTest
{
	TEST_CLASS(TestPsStrand)
	{
	public:
		
		TEST_METHOD(Test)
		{
			PsStrand strand(_T("TestStrand"), PsStrand::Grade::Gr1725, PsStrand::Type::LowRelaxation, PsStrand::Coating::None, PsStrand::Size::D635, 270, 265, 28500, 0.5, 0.153);
			Assert::AreEqual(_T("TestStrand"), strand.GetName().c_str());
			Assert::IsTrue(PsStrand::Grade::Gr1725 == strand.GetGrade());
			Assert::IsTrue(PsStrand::Type::LowRelaxation == strand.GetType());
			Assert::IsTrue(PsStrand::Coating::None == strand.GetCoating());
			Assert::IsTrue(PsStrand::Size::D635 == strand.GetSize());
			Assert::AreEqual(270., strand.GetUltimateStrength());
			Assert::AreEqual(265., strand.GetYieldStrength());
			Assert::AreEqual(28500., strand.GetE());
			Assert::AreEqual(0.5, strand.GetNominalDiameter());
			Assert::AreEqual(0.153, strand.GetNominalArea());
		}

		TEST_METHOD(Grade)
		{
			Assert::AreEqual(_T("250"), PsStrand::GetGrade(PsStrand::Grade::Gr1725, true).c_str());
			Assert::AreEqual(_T("270"), PsStrand::GetGrade(PsStrand::Grade::Gr1860, true).c_str());
			Assert::AreEqual(_T("300"), PsStrand::GetGrade(PsStrand::Grade::Gr2070, true).c_str());

			Assert::AreEqual(_T("1725"), PsStrand::GetGrade(PsStrand::Grade::Gr1725, false).c_str());
			Assert::AreEqual(_T("1860"), PsStrand::GetGrade(PsStrand::Grade::Gr1860, false).c_str());
			Assert::AreEqual(_T("2070"), PsStrand::GetGrade(PsStrand::Grade::Gr2070, false).c_str());
		}

		TEST_METHOD(Type)
		{
			Assert::AreEqual(_T("Low Relaxation"), PsStrand::GetType(PsStrand::Type::LowRelaxation).c_str());
			Assert::AreEqual(_T("Stress Relieved"), PsStrand::GetType(PsStrand::Type::StressRelieved).c_str());
		}

		TEST_METHOD(Coating)
		{
			Assert::AreEqual(_T("None"), PsStrand::GetCoating(PsStrand::Coating::None).c_str());
			Assert::AreEqual(_T("Smooth"), PsStrand::GetCoating(PsStrand::Coating::SmoothEpoxy).c_str());
			Assert::AreEqual(_T("GritEpoxy"), PsStrand::GetCoating(PsStrand::Coating::GritEpoxy).c_str());
		}

		TEST_METHOD(Size)
		{
			Assert::AreEqual(_T("1/4\""), PsStrand::GetSize(PsStrand::Size::D635,true).c_str());
			Assert::AreEqual(_T("5/16\""), PsStrand::GetSize(PsStrand::Size::D794, true).c_str());
			Assert::AreEqual(_T("3/8\""), PsStrand::GetSize(PsStrand::Size::D953, true).c_str());
			Assert::AreEqual(_T("7/16\""), PsStrand::GetSize(PsStrand::Size::D1111, true).c_str());
			Assert::AreEqual(_T("1/2\""), PsStrand::GetSize(PsStrand::Size::D1270, true).c_str());
			Assert::AreEqual(_T("1/2\" Special (0.52\")"), PsStrand::GetSize(PsStrand::Size::D1320, true).c_str());
			Assert::AreEqual(_T("0.6\""), PsStrand::GetSize(PsStrand::Size::D1524, true).c_str());
			Assert::AreEqual(_T("0.62\""), PsStrand::GetSize(PsStrand::Size::D1575, true).c_str());
			Assert::AreEqual(_T("0.7\""), PsStrand::GetSize(PsStrand::Size::D1778, true).c_str());

			Assert::AreEqual(_T("6.35mm"), PsStrand::GetSize(PsStrand::Size::D635, false).c_str());
			Assert::AreEqual(_T("7.94mm"), PsStrand::GetSize(PsStrand::Size::D794, false).c_str());
			Assert::AreEqual(_T("9.53mm"), PsStrand::GetSize(PsStrand::Size::D953, false).c_str());
			Assert::AreEqual(_T("11.11mm"), PsStrand::GetSize(PsStrand::Size::D1111, false).c_str());
			Assert::AreEqual(_T("12.70mm"), PsStrand::GetSize(PsStrand::Size::D1270, false).c_str());
			Assert::AreEqual(_T("1/2\" Special (13.20mm)"), PsStrand::GetSize(PsStrand::Size::D1320, false).c_str());
			Assert::AreEqual(_T("15.24mm"), PsStrand::GetSize(PsStrand::Size::D1524, false).c_str());
			Assert::AreEqual(_T("15.75mm"), PsStrand::GetSize(PsStrand::Size::D1575, false).c_str());
			Assert::AreEqual(_T("17.78mm"), PsStrand::GetSize(PsStrand::Size::D1778, false).c_str());
		}
	};
}
