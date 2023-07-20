#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestStrandPool)
	{
	public:
		
		TEST_METHOD(StrandPoolTest)
		{
         LRFDAutoVersion auto_ver;

         LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);

         const StrandPool* pPool = StrandPool::GetInstance();
         const WBFL::Materials::PsStrand* pStrand;
         WBFL::Materials::PsStrand::Grade grade;
         WBFL::Materials::PsStrand::Type type;
         WBFL::Materials::PsStrand::Size size[] = { 
            WBFL::Materials::PsStrand::Size::D635,// 1/4"
            WBFL::Materials::PsStrand::Size::D794,// 5/16"
            WBFL::Materials::PsStrand::Size::D953,// 3/8"
            WBFL::Materials::PsStrand::Size::D1111,// 7/16"
            WBFL::Materials::PsStrand::Size::D1270,// 1/2"
            WBFL::Materials::PsStrand::Size::D1524,// 0.6"
            WBFL::Materials::PsStrand::Size::D1778,// 0.7"
            WBFL::Materials::PsStrand::Size::D1320,// 1/2 HBS (Special)
            WBFL::Materials::PsStrand::Size::D1575// 0.62"
         };

         Int64 hashval;
         Int16 cGrade, cType, cCoating, cSize;
         Int16 nSize;

         for (cGrade = 0; cGrade < 3; cGrade++)
         {
            grade = (cGrade == 0 ? WBFL::Materials::PsStrand::Grade::Gr1725 : cGrade == 1 ? WBFL::Materials::PsStrand::Grade::Gr1860 : WBFL::Materials::PsStrand::Grade::Gr2070);
            nSize = (cGrade == 0 ? 0 : 2);

            for (cType = 0; cType < 2; cType++)
            {
               type = (cType == 0 ? WBFL::Materials::PsStrand::Type::StressRelieved : WBFL::Materials::PsStrand::Type::LowRelaxation);

               for (cCoating = 0; cCoating < 2; cCoating++)
               {
                  WBFL::Materials::PsStrand::Coating coating = (cCoating == 0 ? WBFL::Materials::PsStrand::Coating::None : WBFL::Materials::PsStrand::Coating::GritEpoxy);
                  for (cSize = nSize; cSize < sizeof(size) / sizeof(WBFL::Materials::PsStrand::Size); cSize++)
                  {
                     hashval = pPool->GetStrandKey(grade, type, coating, size[cSize]);
                     pStrand = pPool->GetStrand(hashval);
                     if (pStrand)
                     {
                        Assert::IsTrue(pStrand->GetGrade() == grade);
                        Assert::IsTrue(pStrand->GetType() == type);
                        Assert::IsTrue(pStrand->GetCoating() == coating);
                        Assert::IsTrue(pStrand->GetSize() == size[cSize]);
                     }
                  }
               }
            }
         }
      }

      TEST_METHOD(StrandIterator)
      {
         StrandIter iter;
         WBFL::Materials::PsStrand::Grade grade;
         WBFL::Materials::PsStrand::Type type;
         Int16 cGrade, cType;
         Int16 nStrand;

         for (cGrade = 0; cGrade < 2; cGrade++)
         {
            grade = (cGrade == 0 ? WBFL::Materials::PsStrand::Grade::Gr1725 : WBFL::Materials::PsStrand::Grade::Gr1860);
            for (cType = 0; cType < 2; cType++)
            {
               nStrand = 0;

               type = (cType == 0 ? WBFL::Materials::PsStrand::Type::StressRelieved : WBFL::Materials::PsStrand::Type::LowRelaxation);

               iter.SetGrade(grade);
               iter.SetType(type);

               for (iter.Begin(); iter; iter.Next())
               {
                  const WBFL::Materials::PsStrand* pStrand = iter.GetCurrentStrand();
                  Assert::IsNotNull(pStrand);

                  Assert::IsTrue(pStrand->GetGrade() == grade);
                  Assert::IsTrue(pStrand->GetType() == type);
                  nStrand++;
               }

               Assert::IsTrue(nStrand == (cGrade == 0 ? 9 : 7));
            }
         }
      }
	};
}
