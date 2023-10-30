#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace WBFL::System;

namespace SystemUnitTest
{
	TEST_CLASS(TestTime)
	{
	public:
		
		TEST_METHOD(Test)
		{
			Time t(Date(25, 6, 2023), 16, 23, 56);
			Assert::AreEqual((HourTy)16, t.Hour());
			Assert::AreEqual((MinuteTy)23, t.Minute());
			Assert::AreEqual((SecondTy)56, t.Second());

			Assert::AreEqual((HourTy)23, t.HourGMT());
			Assert::AreEqual((MinuteTy)23, t.MinuteGMT());

			Assert::AreEqual((ClockTy)3865188236, t.Seconds());
		}

		TEST_METHOD(Boolean_Operators)
		{
			Time now;
			Time later(now.Hour() + 2, now.Minute(), now.Second());

			Assert::IsTrue(now < later);
			Assert::IsTrue(now <= later);
			Assert::IsTrue(now <= now);
			Assert::IsTrue(now == now);
			Assert::IsTrue(now != later);

			Assert::IsTrue(later > now);
			Assert::IsTrue(later >= now);
			Assert::IsTrue(later == later);
			Assert::IsTrue(later != now);

			Time before(now.Hour() - 2, now.Minute(), now.Second());
			Assert::IsTrue(now.Between(before, later));
			Assert::IsFalse(before.Between(now, later));

			Assert::AreEqual((Int16)0, later.CompareTo(later));
			Assert::AreEqual((Int16)1, later.CompareTo(before));
			Assert::AreEqual((Int16)-1, before.CompareTo(later));
		}

		TEST_METHOD(Increment_Operators)
		{
			Time t(16, 23, 56);
			++t;
			Assert::AreEqual((SecondTy)57, t.Second());

			--t;
			Assert::AreEqual((SecondTy)56, t.Second());

			t += 90;
			Assert::AreEqual((MinuteTy)25, t.Minute());
			Assert::AreEqual((SecondTy)26, t.Second());

			t -= 90;
			Assert::AreEqual((MinuteTy)23, t.Minute());
			Assert::AreEqual((SecondTy)56, t.Second());
		}

		TEST_METHOD(Hash)
		{
			Time t(Date(25,6,2023),16, 23, 56);
			Assert::AreEqual((Uint16)6028, t.Hash());
		}

		TEST_METHOD(DST)
		{
			Time dst(Date(1, 1, 2000));
			Time st(Date(1, 6, 2000));

			Assert::IsFalse(dst.IsDST());
			Assert::IsTrue(st.IsDST());
		}

		TEST_METHOD(IsValid)
		{
			Time now;
			Assert::IsTrue(now.IsValid());
		}

		TEST_METHOD(MinMax)
		{
			Time now;
			Time later(now.Hour() + 2, now.Minute(), now.Second());
			Assert::IsTrue(now == now.Min(later));
			Assert::IsTrue(later == now.Max(later));
		}

		TEST_METHOD(AsString)
		{
			Assert::IsTrue(Time::PrintDate());
			Time t(Date(28, 2, 2023), 5, 15, 34);
			Assert::AreEqual(_T("February 28, 2023\0 5:15:34 am"), t.AsString().c_str());

			Assert::IsTrue(Time::PrintDate(false));
			Assert::IsFalse(Time::PrintDate());
			Assert::AreEqual(_T("5:15:34 am"), t.AsString().c_str());
		}
	};
}
