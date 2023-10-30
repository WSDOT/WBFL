#include "pch.h"
#include "CppUnitTest.h"
#include "TxnTestClass.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EAFUnitTests
{
	TEST_CLASS(TestMacroTxn)
	{
	public:
		
		TEST_METHOD(Test)
		{
         testUndoableTxn      txn1;
         testNotUndoableTxn   txn2;
         testNotRepeatableTxn txn3;

         CEAFMacroTxn macro;
         macro.AddTransaction(txn1);
         macro.AddTransaction(txn1);
         macro.AddTransaction(txn1);
         Assert::IsTrue(macro.IsUndoable());
         Assert::IsTrue(macro.IsRepeatable());

         macro.AddTransaction(txn2);
         Assert::IsFalse(macro.IsUndoable());
         Assert::IsTrue(macro.IsRepeatable());

         macro.AddTransaction(txn3);
         Assert::IsFalse(macro.IsUndoable());
         Assert::IsFalse(macro.IsRepeatable());
      }
	};
}
