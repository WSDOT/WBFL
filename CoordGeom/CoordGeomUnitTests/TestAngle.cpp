#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestAngle)
	{
	public:
		
		TEST_METHOD(BasicProperties)
		{
			Angle angle;
			Assert::IsTrue(IsZero(angle.GetValue()));

         angle.SetValue(3.23);
			Assert::IsTrue(IsEqual(angle.GetValue(), 3.23));

         angle.SetValue(-3.23);
			Assert::IsTrue(IsEqual(angle.GetValue(), -3.23));
		}

		TEST_METHOD(DMS)
		{
         Angle angle;

         try { angle.SetDMS(-14, 60, 13.5); } // Invalid minutes
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLE); }

         try { angle.SetDMS(-14, 65, 13.5); } // Invalid minutes
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLE); }

         //try { angle.SetDMS(-14, -10, 13.5); } // Invalid minutes (generates compiler warning C4244)
         //catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLE); }

         try { angle.SetDMS(-14, 25, 60.0); } // Invalid seconds
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLE); }

         try { angle.SetDMS(-14, 25, -10.0); } // Invalid seconds
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLE); }

         try { angle.SetDMS(-14, 25, 13.5); } // Valid angle
         catch (XCoordGeom&) { Assert::IsTrue(false); } // should not get here

         auto [d, m, s] = angle.GetDMS();
         Assert::IsTrue(d == -14);
         Assert::IsTrue(m == 25);
         Assert::IsTrue(IsEqual(s, 13.5));
      }

      TEST_METHOD(Normalize)
      {
         Angle angle(-2 * TWO_PI);
         angle.Normalize();
         Assert::IsTrue(IsZero(angle.GetValue()));

         angle.SetValue(2 * TWO_PI);
         angle.Normalize();
         Assert::IsTrue(IsZero(angle.GetValue()));

         angle.SetValue(TWO_PI);
         angle.Normalize();
         Assert::IsTrue(IsZero(angle.GetValue()));

         angle.SetValue(1.25 * TWO_PI);
         angle.Normalize();
         Assert::IsTrue(IsEqual(angle.GetValue(), PI_OVER_2));

         angle.SetValue(-1.25 * TWO_PI);
         angle.Normalize();
         Assert::IsTrue(IsEqual(angle.GetValue(), 3 * PI_OVER_2));
      }

      TEST_METHOD(Increment)
      {
         Angle angle;
         angle.Increment(PI_OVER_2);
         Assert::IsTrue(IsEqual(angle.GetValue(), PI_OVER_2));

         auto incremented_angle = angle.IncrementBy(PI_OVER_2);
         Assert::IsTrue(IsEqual(incremented_angle.GetValue(), M_PI));
         Assert::IsTrue(IsEqual(angle.GetValue(), PI_OVER_2));
      }

      TEST_METHOD(FromString)
      {
         Angle angle;

         try { angle.FromString(_T("")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("                 ")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("A")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("+12.5 L")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("-12.5 L")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("+12.5 R")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("-12.5 R")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("x12.5 L")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("12.5 LR")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("12.5 x")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("DD 13 14.15")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("12 MM 14.15")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("12 13 SS.ss")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("12 -10 14.15")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("12 60 14.15")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("12 65 14.15")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("12 13 -14.15")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("12 13 60.00")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("12 13 65.00")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("12 13 14.15 LR")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("12 13 14.15 x")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("-12 13 14.15 L")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("+12 13 14.15 L")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("-12 13 14.15 R")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         try { angle.FromString(_T("+12 13 14.15 R")); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

         // these should work
         try { angle.FromString(_T("12 13 R")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         auto [d, m, s] = angle.GetDMS();
         Assert::IsTrue(d == -12);
         Assert::IsTrue(m == 13);
         Assert::IsTrue(IsZero(s));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60.))));

         try { angle.FromString(_T("12 13 L")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         std::tie(d, m, s) = angle.GetDMS();
         Assert::IsTrue(d == 12);
         Assert::IsTrue(m == 13);
         Assert::IsTrue(IsZero(s));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60.))));

         try { angle.FromString(_T("12.5")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         std::tie(d, m, s) = angle.GetDMS();
         Assert::IsTrue(d == 12);
         Assert::IsTrue(m == 30);
         Assert::IsTrue(IsZero(s));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60.))));

         try { angle.FromString(_T("-12.5")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         std::tie(d, m, s) = angle.GetDMS();
         Assert::IsTrue(d == -12);
         Assert::IsTrue(m == 30);
         Assert::IsTrue(IsZero(s));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60.))));

         try { angle.FromString(_T("12.5 L")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         std::tie(d, m, s) = angle.GetDMS();
         Assert::IsTrue(d == 12);
         Assert::IsTrue(m == 30);
         Assert::IsTrue(IsZero(s));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60.))));

         try { angle.FromString(_T("12.5 R")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         std::tie(d, m, s) = angle.GetDMS();
         Assert::IsTrue(d == -12);
         Assert::IsTrue(m == 30);
         Assert::IsTrue(IsZero(s));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60.))));

         try { angle.FromString(_T("12.5 l")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         std::tie(d, m, s) = angle.GetDMS();
         Assert::IsTrue(d == 12);
         Assert::IsTrue(m == 30);
         Assert::IsTrue(IsZero(s));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60.))));

         try { angle.FromString(_T("12.5 r")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         std::tie(d, m, s) = angle.GetDMS();
         Assert::IsTrue(d == -12);
         Assert::IsTrue(m == 30);
         Assert::IsTrue(IsZero(s));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60.))));

         try { angle.FromString(_T("               12.5 L")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         std::tie(d, m, s) = angle.GetDMS();
         Assert::IsTrue(d == 12);
         Assert::IsTrue(m == 30);
         Assert::IsTrue(IsZero(s));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60.))));

         try { angle.FromString(_T("12.5 L                 ")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         std::tie(d, m, s) = angle.GetDMS();
         Assert::IsTrue(d == 12);
         Assert::IsTrue(m == 30);
         Assert::IsTrue(IsZero(s));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60.))));

         try { angle.FromString(_T("         12.5 L           ")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         std::tie(d, m, s) = angle.GetDMS();
         Assert::IsTrue(d == 12);
         Assert::IsTrue(m == 30);
         Assert::IsTrue(IsZero(s));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60.))));

         try { angle.FromString(_T("12 13 14.15 L")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         std::tie(d, m, s) = angle.GetDMS();
         Assert::IsTrue(d == 12);
         Assert::IsTrue(m == 13);
         Assert::IsTrue(IsEqual(s, 14.15));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60. + s / 3600.))));

         try { angle.FromString(_T("12 13 14.15 R")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         std::tie(d, m, s) = angle.GetDMS();
         Assert::IsTrue(d == -12);
         Assert::IsTrue(m == 13);
         Assert::IsTrue(IsEqual(s, 14.15));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60. + s / 3600.))));

         try { angle.FromString(_T("12 13 14.15")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         std::tie(d, m, s) = angle.GetDMS();
         Assert::IsTrue(d == 12);
         Assert::IsTrue(m == 13);
         Assert::IsTrue(IsEqual(s, 14.15));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60. + s / 3600.))));

         try { angle.FromString(_T("+12 13 14.15")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         std::tie(d, m, s) = angle.GetDMS();
         Assert::IsTrue(d == 12);
         Assert::IsTrue(m == 13);
         Assert::IsTrue(IsEqual(s, 14.15));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60. + s / 3600.))));

         try { angle.FromString(_T("-12 13 14.15")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         std::tie(d, m, s) = angle.GetDMS();
         Assert::IsTrue(d == -12);
         Assert::IsTrue(m == 13);
         Assert::IsTrue(IsEqual(s, 14.15));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60. + s / 3600.))));

         try { angle.FromString(_T("00 00 14.15")); }
         catch (XCoordGeom&) { Assert::IsTrue(false); }
         std::tie(d, m, s) = angle.GetDMS();
         Assert::IsTrue(d == 0);
         Assert::IsTrue(m == 0);
         Assert::IsTrue(IsEqual(s, 14.15));
         Assert::IsTrue(IsEqual(angle.GetValue(), ToRadians(BinarySign(d) * (fabs(d) + m / 60. + s / 3600.))));
      }
	};
}
