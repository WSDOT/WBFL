#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

class TestLLDF : public LiveLoadDistributionFactorBase
{
public:
	using LiveLoadDistributionFactorBase::LiveLoadDistributionFactorBase;
   bool m_bROA = true;

   virtual Float64 MomentSkewCorrectionFactor() const { return 0.75; }
   virtual Float64 ShearSkewCorrectionFactor() const { return 0.85; }

protected:
   virtual bool TestRangeOfApplicability(Location loc) const { return m_bROA; }

   virtual DFResult GetMomentDF_Int_1_Strength() const { DFResult result; result.mg = 1.0; return result; }
   virtual DFResult GetMomentDF_Int_2_Strength() const { DFResult result; result.mg = 2.0; return result; }
   virtual DFResult GetMomentDF_Ext_1_Strength() const { DFResult result; result.mg = 3.0; return result; }
   virtual DFResult GetMomentDF_Ext_2_Strength() const { DFResult result; result.mg = 4.0; return result; }
   virtual DFResult GetShearDF_Int_1_Strength() const { DFResult result; result.mg = 5.0; return result; }
   virtual DFResult GetShearDF_Int_2_Strength() const { DFResult result; result.mg = 6.0; return result; }
   virtual DFResult GetShearDF_Ext_1_Strength() const { DFResult result; result.mg = 7.0; return result; }
   virtual DFResult GetShearDF_Ext_2_Strength() const { DFResult result; result.mg = 8.0; return result; }
};

namespace LrfdUnitTests
{
	TEST_CLASS(TestLiveLoadDistributionFactorBase)
	{
		TEST_METHOD(BasicLLDF)
		{
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::PoundMass);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Feet);
         WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

         TestLLDF lldf(0, 8.0, std::vector<Float64>{8.0, 8.0, 8.0, 8.0, 8.0}, 7.0, 7.0, 4, 12.0, true, true);

         Assert::AreEqual(3.0, lldf.MomentDF(LiveLoadDistributionFactorBase::Location::ExtGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::One, LimitState::ServiceI));
         Assert::AreEqual(1.0, lldf.MomentDF(LiveLoadDistributionFactorBase::Location::IntGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::One, LimitState::ServiceI));
         Assert::AreEqual(4.0, lldf.MomentDF(LiveLoadDistributionFactorBase::Location::ExtGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::TwoOrMore, LimitState::ServiceI));
         Assert::AreEqual(2.0, lldf.MomentDF(LiveLoadDistributionFactorBase::Location::IntGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::TwoOrMore, LimitState::ServiceI));

         Assert::AreEqual(3.0, lldf.MomentDF(LiveLoadDistributionFactorBase::Location::ExtGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::One, LimitState::StrengthI));
         Assert::AreEqual(1.0, lldf.MomentDF(LiveLoadDistributionFactorBase::Location::IntGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::One, LimitState::StrengthI));
         Assert::AreEqual(4.0, lldf.MomentDF(LiveLoadDistributionFactorBase::Location::ExtGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::TwoOrMore, LimitState::StrengthI));
         Assert::AreEqual(2.0, lldf.MomentDF(LiveLoadDistributionFactorBase::Location::IntGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::TwoOrMore, LimitState::StrengthI));

         Assert::AreEqual(7.0, lldf.ShearDF(LiveLoadDistributionFactorBase::Location::ExtGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::One, LimitState::ServiceI));
         Assert::AreEqual(5.0, lldf.ShearDF(LiveLoadDistributionFactorBase::Location::IntGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::One, LimitState::ServiceI));
         Assert::AreEqual(8.0, lldf.ShearDF(LiveLoadDistributionFactorBase::Location::ExtGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::TwoOrMore, LimitState::ServiceI));
         Assert::AreEqual(6.0, lldf.ShearDF(LiveLoadDistributionFactorBase::Location::IntGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::TwoOrMore, LimitState::ServiceI));

