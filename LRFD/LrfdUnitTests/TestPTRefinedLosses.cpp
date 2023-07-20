#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestPTRefinedLosses)
	{
	public:
		
		TEST_METHOD(Test)
		{
			LRFDAutoVersion av;
			
			Float64 Fpj   = WBFL::Units::ConvertToSysUnits( 0.80*1860, WBFL::Units::Measure::MPa );
			Float64 Ag    = WBFL::Units::ConvertToSysUnits( 486051, WBFL::Units::Measure::Millimeter2 );
			Float64 Ig    = WBFL::Units::ConvertToSysUnits( 126011e6, WBFL::Units::Measure::Millimeter4 );
			Float64 Ybg   = WBFL::Units::ConvertToSysUnits( 608, WBFL::Units::Measure::Millimeter );
			Float64 Ic    = WBFL::Units::ConvertToSysUnits( 283.7e9, WBFL::Units::Measure::Millimeter4 );
			Float64 Ybc   = WBFL::Units::ConvertToSysUnits( 977, WBFL::Units::Measure::Millimeter );
			Float64 e     = WBFL::Units::ConvertToSysUnits( 489, WBFL::Units::Measure::Millimeter );
			Float64 Aps   = WBFL::Units::ConvertToSysUnits( 5133, WBFL::Units::Measure::Millimeter2 );
			Float64 Mdlg  = WBFL::Units::ConvertToSysUnits( 1328, WBFL::Units::Measure::KilonewtonMeter );
			Float64 Madlg = WBFL::Units::ConvertToSysUnits( 2900-1328, WBFL::Units::Measure::KilonewtonMeter );
			Float64 Msidl = WBFL::Units::ConvertToSysUnits( 540+353, WBFL::Units::Measure::KilonewtonMeter );
			Float64 Rh    = 70.;
			Float64 Eci   = WBFL::Units::ConvertToSysUnits( 30360, WBFL::Units::Measure::MPa );
			Float64 dfFR = WBFL::Units::ConvertToSysUnits(5.5, WBFL::Units::Measure::KSI);
			Float64 Fcgp = WBFL::Units::ConvertToSysUnits(8.0, WBFL::Units::Measure::KSI);
			Float64 dfES = WBFL::Units::ConvertToSysUnits(22.5, WBFL::Units::Measure::KSI);

			
			PTRefinedLosses loss( WBFL::Materials::PsStrand::Grade::Gr1860,
			                     WBFL::Materials::PsStrand::Type::LowRelaxation,
			                     Fpj, Ag, Ig, Ybg, Ic, Ybc, e, Aps, Mdlg, Madlg, Msidl,
			                     Rh, Eci, dfFR, Fcgp, dfES );
			
			LRFDVersionMgr::RegisterListener( &loss );
			
			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FourthEdition2007);
			Assert::ExpectException<XPsLosses>([&]() {loss.FinalLosses(); });

			LRFDVersionMgr::SetVersion( LRFDVersionMgr::Version::FirstEdition1994 );

			Assert::AreEqual(33715363.163601309, loss.ShrinkageLosses(), 0.00001);
			Assert::AreEqual(600289394.63437223, loss.CreepLosses(), 0.00001);
			Assert::AreEqual(0.0, loss.RelaxationLossesAfterXfer(), 0.00001);
			Assert::AreEqual(634004757.79797351, loss.FinalLosses(), 0.00001);
			Assert::AreEqual(8801043.6442782544, loss.GetDeltaFcdp(), 0.00001);
			Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
			Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

			LRFDVersionMgr::UnregisterListener( &loss );
		}
	};
}
