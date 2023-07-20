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
		virtual void DrawGraph(CWnd* pGraphWnd, CDC* pDC) override { m_bGraphDrawn = true; };
		virtual std::unique_ptr<GraphBuilder> Clone() const override { return std::make_unique<TestGB>(*this); }

		virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override { m_bOnUpdateCalled = true; };
		virtual BOOL CanPrint() override { return m_bUseDefaults ? __super::CanPrint() : FALSE; }
		virtual bool HandleDoubleClick(UINT nFlags, CPoint point) override { return m_bUseDefaults ? __super::HandleDoubleClick(nFlags, point) : true; }

		bool m_bUseDefaults = true;
		bool m_bOnUpdateCalled = false;
		bool m_bGraphDrawn = false;

	};

	TEST_CLASS(TestGraphBuilder)
	{
	public:
		
		TEST_METHOD(Test)
		{
			TestGB gb;
			Assert::AreEqual(_T("Unnamed"), gb.GetName().c_str());
			Assert::IsTrue(CString(_T("")) == gb.GetDocumentationSetName());
			Assert::AreEqual((UINT)0, gb.GetHelpID());
			Assert::IsNull(gb.GetMenuBitmap());

			gb.SetName(_T("Test"));
			Assert::AreEqual(_T("Test"), gb.GetName().c_str());

			gb.InitDocumentation(_T("MyDocs"), 200);
			Assert::IsTrue(CString("MyDocs") == gb.GetDocumentationSetName());
			Assert::AreEqual((UINT)200, gb.GetHelpID());

			gb.SetMenuBitmap((const CBitmap*)100);
			Assert::IsTrue((int*)100 == (int*)gb.GetMenuBitmap());

			Assert::AreEqual(0, gb.InitializeGraphController(0, 0));
			
			gb.DrawGraph(0,0);
			Assert::IsTrue(gb.m_bGraphDrawn);

			gb.OnUpdate(0, 0, 0);
			Assert::IsTrue(gb.m_bOnUpdateCalled);

			gb.m_bUseDefaults = true;
			Assert::IsTrue(gb.CanPrint());
			Assert::IsFalse(gb.HandleDoubleClick(0, CPoint()));

			gb.m_bUseDefaults = false;
			Assert::IsFalse(gb.CanPrint());
			Assert::IsTrue(gb.HandleDoubleClick(0, CPoint()));

			auto clone = gb.Clone();

			Assert::AreEqual(_T("Test"), clone->GetName().c_str());
			Assert::IsTrue(CString("MyDocs") == clone->GetDocumentationSetName());
			Assert::AreEqual((UINT)200, clone->GetHelpID());
			Assert::IsTrue((int*)100 == (int*)clone->GetMenuBitmap());
			Assert::AreEqual(0, clone->InitializeGraphController(0, 0));
		}
	};
}
