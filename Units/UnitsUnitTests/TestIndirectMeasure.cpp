#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Units;

namespace UnitsUnitTest
{
	template <typename MeasureData,typename MeasureType>
	void Check(const MeasureData& md,const MeasureType& mt)
	{
		Assert::IsTrue(md.UnitOfMeasure == mt);
		Assert::AreEqual(md.Width, (Uint16)6);
		Assert::AreEqual(md.Precision, (Uint16)3);
		Assert::IsTrue(md.Format == WBFL::System::NumericFormatTool::Format::Automatic);
	}

	TEST_CLASS(TestIndirectMeasure)
	{
	public:
		
		TEST_METHOD(Test)
		{
         // IndirectMeasure is basically a data structure holding indirect measure types.
         // All we can really test is the default values
			IndirectMeasure id;
			Assert::AreEqual(id.Name.c_str(), _T("Default"));
			
         Assert::AreEqual(id.Scalar.Width, (Uint16)8);
         Assert::AreEqual(id.Scalar.Precision, (Uint16)3);
         Assert::IsTrue(id.Scalar.Format == WBFL::System::NumericFormatTool::Format::Fixed);

         Assert::AreEqual(id.Percentage.Width, (Uint16)6);
         Assert::AreEqual(id.Percentage.Precision, (Uint16)2);
         Assert::IsTrue(id.Percentage.Format == WBFL::System::NumericFormatTool::Format::Fixed);

			Check(id.ComponentDim, Measure::Millimeter);
         Check(id.XSectionDim, Measure::Millimeter);
         Check(id.SpanLength, Measure::Meter);
         Check(id.AlignmentLength, Measure::Meter);
         Check(id.Deflection, Measure::Millimeter);
         Check(id.Area, Measure::Millimeter2);
         Check(id.MomentOfInertia, Measure::Millimeter4);
         Check(id.SectModulus, Measure::Millimeter3);
         Check(id.AvOverS, Measure::Meter2PerMeter);
         Check(id.Stress, Measure::MPa);
         Check(id.SmallStress, Measure::MPa);
         Check(id.WindPressure, Measure::Pa);
         Check(id.ModE, Measure::MPa);
         Check(id.GeneralForce, Measure::Kilonewton);
         Check(id.Tonnage, Measure::Kilonewton);
         Check(id.Shear, Measure::Kilonewton);
         Check(id.Moment, Measure::KilonewtonMeter);
         Check(id.SmallMoment, Measure::NewtonMillimeter);
         Check(id.Angle, Measure::Degree);
         Check(id.RadAngle, Measure::Radian);
         Check(id.Density, Measure::KgPerMeter3);
         Check(id.MassPerLength, Measure::KgPerMeter);
         Check(id.ForcePerLength, Measure::KilonewtonPerMeter);
         Check(id.MomentPerAngle, Measure::KiloNewtonMeterPerRadian);
         Check(id.Time, Measure::Hour);
         Check(id.Time2, Measure::Day);
         Check(id.Time3, Measure::Day);
         Check(id.PerLength, Measure::PerMillimeter);
         Check(id.Curvature, Measure::PerMillimeter);
         Check(id.ForceLength2, Measure::KilonewtonMeter2);
         Check(id.SqrtPressure, Measure::SqrtMPa);
         Check(id.Velocity, Measure::KilometerPerHour);
      }
	};
}
