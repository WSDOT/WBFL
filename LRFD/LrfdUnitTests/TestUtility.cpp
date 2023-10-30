#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestUtility)
	{
	public:
		
      TEST_METHOD(IbeamEffFlangeWidth)
      {
         // Reference: WBFL\UnitTest\Supporting Documents\Effective Flange Width.mcd

         Float64 effSpanLength = 30864.;
         Float64 spacing = 1905.;
         Float64 overhang = 990.;
         Float64 tSlab = 175.;
         Float64 tWeb = 152.;
         Float64 wTopFlange = 635.;

         Float64 effFlangeWidth;

         effFlangeWidth = Utility::IbeamEffFlangeWidth(effSpanLength,
            spacing,
            spacing,
            tSlab,
            tWeb,
            wTopFlange,
            Utility::GirderPosition::Interior);
         Assert::AreEqual(1905., effFlangeWidth);

         effFlangeWidth = Utility::IbeamEffFlangeWidth(effSpanLength,
            overhang,
            spacing,
            tSlab,
            tWeb,
            wTopFlange,
            Utility::GirderPosition::LeftExterior);
         Assert::AreEqual(1942.5, effFlangeWidth);

         effFlangeWidth = Utility::IbeamEffFlangeWidth(effSpanLength,
            spacing,
            overhang,
            tSlab,
            tWeb,
            wTopFlange,
            Utility::GirderPosition::RightExterior);
         Assert::AreEqual(1942.5, effFlangeWidth);
      }

      TEST_METHOD(GetDesignLaneWidth)
      {
         BDSAutoVersion av;

         BDSManager::SetEdition(BDSManager::Edition::FirstEdition1994);

         BDSManager::SetUnits(BDSManager::Units::US);
         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(10., WBFL::Units::Measure::Feet), Utility::GetDesignLaneWidth(WBFL::Units::ConvertToSysUnits(10., WBFL::Units::Measure::Feet)));
         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(12., WBFL::Units::Measure::Feet), Utility::GetDesignLaneWidth(WBFL::Units::ConvertToSysUnits(18., WBFL::Units::Measure::Feet)));
         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(11., WBFL::Units::Measure::Feet), Utility::GetDesignLaneWidth(WBFL::Units::ConvertToSysUnits(22., WBFL::Units::Measure::Feet)));
         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(12., WBFL::Units::Measure::Feet), Utility::GetDesignLaneWidth(WBFL::Units::ConvertToSysUnits(28., WBFL::Units::Measure::Feet)));
         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(12., WBFL::Units::Measure::Feet), Utility::GetDesignLaneWidth(WBFL::Units::ConvertToSysUnits(37., WBFL::Units::Measure::Feet)));

         BDSManager::SetUnits(BDSManager::Units::SI);
         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(3200., WBFL::Units::Measure::Millimeter), Utility::GetDesignLaneWidth(WBFL::Units::ConvertToSysUnits(3200., WBFL::Units::Measure::Millimeter)));
         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(3600., WBFL::Units::Measure::Millimeter), Utility::GetDesignLaneWidth(WBFL::Units::ConvertToSysUnits(5000., WBFL::Units::Measure::Millimeter)));
         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(3250., WBFL::Units::Measure::Millimeter), Utility::GetDesignLaneWidth(WBFL::Units::ConvertToSysUnits(6500., WBFL::Units::Measure::Millimeter)));
         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(3600., WBFL::Units::Measure::Millimeter), Utility::GetDesignLaneWidth(WBFL::Units::ConvertToSysUnits(7500., WBFL::Units::Measure::Millimeter)));
         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(3600., WBFL::Units::Measure::Millimeter), Utility::GetDesignLaneWidth(WBFL::Units::ConvertToSysUnits(11000., WBFL::Units::Measure::Millimeter)));
      }

      TEST_METHOD(GetNumDesignLanes)
      {
         BDSAutoVersion av;

         BDSManager::SetEdition(BDSManager::Edition::FirstEdition1994);

         BDSManager::SetUnits(BDSManager::Units::US);
         Assert::IsTrue(Utility::GetNumDesignLanes(WBFL::Units::ConvertToSysUnits(10., WBFL::Units::Measure::Feet)) == 1);
         Assert::IsTrue(Utility::GetNumDesignLanes(WBFL::Units::ConvertToSysUnits(18., WBFL::Units::Measure::Feet)) == 1);
         Assert::IsTrue(Utility::GetNumDesignLanes(WBFL::Units::ConvertToSysUnits(22., WBFL::Units::Measure::Feet)) == 2);
         Assert::IsTrue(Utility::GetNumDesignLanes(WBFL::Units::ConvertToSysUnits(28., WBFL::Units::Measure::Feet)) == 2);
         Assert::IsTrue(Utility::GetNumDesignLanes(WBFL::Units::ConvertToSysUnits(37., WBFL::Units::Measure::Feet)) == 3);

         BDSManager::SetUnits(BDSManager::Units::SI);
         Assert::IsTrue(Utility::GetNumDesignLanes(WBFL::Units::ConvertToSysUnits(3200., WBFL::Units::Measure::Millimeter)) == 1);
         Assert::IsTrue(Utility::GetNumDesignLanes(WBFL::Units::ConvertToSysUnits(5000., WBFL::Units::Measure::Millimeter)) == 1);
         Assert::IsTrue(Utility::GetNumDesignLanes(WBFL::Units::ConvertToSysUnits(6500., WBFL::Units::Measure::Millimeter)) == 2);
         Assert::IsTrue(Utility::GetNumDesignLanes(WBFL::Units::ConvertToSysUnits(7500., WBFL::Units::Measure::Millimeter)) == 2);
         Assert::IsTrue(Utility::GetNumDesignLanes(WBFL::Units::ConvertToSysUnits(11000., WBFL::Units::Measure::Millimeter)) == 3);
      }

	};
}
