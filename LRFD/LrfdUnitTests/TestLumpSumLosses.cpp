#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestLumpSumLosses)
	{
	public:
		
		TEST_METHOD(Test)
		{

         LumpSumLosses loss(
            0.0051799896399999995,  // area of permanent strand
            0.00055999887999999998,  // area of TTS 
            1396186227.0505831, // fpj permanent strands
            1396188385.8038988, // fpj of temporary strands
            Losses::TempStrandUsage::Pretensioned,
            0.1, // beforeXfer
            0.5, // afterXfer
            1.0, // atLifting
            1.5, // atShipping
            2.0, // beforeTempStrandRemoval
            2.5, // afterTempStrandRemoval,
            3.0, // afterDeckPlacement
            3.5, // afterSIDL
            4.0 // final
         );


         // permanent strands
         Assert::AreEqual(0.1, loss.PermanentStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(0.5, loss.PermanentStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(0.5, loss.PermanentStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(1.0, loss.PermanentStrand_AtLifting(), 0.00001);
         Assert::AreEqual(1.5, loss.PermanentStrand_AtShipping(), 0.00001);
         Assert::AreEqual(2.0, loss.PermanentStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(2.5, loss.PermanentStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(3.0, loss.PermanentStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(3.5, loss.PermanentStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(4.0, loss.PermanentStrand_Final(), 0.00001);

         // temporary strands
         Assert::AreEqual(0.1, loss.TemporaryStrand_BeforeTransfer(), 0.00001);
         Assert::AreEqual(0.5, loss.TemporaryStrand_AfterTransfer(), 0.00001);
         Assert::AreEqual(0.5, loss.TemporaryStrand_AfterTemporaryStrandInstallation(), 0.00001);
         Assert::AreEqual(1.0, loss.TemporaryStrand_AtLifting(), 0.00001);
         Assert::AreEqual(1.5, loss.TemporaryStrand_AtShipping(), 0.00001);
         Assert::AreEqual(2.0, loss.TemporaryStrand_BeforeTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterTemporaryStrandRemoval(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterDeckPlacement(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_AfterSIDL(), 0.00001);
         Assert::AreEqual(0., loss.TemporaryStrand_Final(), 0.00001);

         loss.SetTempStrandUsage(Losses::TempStrandUsage::PTBeforeLifting);
         Assert::AreEqual(0.5, loss.PermanentStrand_AfterTemporaryStrandInstallation(), 0.00001);

         loss.SetTempStrandUsage(Losses::TempStrandUsage::PTAfterLifting);
         Assert::AreEqual(1.5, loss.PermanentStrand_AfterTemporaryStrandInstallation(), 0.00001);

         loss.SetTempStrandUsage(Losses::TempStrandUsage::PTBeforeShipping);
         Assert::AreEqual(1.5, loss.PermanentStrand_AfterTemporaryStrandInstallation(), 0.00001);
      }
	};
}
