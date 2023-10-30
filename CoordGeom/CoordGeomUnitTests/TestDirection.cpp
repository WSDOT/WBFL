#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestDirection)
	{
	public:
		
		TEST_METHOD(BasicProperties)
		{
			Direction dir;
			Assert::IsTrue(IsZero(dir.GetValue()));

			dir.SetValue(3.23);
			Assert::IsTrue(IsEqual(dir.GetValue(), 3.23));

			dir.SetValue(-3.23);
			Assert::IsTrue(IsEqual(dir.GetValue(), TWO_PI - 3.23));
		}

		TEST_METHOD(DMS)
		{
         Direction dir;

         // N 45 15 22.5 E =  44.74375deg = 0.780925757rad
         dir.SetDMS(Direction::NSDirection::North, 45, 15, 22.5, Direction::EWDirection::East);
         Assert::IsTrue(IsEqual(dir.GetValue(), 0.780925757));
         dir.SetValue(0);
         dir.SetValue(0.780925757);
         Direction::NSDirection ns;
         Direction::EWDirection ew;
         unsigned short d, m;
         Float64 s;
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);
         Assert::AreEqual(d, (unsigned short)45);
         Assert::AreEqual(m, (unsigned short)15);
         Assert::IsTrue(IsEqual(s, 22.5, 0.1));
         Assert::IsTrue(ew == Direction::EWDirection::East);

         // N 45 15 22.5 W = 135.25625deg = 2.360666897rad
         dir.SetDMS(Direction::NSDirection::North, 45, 15, 22.5, Direction::EWDirection::West);
         Assert::IsTrue(IsEqual(dir.GetValue(), 2.360666897));
         dir.SetValue(0);
         dir.SetValue(2.360666897);
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);
         Assert::AreEqual(d, (unsigned short)45);
         Assert::AreEqual(m, (unsigned short)15);
         Assert::IsTrue(IsEqual(s, 22.5, 0.1));
         Assert::IsTrue(ew == Direction::EWDirection::West);

         // S 45 15 22.5 W = 224.74375deg = 3.922518411rad
         dir.SetDMS(Direction::NSDirection::South, 45, 15, 22.5, Direction::EWDirection::West);
         Assert::IsTrue(IsEqual(dir.GetValue(), 3.922518411));
         dir.SetValue(0);
         dir.SetValue(3.922518411);
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::South);
         Assert::AreEqual(d, (unsigned short)45);
         Assert::AreEqual(m, (unsigned short)15);
         Assert::IsTrue(IsEqual(s, 22.5, 0.1));
         Assert::IsTrue(ew == Direction::EWDirection::West);

         // S 45 15 22.5 E = 315.25625deg = 5.502259551rad
         dir.SetDMS(Direction::NSDirection::South, 45, 15, 22.5, Direction::EWDirection::East);
         Assert::IsTrue(IsEqual(dir.GetValue(), 5.502259551));
         dir.SetValue(0);
         dir.SetValue(5.502259551);
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::South);
         Assert::AreEqual(d, (unsigned short)45);
         Assert::AreEqual(m, (unsigned short)15);
         Assert::IsTrue(IsEqual(s, 22.5, 0.1));
         Assert::IsTrue(ew == Direction::EWDirection::East);


         try { dir.SetDMS(Direction::NSDirection::North, 100, 15, 22.5, Direction::EWDirection::East); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTION); }

         try { dir.SetDMS(Direction::NSDirection::North, -10, 15, 22.5, Direction::EWDirection::East); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTION); }

         try { dir.SetDMS(Direction::NSDirection::North, 45, 90, 22.5, Direction::EWDirection::East); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTION); }

         try { dir.SetDMS(Direction::NSDirection::North, 45, -1, 22.5, Direction::EWDirection::East); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTION); }

         try { dir.SetDMS(Direction::NSDirection::North, 45, 15, 122.5, Direction::EWDirection::East); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTION); }

         try { dir.SetDMS(Direction::NSDirection::North, 45, 15, -22.5, Direction::EWDirection::East); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTION); }


         try { dir.SetDMS(Direction::NSDirection::North, 45, 15, 22.5, Direction::EWDirection::East); }
         catch (XCoordGeom&) { Assert::Fail(); }
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);
         Assert::AreEqual(d, (unsigned short)45);
         Assert::AreEqual(m, (unsigned short)15);
         Assert::IsTrue(IsEqual(s, 22.5));
         Assert::IsTrue(ew == Direction::EWDirection::East);
      }

      TEST_METHOD(Increment)
      {
         Direction dir(M_PI / 4);
         dir.Increment(M_PI / 4);
         Assert::IsTrue(IsEqual(dir.GetValue(), PI_OVER_2));

         dir.SetValue(3 * PI_OVER_2); // S 0 0 0 E
         dir.Increment(M_PI);
         Assert::IsTrue(IsEqual(dir.GetValue(), PI_OVER_2));

         dir.SetValue(3 * PI_OVER_2); // S 0 0 0 E
         dir.Increment(-M_PI);
         Assert::IsTrue(IsEqual(dir.GetValue(), PI_OVER_2));

         dir.SetValue(0);
         auto incremented_direction = dir.IncrementBy(1.0);
         Assert::IsTrue(IsEqual(dir.GetValue(), 0.0));
         Assert::IsTrue(IsEqual(incremented_direction.GetValue(), 1.0));
      }

      TEST_METHOD(FromString)
      {
         Direction dir;
         try { dir.FromString(_T("")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("                ")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("ABC123")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("N")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("N S")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("N 100 45 12.3 E")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("N 45 90 22.5 E")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("N 45 15 90.5 E")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("0.76")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("E 45 15 22.5 W")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("N 45 15 22.5 N")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("NS 45 15 22.5 E")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("N 45 15 22.5 EW")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("N 0A 15 22.5 E")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("N A0 15 22.5 E")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("N 45 0A 22.5 E")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("N 45 A0 22.5 E")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("N 45 15 A0.0 E")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("N     45 15 22.5 E")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("N 45     15 22.5 E")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("N 45 15     22.5 E")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         try { dir.FromString(_T("N 45 15 22.5     E")); Assert::Fail(); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_DIRECTIONSTRING); }

         // these ones are good
         try { dir.FromString(_T("      N 45 15 22.5 E")); }
         catch (XCoordGeom&) { Assert::Fail(); }

         try { dir.FromString(_T("N 45 15 22.5 E        ")); }
         catch (XCoordGeom&) { Assert::Fail(); }

         try { dir.FromString(_T("        N 45 15 22.5 E        ")); }
         catch (XCoordGeom&) { Assert::Fail(); }

         try { dir.FromString(_T("N 45 15 22.5 E")); }
         catch (XCoordGeom&) { Assert::Fail(); }

         Direction::NSDirection ns;
         Direction::EWDirection ew;
         unsigned short d, m;
         Float64 s;
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);
         Assert::AreEqual(d, (unsigned short)45);
         Assert::AreEqual(m, (unsigned short)15);
         Assert::IsTrue(IsEqual(s, 22.5));
         Assert::IsTrue(ew == Direction::EWDirection::East);

         try { dir.FromString(_T("N 00 15 22.5 E")); }
         catch (XCoordGeom&) { Assert::Fail(); }
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);
         Assert::AreEqual(d, (unsigned short)0);
         Assert::AreEqual(m, (unsigned short)15);
         Assert::IsTrue(IsEqual(s, 22.5));
         Assert::IsTrue(ew == Direction::EWDirection::East);

         try { dir.FromString(_T("N 45 00 22.5 E")); }
         catch (XCoordGeom&) { Assert::Fail(); }
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);
         Assert::AreEqual(d, (unsigned short)45);
         Assert::AreEqual(m, (unsigned short)0);
         Assert::IsTrue(IsEqual(s, 22.5));
         Assert::IsTrue(ew == Direction::EWDirection::East);

         try { dir.FromString(_T("N 45 15 0.00 E")); }
         catch (XCoordGeom&) { Assert::Fail(); }
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);
         Assert::AreEqual(d, (unsigned short)45);
         Assert::AreEqual(m, (unsigned short)15);
         Assert::IsTrue(IsEqual(s, 0.0));
         Assert::IsTrue(ew == Direction::EWDirection::East);

         try { dir.FromString(_T("N 45 E")); }
         catch (XCoordGeom&) { Assert::Fail(); }
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);
         Assert::AreEqual(d, (unsigned short)45);
         Assert::AreEqual(m, (unsigned short)0);
         Assert::IsTrue(IsEqual(s, 0.0));
         Assert::IsTrue(ew == Direction::EWDirection::East);

         try { dir.FromString(_T("N 0 E")); }
         catch (XCoordGeom&) { Assert::Fail(); }
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);
         Assert::AreEqual(d, (unsigned short)0);
         Assert::AreEqual(m, (unsigned short)0);
         Assert::IsTrue(IsEqual(s, 0.0));
         Assert::IsTrue(ew == Direction::EWDirection::East);
         Assert::IsTrue(IsEqual(dir.GetValue(), PI_OVER_2));

         try { dir.FromString(_T("N 0 W")); }
         catch (XCoordGeom&) { Assert::Fail(); }
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);
         Assert::AreEqual(d, (unsigned short)0);
         Assert::AreEqual(m, (unsigned short)0);
         Assert::IsTrue(IsEqual(s, 0.0));
         Assert::IsTrue(ew == Direction::EWDirection::East);
         Assert::IsTrue(IsEqual(dir.GetValue(), PI_OVER_2));

         try { dir.FromString(_T("N 90 E")); }
         catch (XCoordGeom&) { Assert::Fail(); }
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);
         Assert::AreEqual(d, (unsigned short)90);
         Assert::AreEqual(m, (unsigned short)0);
         Assert::IsTrue(IsEqual(s, 0.0));
         Assert::IsTrue(ew == Direction::EWDirection::East);
         Assert::IsTrue(IsEqual(dir.GetValue(), 0.0));

         try { dir.FromString(_T("N 90 W")); }
         catch (XCoordGeom&) { Assert::Fail(); }
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);
         Assert::AreEqual(d,(unsigned short)90);
         Assert::AreEqual(m,(unsigned short)0);
         Assert::IsTrue(IsEqual(s, 0.0));
         Assert::IsTrue(ew == Direction::EWDirection::West);
         Assert::IsTrue(IsEqual(dir.GetValue(), M_PI));

         try { dir.FromString(_T("S 0 E")); }
         catch (XCoordGeom&) { Assert::Fail(); }
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::South);
         Assert::AreEqual(d, (unsigned short)0);
         Assert::AreEqual(m, (unsigned short)0);
         Assert::IsTrue(IsEqual(s, 0.0));
         Assert::IsTrue(ew == Direction::EWDirection::East);
         Assert::IsTrue(IsEqual(dir.GetValue(), 3 * PI_OVER_2));

         try { dir.FromString(_T("S 0 W")); }
         catch (XCoordGeom&) { Assert::Fail(); }
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::South);
         Assert::AreEqual(d, (unsigned short)0);
         Assert::AreEqual(m, (unsigned short)0);
         Assert::IsTrue(IsEqual(s, 0.0));
         Assert::IsTrue(ew == Direction::EWDirection::East); // East is favored when ambiguous
         Assert::IsTrue(IsEqual(dir.GetValue(), 3 * PI_OVER_2));

         try { dir.FromString(_T("S 90 E")); }
         catch (XCoordGeom&) { Assert::Fail(); }
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);  // North is favored when ambiguous
         Assert::AreEqual(d, (unsigned short)90);
         Assert::AreEqual(m, (unsigned short)0);
         Assert::IsTrue(IsEqual(s, 0.0));
         Assert::IsTrue(ew == Direction::EWDirection::East);
         Assert::IsTrue(IsEqual(dir.GetValue(), 0.0));

         try { dir.FromString(_T("S 90 W")); }
         catch (XCoordGeom&) { Assert::Fail(); }
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);  // North is favored when ambiguous
         Assert::AreEqual(d,(unsigned short)90);
         Assert::AreEqual(m,(unsigned short)0);
         Assert::IsTrue(IsEqual(s, 0.0));
         Assert::IsTrue(ew == Direction::EWDirection::West);
         Assert::IsTrue(IsEqual(dir.GetValue(), M_PI));

         try { dir.FromString(_T("N 34 54 W")); }
         catch (XCoordGeom&) { Assert::Fail(); }
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);
         Assert::AreEqual(d, (unsigned short)34);
         Assert::AreEqual(m, (unsigned short)54);
         Assert::IsTrue(IsEqual(s, 0.0));
         Assert::IsTrue(ew == Direction::EWDirection::West);
      }

      TEST_METHOD(Azimuth)
      {
         Direction dir;
         try { dir.SetAzimuth(370, 15, 22.5); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_AZIMUTH); }

         try { dir.SetAzimuth(360, 15, 22.5); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_AZIMUTH); }

         try { dir.SetAzimuth(-360, 15, 22.5); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_AZIMUTH); }

         try { dir.SetAzimuth(-370, 15, 22.5); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_AZIMUTH); }

         try { dir.SetAzimuth(45, 60, 22.5); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_AZIMUTH); }

         try { dir.SetAzimuth(45, 90, 22.5); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_AZIMUTH); }

         try { dir.SetAzimuth(45, -15, 22.5); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_AZIMUTH); }

         try { dir.SetAzimuth(45, 15, 60.0); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_AZIMUTH); }

         try { dir.SetAzimuth(45, 15, 90.5); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_AZIMUTH); }

         try { dir.SetAzimuth(45, 15, -22.5); }
         catch (XCoordGeom& e) { Assert::AreEqual(e.GetReason(), WBFL_COGO_E_AZIMUTH); }


         try { dir.SetAzimuth(45, 15, 22.5); }
         catch (XCoordGeom&) { Assert::Fail(); }
         Direction::NSDirection ns;
         Direction::EWDirection ew;
         unsigned short d, m;
         Float64 s;
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);
         Assert::AreEqual(d, (unsigned short)45);
         Assert::AreEqual(m, (unsigned short)15);
         Assert::IsTrue(IsEqual(s, 22.5));
         Assert::IsTrue(ew == Direction::EWDirection::East);

         try { dir.SetAzimuth(-45, 15, 22.5); }
         catch (XCoordGeom&) { Assert::Fail(); }
         std::tie(ns, d, m, s, ew) = dir.GetDMS();
         Assert::IsTrue(ns == Direction::NSDirection::North);
         Assert::AreEqual(d, (unsigned short)45);
         Assert::AreEqual(m, (unsigned short)15);
         Assert::IsTrue(IsEqual(s, 22.5));
         Assert::IsTrue(ew == Direction::EWDirection::West);
      }

      TEST_METHOD(AngleBetween)
      {
         Direction d1(Direction::NSDirection::North, 45, 0, 0, Direction::EWDirection::East);
         Direction d2(Direction::NSDirection::North, 45, 0, 0, Direction::EWDirection::West);
         auto angle = d2.AngleBetween(d1);
         Assert::IsTrue(IsEqual(angle.GetValue(), PI_OVER_2));

         angle = d1.AngleBetween(d2);
         Assert::IsTrue(IsEqual(angle.GetValue(), 3 * PI_OVER_2));

         angle = d1.AngleBetween(d1);
         Assert::IsTrue(IsEqual(angle.GetValue(), 0.0));
      }
	};
}
