#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;
using namespace WBFL::Materials;

namespace LrfdUnitTests
{
	TEST_CLASS(TestApproximateLosses)
	{
	public:
		
      ApproximateLosses CreateTestObject(ApproximateLosses::BeamType beamType)
      {
         ApproximateLosses loss(beamType,
            -0.50, // 50% loss at shipping
            1.0, // ppr
            17.5, // location where losses computed
            39.0144,    // girder length
            Losses::SectionPropertiesType::Gross,
            WBFL::Materials::PsStrand::Grade::Gr1860,
            WBFL::Materials::PsStrand::Type::LowRelaxation,
            WBFL::Materials::PsStrand::Coating::None,
            WBFL::Materials::PsStrand::Grade::Gr1860,
            WBFL::Materials::PsStrand::Type::LowRelaxation,
            WBFL::Materials::PsStrand::Coating::None,
            1396186227.0505831, // fpj permanent strands
            1396188385.8038988, // fpj of temporary strands
            0.0051799896399999995,  // area of permanent strand
            0.00055999887999999998,  // area of TTS 
            0.00013999972000000000,      // area of one strand
            WBFL::Geometry::Point2d(0, 0.73344249937779116), // eccentricity of permanent ps strands with respect to CG of girder
            WBFL::Geometry::Point2d(0, 0.73344249937779116), // eccentricity of permanent ps strands with respect to CG of girder
            WBFL::Geometry::Point2d(0, -0.81870344656815441), // eccentricity of temporary strands with respect to CG of girder
            Losses::TempStrandUsage::Pretensioned, // temporary strand usage
            0.0095250000000000005, // anchor set
            0.00065616797900200005, // wobble
            0.25000000000000000, // friction
            0, // angle change

            ConcreteType::Normal,
            41368543.759020001,   // 28 day strength of girder concrete
            35852736.609413415,  // Release strength
            27579029.172680002, // FcSlab
            35668801112.349388,   // Modulus of elasticity of girder
            33205846111.428368,  // Modulus of elasticity of girder at transfer
            29123454154.024353,  // Modulus of elasticity of deck

            2701223.1744837998,  // Dead load moment of girder only
            std::vector<std::pair<Float64, Float64>>{std::make_pair(2144430.8154568151, 1.0)},  // Additional dead load on girder section
            std::vector<std::pair<Float64, Float64>>{std::make_pair(0, 1.0)},
            std::vector<std::pair<Float64, Float64>>{std::make_pair(494526.00384487113, 1.0)}, // Superimposed dead loads

            // Gross
            0.56485774124999988,   // area of girder
            0.23197765412628035,   // moment of inertia of girder Ixx
            0.23197765412628035,   // moment of inertia of girder Iyy
            0.0, // Ixy
            0.80689655343184530,  // Centroid of girder measured from bottom
            0.83035029207347855,   // area of composite girder
            0.39856959307884982,   // moment of inertia of composite
            1.1133322567444859,  // Centroid of composite measured from bottom
            0.83035029207347855,   // area of composite girder
            0.39856959307884982,   // moment of inertia of composite
            1.1133322567444859,  // Centroid of composite measured from bottom

            // Net
            0.56485774124999988,   // area of girder
            0.23197765412628035,   // moment of inertia of girder
            0.23197765412628035,   // moment of inertia of girder Iyy
            0.0, // Ixy
            0.80689655343184530,  // Centroid of girder measured from bottom
            0.83035029207347855,   // area of composite girder
            0.39856959307884982,   // moment of inertia of composite
            1.1133322567444859,  // Centroid of composite measured from bottom

            75,  // Relative humidity [0,100]
            86400.000000000000,   // Time until prestress transfer
            false, // ignore initial relaxation
            true // validate parameters
         );

         return loss;
      }

      TEST_METHOD(IBeam)
		{
         BDSAutoVersion av;
         BDSManager::SetEdition(BDSManager::Edition::FourthEditionWith2009Interims); // last  where this method is applicable


         auto loss = CreateTestObject(ApproximateLosses::BeamType::IBeam);


         BDSManager::SetEdition(BDSManager::Edition::FifthEdition2010); // loss method became invalid in 2010
         Assert::ExpectException<XPsLosses>([&]() {loss.PermanentStrand_AfterTransfer(); });

         BDSManager::SetEdition(BDSManager::Edition::FourthEditionWith2009Interims); // last  where this method is applicable
         BDSManager::SetUnits(BDSManager::Units::US);

         // permanent strands
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AtLifting(), 0.00001);
         Assert::AreEqual(127413243.71610552, loss.PermanentStrand_AtShipping(), 0.00001);
         Assert::AreEqual(127413243.71610552, loss.PermanentStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(127413243.71610552, loss.PermanentStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(241176739.05341053, loss.PermanentStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(241176739.05341053, loss.PermanentStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(241176739.05341053, loss.PermanentStrand_Final(), 0.00001);

         // temporary strands
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AtLifting(), 0.00001);
         Assert::AreEqual(127413326.89471458, loss.TemporaryStrand_AtShipping(), 0.00001);
         Assert::AreEqual(127413326.89471458, loss.TemporaryStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_Final(), 0.00001);

         // SI Spec
         BDSManager::SetEdition(BDSManager::Edition::ThirdEditionWith2006Interims); // last  where this method is applicable with SI Units
         BDSManager::SetUnits(BDSManager::Units::SI);

         // permanent strands
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AtLifting(), 0.00001);
         Assert::AreEqual(128494690.33384697, loss.PermanentStrand_AtShipping(), 0.00001);
         Assert::AreEqual(128494690.33384697, loss.PermanentStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(128494690.33384697, loss.PermanentStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(243339632.28889343, loss.PermanentStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(243339632.28889343, loss.PermanentStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(243339632.28889343, loss.PermanentStrand_Final(), 0.00001);

         // temporary strands
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AtLifting(), 0.00001);
         Assert::AreEqual(128494773.51245603, loss.TemporaryStrand_AtShipping(), 0.00001);
         Assert::AreEqual(128494773.51245603, loss.TemporaryStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_Final(), 0.00001);
      }

      TEST_METHOD(UBeam)
      {
         BDSAutoVersion av;
         BDSManager::SetEdition(BDSManager::Edition::FourthEditionWith2009Interims); // last  where this method is applicable


         auto loss = CreateTestObject(ApproximateLosses::BeamType::UBeam);


         BDSManager::SetEdition(BDSManager::Edition::FifthEdition2010); // loss method became invalid in 2010
         Assert::ExpectException<XPsLosses>([&]() {loss.PermanentStrand_AfterTransfer(); });

         BDSManager::SetEdition(BDSManager::Edition::FourthEditionWith2009Interims); // last  where this method is applicable
         BDSManager::SetUnits(BDSManager::Units::US);

         // permanent strands
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AtLifting(), 0.00001);
         Assert::AreEqual(86044699.957085520, loss.PermanentStrand_AtShipping(), 0.00001);
         Assert::AreEqual(86044699.957085520, loss.PermanentStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(86044699.957085520, loss.PermanentStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(158439651.53537053, loss.PermanentStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(158439651.53537053, loss.PermanentStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(158439651.53537053, loss.PermanentStrand_Final(), 0.00001);

         // temporary strands
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AtLifting(), 0.00001);
         Assert::AreEqual(86044783.135694578, loss.TemporaryStrand_AtShipping(), 0.00001);
         Assert::AreEqual(86044783.135694578, loss.TemporaryStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_Final(), 0.00001);

         // SI Spec
         BDSManager::SetEdition(BDSManager::Edition::ThirdEditionWith2006Interims); // last  where this method is applicable with SI Units
         BDSManager::SetUnits(BDSManager::Units::SI);

         // permanent strands
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AtLifting(), 0.00001);
         Assert::AreEqual(86149748.378800511, loss.PermanentStrand_AtShipping(), 0.00001);
         Assert::AreEqual(86149748.378800511, loss.PermanentStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(86149748.378800511, loss.PermanentStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(158649748.37880051, loss.PermanentStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(158649748.37880051, loss.PermanentStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(158649748.37880051, loss.PermanentStrand_Final(), 0.00001);

         // temporary strands
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AtLifting(), 0.00001);
         Assert::AreEqual(86149831.557409570, loss.TemporaryStrand_AtShipping(), 0.00001);
         Assert::AreEqual(86149831.557409570, loss.TemporaryStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_Final(), 0.00001);
      }

      TEST_METHOD(BoxBeam)
      {
         BDSAutoVersion av;
         BDSManager::SetEdition(BDSManager::Edition::FourthEditionWith2009Interims); // last  where this method is applicable


         auto loss = CreateTestObject(ApproximateLosses::BeamType::BoxBeam);


         BDSManager::SetEdition(BDSManager::Edition::FifthEdition2010); // loss method became invalid in 2010
         Assert::ExpectException<XPsLosses>([&]() {loss.PermanentStrand_AfterTransfer(); });

         BDSManager::SetEdition(BDSManager::Edition::FourthEditionWith2009Interims); // last  where this method is applicable
         BDSManager::SetUnits(BDSManager::Units::US);

         // permanent strands
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AtLifting(), 0.00001);
         Assert::AreEqual(79149942.663915515, loss.PermanentStrand_AtShipping(), 0.00001);
         Assert::AreEqual(79149942.663915515, loss.PermanentStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(79149942.663915515, loss.PermanentStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(144650136.94903052, loss.PermanentStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(144650136.94903052, loss.PermanentStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(144650136.94903052, loss.PermanentStrand_Final(), 0.00001);

         // temporary strands
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AtLifting(), 0.00001);
         Assert::AreEqual(79150025.842524573, loss.TemporaryStrand_AtShipping(), 0.00001);
         Assert::AreEqual(79150025.842524573, loss.TemporaryStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_Final(), 0.00001);

         // SI Spec
         BDSManager::SetEdition(BDSManager::Edition::ThirdEditionWith2006Interims); // last  where this method is applicable with SI Units
         BDSManager::SetUnits(BDSManager::Units::SI);

         // permanent strands
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AtLifting(), 0.00001);
         Assert::AreEqual(78649748.378800511, loss.PermanentStrand_AtShipping(), 0.00001);
         Assert::AreEqual(78649748.378800511, loss.PermanentStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(78649748.378800511, loss.PermanentStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(143649748.37880051, loss.PermanentStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(143649748.37880051, loss.PermanentStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(143649748.37880051, loss.PermanentStrand_Final(), 0.00001);

         // temporary strands
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AtLifting(), 0.00001);
         Assert::AreEqual(78649831.557409570, loss.TemporaryStrand_AtShipping(), 0.00001);
         Assert::AreEqual(78649831.557409570, loss.TemporaryStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_Final(), 0.00001);
      }

      TEST_METHOD(SingleT)
      {
         BDSAutoVersion av;
         BDSManager::SetEdition(BDSManager::Edition::FourthEditionWith2009Interims); // last  where this method is applicable


         auto loss = CreateTestObject(ApproximateLosses::BeamType::SingleT);


         BDSManager::SetEdition(BDSManager::Edition::FifthEdition2010); // loss method became invalid in 2010
         Assert::ExpectException<XPsLosses>([&]() {loss.PermanentStrand_AfterTransfer(); });

         BDSManager::SetEdition(BDSManager::Edition::FourthEditionWith2009Interims); // last  where this method is applicable
         BDSManager::SetUnits(BDSManager::Units::US);

         // permanent strands
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AtLifting(), 0.00001);
         Assert::AreEqual(120518486.42293552, loss.PermanentStrand_AtShipping(), 0.00001);
         Assert::AreEqual(120518486.42293552, loss.PermanentStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(120518486.42293552, loss.PermanentStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(227387224.46707052, loss.PermanentStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(227387224.46707052, loss.PermanentStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(227387224.46707052, loss.PermanentStrand_Final(), 0.00001);

         // temporary strands
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AtLifting(), 0.00001);
         Assert::AreEqual(120518569.60154457, loss.TemporaryStrand_AtShipping(), 0.00001);
         Assert::AreEqual(120518569.60154457, loss.TemporaryStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_Final(), 0.00001);

         // SI Spec
         BDSManager::SetEdition(BDSManager::Edition::ThirdEditionWith2006Interims); // last  where this method is applicable with SI Units
         BDSManager::SetUnits(BDSManager::Units::SI);

         // permanent strands
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AtLifting(), 0.00001);
         Assert::AreEqual(121494690.33384697, loss.PermanentStrand_AtShipping(), 0.00001);
         Assert::AreEqual(121494690.33384697, loss.PermanentStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(121494690.33384697, loss.PermanentStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(229339632.28889343, loss.PermanentStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(229339632.28889343, loss.PermanentStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(229339632.28889343, loss.PermanentStrand_Final(), 0.00001);

         // temporary strands
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AtLifting(), 0.00001);
         Assert::AreEqual(121494773.51245603, loss.TemporaryStrand_AtShipping(), 0.00001);
         Assert::AreEqual(121494773.51245603, loss.TemporaryStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_Final(), 0.00001);
      }

      TEST_METHOD(SolidSlab)
      {
         BDSAutoVersion av;
         BDSManager::SetEdition(BDSManager::Edition::FourthEditionWith2009Interims); // last  where this method is applicable


         auto loss = CreateTestObject(ApproximateLosses::BeamType::SolidSlab);


         BDSManager::SetEdition(BDSManager::Edition::FifthEdition2010); // loss method became invalid in 2010
         Assert::ExpectException<XPsLosses>([&]() {loss.PermanentStrand_AfterTransfer(); });

         BDSManager::SetEdition(BDSManager::Edition::FourthEditionWith2009Interims); // last  where this method is applicable
         BDSManager::SetUnits(BDSManager::Units::US);

         // permanent strands
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AtLifting(), 0.00001);
         Assert::AreEqual(96386835.896840513, loss.PermanentStrand_AtShipping(), 0.00001);
         Assert::AreEqual(96386835.896840513, loss.PermanentStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(96386835.896840513, loss.PermanentStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(179123923.41488051, loss.PermanentStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(179123923.41488051, loss.PermanentStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(179123923.41488051, loss.PermanentStrand_Final(), 0.00001);

         // temporary strands
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AtLifting(), 0.00001);
         Assert::AreEqual(96386919.075449571, loss.TemporaryStrand_AtShipping(), 0.00001);
         Assert::AreEqual(96386919.075449571, loss.TemporaryStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_Final(), 0.00001);

         // SI Spec
         BDSManager::SetEdition(BDSManager::Edition::ThirdEditionWith2006Interims); // last  where this method is applicable with SI Units
         BDSManager::SetUnits(BDSManager::Units::SI);

         // permanent strands
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AtLifting(), 0.00001);
         Assert::AreEqual(97149748.378800511, loss.PermanentStrand_AtShipping(), 0.00001);
         Assert::AreEqual(97149748.378800511, loss.PermanentStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(97149748.378800511, loss.PermanentStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(180649748.37880051, loss.PermanentStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(180649748.37880051, loss.PermanentStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(180649748.37880051, loss.PermanentStrand_Final(), 0.00001);

         // temporary strands
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AtLifting(), 0.00001);
         Assert::AreEqual(97149831.557409570, loss.TemporaryStrand_AtShipping(), 0.00001);
         Assert::AreEqual(97149831.557409570, loss.TemporaryStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_Final(), 0.00001);
      }
   };
}
