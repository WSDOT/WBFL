#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;
using namespace WBFL::Materials;

namespace LrfdUnitTests
{
   TEST_CLASS(TestConcreteUtil)
   {
   public:

      TEST_METHOD(Beta1)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEditionWith1996Interims); // use a version before SI units were dropped

         {
            // want to work in KSI
            WBFL::Units::AutoSystem au;
            WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
            WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
            WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

            Assert::AreEqual(0.85, ConcreteUtil::Beta1(4.0), 0.01);
            Assert::AreEqual(0.80, ConcreteUtil::Beta1(5.0), 0.01);
            Assert::AreEqual(0.75, ConcreteUtil::Beta1(6.0), 0.01);
            Assert::AreEqual(0.70, ConcreteUtil::Beta1(7.0), 0.01);
            Assert::AreEqual(0.65, ConcreteUtil::Beta1(8.0), 0.01);
            Assert::AreEqual(0.65, ConcreteUtil::Beta1(15.0), 0.01);
         }

         {
            // working in default SI Units
            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);

            Assert::AreEqual(0.85, ConcreteUtil::Beta1(28e6), 0.01);
            Assert::AreEqual(0.80, ConcreteUtil::Beta1(35e6), 0.01);
            Assert::AreEqual(0.75, ConcreteUtil::Beta1(42e6), 0.01);
            Assert::AreEqual(0.70, ConcreteUtil::Beta1(49e6), 0.01);
            Assert::AreEqual(0.65, ConcreteUtil::Beta1(56e6), 0.01);
            Assert::AreEqual(0.65, ConcreteUtil::Beta1(103e6), 0.01);
         }
      }

      TEST_METHOD(ModulusOfRupture_PreLRFD2005)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEditionWith1996Interims); // use a version before SI units were dropped

         {
            // want to work in KSI
            WBFL::Units::AutoSystem au;
            WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
            WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
            WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);
            Float64 fc = WBFL::Units::ConvertToSysUnits(5, WBFL::Units::Measure::KSI);
            Assert::AreEqual(0.53665631460153684, ConcreteUtil::ModRupture(fc, WBFL::Materials::ConcreteType::Normal), 0.001);
            Assert::AreEqual(0.44721359550128076, ConcreteUtil::ModRupture(fc, WBFL::Materials::ConcreteType::SandLightweight), 0.001);
            Assert::AreEqual(0.38013155617608868, ConcreteUtil::ModRupture(fc, WBFL::Materials::ConcreteType::AllLightweight), 0.001);
         }

         {
            // working in default SI Units
            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
            Float64 fc = WBFL::Units::ConvertToSysUnits(50, WBFL::Units::Measure::MPa);

            Assert::AreEqual(4454772.7214752492, ConcreteUtil::ModRupture(fc, WBFL::Materials::ConcreteType::Normal), 0.001);
            Assert::AreEqual(3676955.2621700475, ConcreteUtil::ModRupture(fc, WBFL::Materials::ConcreteType::SandLightweight), 0.001);
            Assert::AreEqual(3181980.5153394644, ConcreteUtil::ModRupture(fc, WBFL::Materials::ConcreteType::AllLightweight), 0.001);
         }
      }

      TEST_METHOD(ModulusOfRupture_LRFD2005)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEditionWith2005Interims);

         // want to work in KSI
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
         WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

         LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);
         Float64 fc = WBFL::Units::ConvertToSysUnits(5, WBFL::Units::Measure::KSI);
         Assert::AreEqual(0.82734515167736944, ConcreteUtil::ModRupture(fc, WBFL::Materials::ConcreteType::Normal), 0.001);
         Assert::AreEqual(0.44721359550128076, ConcreteUtil::ModRupture(fc, WBFL::Materials::ConcreteType::SandLightweight), 0.001);
         Assert::AreEqual(0.38013155617608868, ConcreteUtil::ModRupture(fc, WBFL::Materials::ConcreteType::AllLightweight), 0.001);
      }

      TEST_METHOD(ModulusOfRupture)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEditionWith2005Interims);

         // want to work in KSI
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
         WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

         LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);
         Float64 fc = WBFL::Units::ConvertToSysUnits(5, WBFL::Units::Measure::KSI);

         Assert::AreEqual(0.55901699409906491, ConcreteUtil::ModRupture(fc, 0.25));
      }

      TEST_METHOD(FcFromEc_UHPC)
      {
         // want to work in KSI
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
         WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

         Assert::AreEqual(5.0, ConcreteUtil::FcFromEc(ConcreteType::PCI_UHPC, 4252.0671077182387, 0.155), 0.0001);
         Assert::AreEqual(5.0, ConcreteUtil::FcFromEc(ConcreteType::UHPC, 4252.0671077182387, 0.155), 0.0001);
      }

      TEST_METHOD(FcFromEc_PreLRFD2015)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994);

         {
            // US units
            WBFL::Units::AutoSystem au;
            WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
            WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
            WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);

            Float64 density = WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3);
            Assert::AreEqual(5.0, ConcreteUtil::FcFromEc(ConcreteType::Normal, 4502.9434123826095, density), 0.0001);
            Assert::AreEqual(5.0, ConcreteUtil::FcFromEc(ConcreteType::AllLightweight, 4502.9434123826095, density), 0.0001);
            Assert::AreEqual(5.0, ConcreteUtil::FcFromEc(ConcreteType::SandLightweight, 4502.9434123826095, density), 0.0001);
         }

         {
            // SI units
            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);

            Float64 density = WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3);
            Assert::AreEqual(34473786.465850003, ConcreteUtil::FcFromEc(ConcreteType::Normal, 31235019059.731911, density), 0.0001);
            Assert::AreEqual(34473786.465850003, ConcreteUtil::FcFromEc(ConcreteType::AllLightweight, 31235019059.731911, density), 0.0001);
            Assert::AreEqual(34473786.465850003, ConcreteUtil::FcFromEc(ConcreteType::SandLightweight, 31235019059.731911, density), 0.0001);
         }
      }

      TEST_METHOD(FcFromEc_LRFD2015)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SeventhEditionWith2015Interims);

         // in 2015, modulus of elasticity equation changed

         // US units (no SI units version of LRFD in 2015)
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
         WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

         LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);

         Float64 density = WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3);
         Assert::AreEqual(5.0, ConcreteUtil::FcFromEc(ConcreteType::Normal,4903.4837886254563, density), 0.0001);
         Assert::AreEqual(5.0, ConcreteUtil::FcFromEc(ConcreteType::AllLightweight, 4903.4837886254563, density), 0.0001);
         Assert::AreEqual(5.0, ConcreteUtil::FcFromEc(ConcreteType::SandLightweight, 4903.4837886254563, density), 0.0001);
      }

      TEST_METHOD(ModulusOfElasticity_UHPC)
      {
         // want to work in KSI
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
         WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

         // note that unit weight and f'c range are not applicable to UHPC
         Assert::AreEqual(4252.0671077182387, ConcreteUtil::ModE(ConcreteType::PCI_UHPC, 5.0, 0.150, true));
         Assert::AreEqual(4252.0671077182387, ConcreteUtil::ModE(ConcreteType::UHPC, 5.0, 0.150, true));
      }

      TEST_METHOD(ModulusOfElasticity_PreLRFD2015)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994);

         {
            // US units
            WBFL::Units::AutoSystem au;
            WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
            WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
            WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);

            Float64 fc = WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::KSI);
            Float64 density = WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3);
            Assert::AreEqual(4502.9434123826095, ConcreteUtil::ModE(ConcreteType::Normal, fc, density, true));
            Assert::AreEqual(4502.9434123826095, ConcreteUtil::ModE(ConcreteType::AllLightweight, fc, density, true));
            Assert::AreEqual(4502.9434123826095, ConcreteUtil::ModE(ConcreteType::SandLightweight, fc, density, true));

            // valid range of density is 0.090-0.155 kcf
            density = WBFL::Units::ConvertToSysUnits(0.080, WBFL::Units::Measure::KipPerFeet3);
            Assert::ExpectException<WBFL::System::XProgrammingError>([&]() {ConcreteUtil::ModE(ConcreteType::Normal, fc, density, true); });
            Assert::AreEqual(1669.6826045738435, ConcreteUtil::ModE(ConcreteType::Normal, fc, density, false));

            density = WBFL::Units::ConvertToSysUnits(0.090, WBFL::Units::Measure::KipPerFeet3);
            Assert::AreEqual(1992.3365679582062, ConcreteUtil::ModE(ConcreteType::Normal, fc, density, true));

            density = WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3);
            Assert::AreEqual(4502.9434123826095, ConcreteUtil::ModE(ConcreteType::Normal, fc, density, true));

            density = WBFL::Units::ConvertToSysUnits(0.160, WBFL::Units::Measure::KipPerFeet3);
            Assert::ExpectException<WBFL::System::XProgrammingError>([&]() {ConcreteUtil::ModE(ConcreteType::Normal, fc, density, true); });
            Assert::AreEqual(4722.5755684935257, ConcreteUtil::ModE(ConcreteType::Normal, fc, density, false));
         }

         {
            // SI units
            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);

            Float64 fc = WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::KSI);
            Float64 density = WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3);
            Assert::AreEqual(31235019059.731911, ConcreteUtil::ModE(ConcreteType::Normal, fc, density, true));
            Assert::AreEqual(31235019059.731911, ConcreteUtil::ModE(ConcreteType::AllLightweight, fc, density, true));
            Assert::AreEqual(31235019059.731911, ConcreteUtil::ModE(ConcreteType::SandLightweight, fc, density, true));

            // valid range of density is 1440-2500 kg/m^3
            density = WBFL::Units::ConvertToSysUnits(1300, WBFL::Units::Measure::KgPerMeter3);
            Assert::ExpectException<WBFL::System::XProgrammingError>([&]() {ConcreteUtil::ModE(ConcreteType::Normal, fc, density, true); });
            Assert::AreEqual(11833902251.255016, ConcreteUtil::ModE(ConcreteType::Normal, fc, density, false));

            density = WBFL::Units::ConvertToSysUnits(1440, WBFL::Units::Measure::KgPerMeter3);
            Assert::AreEqual(13796111235.312513, ConcreteUtil::ModE(ConcreteType::Normal, fc, density, true));

            density = WBFL::Units::ConvertToSysUnits(2500, WBFL::Units::Measure::KgPerMeter3);
            Assert::AreEqual(31558980292.698742, ConcreteUtil::ModE(ConcreteType::Normal, fc, density, true));

            density = WBFL::Units::ConvertToSysUnits(2600, WBFL::Units::Measure::KgPerMeter3);
            Assert::ExpectException<WBFL::System::XProgrammingError>([&]() {ConcreteUtil::ModE(ConcreteType::Normal, fc, density, true); });
            Assert::AreEqual(33471330119.044689, ConcreteUtil::ModE(ConcreteType::Normal, fc, density, false));         }
      }

      TEST_METHOD(ModulusOfElasticity_LRFD2015)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SeventhEditionWith2015Interims);

         // in 2015, modulus of elasticity equation changed

         // US units (no SI units version of LRFD in 2015)
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
         WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

         LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);

         Float64 fc = WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::KSI);
         Float64 density = WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3);
         Assert::AreEqual(4903.4837886254563, ConcreteUtil::ModE(ConcreteType::Normal, fc, density, true));
         Assert::AreEqual(4903.4837886254563, ConcreteUtil::ModE(ConcreteType::AllLightweight, fc, density, true));
         Assert::AreEqual(4903.4837886254563, ConcreteUtil::ModE(ConcreteType::SandLightweight, fc, density, true));
      }

      TEST_METHOD(DensityLimits)
      {
         {
            // US units
            WBFL::Units::AutoSystem au;
            WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::PoundMass);
            WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Feet);

            LRFDAutoVersion av;
            LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994);
            Assert::AreEqual(135.0, ConcreteUtil::GetNWCDensityLimit());
            Assert::AreEqual(120.0, ConcreteUtil::GetLWCDensityLimit());

            LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SeventhEditionWith2016Interims);
            Assert::AreEqual(135.0, ConcreteUtil::GetNWCDensityLimit());
            Assert::AreEqual(135.0, ConcreteUtil::GetLWCDensityLimit());
         }

         {
            // SI Units
            LRFDAutoVersion av;
            LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994);
            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
            Assert::AreEqual(2150.0, ConcreteUtil::GetNWCDensityLimit());
            Assert::AreEqual(1925.0, ConcreteUtil::GetLWCDensityLimit());

            LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SeventhEditionWith2016Interims);
            Assert::AreEqual(2162.4925554846186, ConcreteUtil::GetNWCDensityLimit());
            Assert::AreEqual(2162.4925554846186, ConcreteUtil::GetLWCDensityLimit());
         }
      }

      TEST_METHOD(PCIUHPCProperties)
      {
         // US units
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);

         Float64 fcMin, fcMax;
         ConcreteUtil::GetPCIUHPCStrengthRange(&fcMin, &fcMax);
         Assert::AreEqual(17.4, fcMin, 0.0001);
         Assert::AreEqual(99999.0, fcMax, 0.0001);

         Float64 ffc, fpeak, frr;
         ConcreteUtil::GetPCIUHPCMinProperties(&fcMin, &ffc, &fpeak, &frr);
         Assert::AreEqual(17.4, fcMin, 0.0001);
         Assert::AreEqual(1.5, ffc, 0.0001);
         Assert::AreEqual(2.0, fpeak, 0.0001);
         Assert::AreEqual(0.75, frr, 0.0001);
      }

      TEST_METHOD(InterfaceShearParameters_ConventionalConcrete)
      {
         // US units
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);

         // LRFD before 4th Edition
         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEditionWith2006Interims);

         Float64 c, u, k1, k2;
         ConcreteUtil::InterfaceShearParameters(true, ConcreteType::Normal, ConcreteType::Normal, &c, &u, &k1, &k2);
         Assert::AreEqual(0.1, c, 0.0001);
         Assert::AreEqual(1.0, u);
         Assert::AreEqual(0.2, k1);
         Assert::AreEqual(0.8, k2, 0.0001);

         ConcreteUtil::InterfaceShearParameters(false, ConcreteType::Normal, ConcreteType::Normal, &c, &u, &k1, &k2);
         Assert::AreEqual(0.075, c, 0.0001);
         Assert::AreEqual(0.6, u);
         Assert::AreEqual(0.2, k1);
         Assert::AreEqual(0.8, k2, 0.0001);

         // LRFD changed in 4th Edition
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FourthEdition2007);

         ConcreteUtil::InterfaceShearParameters(true, ConcreteType::Normal, ConcreteType::Normal, &c, &u, &k1, &k2);
         Assert::AreEqual(0.28, c, 0.0001);
         Assert::AreEqual(1.0, u);
         Assert::AreEqual(0.3, k1);
         Assert::AreEqual(1.8, k2, 0.0001);

         ConcreteUtil::InterfaceShearParameters(false, ConcreteType::Normal, ConcreteType::Normal, &c, &u, &k1, &k2);
         Assert::AreEqual(0.075, c, 0.0001);
         Assert::AreEqual(0.6, u);
         Assert::AreEqual(0.2, k1);
         Assert::AreEqual(0.8, k2, 0.0001);

         // LWC

         ConcreteUtil::InterfaceShearParameters(true, ConcreteType::AllLightweight, ConcreteType::Normal, &c, &u, &k1, &k2);
         Assert::AreEqual(0.28, c, 0.0001);
         Assert::AreEqual(1.0, u);
         Assert::AreEqual(0.3, k1);
         Assert::AreEqual(1.3, k2, 0.0001);

         ConcreteUtil::InterfaceShearParameters(false, ConcreteType::Normal, ConcreteType::AllLightweight, &c, &u, &k1, &k2);
         Assert::AreEqual(0.075, c, 0.0001);
         Assert::AreEqual(0.6, u);
         Assert::AreEqual(0.2, k1);
         Assert::AreEqual(0.80, k2, 0.0001);
      }

      TEST_METHOD(InterfaceShearParameters_PCIUHPC)
      {
         // US units
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);


         Float64 c, u, k1, k2;
         ConcreteUtil::InterfaceShearParameters(true, ConcreteType::PCI_UHPC, ConcreteType::Normal, &c, &u, &k1, &k2);
         Assert::AreEqual(0.24, c, 0.0001);
         Assert::AreEqual(1.0, u);
         Assert::AreEqual(0.25, k1);
         Assert::AreEqual(1.5, k2, 0.0001);

         ConcreteUtil::InterfaceShearParameters(true, ConcreteType::PCI_UHPC, ConcreteType::PCI_UHPC, &c, &u, &k1, &k2);
         Assert::AreEqual(0.5, c, 0.0001);
         Assert::AreEqual(1.4, u);
         Assert::AreEqual(0.3, k1);
         Assert::AreEqual(3.6, k2, 0.0001);

         ConcreteUtil::InterfaceShearParameters(false, ConcreteType::PCI_UHPC, ConcreteType::Normal, &c, &u, &k1, &k2);
         Assert::AreEqual(0.025, c, 0.0001);
         Assert::AreEqual(0.7, u);
         Assert::AreEqual(0.2, k1);
         Assert::AreEqual(0.8, k2, 0.0001);

         ConcreteUtil::InterfaceShearParameters(false, ConcreteType::PCI_UHPC, ConcreteType::PCI_UHPC, &c, &u, &k1, &k2);
         Assert::AreEqual(0.2, c, 0.0001);
         Assert::AreEqual(0.6, u);
         Assert::AreEqual(0.2, k1);
         Assert::AreEqual(3.6, k2, 0.0001);
      }

      TEST_METHOD(InterfaceShearParameters_UHPC)
      {
         // US units
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);


         Float64 c, u, k1, k2;
         ConcreteUtil::InterfaceShearParameters(true, ConcreteType::UHPC, ConcreteType::Normal, &c, &u, &k1, &k2);
         Assert::AreEqual(0.24, c, 0.0001);
         Assert::AreEqual(1.0, u);
         Assert::AreEqual(99999999., k1);
         Assert::AreEqual(1.8, k2, 0.0001);

         ConcreteUtil::InterfaceShearParameters(true, ConcreteType::UHPC, ConcreteType::UHPC, &c, &u, &k1, &k2);
         Assert::AreEqual(0.5, c, 0.0001);
         Assert::AreEqual(1.0, u);
         Assert::AreEqual(99999999., k1);
         Assert::AreEqual(1.8, k2, 0.0001);

         ConcreteUtil::InterfaceShearParameters(false, ConcreteType::UHPC, ConcreteType::Normal, &c, &u, &k1, &k2);
         Assert::AreEqual(0.025, c, 0.0001);
         Assert::AreEqual(0.6, u);
         Assert::AreEqual(99999999., k1);
         Assert::AreEqual(0.8, k2, 0.0001);

         ConcreteUtil::InterfaceShearParameters(false, ConcreteType::UHPC, ConcreteType::UHPC, &c, &u, &k1, &k2);
         Assert::AreEqual(0.025, c, 0.0001);
         Assert::AreEqual(0.6, u);
         Assert::AreEqual(99999999., k1);
         Assert::AreEqual(0.8, k2, 0.0001);
      }

      TEST_METHOD(InterfaceShearResistance)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SixthEdition2012);

         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);

         Float64 c, u, k1, k2;
         ConcreteUtil::InterfaceShearParameters(true, ConcreteType::Normal, ConcreteType::Normal, &c, &u, &k1, &k2);

         Float64 eq1, eq2, eq3;
         ConcreteUtil::InterfaceShearResistances(c, u, k1, k2, 10.0, 0.88, 1.0, 5.0, 100.0, &eq1, &eq2, &eq3);

         Assert::AreEqual(56.6, eq1, 0.00001);
         Assert::AreEqual(15.0, eq2, 0.00001);
         Assert::AreEqual(18.0, eq3, 0.00001);

         // Beginning with 7th Edition, fy is no longer limited to 60 ksi
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SeventhEdition2014);
         ConcreteUtil::InterfaceShearResistances(c, u, k1, k2, 10.0, 0.88, 1.0, 5.0, 100.0, &eq1, &eq2, &eq3);

         Assert::AreEqual(91.8, eq1, 0.00001);
         Assert::AreEqual(15.0, eq2, 0.00001);
         Assert::AreEqual(18.0, eq3, 0.00001);
      }

      TEST_METHOD(LowerLimitOfShearStrength)
      {
         LRFDAutoVersion av;
         
         // before 2nd Edition
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994);
         Assert::AreEqual(0.0, ConcreteUtil::LowerLimitOfShearStrength(true, true));
         Assert::AreEqual(0.0, ConcreteUtil::LowerLimitOfShearStrength(true, false));
         Assert::AreEqual(0.0, ConcreteUtil::LowerLimitOfShearStrength(false, true));
         Assert::AreEqual(0.0, ConcreteUtil::LowerLimitOfShearStrength(false, false));

         // 2nd edition
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SecondEdition1998);
         {
            // US units
            WBFL::Units::AutoSystem au;
            WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
            WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch); 
            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);

            Assert::AreEqual(0.1, ConcreteUtil::LowerLimitOfShearStrength(true, true), 0.0001);
            Assert::AreEqual(0.1, ConcreteUtil::LowerLimitOfShearStrength(true, false), 0.0001);
            Assert::AreEqual(0.1, ConcreteUtil::LowerLimitOfShearStrength(false, true), 0.0001);
            Assert::AreEqual(0.1, ConcreteUtil::LowerLimitOfShearStrength(false, false), 0.0001);
         }

         {
            // SI Units
            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);

            Assert::AreEqual(0.7e6, ConcreteUtil::LowerLimitOfShearStrength(true, true), 0.0001);
            Assert::AreEqual(0.7e6, ConcreteUtil::LowerLimitOfShearStrength(true, false), 0.0001);
            Assert::AreEqual(0.7e6, ConcreteUtil::LowerLimitOfShearStrength(false, true), 0.0001);
            Assert::AreEqual(0.7e6, ConcreteUtil::LowerLimitOfShearStrength(false, false), 0.0001);
         }

         // 4th edition
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FourthEdition2007);
         {
            // US units
            WBFL::Units::AutoSystem au;
            WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
            WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);

            Assert::AreEqual(0.21, ConcreteUtil::LowerLimitOfShearStrength(true, true), 0.0001);
            Assert::AreEqual(0.0, ConcreteUtil::LowerLimitOfShearStrength(true, false), 0.0001);
            Assert::AreEqual(0.0, ConcreteUtil::LowerLimitOfShearStrength(false, true), 0.0001);
            Assert::AreEqual(0.0, ConcreteUtil::LowerLimitOfShearStrength(false, false), 0.0001);
         }
      }

      TEST_METHOD(UpperLimitForBv)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEditionWith1997Interims);
         {
            // US units
            WBFL::Units::AutoSystem au;
            WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
            WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);

            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);
            Assert::AreEqual(36.0, ConcreteUtil::UpperLimitForBv());
         }

         {
            // SI units
            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
            Assert::AreEqual(0.9, ConcreteUtil::UpperLimitForBv());
         }

         // no limit starting with 2nd Edition
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SecondEdition1998);
         Assert::AreEqual(Float64_Max, ConcreteUtil::UpperLimitForBv());
      }

      TEST_METHOD(MinLegsForBv)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEditionWith1997Interims);
         {
            // US units
            WBFL::Units::AutoSystem au;
            WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
            WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);

            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);
            Assert::AreEqual((Uint16)1, ConcreteUtil::MinLegsForBv(12.0));
            Assert::AreEqual((Uint16)4, ConcreteUtil::MinLegsForBv(56.0));
         }

         {
            // SI units
            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
            Assert::AreEqual((Uint16)1, ConcreteUtil::MinLegsForBv(0.1));
            Assert::AreEqual((Uint16)4, ConcreteUtil::MinLegsForBv(1.0));
         }

         // Always 1 starting with 2nd Edition
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SecondEdition1998);
         Assert::AreEqual((Uint16)1, ConcreteUtil::MinLegsForBv(0.1));
         Assert::AreEqual((Uint16)1, ConcreteUtil::MinLegsForBv(Float64_Max));
      }

      TEST_METHOD(AvfOverSMin)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEditionWith1997Interims);

         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);

         Float64 c, u, k1, k2;
         ConcreteUtil::InterfaceShearParameters(true, ConcreteType::Normal, ConcreteType::Normal, &c, &u, &k1, &k2);

         auto results = ConcreteUtil::AvfOverSMin(48.0, 100.0, 30.0, 0.9, c, u, 0.0);
         Assert::IsTrue(ConcreteUtil::HsAvfOverSMinType::ValidEqnsType::eq41only == results.ValidEqns);
         Assert::AreEqual(0.024, results.res5_7_4_2_1, 0.0001);
         Assert::AreEqual(0.0, results.res5_7_4_2_3, 0.0001);
         Assert::AreEqual(0.024, results.AvfOverSMin, 0.0001);

         // additional requirements added 4th Edition 2007
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FourthEdition2007);
         results = ConcreteUtil::AvfOverSMin(48.0, 100.0, 30.0, 0.9, c, u, 0.0);
         Assert::IsTrue(ConcreteUtil::HsAvfOverSMinType::ValidEqnsType::eqBoth == results.ValidEqns);
         Assert::AreEqual(0.024, results.res5_7_4_2_1, 0.0001);
         Assert::AreEqual(0.3953333, results.res5_7_4_2_3, 0.0001);
         Assert::AreEqual(0.024, results.AvfOverSMin, 0.0001);
      }

      TEST_METHOD(MaxStirrupSpacingForHoriz)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994);

         {
            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);

            WBFL::Units::AutoSystem au;
            WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
            WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);

            Assert::AreEqual(24.0, ConcreteUtil::MaxStirrupSpacingForHoriz(24.0));
            Assert::AreEqual(24.0, ConcreteUtil::MaxStirrupSpacingForHoriz(56.0));
         }

         {
            LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
            Assert::AreEqual(0.6, ConcreteUtil::MaxStirrupSpacingForHoriz(0.6));
            Assert::AreEqual(0.6, ConcreteUtil::MaxStirrupSpacingForHoriz(1.2));
         }

         
         // Changed in 7th Edition 2014
         LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SeventhEdition2014);
         {
            // US units
            WBFL::Units::AutoSystem au;
            WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
            WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);

            Assert::AreEqual(48.0, ConcreteUtil::MaxStirrupSpacingForHoriz(56.0));
            Assert::AreEqual(24.0, ConcreteUtil::MaxStirrupSpacingForHoriz(24.0));
         }
      }

      TEST_METHOD(AvfRequiredForHoriz)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);

         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);

         Float64 c, u, k1, k2;
         ConcreteUtil::InterfaceShearParameters(true, ConcreteType::Normal, ConcreteType::Normal, &c, &u, &k1, &k2);
         Assert::AreEqual(0.1, ConcreteUtil::AvfRequiredForHoriz(10.0, 0.9, 0.1, c, u, k1, k2, 6.0, 10, 0.88, 0.0, 5.0, 100.0), 0.00001);
         Assert::AreEqual(Float64_Max, ConcreteUtil::AvfRequiredForHoriz(30.0, 0.9, 0.1, c, u, k1, k2, 6.0, 10, 0.88, 0.0, 5.0, 100.0), 0.00001);
      }

      TEST_METHOD(ComputeConcreteDensityModificationFactor)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SeventhEdition2014);
         // there wasn't LWC modifications before 2nd Edition 2016 interims, also no modifications for Normal concrete or UHPC
         Assert::AreEqual(1.0, ConcreteUtil::ComputeConcreteDensityModificationFactor(ConcreteType::AllLightweight, 0.0, false, 0.0, 0.0));
         Assert::AreEqual(1.0, ConcreteUtil::ComputeConcreteDensityModificationFactor(ConcreteType::SandLightweight, 0.0, false, 0.0, 0.0));

         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SeventhEditionWith2016Interims);
         Assert::AreEqual(1.0, ConcreteUtil::ComputeConcreteDensityModificationFactor(ConcreteType::Normal, 0.0, false, 0.0, 0.0));
         Assert::AreEqual(1.0, ConcreteUtil::ComputeConcreteDensityModificationFactor(ConcreteType::PCI_UHPC, 0.0, false, 0.0, 0.0));
         Assert::AreEqual(1.0, ConcreteUtil::ComputeConcreteDensityModificationFactor(ConcreteType::UHPC, 0.0, false, 0.0, 0.0));

         {
            // US units
            WBFL::Units::AutoSystem au;
            WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
            WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);

            Float64 fc = WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::KSI);
            Float64 fct = WBFL::Units::ConvertToSysUnits(0.1, WBFL::Units::Measure::KSI);

            Float64 density = WBFL::Units::ConvertToSysUnits(0.100, WBFL::Units::Measure::KipPerFeet3);
            Assert::AreEqual(0.75, ConcreteUtil::ComputeConcreteDensityModificationFactor(ConcreteType::AllLightweight, density, false, fct, fc));
            Assert::AreEqual(0.21019038988498026, ConcreteUtil::ComputeConcreteDensityModificationFactor(ConcreteType::AllLightweight, density, true, fct, fc));

            density = WBFL::Units::ConvertToSysUnits(0.125, WBFL::Units::Measure::KipPerFeet3);
            Assert::AreEqual(0.9375, ConcreteUtil::ComputeConcreteDensityModificationFactor(ConcreteType::AllLightweight, density, false, fct, fc));
            Assert::AreEqual(0.21019038988498026, ConcreteUtil::ComputeConcreteDensityModificationFactor(ConcreteType::AllLightweight, density, true, fct, fc));

            density = WBFL::Units::ConvertToSysUnits(0.149, WBFL::Units::Measure::KipPerFeet3);
            fct = WBFL::Units::ConvertToSysUnits(3.0, WBFL::Units::Measure::KSI);
            Assert::AreEqual(1.0, ConcreteUtil::ComputeConcreteDensityModificationFactor(ConcreteType::AllLightweight, density, false, fct, fc));
            Assert::AreEqual(1.0, ConcreteUtil::ComputeConcreteDensityModificationFactor(ConcreteType::AllLightweight, density, true, fct, fc));
         }
      }

      TEST_METHOD(GetTypeName)
      {
         LRFDAutoVersion av;

         Assert::AreEqual(_T("Normal Weight Concrete"), ConcreteUtil::GetTypeName(ConcreteType::Normal, true).c_str());
         Assert::AreEqual(_T("Normal"), ConcreteUtil::GetTypeName(ConcreteType::Normal, false).c_str());

         Assert::AreEqual(_T("PCI Ultra High Performance Concrete (PCI-UHPC)"), ConcreteUtil::GetTypeName(ConcreteType::PCI_UHPC, true).c_str());
         Assert::AreEqual(_T("PCI-UHPC"), ConcreteUtil::GetTypeName(ConcreteType::PCI_UHPC, false).c_str());

         Assert::AreEqual(_T("Ultra High Performance Concrete (UHPC)"), ConcreteUtil::GetTypeName(ConcreteType::UHPC, true).c_str());
         Assert::AreEqual(_T("UHPC"), ConcreteUtil::GetTypeName(ConcreteType::UHPC, false).c_str());

         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SeventhEditionWith2015Interims);
         Assert::AreEqual(_T("All Lightweight Concrete"), ConcreteUtil::GetTypeName(ConcreteType::AllLightweight, true).c_str());
         Assert::AreEqual(_T("AllLightweight"), ConcreteUtil::GetTypeName(ConcreteType::AllLightweight, false).c_str());

         Assert::AreEqual(_T("Sand Lightweight Concrete"), ConcreteUtil::GetTypeName(ConcreteType::SandLightweight, true).c_str());
         Assert::AreEqual(_T("SandLightweight"), ConcreteUtil::GetTypeName(ConcreteType::SandLightweight, false).c_str());

         // 7th Edition w/ 2016 interims, All and Sand LWC became just LWC
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SeventhEditionWith2016Interims);
         Assert::AreEqual(_T("Lightweight Concrete"), ConcreteUtil::GetTypeName(ConcreteType::AllLightweight, true).c_str());
         Assert::AreEqual(_T("AllLightweight"), ConcreteUtil::GetTypeName(ConcreteType::AllLightweight, false).c_str());

         Assert::AreEqual(_T("Lightweight Concrete"), ConcreteUtil::GetTypeName(ConcreteType::SandLightweight, true).c_str());
         Assert::AreEqual(_T("SandLightweight"), ConcreteUtil::GetTypeName(ConcreteType::SandLightweight, false).c_str());
      }

      TEST_METHOD(GetTypeFromTypeName)
      {
         LRFDAutoVersion av;
         Assert::IsTrue(ConcreteType::Normal == ConcreteUtil::GetTypeFromTypeName(_T("Normal")));
         Assert::IsTrue(ConcreteType::PCI_UHPC == ConcreteUtil::GetTypeFromTypeName(_T("PCI-UHPC")));
         Assert::IsTrue(ConcreteType::UHPC == ConcreteUtil::GetTypeFromTypeName(_T("UHPC")));

         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SeventhEditionWith2015Interims);
         Assert::IsTrue(ConcreteType::AllLightweight == ConcreteUtil::GetTypeFromTypeName(_T("AllLightweight")));
         Assert::IsTrue(ConcreteType::SandLightweight == ConcreteUtil::GetTypeFromTypeName(_T("SandLightweight")));

         // 7th Edition w/ 2016 interims, All and Sand LWC became just LWC, using SandLightWeight to mean LWC
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SeventhEditionWith2016Interims);
         Assert::IsTrue(ConcreteType::SandLightweight == ConcreteUtil::GetTypeFromTypeName(_T("AllLightweight")));
         Assert::IsTrue(ConcreteType::SandLightweight == ConcreteUtil::GetTypeFromTypeName(_T("SandLightweight")));
      }
   };
}
