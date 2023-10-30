#include "pch.h"
#include "CppUnitTest.h"
#include "TxnTestClass.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EAFUnitTests
{
	TEST_CLASS(TestTxnManager)
	{
	public:
		
		TEST_METHOD(Test)
		{
         testUndoableTxn txn1;
         testNotRepeatableTxn txn2;
         testNotUndoableTxn txn3;

         auto& txn_mgr = CEAFTxnManager::GetInstance();

         // Test the start up state
         Assert::IsFalse(txn_mgr.CanUndo());
         Assert::IsFalse(txn_mgr.CanRedo());
         Assert::IsFalse(txn_mgr.CanRepeat());
         Assert::AreEqual((IndexType)0,txn_mgr.GetTxnCount());
         Assert::AreEqual((IndexType)0,txn_mgr.GetUndoCount());
         Assert::IsFalse(txn_mgr.IsRedoMode());
         Assert::IsTrue(txn_mgr.IsRepeatMode());

         // Add a couple of non-repeatable transactions
         txn_mgr.Execute(txn2);
         txn_mgr.Execute(txn2);
         Assert::IsFalse(txn_mgr.CanRepeat()); // there are no repeatable txn's
         Assert::IsFalse(txn_mgr.IsRedoMode());
         Assert::IsTrue(txn_mgr.IsRepeatMode());

         // Add a repeatable txn
         txn_mgr.Execute(txn1);
         Assert::IsTrue(txn_mgr.CanRepeat()); // now there is one repeatable txn
         Assert::AreEqual(_T("Undoable Txn"),txn_mgr.RepeatName().c_str());
         Assert::IsFalse(txn_mgr.IsRedoMode());
         Assert::IsTrue(txn_mgr.IsRepeatMode());

         // Repeat the last txn
         txn_mgr.Repeat();
         Assert::IsTrue(txn_mgr.CanRepeat());
         Assert::AreEqual(_T("Undoable Txn"), txn_mgr.RepeatName().c_str());
         Assert::AreEqual((IndexType)4, txn_mgr.GetTxnCount());
         Assert::AreEqual((IndexType)0, txn_mgr.GetUndoCount());
         Assert::IsFalse(txn_mgr.IsRedoMode());
         Assert::IsTrue(txn_mgr.IsRepeatMode());

         // At this point, we can undo txn1, txn1, txn2, txn2 or we can repeat txn1
         Assert::IsTrue(txn_mgr.CanUndo());
         Assert::IsFalse(txn_mgr.CanRedo());
         Assert::IsTrue(txn_mgr.CanRepeat());

         // Undo the last txn
         Assert::AreEqual(_T("Undoable Txn"), txn_mgr.UndoName().c_str());
         txn_mgr.Undo();
         txn_mgr.Undo();
         Assert::AreEqual(_T("Not Repeatable Txn"), txn_mgr.UndoName().c_str());
         Assert::IsTrue(txn_mgr.CanUndo());
         Assert::IsTrue(txn_mgr.CanRedo());
         Assert::IsFalse(txn_mgr.CanRepeat());
         Assert::AreEqual((IndexType)2,txn_mgr.GetTxnCount());
         Assert::AreEqual((IndexType)2,txn_mgr.GetUndoCount());
         Assert::IsTrue(txn_mgr.IsRedoMode());
         Assert::IsFalse(txn_mgr.IsRepeatMode());

         // Redo the last undo
         Assert::AreEqual(_T("Undoable Txn"), txn_mgr.RedoName().c_str());
         txn_mgr.Redo();
         Assert::AreEqual(_T("Undoable Txn"), txn_mgr.UndoName().c_str());
         Assert::IsTrue(txn_mgr.CanUndo());
         Assert::IsTrue(txn_mgr.CanRedo());
         Assert::IsFalse(txn_mgr.CanRepeat());
         Assert::AreEqual((IndexType)3,txn_mgr.GetTxnCount());
         Assert::AreEqual((IndexType)1,txn_mgr.GetUndoCount());
         Assert::IsTrue(txn_mgr.IsRedoMode());
         Assert::IsFalse(txn_mgr.IsRepeatMode());

         // Add a non-undoable txn followed by an undoable txn
         txn_mgr.Execute(txn3);
         txn_mgr.Execute(txn1);
         Assert::AreEqual(_T("Undoable Txn"), txn_mgr.UndoName().c_str());
         Assert::IsTrue(txn_mgr.CanUndo());
         Assert::IsFalse(txn_mgr.CanRedo());
         Assert::IsTrue(txn_mgr.CanRepeat());
         Assert::AreEqual((IndexType)5,txn_mgr.GetTxnCount());
         Assert::AreEqual((IndexType)1,txn_mgr.GetUndoCount());
         Assert::IsFalse(txn_mgr.IsRedoMode());
         Assert::IsTrue(txn_mgr.IsRepeatMode());

         // Undo the last txn, the next txn is not-undoable, but there is another
         // undoable one farther up the stack so undo should be enabled.
         txn_mgr.Undo();
         Assert::AreEqual(_T("Undoable Txn"), txn_mgr.UndoName().c_str());
         Assert::IsTrue(txn_mgr.CanUndo());
         Assert::IsTrue(txn_mgr.CanRedo());
         Assert::IsFalse(txn_mgr.CanRepeat());
         Assert::AreEqual((IndexType)4,txn_mgr.GetTxnCount());
         Assert::AreEqual((IndexType)2,txn_mgr.GetUndoCount());
         Assert::IsTrue(txn_mgr.IsRedoMode());
         Assert::IsFalse(txn_mgr.IsRepeatMode());

         // Undo all that we can (should be 3 times)
         txn_mgr.Undo();
         txn_mgr.Undo();
         txn_mgr.Undo();
         Assert::IsFalse(txn_mgr.CanUndo());
         Assert::IsTrue(txn_mgr.CanRedo());
         Assert::IsFalse(txn_mgr.CanRepeat());
         Assert::AreEqual((IndexType)1,txn_mgr.GetTxnCount());
         Assert::AreEqual((IndexType)5,txn_mgr.GetUndoCount());
         Assert::IsTrue(txn_mgr.IsRedoMode());
         Assert::IsFalse(txn_mgr.IsRepeatMode());

         // Clear the txn history, but keep the undo history
         txn_mgr.ClearTxnHistory();
         Assert::IsFalse(txn_mgr.CanUndo());
         Assert::IsTrue(txn_mgr.CanRedo());
         Assert::IsFalse(txn_mgr.CanRepeat());
         Assert::AreEqual((IndexType)0,txn_mgr.GetTxnCount());
         Assert::AreEqual((IndexType)5,txn_mgr.GetUndoCount());
         Assert::IsTrue(txn_mgr.IsRedoMode());
         Assert::IsFalse(txn_mgr.IsRepeatMode());

         // Add a few txns back
         txn_mgr.Execute(txn1);
         txn_mgr.Execute(txn1);
         txn_mgr.Execute(txn1);
         Assert::IsTrue(txn_mgr.CanUndo());
         Assert::IsFalse(txn_mgr.CanRedo());
         Assert::IsTrue(txn_mgr.CanRepeat());
         Assert::AreEqual((IndexType)3,txn_mgr.GetTxnCount());
         Assert::AreEqual((IndexType)5,txn_mgr.GetUndoCount());
         Assert::IsFalse(txn_mgr.IsRedoMode());
         Assert::IsTrue(txn_mgr.IsRepeatMode());
         Assert::AreEqual(_T("Undoable Txn"), txn_mgr.UndoName().c_str());

         // Clear the undo history, but keep the txn history
         txn_mgr.ClearUndoHistory();
         Assert::IsTrue(txn_mgr.CanUndo());
         Assert::IsFalse(txn_mgr.CanRedo());
         Assert::IsTrue(txn_mgr.CanRepeat());
         Assert::AreEqual((IndexType)3,txn_mgr.GetTxnCount());
         Assert::AreEqual((IndexType)0,txn_mgr.GetUndoCount());
         Assert::IsFalse(txn_mgr.IsRedoMode());
         Assert::IsTrue(txn_mgr.IsRepeatMode());

         // Undo one CEAF just so there is something in m_UndoHistory
         txn_mgr.Undo();
         Assert::IsTrue(txn_mgr.CanUndo());
         Assert::IsTrue(txn_mgr.CanRedo());
         Assert::IsFalse(txn_mgr.CanRepeat());
         Assert::AreEqual((IndexType)2,txn_mgr.GetTxnCount());
         Assert::AreEqual((IndexType)1,txn_mgr.GetUndoCount());
         Assert::IsTrue(txn_mgr.IsRedoMode());
         Assert::IsFalse(txn_mgr.IsRepeatMode());
         Assert::AreEqual(_T("Undoable Txn"), txn_mgr.RedoName().c_str());

         // Clear everything out
         txn_mgr.Clear();
         Assert::IsFalse(txn_mgr.CanUndo());
         Assert::IsFalse(txn_mgr.CanRedo());
         Assert::IsFalse(txn_mgr.CanRepeat());
         Assert::AreEqual((IndexType)0,txn_mgr.GetTxnCount());
         Assert::AreEqual((IndexType)0,txn_mgr.GetUndoCount());
         Assert::IsFalse(txn_mgr.IsRedoMode());
         Assert::IsTrue(txn_mgr.IsRepeatMode());
      }
	};
}
