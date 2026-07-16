#include "pch.h"
#include "CppUnitTest.h"
#include <System\XProgrammingError.h>

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

		// Builds a manager seeded with the same five fundamental unit types (Mass, Length, Time,
		// Temperature, Angle) and derived types (Pressure, ThermalExpansion) that
		// WBFL::Units::UnitsXML::InitDefaultUnits() seeds a real manager with, using the same tags and
		// conversion equations, without depending on the UnitsXML/xsd-cxx-generated schema types
		// themselves - this keeps the test focused purely on DynamicUnitTypeManager's own
		// SetBaseUnits()/GetBaseUnit() logic.
		static void SeedFundamentalUnitTypes(DynamicUnitTypeManager& mgr)
		{
			mgr.AddUnitType(_T("Mass"), 1.0, 0.0, 0.0, 0.0, 0.0);
			mgr.AddUnit(_T("Mass"), _T("kg"), 1.0);
			mgr.AddUnit(_T("Mass"), _T("lb"), 0.45359237);

			mgr.AddUnitType(_T("Length"), 0.0, 1.0, 0.0, 0.0, 0.0);
			mgr.AddUnit(_T("Length"), _T("m"), 1.0);
			mgr.AddUnit(_T("Length"), _T("ft"), 0.3048);

			mgr.AddUnitType(_T("Time"), 0.0, 0.0, 1.0, 0.0, 0.0);
			mgr.AddUnit(_T("Time"), _T("sec"), 1.0);

			mgr.AddUnitType(_T("Temperature"), 0.0, 0.0, 0.0, 1.0, 0.0);
			mgr.AddUnit(_T("Temperature"), _T("C"), 0.0, 1.0, 0.0);
			mgr.AddUnit(_T("Temperature"), _T("F"), -32.0, 5. / 9., 0.0);

			mgr.AddUnitType(_T("Angle"), 0.0, 0.0, 0.0, 0.0, 1.0);
			mgr.AddUnit(_T("Angle"), _T("rad"), 1.0);

			// Pressure = Mass / (Length * Time^2)
			mgr.AddUnitType(_T("Pressure"), 1.0, -1.0, -2.0, 0.0, 0.0);

			// ThermalExpansion = 1 / Temperature
			mgr.AddUnitType(_T("ThermalExpansion"), 0.0, 0.0, 0.0, -1.0, 0.0);
		}

		TEST_METHOD(TestSetBaseUnits)
		{
			DynamicUnitTypeManager mgr;
			SeedFundamentalUnitTypes(mgr);

			Assert::IsFalse(mgr.HasBaseUnits());
			Assert::ExpectException<WBFL::System::XProgrammingError>([&mgr]() { mgr.GetBaseUnit(_T("Pressure")); });

			mgr.SetBaseUnits(_T("kg"), _T("m"), _T("sec"), _T("C"), _T("rad"));
			Assert::IsTrue(mgr.HasBaseUnits());

			// A tag that doesn't exist under the corresponding fundamental unit type must be rejected, and
			// must not partially apply (the previously-set base units must survive unchanged).
			Assert::ExpectException<XUnit>([&mgr]() { mgr.SetBaseUnits(_T("junk"), _T("m"), _T("sec"), _T("C"), _T("rad")); });
			Assert::IsTrue(mgr.HasBaseUnits());
			Assert::IsTrue(IsEqual(mgr.GetBaseUnit(_T("Length")).GetConvFactor(), 1.0));
		}

		TEST_METHOD(TestGetBaseUnitComposesAcrossDimensions)
		{
			// Pressure's base unit (Mass/(Length*Time^2)) must be the product of the three base units raised
			// to their respective exponents, independent of which tag was chosen for each fundamental type.
			DynamicUnitTypeManager mgr;
			SeedFundamentalUnitTypes(mgr);
			mgr.SetBaseUnits(_T("lb"), _T("ft"), _T("sec"), _T("F"), _T("rad"));

			const DynamicPhysical& pressureBase = mgr.GetBaseUnit(_T("Pressure"));
			Float64 expectedCf = pow(0.45359237, 1.0) * pow(0.3048, -1.0) * pow(1.0, -2.0);
			Assert::IsTrue(IsEqual(pressureBase.GetConvFactor(), expectedCf));
			Assert::IsTrue(IsEqual(pressureBase.GetPreTerm(), 0.0));
			Assert::IsTrue(IsEqual(pressureBase.GetPostTerm(), 0.0));

			// Converting a value already in this manager's own Pressure base units to itself must be a
			// no-op, since fromMgr and toMgr's base units are identical.
			Assert::IsTrue(IsEqual(Convert(42.0, pressureBase, mgr.GetBaseUnit(_T("Pressure"))), 42.0));
		}

		TEST_METHOD(TestGetBaseUnitTemperatureExponentGating)
		{
			// Temperature's pre/post conversion terms must be carried into a composite base unit only when
			// that unit type's temperature exponent is exactly 1 - not for ThermalExpansion (exponent -1),
			// even though its base unit is derived from the very same Fahrenheit tag, whose pre term (-32)
			// would badly corrupt the result if it leaked in.
			DynamicUnitTypeManager mgr;
			SeedFundamentalUnitTypes(mgr);
			mgr.SetBaseUnits(_T("kg"), _T("m"), _T("sec"), _T("F"), _T("rad"));

			const DynamicPhysical& temperatureBase = mgr.GetBaseUnit(_T("Temperature"));
			Assert::IsTrue(IsEqual(temperatureBase.GetConvFactor(), 5. / 9.));
			Assert::IsTrue(IsEqual(temperatureBase.GetPreTerm(), -32.0));

			const DynamicPhysical& thermalExpansionBase = mgr.GetBaseUnit(_T("ThermalExpansion"));
			Assert::IsTrue(IsEqual(thermalExpansionBase.GetConvFactor(), 9. / 5.)); // 1 / (5/9)
			Assert::IsTrue(IsEqual(thermalExpansionBase.GetPreTerm(), 0.0));
			Assert::IsTrue(IsEqual(thermalExpansionBase.GetPostTerm(), 0.0));

			// steel's coefficient of thermal expansion, ~6.5e-6/F - converting it from this manager's own
			// (1/F) base unit to itself must round-trip exactly, exercising the composed conversion equation
			// end to end rather than just its individual terms.
			Assert::IsTrue(IsEqual(Convert(6.5e-6, thermalExpansionBase, thermalExpansionBase), 6.5e-6));
		}

		TEST_METHOD(TestConvertBetweenTwoManagersBaseUnits)
		{
			// The scenario ConvertBetweenBaseUnits() (WBFL::Units::UnitsXML) is built on: two
			// independently-configured managers, each with their own base units, converting a value from
			// one's base units to the other's.
			DynamicUnitTypeManager fromMgr;
			SeedFundamentalUnitTypes(fromMgr);
			fromMgr.SetBaseUnits(_T("lb"), _T("ft"), _T("sec"), _T("F"), _T("rad"));

			DynamicUnitTypeManager toMgr;
			SeedFundamentalUnitTypes(toMgr);
			toMgr.SetBaseUnits(_T("kg"), _T("m"), _T("sec"), _T("C"), _T("rad"));

			// Length reduces to a single dimension, so the expected result is just the from-tag's own
			// conversion factor (ft -> m).
			Float64 lengthResult = Convert(10.0, fromMgr.GetBaseUnit(_T("Length")), toMgr.GetBaseUnit(_T("Length")));
			Assert::IsTrue(IsEqual(lengthResult, 10.0 * 0.3048));

			// Pressure exercises all three of Mass/Length/Time at once.
			Float64 fromCf = pow(0.45359237, 1.0) * pow(0.3048, -1.0);
			Float64 pressureResult = Convert(1.0, fromMgr.GetBaseUnit(_T("Pressure")), toMgr.GetBaseUnit(_T("Pressure")));
			Assert::IsTrue(IsEqual(pressureResult, fromCf));
		}
	};
}
