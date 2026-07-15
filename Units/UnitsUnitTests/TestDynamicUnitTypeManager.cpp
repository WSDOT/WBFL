#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Units;

namespace UnitsUnitTest
{
	TEST_CLASS(TestDynamicUnitTypeManager)
	{
	public:

		TEST_METHOD(TestUnitTypes)
		{
			DynamicUnitTypeManager mgr;

			Assert::IsTrue(mgr.GetUnitTypeCount() == 0);
			Assert::IsFalse(mgr.HasUnitType(_T("Velocity")));

			mgr.AddUnitType(_T("Velocity"), 0.0, 1.0, -1.0, 0.0, 0.0);
			Assert::IsTrue(mgr.HasUnitType(_T("Velocity")));
			Assert::IsTrue(mgr.GetUnitTypeCount() == 1);

			auto dim = mgr.GetUnitTypeDimension(_T("Velocity"));
			Assert::AreEqual(0.0, dim.Mass);
			Assert::AreEqual(1.0, dim.Length);
			Assert::AreEqual(-1.0, dim.Time);
			Assert::AreEqual(0.0, dim.Temperature);
			Assert::AreEqual(0.0, dim.Angle);

			Assert::ExpectException<XUnit>([&mgr]() { mgr.AddUnitType(_T("Velocity"), 0.0, 1.0, -1.0, 0.0, 0.0); });

			mgr.RemoveUnitType(_T("Velocity"));
			Assert::IsFalse(mgr.HasUnitType(_T("Velocity")));
			Assert::ExpectException<XUnit>([&mgr]() { mgr.RemoveUnitType(_T("Velocity")); });
			Assert::ExpectException<XUnit>([&mgr]() { mgr.GetUnitTypeDimension(_T("Velocity")); });
		}

		TEST_METHOD(TestUnits)
		{
			DynamicUnitTypeManager mgr;
			mgr.AddUnitType(_T("Velocity"), 0.0, 1.0, -1.0, 0.0, 0.0);

			Assert::IsTrue(mgr.GetUnitCount(_T("Velocity")) == 0);

			mgr.AddUnit(_T("Velocity"), _T("mps"), 1.0);
			mgr.AddUnit(_T("Velocity"), _T("fps"), 0.3048);

			Assert::IsTrue(mgr.GetUnitCount(_T("Velocity")) == 2);
			Assert::IsTrue(mgr.HasUnit(_T("Velocity"), _T("mps")));
			Assert::IsTrue(mgr.HasUnit(_T("Velocity"), _T("fps")));
			Assert::IsFalse(mgr.HasUnit(_T("Velocity"), _T("junk")));
			Assert::IsFalse(mgr.HasUnit(_T("Junk"), _T("mps")));

			const DynamicPhysical& fps = mgr.GetUnit(_T("Velocity"), _T("fps"));
			const DynamicPhysical& mps = mgr.GetUnit(_T("Velocity"), _T("mps"));
			Assert::IsTrue(IsEqual(Convert(1.0, fps, mps), 0.3048));

			Assert::ExpectException<XUnit>([&mgr]() { mgr.AddUnit(_T("Velocity"), _T("mps"), 1.0); });
			Assert::ExpectException<XUnit>([&mgr]() { mgr.GetUnit(_T("Velocity"), _T("junk")); });
			Assert::ExpectException<XUnit>([&mgr]() { mgr.AddUnit(_T("Junk"), _T("x"), 1.0); });

			mgr.RemoveUnit(_T("Velocity"), _T("fps"));
			Assert::IsFalse(mgr.HasUnit(_T("Velocity"), _T("fps")));
			Assert::ExpectException<XUnit>([&mgr]() { mgr.RemoveUnit(_T("Velocity"), _T("fps")); });

			mgr.ClearUnits(_T("Velocity"));
			Assert::IsTrue(mgr.GetUnitCount(_T("Velocity")) == 0);
		}

		TEST_METHOD(TestClearUnitTypes)
		{
			DynamicUnitTypeManager mgr;
			mgr.AddUnitType(_T("Velocity"), 0.0, 1.0, -1.0, 0.0, 0.0);
			mgr.AddUnitType(_T("Acceleration"), 0.0, 1.0, -2.0, 0.0, 0.0);
			Assert::IsTrue(mgr.GetUnitTypeCount() == 2);

			mgr.ClearUnitTypes();
			Assert::IsTrue(mgr.GetUnitTypeCount() == 0);
		}

		TEST_METHOD(TestEnumeration)
		{
			DynamicUnitTypeManager mgr;
			mgr.AddUnitType(_T("Velocity"), 0.0, 1.0, -1.0, 0.0, 0.0);
			mgr.AddUnit(_T("Velocity"), _T("mps"), 1.0);
			mgr.AddUnit(_T("Velocity"), _T("fps"), 0.3048);

			auto names = mgr.GetUnitTypeNames();
			Assert::IsTrue(names.size() == 1);
			Assert::AreEqual(_T("Velocity"), names[0].c_str());

			auto tags = mgr.GetUnitTags(_T("Velocity"));
			Assert::IsTrue(tags.size() == 2);
		}

		TEST_METHOD(TestInsertionOrder)
		{
			// GetUnitTypeNames()/GetUnitTags() and the index-based accessors must reflect insertion
			// order, not map/alphabetical order - "Velocity" is added before "Acceleration", and "z"/"a"
			// tags are added out of alphabetical order, on purpose.
			DynamicUnitTypeManager mgr;
			mgr.AddUnitType(_T("Velocity"), 0.0, 1.0, -1.0, 0.0, 0.0);
			mgr.AddUnitType(_T("Acceleration"), 0.0, 1.0, -2.0, 0.0, 0.0);

			auto names = mgr.GetUnitTypeNames();
			Assert::IsTrue(names.size() == 2);
			Assert::AreEqual(_T("Velocity"), names[0].c_str());
			Assert::AreEqual(_T("Acceleration"), names[1].c_str());

			Assert::AreEqual(_T("Velocity"), mgr.GetUnitTypeName(0).c_str());
			Assert::AreEqual(_T("Acceleration"), mgr.GetUnitTypeName(1).c_str());
			Assert::ExpectException<XUnit>([&mgr]() { mgr.GetUnitTypeName(2); });

			mgr.AddUnit(_T("Velocity"), _T("mps"), 1.0);
			mgr.AddUnit(_T("Velocity"), _T("z"), 0.5);
			mgr.AddUnit(_T("Velocity"), _T("a"), 0.25);

			auto tags = mgr.GetUnitTags(_T("Velocity"));
			Assert::IsTrue(tags.size() == 3);
			Assert::AreEqual(_T("mps"), tags[0].c_str());
			Assert::AreEqual(_T("z"), tags[1].c_str());
			Assert::AreEqual(_T("a"), tags[2].c_str());

			Assert::AreEqual(_T("mps"), mgr.GetUnitTag(_T("Velocity"), 0).c_str());
			Assert::AreEqual(_T("z"), mgr.GetUnitTag(_T("Velocity"), 1).c_str());
			Assert::AreEqual(_T("a"), mgr.GetUnitTag(_T("Velocity"), 2).c_str());
			Assert::ExpectException<XUnit>([&mgr]() { mgr.GetUnitTag(_T("Velocity"), 3); });
			Assert::ExpectException<XUnit>([&mgr]() { mgr.GetUnitTag(_T("Junk"), 0); });

			// removing and re-adding a unit type/unit moves it to the end of the order, matching the
			// documented "insertion order" contract (not "original definition order")
			mgr.RemoveUnitType(_T("Velocity"));
			mgr.AddUnitType(_T("Velocity"), 0.0, 1.0, -1.0, 0.0, 0.0);
			names = mgr.GetUnitTypeNames();
			Assert::AreEqual(_T("Acceleration"), names[0].c_str());
			Assert::AreEqual(_T("Velocity"), names[1].c_str());
		}

		TEST_METHOD(TestExtendedUnit)
		{
			// Verifies AddUnit's full pre/cf/post overload against a temperature-like affine conversion.
			DynamicUnitTypeManager mgr;
			mgr.AddUnitType(_T("Temperature2"), 0.0, 0.0, 0.0, 1.0, 0.0);
			mgr.AddUnit(_T("Temperature2"), _T("C"), 0.0, 1.0, 0.0);
			mgr.AddUnit(_T("Temperature2"), _T("F"), -32.0, 5. / 9., 0.0);

			const DynamicPhysical& F = mgr.GetUnit(_T("Temperature2"), _T("F"));
			const DynamicPhysical& C = mgr.GetUnit(_T("Temperature2"), _T("C"));

			Assert::IsTrue(IsEqual(Convert(212.0, F, C), 100.0));
			Assert::IsTrue(IsEqual(Convert(100.0, C, F), 212.0));
		}
	};
}
