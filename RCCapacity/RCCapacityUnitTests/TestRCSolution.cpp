#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RCCapacityUnitTest
{
	TEST_CLASS(TestRCSolution)
	{
	public:

		TEST_METHOD(Test)
		{
         CComPtr<IRCSolution> soln;
         Assert::AreEqual(S_OK, soln.CoCreateInstance(CLSID_RCSolution));

         Assert::AreEqual(S_OK, soln->InitSolution(1, 2, 3, 4, 5, 6, 7, 8, VARIANT_FALSE));

         Float64 val;
         Assert::AreEqual(E_POINTER, soln->get_Mn(nullptr));
         Assert::AreEqual(S_OK, soln->get_Mn(&val));
         Assert::IsTrue(IsEqual(val, 1.0));

         Assert::AreEqual(E_POINTER, soln->get_NeutralAxisDepth(nullptr));
         Assert::AreEqual(S_OK, soln->get_NeutralAxisDepth(&val));
         Assert::IsTrue(IsEqual(val, 2.0));

         Assert::AreEqual(E_POINTER, soln->get_fps(nullptr));
         Assert::AreEqual(S_OK, soln->get_fps(&val));
         Assert::IsTrue(IsEqual(val, 3.0));

         Assert::AreEqual(E_POINTER, soln->get_Cflange(nullptr));
         Assert::AreEqual(S_OK, soln->get_Cflange(&val));
         Assert::IsTrue(IsEqual(val, 4.0));

         Assert::AreEqual(E_POINTER, soln->get_Cweb(nullptr));
         Assert::AreEqual(S_OK, soln->get_Cweb(&val));
         Assert::IsTrue(IsEqual(val, 5.0));

         Assert::AreEqual(E_POINTER, soln->get_T(nullptr));
         Assert::AreEqual(S_OK, soln->get_T(&val));
         Assert::IsTrue(IsEqual(val, 6.0));

         Assert::AreEqual(E_POINTER, soln->get_Yflange(nullptr));
         Assert::AreEqual(S_OK, soln->get_Yflange(&val));
         Assert::IsTrue(IsEqual(val, 7.0));

         Assert::AreEqual(E_POINTER, soln->get_Yweb(nullptr));
         Assert::AreEqual(S_OK, soln->get_Yweb(&val));
         Assert::IsTrue(IsEqual(val, 8.0));

         VARIANT_BOOL bVal;
         Assert::AreEqual(E_POINTER, soln->get_IsOverReinforced(nullptr));
         Assert::AreEqual(S_OK, soln->get_IsOverReinforced(&bVal));
         Assert::AreEqual((int)VARIANT_FALSE, (int)bVal);

         CComQIPtr<ISupportErrorInfo> eInfo(soln);
         Assert::IsTrue(eInfo != nullptr);
         Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_IRCSolution));
         Assert::AreEqual(S_FALSE, eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo));
      }
	};
}
