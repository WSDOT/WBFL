#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestNoncompositeApproximateLosses2005)
	{
	public:
		
      NoncompositeApproximateLosses2005 GetLossModel(WBFL::Materials::PsStrand::Grade grade, WBFL::Materials::PsStrand::Type type, NoncompositeApproximateLosses2005::BeamType beamType, NoncompositeApproximateLosses2005::Level level)
      {
         NoncompositeApproximateLosses2005 loss(
            grade,
            type,
            beamType,
            level,
            1396186227.0505831, // fpj permanent strands
            0.56485774124999988,   // area of girder
            0.23197765412628035,   // moment of inertia of girder Ixx
            0.80689655343184530,  // Centroid of girder measured from bottom
            0.73344249937779116, // eccentricity of permanent ps strands with respect to CG of girder
            0.73344249937779116, // eccentricity of permanent ps strands with respect to CG of girder
            0.0051799896399999995,  // area of permanent strand
            2701223.1744837998,  // Dead load moment of girder only
            1.0, // K for elastic shortening of PT members
            33205846111.428368,  // Modulus of elasticity of girder at transfer
            41368543.759020001,   // 28 day strength of girder concrete
            0.95, // PPR
            86400.000000000000   // Time until prestress transfer
            );
            return loss;
      }

      TEST_METHOD(BoxBeam)
		{
         auto loss = GetLossModel(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, NoncompositeApproximateLosses2005::BeamType::BoxBeam, NoncompositeApproximateLosses2005::Level::Average);

         LRFDAutoVersion av;

         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEdition2004); // loss method became invalid in 2005
         Assert::ExpectException<XPsLosses>([&]() {loss.FinalLosses(); });

         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FifthEdition2010); // loss method became invalid in 2010
         Assert::ExpectException<XPsLosses>([&]() {loss.FinalLosses(); });

         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEditionWith2005Interims); // first time loss method was added to 

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::Average);
         Assert::AreEqual(109087651.86937881, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(122737400.24817932, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(129621437.11159602, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(225059340.60217431, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(18434285.171043362, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6596451.7299161749, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::UpperBound);
         Assert::AreEqual(109087651.86937881, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(122737400.24817932, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(143410951.69793603, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(238848855.18851432, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(18434285.171043362, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6596451.7299161749, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         // Stress Relieved
         loss.SetStrandType(WBFL::Materials::PsStrand::Type::StressRelieved);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::Average);
         Assert::AreEqual(104526410.09122445, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(159125403.60642651, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(157200466.28427601, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(207127882.86029837, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(17663499.200022046, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6407962.2494997690, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::UpperBound);
         Assert::AreEqual(104526410.09122445, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(159125403.60642651, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(170989980.87061602, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(220917397.44663838, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(17663499.200022046, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6407962.2494997690, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);


         // Concrete limit exceptions
         loss.SetFc(WBFL::Units::ConvertToSysUnits(12.0, WBFL::Units::Measure::KSI)); // 10 ksi max
         Assert::ExpectException<XPsLosses>([&]() {loss.ElasticShorteningLosses(); });
      }

      TEST_METHOD(DoubleT)
      {
         auto loss = GetLossModel(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, NoncompositeApproximateLosses2005::BeamType::DoubleT, NoncompositeApproximateLosses2005::Level::Average);

         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEditionWith2005Interims); // first time loss method was added to 

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::Average);
         Assert::AreEqual(109087651.86937881, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(122737400.24817932, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(211669048.90031904, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(307106952.39089733, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(18434285.171043362, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6596451.7299161749, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::UpperBound);
         Assert::AreEqual(109087651.86937881, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(122737400.24817932, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(253037592.65933904, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(348475496.14991736, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(18434285.171043362, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6596451.7299161749, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         // Stress Relieved
         loss.SetStrandType(WBFL::Materials::PsStrand::Type::StressRelieved);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::Average);
         Assert::AreEqual(104526410.09122445, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(159125403.60642651, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(266827107.24567905, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(316754523.82170147, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(17663499.200022046, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6407962.2494997690, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::UpperBound);
         Assert::AreEqual(104526410.09122445, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(159125403.60642651, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(308195651.00469905, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(358123067.58072144, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(17663499.200022046, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6407962.2494997690, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);
      }

      TEST_METHOD(HollowCore)
      {
         auto loss = GetLossModel(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, NoncompositeApproximateLosses2005::BeamType::HollowCore, NoncompositeApproximateLosses2005::Level::Average);

         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEditionWith2005Interims); // first time loss method was added to 

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::Average);
         Assert::AreEqual(109087651.86937881, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(122737400.24817932, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(211669048.90031904, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(307106952.39089733, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(18434285.171043362, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6596451.7299161749, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::UpperBound);
         Assert::AreEqual(109087651.86937881, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(122737400.24817932, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(253037592.65933904, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(348475496.14991736, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(18434285.171043362, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6596451.7299161749, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         // Stress Relieved
         loss.SetStrandType(WBFL::Materials::PsStrand::Type::StressRelieved);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::Average);
         Assert::AreEqual(104526410.09122445, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(159125403.60642651, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(266827107.24567905, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(316754523.82170147, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(17663499.200022046, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6407962.2494997690, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::UpperBound);
         Assert::AreEqual(104526410.09122445, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(159125403.60642651, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(308195651.00469905, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(358123067.58072144, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(17663499.200022046, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6407962.2494997690, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);
      }

      TEST_METHOD(SingleT)
      {
         auto loss = GetLossModel(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, NoncompositeApproximateLosses2005::BeamType::SingleT, NoncompositeApproximateLosses2005::Level::Average);

         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEditionWith2005Interims); // first time loss method was added to 

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::Average);
         Assert::AreEqual(109087651.86937881, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(122737400.24817932, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(211669048.90031904, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(307106952.39089733, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(18434285.171043362, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6596451.7299161749, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::UpperBound);
         Assert::AreEqual(109087651.86937881, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(122737400.24817932, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(253037592.65933904, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(348475496.14991736, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(18434285.171043362, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6596451.7299161749, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         // Stress Relieved
         loss.SetStrandType(WBFL::Materials::PsStrand::Type::StressRelieved);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::Average);
         Assert::AreEqual(104526410.09122445, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(159125403.60642651, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(266827107.24567905, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(316754523.82170147, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(17663499.200022046, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6407962.2494997690, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::UpperBound);
         Assert::AreEqual(104526410.09122445, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(159125403.60642651, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(308195651.00469905, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(358123067.58072144, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(17663499.200022046, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6407962.2494997690, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);
      }

      TEST_METHOD(VoidedSlab)
      {
         auto loss = GetLossModel(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, NoncompositeApproximateLosses2005::BeamType::VoidedSlab, NoncompositeApproximateLosses2005::Level::Average);

         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEditionWith2005Interims); // first time loss method was added to 

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::Average);
         Assert::AreEqual(109087651.86937881, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(122737400.24817932, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(211669048.90031904, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(307106952.39089733, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(18434285.171043362, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6596451.7299161749, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::UpperBound);
         Assert::AreEqual(109087651.86937881, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(122737400.24817932, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(253037592.65933904, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(348475496.14991736, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(18434285.171043362, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6596451.7299161749, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         // Stress Relieved
         loss.SetStrandType(WBFL::Materials::PsStrand::Type::StressRelieved);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::Average);
         Assert::AreEqual(104526410.09122445, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(159125403.60642651, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(266827107.24567905, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(316754523.82170147, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(17663499.200022046, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6407962.2494997690, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::UpperBound);
         Assert::AreEqual(104526410.09122445, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(159125403.60642651, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(308195651.00469905, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(358123067.58072144, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(17663499.200022046, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6407962.2494997690, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);
      }

      TEST_METHOD(SolidSlab)
      {
         auto loss = GetLossModel(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, NoncompositeApproximateLosses2005::BeamType::SolidSlab, NoncompositeApproximateLosses2005::Level::Average);

         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEditionWith2005Interims); // first time loss method was added to 

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::Average);
         Assert::AreEqual(109087651.86937881, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(122737400.24817932, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(164095223.57744601, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(259533127.06802428, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(18434285.171043362, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6596451.7299161749, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::UpperBound);
         Assert::AreEqual(109087651.86937881, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(122737400.24817932, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(184779495.45695600, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(280217398.94753432, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(18434285.171043362, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6596451.7299161749, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         // Stress Relieved
         loss.SetStrandType(WBFL::Materials::PsStrand::Type::StressRelieved);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::Average);
         Assert::AreEqual(104526410.09122445, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(159125403.60642651, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(205463767.33646601, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(255391183.91248837, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(17663499.200022046, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6407962.2494997690, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);

         loss.SetLevel(NoncompositeApproximateLosses2005::Level::UpperBound);
         Assert::AreEqual(104526410.09122445, loss.ElasticShorteningLosses(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(54598993.515202068, loss.ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(159125403.60642651, loss.ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(226148039.21597600, loss.ApproxLosses(), 0.00001);
         Assert::AreEqual(276075455.79199839, loss.FinalLosses(), 0.00001);
         Assert::AreEqual(17663499.200022046, loss.GetFcgp(), 0.00001);
         Assert::AreEqual(1675426022.2403100, loss.GetFpy(), 0.00001);
         Assert::AreEqual(-6407962.2494997690, loss.GetP(), 0.00001);
         Assert::AreEqual(196500582855.34500, loss.GetEp(), 0.00001);
      }
   };
}