         Assert::AreEqual(7.0, lldf.ShearDF(LiveLoadDistributionFactorBase::Location::ExtGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::One, LimitState::StrengthI));
         Assert::AreEqual(5.0, lldf.ShearDF(LiveLoadDistributionFactorBase::Location::IntGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::One, LimitState::StrengthI));
         Assert::AreEqual(8.0, lldf.ShearDF(LiveLoadDistributionFactorBase::Location::ExtGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::TwoOrMore, LimitState::StrengthI));
         Assert::AreEqual(6.0, lldf.ShearDF(LiveLoadDistributionFactorBase::Location::IntGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::TwoOrMore, LimitState::StrengthI));
      }

      TEST_METHOD(MomentByLeverRule)
      {
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::PoundMass);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Feet);
         WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

         TestLLDF lldf(0, 8.0, std::vector<Float64>{8.0, 8.0, 8.0, 8.0, 8.0}, 7.0, 7.0, 4, 12.0, true, true);

         auto result = lldf.DistributeMomentByLeverRule(LiveLoadDistributionFactorBase::Location::ExtGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::One, true);
         Assert::IsTrue(result.ControllingMethod & LEVER_RULE);
         Assert::IsTrue(result.ControllingMethod & MOMENT_SKEW_CORRECTION_APPLIED);
         Assert::AreEqual(1.125, result.mg);
         Assert::AreEqual(0.75, result.SkewCorrectionFactor);
         Assert::IsTrue(result.LeverRuleData.bWasUsed);
         Assert::IsTrue(result.LeverRuleData.bWasExterior);
         Assert::AreEqual(1.2, result.LeverRuleData.m);
         Assert::AreEqual(7.0, result.LeverRuleData.de);
         Assert::AreEqual((IndexType)1, result.LeverRuleData.nLanesUsed);
         Assert::AreEqual(1.5, result.LeverRuleData.mg);

         result = lldf.DistributeMomentByLeverRule(LiveLoadDistributionFactorBase::Location::IntGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::One, true);
         Assert::IsTrue(result.ControllingMethod & LEVER_RULE);
         Assert::IsTrue(result.ControllingMethod & MOMENT_SKEW_CORRECTION_APPLIED);
         Assert::AreEqual(0.5625, result.mg);
         Assert::AreEqual(0.75, result.SkewCorrectionFactor);
         Assert::IsTrue(result.LeverRuleData.bWasUsed);
         Assert::IsFalse(result.LeverRuleData.bWasExterior);
         Assert::AreEqual(1.2, result.LeverRuleData.m);
         Assert::AreEqual(0.0, result.LeverRuleData.de);
         Assert::AreEqual((IndexType)1, result.LeverRuleData.nLanesUsed);
         Assert::AreEqual(0.75, result.LeverRuleData.mg);

         result = lldf.DistributeMomentByLeverRule(LiveLoadDistributionFactorBase::Location::ExtGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::TwoOrMore, true);
         Assert::IsTrue(result.ControllingMethod & LEVER_RULE);
         Assert::IsTrue(result.ControllingMethod & MOMENT_SKEW_CORRECTION_APPLIED);
         Assert::AreEqual(0.984375, result.mg);
         Assert::AreEqual(0.75, result.SkewCorrectionFactor);
         Assert::IsTrue(result.LeverRuleData.bWasUsed);
         Assert::IsTrue(result.LeverRuleData.bWasExterior);
         Assert::AreEqual(1.0, result.LeverRuleData.m);
         Assert::AreEqual(7.0, result.LeverRuleData.de);
         Assert::AreEqual((IndexType)2, result.LeverRuleData.nLanesUsed);
         Assert::AreEqual(1.3125, result.LeverRuleData.mg);

         result = lldf.DistributeMomentByLeverRule(LiveLoadDistributionFactorBase::Location::IntGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::TwoOrMore, true);
         Assert::IsTrue(result.ControllingMethod & LEVER_RULE);
         Assert::IsTrue(result.ControllingMethod & MOMENT_SKEW_CORRECTION_APPLIED);
         Assert::AreEqual(0.65625, result.mg);
         Assert::AreEqual(0.75, result.SkewCorrectionFactor);
         Assert::IsTrue(result.LeverRuleData.bWasUsed);
         Assert::IsFalse(result.LeverRuleData.bWasExterior);
         Assert::AreEqual(1.0, result.LeverRuleData.m);
         Assert::AreEqual(0.0, result.LeverRuleData.de);
         Assert::AreEqual((IndexType)2, result.LeverRuleData.nLanesUsed);
         Assert::AreEqual(0.875, result.LeverRuleData.mg);
      }

      TEST_METHOD(ShearByLeverRule)
      {
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::PoundMass);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Feet);
         WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

         TestLLDF lldf(0, 8.0, std::vector<Float64>{8.0, 8.0, 8.0, 8.0, 8.0}, 7.0, 7.0, 4, 12.0, true, true);

         auto result = lldf.DistributeShearByLeverRule(LiveLoadDistributionFactorBase::Location::ExtGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::One, true);
         Assert::IsTrue(result.ControllingMethod & LEVER_RULE);
         Assert::IsTrue(result.ControllingMethod & SHEAR_SKEW_CORRECTION_APPLIED);
         Assert::AreEqual(1.275, result.mg, 0.001);
         Assert::AreEqual(0.85, result.SkewCorrectionFactor);
         Assert::IsTrue(result.LeverRuleData.bWasUsed);
         Assert::IsTrue(result.LeverRuleData.bWasExterior);
         Assert::AreEqual(1.2, result.LeverRuleData.m);
         Assert::AreEqual(7.0, result.LeverRuleData.de);
         Assert::AreEqual((IndexType)1, result.LeverRuleData.nLanesUsed);
         Assert::AreEqual(1.5, result.LeverRuleData.mg);

         result = lldf.DistributeShearByLeverRule(LiveLoadDistributionFactorBase::Location::IntGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::One, true);
         Assert::IsTrue(result.ControllingMethod & LEVER_RULE);
         Assert::IsTrue(result.ControllingMethod & SHEAR_SKEW_CORRECTION_APPLIED);
         Assert::AreEqual(0.6375, result.mg);
         Assert::AreEqual(0.85, result.SkewCorrectionFactor);
         Assert::IsTrue(result.LeverRuleData.bWasUsed);
         Assert::IsFalse(result.LeverRuleData.bWasExterior);
         Assert::AreEqual(1.2, result.LeverRuleData.m);
         Assert::AreEqual(0.0, result.LeverRuleData.de);
         Assert::AreEqual((IndexType)1, result.LeverRuleData.nLanesUsed);
         Assert::AreEqual(0.75, result.LeverRuleData.mg);

         result = lldf.DistributeShearByLeverRule(LiveLoadDistributionFactorBase::Location::ExtGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::TwoOrMore, true);
         Assert::IsTrue(result.ControllingMethod & LEVER_RULE);
         Assert::IsTrue(result.ControllingMethod & SHEAR_SKEW_CORRECTION_APPLIED);
         Assert::AreEqual(1.115625, result.mg, 0.000001);
         Assert::AreEqual(0.85, result.SkewCorrectionFactor);
         Assert::IsTrue(result.LeverRuleData.bWasUsed);
         Assert::IsTrue(result.LeverRuleData.bWasExterior);
         Assert::AreEqual(1.0, result.LeverRuleData.m);
         Assert::AreEqual(7.0, result.LeverRuleData.de);
         Assert::AreEqual((IndexType)2, result.LeverRuleData.nLanesUsed);
         Assert::AreEqual(1.3125, result.LeverRuleData.mg);

         result = lldf.DistributeShearByLeverRule(LiveLoadDistributionFactorBase::Location::IntGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::TwoOrMore, true);
         Assert::IsTrue(result.ControllingMethod & LEVER_RULE);
         Assert::IsTrue(result.ControllingMethod & SHEAR_SKEW_CORRECTION_APPLIED);
         Assert::AreEqual(0.74375, result.mg);
         Assert::AreEqual(0.85, result.SkewCorrectionFactor);
         Assert::IsTrue(result.LeverRuleData.bWasUsed);
         Assert::IsFalse(result.LeverRuleData.bWasExterior);
         Assert::AreEqual(1.0, result.LeverRuleData.m);
         Assert::AreEqual(0.0, result.LeverRuleData.de);
         Assert::AreEqual((IndexType)2, result.LeverRuleData.nLanesUsed);
         Assert::AreEqual(0.875, result.LeverRuleData.mg);
      }

      TEST_METHOD(ReactionByLeverRule)
      {
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::PoundMass);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Feet);
         WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

         TestLLDF lldf(0, 8.0, std::vector<Float64>{8.0, 8.0, 8.0, 8.0, 8.0}, 7.0, 7.0, 4, 12.0, true, true);

         auto result = lldf.DistributeReactionByLeverRule(LiveLoadDistributionFactorBase::Location::ExtGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::One, true);
         Assert::IsTrue(result.ControllingMethod & LEVER_RULE);
         Assert::IsTrue(result.ControllingMethod & SHEAR_SKEW_CORRECTION_APPLIED);
         Assert::AreEqual(1.275, result.mg, 0.001);
         Assert::AreEqual(0.85, result.SkewCorrectionFactor);
         Assert::IsTrue(result.LeverRuleData.bWasUsed);
         Assert::IsTrue(result.LeverRuleData.bWasExterior);
         Assert::AreEqual(1.2, result.LeverRuleData.m);
         Assert::AreEqual(7.0, result.LeverRuleData.de);
         Assert::AreEqual((IndexType)1, result.LeverRuleData.nLanesUsed);
         Assert::AreEqual(1.5, result.LeverRuleData.mg);

         result = lldf.DistributeReactionByLeverRule(LiveLoadDistributionFactorBase::Location::IntGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::One, true);
         Assert::IsTrue(result.ControllingMethod & LEVER_RULE);
         Assert::IsTrue(result.ControllingMethod & SHEAR_SKEW_CORRECTION_APPLIED);
         Assert::AreEqual(0.6375, result.mg);
         Assert::AreEqual(0.85, result.SkewCorrectionFactor);
         Assert::IsTrue(result.LeverRuleData.bWasUsed);
         Assert::IsFalse(result.LeverRuleData.bWasExterior);
         Assert::AreEqual(1.2, result.LeverRuleData.m);
         Assert::AreEqual(0.0, result.LeverRuleData.de);
         Assert::AreEqual((IndexType)1, result.LeverRuleData.nLanesUsed);
         Assert::AreEqual(0.75, result.LeverRuleData.mg);

         result = lldf.DistributeReactionByLeverRule(LiveLoadDistributionFactorBase::Location::ExtGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::TwoOrMore, true);
         Assert::IsTrue(result.ControllingMethod & LEVER_RULE);
         Assert::IsTrue(result.ControllingMethod & SHEAR_SKEW_CORRECTION_APPLIED);
         Assert::AreEqual(1.115625, result.mg, 0.000001);
         Assert::AreEqual(0.85, result.SkewCorrectionFactor);
         Assert::IsTrue(result.LeverRuleData.bWasUsed);
         Assert::IsTrue(result.LeverRuleData.bWasExterior);
         Assert::AreEqual(1.0, result.LeverRuleData.m);
         Assert::AreEqual(7.0, result.LeverRuleData.de);
         Assert::AreEqual((IndexType)2, result.LeverRuleData.nLanesUsed);
         Assert::AreEqual(1.3125, result.LeverRuleData.mg);

         result = lldf.DistributeReactionByLeverRule(LiveLoadDistributionFactorBase::Location::IntGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::TwoOrMore, true);
         Assert::IsTrue(result.ControllingMethod & LEVER_RULE);
         Assert::IsTrue(result.ControllingMethod & SHEAR_SKEW_CORRECTION_APPLIED);
         Assert::AreEqual(0.74375, result.mg);
         Assert::AreEqual(0.85, result.SkewCorrectionFactor);
         Assert::IsTrue(result.LeverRuleData.bWasUsed);
         Assert::IsFalse(result.LeverRuleData.bWasExterior);
         Assert::AreEqual(1.0, result.LeverRuleData.m);
         Assert::AreEqual(0.0, result.LeverRuleData.de);
         Assert::AreEqual((IndexType)2, result.LeverRuleData.nLanesUsed);
         Assert::AreEqual(0.875, result.LeverRuleData.mg);
      }

      TEST_METHOD(LeverRuleEx)
      {
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::PoundMass);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Feet);
         WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

         TestLLDF lldf(0, 8.0, std::vector<Float64>{8.0, 8.0, 8.0, 8.0, 8.0}, 7.0, 7.0, 4, 12.0, true, true);

         auto result = lldf.DistributeByLeverRuleEx(LiveLoadDistributionFactorBase::Location::ExtGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::One, true);
         Assert::AreEqual(1.5, result.mg, 0.001);
         Assert::IsTrue(result.bWasUsed);
         Assert::IsTrue(result.bWasExterior);
         Assert::AreEqual(1.2, result.m);
         Assert::AreEqual(7.0, result.de);
         Assert::AreEqual((IndexType)1, result.nLanesUsed);
         Assert::AreEqual((IndexType)6, result.Nb);

         result = lldf.DistributeByLeverRuleEx(LiveLoadDistributionFactorBase::Location::IntGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::One, true);
         Assert::AreEqual(0.75, result.mg, 0.001);
         Assert::IsTrue(result.bWasUsed);
         Assert::IsFalse(result.bWasExterior);
         Assert::AreEqual(1.2, result.m);
         Assert::AreEqual(0.0, result.de);
         Assert::AreEqual((IndexType)1, result.nLanesUsed);
         Assert::AreEqual((IndexType)6, result.Nb);

         result = lldf.DistributeByLeverRuleEx(LiveLoadDistributionFactorBase::Location::ExtGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::TwoOrMore, true);
         Assert::AreEqual(1.3125, result.mg, 0.001);
         Assert::IsTrue(result.bWasUsed);
         Assert::IsTrue(result.bWasExterior);
         Assert::AreEqual(1.0, result.m);
         Assert::AreEqual(7.0, result.de);
         Assert::AreEqual((IndexType)2, result.nLanesUsed);
         Assert::AreEqual((IndexType)6, result.Nb);

         result = lldf.DistributeByLeverRuleEx(LiveLoadDistributionFactorBase::Location::IntGirder, LiveLoadDistributionFactorBase::NumLoadedLanes::TwoOrMore, true);
         Assert::AreEqual(0.875, result.mg, 0.001);
         Assert::IsTrue(result.bWasUsed);
         Assert::IsFalse(result.bWasExterior);
         Assert::AreEqual(1.0, result.m);
         Assert::AreEqual(0.0, result.de);
         Assert::AreEqual((IndexType)2, result.nLanesUsed);
         Assert::AreEqual((IndexType)6, result.Nb);
      }
   };
}
