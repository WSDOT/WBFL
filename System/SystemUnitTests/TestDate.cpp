#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace WBFL::System;

namespace SystemUnitTest
{
	TEST_CLASS(TestDate)
	{
	public:
		
		TEST_METHOD(Test)
		{
         // Check date integrity
         Date d1(01, 01, 2000);
         Assert::IsTrue(std::_tstring(d1.NameOfDay()) == _T("Saturday"), _T("Test day name"));

         Date d2(02, 01, 2000);
         Assert::IsTrue(std::_tstring(d2.NameOfDay()) == _T("Sunday"));

         Date d3(29, 02, 2000);
         Assert::IsTrue(std::_tstring(d3.NameOfDay()) == _T("Tuesday"));

         Date d4(01, 03, 2000);
         Assert::IsTrue(std::_tstring(d4.NameOfDay()) == _T("Wednesday"));

         // Check date roll over
         Date d5(31, 12, 1998);
         ++d5;
         Assert::IsTrue(d5.DayOfMonth() == 1 && d5.Month() == 1 && d5.Year() == 1999);

         Date d6(31, 12, 1999);
         ++d6;
         Assert::IsTrue(d6.DayOfMonth() == 1 && d6.Month() == 1 && d6.Year() == 2000);

         Date d7(28, 02, 2000);
         ++d7;
         Assert::IsTrue(d7.DayOfMonth() == 29 && d7.Month() == 2 && d7.Year() == 2000);

         ++d7;
         Assert::IsTrue(d7.DayOfMonth() == 1 && d7.Month() == 3 && d7.Year() == 2000);

         // Test Leap Years
         Date d8(31, 12, 2000);
         Assert::IsTrue(d8.IsLeapYear());

         Date d9(31, 12, 1900);
         Assert::IsTrue(!d9.IsLeapYear());

         // Test Day of Year
         Assert::IsTrue(d8.Day() == 366);
         Assert::IsTrue(d9.Day() == 365);
      }
	};
}
