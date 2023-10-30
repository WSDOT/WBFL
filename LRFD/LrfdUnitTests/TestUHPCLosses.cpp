#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestUHPCLosses)
	{
	public:
		
		TEST_METHOD(Test)
		{
         BDSAutoVersion av;

         std::shared_ptr<UHPCCreepCoefficient> pGirderCreep = std::make_shared<UHPCCreepCoefficient>();
         pGirderCreep->SetFci(WBFL::Units::ConvertToSysUnits(14.0, WBFL::Units::Measure::KSI));
         pGirderCreep->SetRelHumidity(73);
         pGirderCreep->SetK1(0.62);

         std::shared_ptr<CreepCoefficient2005> pDeckCreep = std::make_shared<CreepCoefficient2005>();
         pDeckCreep->SetCuringMethod(CreepCoefficient2005::CuringMethod::Normal);
         pDeckCreep->SetCuringMethodTimeAdjustmentFactor(WBFL::Units::ConvertToSysUnits(7, WBFL::Units::Measure::Day));
         pDeckCreep->SetFci(0.8 * WBFL::Units::ConvertToSysUnits(4.0, WBFL::Units::Measure::KSI)); // deck is non-prestressed. Use 80% of strength. See NCHRP 496 (page 27 and 30)
         pDeckCreep->SetRelHumidity(73);
         pDeckCreep->SetSurfaceArea(1.0);
         pDeckCreep->SetVolume(WBFL::Units::ConvertToSysUnits(3.940, WBFL::Units::Measure::Inch));
         pDeckCreep->SetK1(1.0);
         pDeckCreep->SetK2(1.0);

         UHPCLosses loss(19.5072, // location along girder where losses are computed
            39.0144,    // girder length
            UHPCLosses::SectionPropertiesType::Gross,
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

            UHPCLosses::TempStrandUsage::Pretensioned, // temporary strand usage

            0.0095250000000000005, // anchor set
            0.00065616797900200005, // wobble
            0.25000000000000000, // friction
            0, // angle change

            0.41, 1, // K for girder
            1, 1, // K fog slab

            41368543.759020001,   // 28 day strength of girder concrete
            35852736.609413415,  // Release strength
            27579029.172680002,
            35668801112.349388,   // Modulus of elasticity of girder
            33205846111.428368,  // Modulus of elasticity of girder at transfer
            29123454154.024353,  // Modulus of elasticity of deck

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

            0.34838640001448046,   // area of deck
            -0.65196774325551399,   // eccentricity of deck CG with respect to CG of composite
            1.0,

            2701223.1744837998,  // Dead load moment of girder only
            std::vector<std::pair<Float64, Float64>>{std::make_pair(2144430.8154568151, 1.0)},  // Additional dead load on girder section
            std::vector<std::pair<Float64, Float64>>{std::make_pair(0, 1.0)},
            std::vector<std::pair<Float64, Float64>>{std::make_pair(494526.00384487113, 1.0)}, // Superimposed dead loads

            75,  // Relative humidity [0,100]
            86400.000000000000,   // Time until prestress transfer
            864000.00000000000,   // Time at hauling
            10368000.000000000,   // Time to deck placement
            172800000.00000000,   // Final time
            false, true, UHPCLosses::RelaxationLossMethod::Refined,
            std::shared_ptr<const CreepCoefficient2005>(std::dynamic_pointer_cast<const CreepCoefficient2005>(pGirderCreep)),
            std::shared_ptr<const CreepCoefficient2005>(pDeckCreep)
         );

         BDSManager::RegisterListener(&loss);
         BDSManager::SetEdition(BDSManager::Edition::NinthEdition2020);
         BDSManager::SetUnits(BDSManager::Units::US);

         // permanent strands
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_BeforeTransfer(), 0.0001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTransfer(), 0.0001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AfterTemporaryStrandInstallation(), 0.0001);
         Assert::AreEqual(13649748.378800517, loss.PermanentStrand_AtLifting(), 0.0001);
         Assert::AreEqual(81340582.966499269, loss.PermanentStrand_AtShipping(), 0.0001);
         Assert::AreEqual(81340582.966499269, loss.PermanentStrand_BeforeTemporaryStrandRemoval(), 0.0001);
         Assert::AreEqual(81340582.966499269, loss.PermanentStrand_AfterTemporaryStrandRemoval(), 0.0001);
         Assert::AreEqual(139856443.92492411, loss.PermanentStrand_AfterDeckPlacement(), 0.0001);
         Assert::AreEqual(139856443.92492411, loss.PermanentStrand_AfterSIDL(), 0.0001);
         Assert::AreEqual(140798870.67772746, loss.PermanentStrand_Final(), 0.0001);

         // temporary strands
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_BeforeTransfer(), 0.0001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTransfer(), 0.0001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AfterTemporaryStrandInstallation(), 0.0001);
         Assert::AreEqual(13649831.557409566, loss.TemporaryStrand_AtLifting(), 0.0001);
         Assert::AreEqual(70200702.851341456, loss.TemporaryStrand_AtShipping(), 0.0001);
         Assert::AreEqual(70200702.851341456, loss.TemporaryStrand_BeforeTemporaryStrandRemoval(), 0.0001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterTemporaryStrandRemoval(), 0.0001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterDeckPlacement(), 0.0001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterSIDL(), 0.0001);
         Assert::AreEqual(0., loss.TemporaryStrand_Final(), 0.0001);

         BDSManager::UnregisterListener(&loss);
      }
	};
}
