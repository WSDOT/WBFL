#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Graphing;

namespace GraphingUnitTests
{
	class TestGB : public GraphBuilder
	{
	public:
		GraphBuilder::GraphBuilder;

		virtual int InitializeGraphController(CWnd* pParent, UINT nID) override { return 0; };
		virtual void DrawGraph(CWnd* pGraphWnd, CDC* pDC) override { };
		virtual std::unique_ptr<GraphBuilder> Clone() const override { return std::make_unique<TestGB>(*this); }
	};

	TEST_CLASS(TestGraphManager)
	{
	public:
		
		TEST_METHOD(Test)
		{
			GraphManager mgr;
			mgr.SortByName(false);

			Assert::IsTrue(mgr.AddGraphBuilder(TestGB(_T("Alpha"))));
			Assert::IsTrue(mgr.AddGraphBuilder(TestGB(_T("Gamma"))));
			Assert::IsTrue(mgr.AddGraphBuilder(TestGB(_T("Beta"))));
			Assert::AreEqual((IndexType)3, mgr.GetGraphBuilderCount());

			Assert::IsFalse(mgr.AddGraphBuilder(TestGB(_T("Alpha")))); // one named Alpha is already being managed
			Assert::AreEqual((IndexType)3, mgr.GetGraphBuilderCount());

			std::vector<std::_tstring> unsorted{_T("Alpha"), _T("Gamma"), _T("Beta")};
			Assert::IsTrue(unsorted == mgr.GetGraphNames());

			mgr.SortByName(true);
			std::vector<std::_tstring> sorted{_T("Alpha"), _T("Beta"), _T("Gamma")};
			Assert::IsTrue(sorted == mgr.GetGraphNames());

			Assert::IsNull(mgr.RemoveGraphBuilder(_T("Junk")).get());
			Assert::AreEqual((IndexType)3, mgr.GetGraphBuilderCount());
			Assert::IsNotNull(mgr.RemoveGraphBuilder(_T("Alpha")).get());
			Assert::AreEqual((IndexType)2, mgr.GetGraphBuilderCount());

			Assert::ExpectException<std::invalid_argument>([&]() {mgr.GetGraphBuilder(100); });
			Assert::ExpectException<std::invalid_argument>([&]() {mgr.GetGraphBuilder(_T("Junk")); });

			mgr.ClearAll();
			Assert::AreEqual((IndexType)0, mgr.GetGraphBuilderCount());
		}
	};
}
