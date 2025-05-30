#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EAFUnitTests
{
	class TestTxn : public WBFL::EAF::Transaction
	{
	public:
		virtual std::unique_ptr<WBFL::EAF::Transaction> CreateClone() const override { return std::make_unique<TestTxn>(); }
		virtual std::_tstring Name() const override { return _T("TestTxn"); }
	};

	TEST_CLASS(TestTransaction)
	{
	public:
		
		TEST_METHOD(Test)
		{
			TestTxn txn;
			Assert::IsTrue(txn.Execute());
			Assert::IsFalse(txn.IsRepeatable());
			Assert::IsFalse(txn.IsUndoable());
			Assert::AreEqual(_T("TestTxn"), txn.Name().c_str());

			std::_tostringstream os;
			txn.Log(os);
			Assert::AreEqual(_T("TestTxn"), os.str().c_str());


			auto clone = txn.CreateClone();
			Assert::IsTrue(clone->Execute());
			Assert::IsFalse(clone->IsRepeatable());
			Assert::IsFalse(clone->IsUndoable());
			Assert::AreEqual(_T("TestTxn"), clone->Name().c_str());
		}
	};
}
