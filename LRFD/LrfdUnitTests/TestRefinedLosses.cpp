#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestRefinedLosses)
	{
	public:
		
		TEST_METHOD(Test)
		{
         LRFDAutoVersion av;

         std::shared_ptr<CreepCoefficient2005> pGirderCreep = std::make_shared<CreepCoefficient2005>();
         pGirderCreep->SetCuringMethod(CreepCoefficient2005::CuringMethod::Accelerated);
         pGirderCreep->SetCuringMethodTimeAdjustmentFactor(WBFL::Units::ConvertToSysUnits(7, WBFL::Units::Measure::Day));
         pGirderCreep->SetFci(35852736.609413415);
         pGirderCreep->SetRelHumidity(75);
         pGirderCreep->SetSurfaceArea(6.9711699425657105);
         pGirderCreep->SetVolume(0.56485774124999988);
         pGirderCreep->SetK1(1.0);
         pGirderCreep->SetK2(1.0);

         std::shared_ptr<CreepCoefficient2005> pDeckCreep = std::make_shared<CreepCoefficient2005>();
         pDeckCreep->SetCuringMethod(CreepCoefficient2005::CuringMethod::Normal);
         pDeckCreep->SetCuringMethodTimeAdjustmentFactor(WBFL::Units::ConvertToSysUnits(7, WBFL::Units::Measure::Day));
         pDeckCreep->SetFci(0.8 * 27579029.172680002); // deck is non-prestressed. Use 80% of strength. See NCHRP 496 (page 27 and 30)
         pDeckCreep->SetRelHumidity(75);
         pDeckCreep->SetSurfaceArea(1.8288000000760127);
         pDeckCreep->SetVolume(0.32516064001351508);
         pDeckCreep->SetK1(1.0);
         pDeckCreep->SetK2(1.0);


         RefinedLosses loss(19.5072, // location along girder where losses are computed
            39.0144,    // girder length
            RefinedLosses2005::SectionPropertiesType::Gross,
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

            RefinedLosses2005::TempStrandUsage::Pretensioned, // temporary strand usage
            0.0095250000000000005, // anchor set
            0.00065616797900200005, // wobble
            0.25000000000000000, // friction
            0, // angle change

            41368543.759020001,   // 28 day strength of girder concrete
            35852736.609413415,  // Release strength
            27579029.172680002,
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
            -0.5,   // Shipping losses 50% of total
            true // validate parameters
         );

         LRFDVersionMgr::RegisterListener(&loss);
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEditionWith2005Interims);
         LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);

         Assert::AreEqual(39644854.435727499, loss.ShrinkageLosses(), 0.00001);
         Assert::AreEqual(159836535.47960073, loss.CreepLosses(), 0.00001);
         Assert::AreEqual(16598102.340557437, loss.RelaxationLossesAfterXfer(), 0.00001);
         Assert::AreEqual(216079492.25588566, loss.TimeDependentLossesBeforeDeck(), 0.00001);
         Assert::AreEqual(0, loss.TimeDependentLossesAfterDeck(), 0.00001);
         Assert::AreEqual(216079492.25588566, loss.TimeDependentLosses(), 0.00001);

         // permanent strands
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(120329398.57499108, loss.PermanentStrand_ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AtLifting(), 0.00001);
         Assert::AreEqual(121689494.50674334, loss.PermanentStrand_AtShipping(), 0.00001);
         Assert::AreEqual(108039746.12794283, loss.PermanentStrand_TimeDependentLossesAtShipping(), 0.00001);
         Assert::AreEqual(121689494.50674334, loss.PermanentStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(121689494.50674334, loss.PermanentStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(229729240.63468617, loss.PermanentStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(229729240.63468617, loss.PermanentStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(229729240.63468617, loss.PermanentStrand_Final(), 0.00001);

         // temporary strands
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_RelaxationLossesAtXfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_ImmediatelyBeforeXferLosses(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(57710366.334865674, loss.TemporaryStrand_ImmediatelyAfterXferLosses(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AtLifting(), 0.00001);
         Assert::AreEqual(121689577.68535240, loss.TemporaryStrand_AtShipping(), 0.00001);
         Assert::AreEqual(108039746.12794283, loss.TemporaryStrand_TimeDependentLossesAtShipping(), 0.00001);
         Assert::AreEqual(121689577.68535240, loss.TemporaryStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_Final(), 0.00001);

         LRFDVersionMgr::UnregisterListener(&loss);
      }
	};
}
