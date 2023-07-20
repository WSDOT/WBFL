#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestLoadModifier)
	{
	public:
		
      TEST_METHOD(LRFD_1st_Edition)
      {
         LRFDAutoVersion av;

         LoadModifier lm;

         // Test First Edition Implementation
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994);
         lm.SetDuctilityFactor(LoadModifier::Level::High);
         lm.SetImportanceFactor(LoadModifier::Level::High);
         lm.SetRedundancyFactor(LoadModifier::Level::High);

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI));
         Assert::AreEqual(1.157625, lm.GetLoadModifier(LimitState::StrengthI), 0.0001);

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI, Optimization::Min));
         Assert::AreEqual(1.157625, lm.GetLoadModifier(LimitState::StrengthI, Optimization::Min), 0.0001);
         
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueII, Optimization::Max));
         Assert::AreEqual(1.157625, lm.GetLoadModifier(LimitState::StrengthI, Optimization::Max), 0.0001);

         lm.SetDuctilityFactor(LoadModifier::Level::Normal);
         lm.SetImportanceFactor(LoadModifier::Level::Normal);
         lm.SetRedundancyFactor(LoadModifier::Level::Normal);

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::StrengthI));

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::StrengthI, Optimization::Min));

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::StrengthI, Optimization::Max));

         lm.SetDuctilityFactor(LoadModifier::Level::Low);
         lm.SetImportanceFactor(LoadModifier::Level::Low);
         lm.SetRedundancyFactor(LoadModifier::Level::Low);

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI));
         Assert::AreEqual(0.95, lm.GetLoadModifier(LimitState::StrengthI));

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI, Optimization::Min));
         Assert::AreEqual(0.95, lm.GetLoadModifier(LimitState::StrengthI, Optimization::Min));

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI, Optimization::Max));
         Assert::AreEqual(0.95, lm.GetLoadModifier(LimitState::StrengthI, Optimization::Max));

         lm.SetDuctilityFactor(LoadModifier::Level::Low, 0.98);
         lm.SetImportanceFactor(LoadModifier::Level::Low, 0.98);
         lm.SetRedundancyFactor(LoadModifier::Level::Normal, 10.0); // Should ignore the 10.0

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI));
         Assert::AreEqual(0.9604, lm.GetLoadModifier(LimitState::StrengthI), 0.0001);

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI, Optimization::Min));
         Assert::AreEqual(0.9604, lm.GetLoadModifier(LimitState::StrengthI, Optimization::Min), 0.0001);

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI, Optimization::Max));
         Assert::AreEqual(0.9604, lm.GetLoadModifier(LimitState::StrengthI, Optimization::Max), 0.0001);
      }

      TEST_METHOD(LRFD_2nd_Edition)
      {
         LRFDAutoVersion av;

         LoadModifier lm;

         // Test First Edition + 1996, 1997 Interims and Second Edition Implementation
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SecondEdition1998);
         lm.SetDuctilityFactor(LoadModifier::Level::High);
         lm.SetImportanceFactor(LoadModifier::Level::High);
         lm.SetRedundancyFactor(LoadModifier::Level::High);

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI, Optimization::Min));
         Assert::AreEqual(0.863837598531, lm.GetLoadModifier(LimitState::StrengthI, Optimization::Min), 0.0001);

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI, Optimization::Max));
         Assert::AreEqual(1.157625, lm.GetLoadModifier(LimitState::StrengthI, Optimization::Max), 0.0001);

         lm.SetDuctilityFactor(LoadModifier::Level::Normal);
         lm.SetImportanceFactor(LoadModifier::Level::Normal);
         lm.SetRedundancyFactor(LoadModifier::Level::Normal);

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::StrengthI, Optimization::Min));

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::StrengthI, Optimization::Max));

         lm.SetDuctilityFactor(LoadModifier::Level::Low);
         lm.SetImportanceFactor(LoadModifier::Level::Low);
         lm.SetRedundancyFactor(LoadModifier::Level::Low);

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::StrengthI, Optimization::Min));

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI, Optimization::Max));
         Assert::AreEqual(0.95, lm.GetLoadModifier(LimitState::StrengthI, Optimization::Max));

         lm.SetDuctilityFactor(LoadModifier::Level::Low, 0.98);
         lm.SetImportanceFactor(LoadModifier::Level::Low, 0.98);
         lm.SetRedundancyFactor(LoadModifier::Level::Normal, 10.0); // Should ignore the 10.0

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI, Optimization::Min));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::StrengthI, Optimization::Min));

         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ServiceI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::ExtremeEventI, Optimization::Max));
         Assert::AreEqual(1.0, lm.GetLoadModifier(LimitState::FatigueI, Optimization::Max));
         Assert::AreEqual(0.9604, lm.GetLoadModifier(LimitState::StrengthI, Optimization::Max), 0.0001);
      }
	};
}
