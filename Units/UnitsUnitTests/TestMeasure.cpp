#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Units;

namespace UnitsUnitTest
{
	TEST_CLASS(TestMeasure)
	{
	public:
		
		template<typename T>
		void Check(const T& t, Float64 cf, TCHAR* strUnit)
		{
			Assert::AreEqual(cf, t.GetConvFactor());
			Assert::AreEqual(strUnit, t.UnitTag().c_str());
		}

		template<typename T>
		void Check(const T& t, Float64 pre, Float64 cf, Float64 post, TCHAR* strUnit)
		{
			Assert::AreEqual(pre, t.GetPreTerm());
			Assert::AreEqual(cf, t.GetConvFactor());
			Assert::AreEqual(post, t.GetPostTerm());
			Assert::AreEqual(strUnit, t.UnitTag().c_str());
		}

		TEST_METHOD(Test)
		{
			// This is a class of nothing but static data members
			// All we can check is the initialization
			Check(Measure::Kilogram, 1.000, _T("kg"));
			Check(Measure::Gram, 0.001, _T("g"));
			Check(Measure::MetricTon, 1.0e03, _T("MT"));
			Check(Measure::Slug, 14.5939029372, _T("slug"));
			Check(Measure::PoundMass, 0.45359237, _T("lbm"));
			Check(Measure::KSlug, 14593.9029372, _T("kslug"));
			Check(Measure::_12Slug, 175.126835246, _T("12slug"));
			Check(Measure::_12KSlug, 175126.835246, _T("12kslug"));

			Check(Measure::KgPerMeter,1.000, _T("kg/m"));
			Check(Measure::LbmPerFeet,0.671968975139, _T("lbm/ft"));
			Check(Measure::SlugPerFeet,0.0208854342115, _T("slug/ft"));
			Check(Measure::LbfPerFeet,1.48816394357, _T("lbf/ft"));

			Check(Measure::Meter,1.0, _T("m"));
			Check(Measure::Millimeter,1.0e-03, _T("mm"));
			Check(Measure::Centimeter,1.0e-02, _T("cm"));
			Check(Measure::Kilometer,1.0e03, _T("km"));
			Check(Measure::Feet,0.3048, _T("ft"));
			Check(Measure::USSurveyFoot,1200. / 3937., _T("ft"));
			Check(Measure::Inch,0.0254, _T("in"));
			Check(Measure::Mile,1609.344, _T("mile"));
			Check(Measure::Yard,0.9144, _T("yd"));
			Check(Measure::USSurveyYard,3600. / 3937., _T("yd"));

			Check(Measure::Meter2PerMeter,1.0, _T("m^2/m"));
			Check(Measure::Millimeter2PerMillimeter,1.0e-03, _T("mm^2/mm"));
			Check(Measure::Millimeter2PerMeter,1.0e-06, _T("mm^2/m"));
			Check(Measure::Feet2PerFoot,0.3048, _T("ft^2/ft"));
			Check(Measure::Inch2PerInch,0.0254, _T("in^2/in"));
			Check(Measure::Inch2PerFoot,0.0021166666666667, _T("in^2/ft"));

			Check(Measure::Meter2,1.0, _T("m^2"));
			Check(Measure::Millimeter2,1.0e-06, _T("mm^2"));
			Check(Measure::Centimeter2,1.0e-04, _T("cm^2"));
			Check(Measure::Kilometer2,1.0e06, _T("km^2"));
			Check(Measure::Feet2,0.09290304, _T("ft^2"));
			Check(Measure::Inch2,0.00064516, _T("in^2"));
			Check(Measure::Mile2,2589988.11034, _T("mile^2"));
			Check(Measure::Yard2,0.83612736, _T("yd^2"));

			Check(Measure::Meter3,1.0, _T("m^3"));
			Check(Measure::Millimeter3,1.0e-09, _T("mm^3"));
			Check(Measure::Centimeter3,1.0e-06, _T("cm^3"));
			Check(Measure::Kilometer3,1.0e09, _T("km^3"));
			Check(Measure::Feet3,0.028316846592, _T("ft^3"));
			Check(Measure::Inch3,0.000016387064, _T("in^3"));
			Check(Measure::Mile3,4168181825.44, _T("mile^3"));
			Check(Measure::Yard3,0.764554857984, _T("yd^3"));

			Check(Measure::Meter4,1.0, _T("m^4"));
			Check(Measure::Millimeter4,1.0e-12, _T("mm^4"));
			Check(Measure::Centimeter4,1.0e-08, _T("cm^4"));
			Check(Measure::Kilometer4,1.0e12, _T("km^4"));
			Check(Measure::Feet4,8.63097484124e-03, _T("ft^4"));
			Check(Measure::Inch4,4.162314256e-07, _T("in^4"));
			Check(Measure::Mile4,6.70803841168e12, _T("mile^4"));
			Check(Measure::Yard4,0.699108962141, _T("yd^4"));

			Check(Measure::Second,1.0, _T("sec"));
			Check(Measure::Minute,60.0, _T("min"));
			Check(Measure::Hour,3600.0, _T("hr"));
			Check(Measure::Day,86400.0, _T("day"));

			Check(Measure::Celsius,0.0, 1.0, 0.0, _T("C"));
			Check(Measure::Fahrenheit,-32.0, 5. / 9., 0.0, _T("F"));

			Check(Measure::Radian,1.0, _T("rad"));
			Check(Measure::Degree,1.74532925199e-02, _T("deg"));

			Check(Measure::Pa,1.0, _T("Pa"));
			Check(Measure::kPa,1.0e03, _T("kPa"));
			Check(Measure::MPa,1.0e06, _T("MPa"));
			Check(Measure::PSI,6.89475729317e03, _T("PSI"));
			Check(Measure::PSF,4.78802589803e01, _T("PSF"));
			Check(Measure::KSI,6.89475729317e06, _T("KSI"));
			Check(Measure::KSF,4.78802589803e04, _T("KSF"));

			Check(Measure::NewtonPerMeter3,1.0, _T("N/m^3"));
			Check(Measure::PCI,271447.1375263134, _T("PCI"));
			Check(Measure::PCF,157.08746384624618, _T("PCF"));

			Check(Measure::KgPerMeter3,1.0, _T("kg/m^3"));
			Check(Measure::LbmPerFeet3,16.01846337396013800, _T("lbm/ft^3"));
			Check(Measure::SlugPerFeet3,515.37881839319730000, _T("slug/ft^3"));
			Check(Measure::LbfPerFeet3,16.01846337396013800, _T("lbf/ft^3"));
			Check(Measure::KipPerFeet3,16018.46337396013800, _T("kip/ft^3"));

			Check(Measure::Newton,1.0, _T("N"));
			Check(Measure::Kilonewton,1.0e03, _T("kN"));
			Check(Measure::Pound,4.4482216152605, _T("lbf"));
			Check(Measure::Kip,4448.2216152605, _T("kip"));
			Check(Measure::Ton,8896.44323052, _T("ton"));

			Check(Measure::NewtonPerMeter,1.0, _T("N/m"));
			Check(Measure::KilonewtonPerMeter,1.0e03, _T("kN/m"));
			Check(Measure::NewtonPerMillimeter,1.0e03, _T("N/mm"));
			Check(Measure::LbfPerFoot,14.593902937206362, _T("lbf/ft"));
			Check(Measure::LbfPerInch,175.126835246, _T("lbf/in"));
			Check(Measure::KipPerFoot,14593.902937206362, _T("kip/ft"));
			Check(Measure::KipPerInch,175126.835246, _T("kip/in"));

			Check(Measure::NewtonMeter,1.0, _T("N-m"));
			Check(Measure::KilonewtonMeter,1.0e03, _T("kN-m"));
			Check(Measure::NewtonMillimeter,1.0e-03, _T("N-mm"));
			Check(Measure::InchLbf,0.112984829028, _T("in-lbf"));
			Check(Measure::KipFeet,1355.8179483314004, _T("kip-ft"));
			Check(Measure::KipInch,112.984829028, _T("kip-in"));

			Check(Measure::NewtonMeterPerRadian,1.0, _T("N-m/rad"));
			Check(Measure::KiloNewtonMeterPerRadian,1.0e03, _T("kN-m/rad"));
			Check(Measure::KipInchPerRadian,112.984829028, _T("kip-in/rad"));
			Check(Measure::KipFeetPerRadian,1355.81794833, _T("kip-ft/rad"));

			Check(Measure::SqrtPa,1.0, _T("Pa^0.5"));
			Check(Measure::SqrtMPa,1000.0, _T("MPa^0.5"));
			Check(Measure::SqrtKSI,2625.78698679, _T("KSI^0.5"));

			Check(Measure::MeterPerSec2,1.0, _T("m/s^2"));
			Check(Measure::FeetPerSec2,0.3048, _T("ft/s^2"));

			Check(Measure::PerMeter,1.0, _T("m^-1"));
			Check(Measure::PerMillimeter,1.0e3, _T("mm^-1"));
			Check(Measure::PerInch,39.3700787402, _T("in^-1"));
			Check(Measure::PerFeet,3.28083989501, _T("ft^-1"));;

			Check(Measure::NewtonMeter2,1.0, _T("N-m^2"));
			Check(Measure::NewtonMillimeter2,1.0e09, _T("N-mm^2"));
			Check(Measure::KilonewtonMeter2,1.0e03, _T("kN-m^2"));
			Check(Measure::KipFoot2,413.253311, _T("kip-ft^2"));
			Check(Measure::KipInch2,2.869815, _T("kip-in^2"));
			Check(Measure::LbfInch2,2.869815e-03, _T("lbf-in^2"));
			Check(Measure::LbfFoot2,0.413253, _T("lbf-ft^2"));

			Check(Measure::KilometerPerHour,0.2777777777777777, _T("Km/h"));
			Check(Measure::MeterPerSecond,1.0, _T("m/s"));
			Check(Measure::MilePerHour,0.44704, _T("MPH"));
			Check(Measure::FeetPerSecond,0.3048, _T("ft/s"));
		}
	};
}
