#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestPsStrand)
	{
	public:
		
      TEST_METHOD(LRFD_1st_Edition)
      {
         BDSAutoVersion auto_ver;

         Uint16 nStrands = 10;
         Float64 Pjack;
         Float64 xferTime = WBFL::Units::ConvertToSysUnits(24.0, WBFL::Units::Measure::Hour);
         const StrandPool* pPool = StrandPool::GetInstance();

         // LRFD 1st Edition

         BDSManager::SetEdition(BDSManager::Edition::FirstEdition1994);
         BDSManager::SetUnits(BDSManager::Units::SI);

         // Grade 1725 SR
         const auto* pStrand = pPool->GetStrand(WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, WBFL::Materials::PsStrand::Coating::None, WBFL::Materials::PsStrand::Size::D1270);
         Pjack = PsStrand::GetPjack(*pStrand, nStrands, xferTime);
         Pjack = WBFL::Units::ConvertFromSysUnits(Pjack, WBFL::Units::Measure::Kilonewton);
         Assert::AreEqual(1153.82, Pjack, 0.01);
         Assert::AreEqual(60.0, PsStrand::GetXferLength(*pStrand, false)/pStrand->GetNominalDiameter(), 0.0001);
         Assert::AreEqual(50.0, PsStrand::GetXferLength(*pStrand, true) / pStrand->GetNominalDiameter(), 0.0001);
         auto fpj = WBFL::Units::ConvertToSysUnits(Pjack, WBFL::Units::Measure::Kilonewton) / (nStrands * pStrand->GetNominalArea());
         Assert::AreEqual(1.89438534, PsStrand::GetDevLength(*pStrand, 0.95 * fpj, 0.85 * fpj, WBFL::Units::ConvertToSysUnits(48., WBFL::Units::Measure::Inch), true), 0.00001);
         Assert::AreEqual(1.51550827, PsStrand::GetDevLength(*pStrand, 0.95 * fpj, 0.85 * fpj, WBFL::Units::ConvertToSysUnits(48., WBFL::Units::Measure::Inch), false), 0.00001);
         Assert::AreEqual(1.89438534, PsStrand::GetDevLength(*pStrand, 0.95 * fpj, 0.85 * fpj, WBFL::Units::ConvertToSysUnits(12., WBFL::Units::Measure::Inch), true), 0.00001);
         Assert::AreEqual(1.51550827, PsStrand::GetDevLength(*pStrand, 0.95 * fpj, 0.85 * fpj, WBFL::Units::ConvertToSysUnits(12., WBFL::Units::Measure::Inch), false), 0.00001);
         Assert::AreEqual(0.9, PsStrand::GetFpjPT(*pStrand) / pStrand->GetYieldStrength());
         Assert::AreEqual(1225931.625, PsStrand::GetPjackPT(*pStrand, nStrands));

         // Grade 1725 LR
         pStrand = pPool->GetStrand(WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, WBFL::Materials::PsStrand::Coating::None, WBFL::Materials::PsStrand::Size::D1270);
         Pjack = PsStrand::GetPjack(*pStrand, nStrands, xferTime);
         Pjack = WBFL::Units::ConvertFromSysUnits(Pjack, WBFL::Units::Measure::Kilonewton);
         Assert::AreEqual(1249.97, Pjack, 0.01);

         // Grade 1860 SR
         pStrand = pPool->GetStrand(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, WBFL::Materials::PsStrand::Coating::None, WBFL::Materials::PsStrand::Size::D1270);
         Pjack = PsStrand::GetPjack(*pStrand, nStrands, xferTime);
         Pjack = WBFL::Units::ConvertFromSysUnits(Pjack, WBFL::Units::Measure::Kilonewton);
         Assert::AreEqual(1321.92, Pjack, 0.01);

         // Grade 1860 LR
         pStrand = pPool->GetStrand(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, WBFL::Materials::PsStrand::Coating::None, WBFL::Materials::PsStrand::Size::D1270);
         Pjack = PsStrand::GetPjack(*pStrand, nStrands, xferTime);
         Pjack = WBFL::Units::ConvertFromSysUnits(Pjack, WBFL::Units::Measure::Kilonewton);
         Assert::AreEqual(1432.08, Pjack, 0.01);

         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(1725, WBFL::Units::Measure::MPa), PsStrand::GetUltimateStrength(WBFL::Materials::PsStrand::Grade::Gr1725));
         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(1860, WBFL::Units::Measure::MPa), PsStrand::GetUltimateStrength(WBFL::Materials::PsStrand::Grade::Gr1860));
         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(2070, WBFL::Units::Measure::MPa), PsStrand::GetUltimateStrength(WBFL::Materials::PsStrand::Grade::Gr2070));

         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(197000.0, WBFL::Units::Measure::MPa), PsStrand::GetModE());

         BDSManager::SetUnits(BDSManager::Units::US);
         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(250, WBFL::Units::Measure::KSI), PsStrand::GetUltimateStrength(WBFL::Materials::PsStrand::Grade::Gr1725));
         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(270, WBFL::Units::Measure::KSI), PsStrand::GetUltimateStrength(WBFL::Materials::PsStrand::Grade::Gr1860));
         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(300, WBFL::Units::Measure::KSI), PsStrand::GetUltimateStrength(WBFL::Materials::PsStrand::Grade::Gr2070));

         Assert::AreEqual(0.90, PsStrand::GetYieldStrength(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation) / PsStrand::GetUltimateStrength(WBFL::Materials::PsStrand::Grade::Gr1860));
         Assert::AreEqual(0.85, PsStrand::GetYieldStrength(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved) / PsStrand::GetUltimateStrength(WBFL::Materials::PsStrand::Grade::Gr1860));

         Assert::AreEqual(0.78, PsStrand::GetStressLimit(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, PsStrand::Stage::Jacking) / PsStrand::GetUltimateStrength(WBFL::Materials::PsStrand::Grade::Gr1860));
         Assert::AreEqual(0.72, PsStrand::GetStressLimit(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, PsStrand::Stage::Jacking) / PsStrand::GetUltimateStrength(WBFL::Materials::PsStrand::Grade::Gr1860));
         Assert::AreEqual(0.74, PsStrand::GetStressLimit(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, PsStrand::Stage::AfterTransfer) / PsStrand::GetUltimateStrength(WBFL::Materials::PsStrand::Grade::Gr1860));
         Assert::AreEqual(0.70, PsStrand::GetStressLimit(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, PsStrand::Stage::AfterTransfer) / PsStrand::GetUltimateStrength(WBFL::Materials::PsStrand::Grade::Gr1860));
         Assert::AreEqual(0.80, PsStrand::GetStressLimit(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, PsStrand::Stage::AfterAllLosses) / PsStrand::GetYieldStrength(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation));
         Assert::AreEqual(0.80, PsStrand::GetStressLimit(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, PsStrand::Stage::AfterAllLosses) / PsStrand::GetYieldStrength(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved));
         Assert::ExpectException<XCodeVersion>([&]() {PsStrand::GetStressLimit(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, PsStrand::Stage::BeforeTransfer); });

         Assert::AreEqual(WBFL::Units::ConvertToSysUnits(28500.0, WBFL::Units::Measure::KSI), PsStrand::GetModE());

      }

      TEST_METHOD(LRFD_1st_Edition_with_1997_interims)
      {
         BDSAutoVersion auto_ver;

         Uint16 nStrands = 10;
         Float64 Pjack;
         Float64 xferTime = WBFL::Units::ConvertToSysUnits(24.0, WBFL::Units::Measure::Hour);
         const StrandPool* pPool = StrandPool::GetInstance();

         // LRFD 1st Edition with 1996 and/or 1997 interim provisions

         BDSManager::SetEdition(BDSManager::Edition::FirstEditionWith1997Interims);
         BDSManager::SetUnits(BDSManager::Units::SI);

         // Grade 1725 SR
         const auto* pStrand = pPool->GetStrand(WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, WBFL::Materials::PsStrand::Coating::None, WBFL::Materials::PsStrand::Size::D1270);
         Pjack = PsStrand::GetPjack(*pStrand, nStrands, xferTime);
         Pjack = WBFL::Units::ConvertFromSysUnits(Pjack, WBFL::Units::Measure::Kilonewton);
         Assert::AreEqual(9446.32, Pjack, 0.01);
         auto fpj = WBFL::Units::ConvertToSysUnits(Pjack, WBFL::Units::Measure::Kilonewton) / (nStrands * pStrand->GetNominalArea());
         Assert::AreEqual(15.509351883900017, PsStrand::GetDevLength(*pStrand, 0.95 * fpj, 0.85 * fpj, WBFL::Units::ConvertToSysUnits(48., WBFL::Units::Measure::Inch), true));
         Assert::AreEqual(12.407481507120016, PsStrand::GetDevLength(*pStrand, 0.95 * fpj, 0.85 * fpj, WBFL::Units::ConvertToSysUnits(48., WBFL::Units::Measure::Inch), false));
         Assert::AreEqual(15.509351883900017, PsStrand::GetDevLength(*pStrand, 0.95 * fpj, 0.85 * fpj, WBFL::Units::ConvertToSysUnits(12., WBFL::Units::Measure::Inch), true));
         Assert::AreEqual(12.407481507120016, PsStrand::GetDevLength(*pStrand, 0.95 * fpj, 0.85 * fpj, WBFL::Units::ConvertToSysUnits(12., WBFL::Units::Measure::Inch), false));

         // Grade 1725 LR
         pStrand = pPool->GetStrand(WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, WBFL::Materials::PsStrand::Coating::None, WBFL::Materials::PsStrand::Size::D1270);
         Pjack = PsStrand::GetPjack(*pStrand, nStrands, xferTime);
         Pjack = WBFL::Units::ConvertFromSysUnits(Pjack, WBFL::Units::Measure::Kilonewton);
         Assert::AreEqual(41377.73, Pjack, 0.01);

         // Grade 1860 SR
         pStrand = pPool->GetStrand(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, WBFL::Materials::PsStrand::Coating::None, WBFL::Materials::PsStrand::Size::D1270);
         Pjack = PsStrand::GetPjack(*pStrand, nStrands, xferTime);
         Pjack = WBFL::Units::ConvertFromSysUnits(Pjack, WBFL::Units::Measure::Kilonewton);
         Assert::AreEqual(10822.61, Pjack, 0.01);

         // Grade 1860 LR
         pStrand = pPool->GetStrand(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, WBFL::Materials::PsStrand::Coating::None, WBFL::Materials::PsStrand::Size::D1270);
         Pjack = PsStrand::GetPjack(*pStrand, nStrands, xferTime);
         Pjack = WBFL::Units::ConvertFromSysUnits(Pjack, WBFL::Units::Measure::Kilonewton);
         Assert::AreEqual(47406.29, Pjack, 0.01);


         Assert::AreEqual(0.75, PsStrand::GetStressLimit(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, PsStrand::Stage::BeforeTransfer) / PsStrand::GetUltimateStrength(WBFL::Materials::PsStrand::Grade::Gr1860));
         Assert::AreEqual(0.70, PsStrand::GetStressLimit(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, PsStrand::Stage::BeforeTransfer) / PsStrand::GetUltimateStrength(WBFL::Materials::PsStrand::Grade::Gr1860));
         Assert::AreEqual(0.80, PsStrand::GetStressLimit(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, PsStrand::Stage::AfterAllLosses) / PsStrand::GetYieldStrength(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation));
         Assert::AreEqual(0.80, PsStrand::GetStressLimit(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, PsStrand::Stage::AfterAllLosses) / PsStrand::GetYieldStrength(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved));
         Assert::ExpectException<XCodeVersion>([&]() {PsStrand::GetStressLimit(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, PsStrand::Stage::Jacking); });
         Assert::ExpectException<XCodeVersion>([&]() {PsStrand::GetStressLimit(WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, PsStrand::Stage::AfterTransfer); });
      }
	};
}
