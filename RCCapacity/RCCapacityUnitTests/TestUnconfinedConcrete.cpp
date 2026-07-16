#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RCCapacityUnitTest
{
	TEST_CLASS(TestUnconfinedConcrete)
	{
	public:

		TEST_METHOD(Test)
		{
         CComPtr<IUnconfinedConcrete> concrete;
         Assert::AreEqual(S_OK, concrete.CoCreateInstance(CLSID_UnconfinedConcrete));

         Float64 val;
         Assert::AreEqual(E_INVALIDARG, concrete->put_fc(0));
         Assert::AreEqual(E_INVALIDARG, concrete->put_fc(-10));
         Assert::AreEqual(S_OK, concrete->put_fc(13789514.59)); // 2 KSI
         Assert::AreEqual(S_OK, concrete->put_fc(20684271.88)); // 3 KSI
         Assert::AreEqual(S_OK, concrete->put_fc(89631844.81)); // 13 KSI
         Assert::AreEqual(S_OK, concrete->put_fc(117210874)); // 17 KSI
         Assert::AreEqual(E_POINTER, concrete->get_fc(nullptr));

         Assert::AreEqual(S_OK, concrete->put_fc(89631844.81));
         Assert::AreEqual(S_OK, concrete->get_fc(&val));
         Assert::IsTrue(IsEqual(val, 89631844.810000));

         TestISupportUnitServer(concrete);

         CComQIPtr<IStressStrain> ss(concrete);
         Assert::IsTrue(ss != nullptr);

         Assert::AreEqual(E_POINTER, ss->ComputeStress(0.00764, nullptr));
         Assert::AreEqual(S_OK, ss->ComputeStress(0.00764, &val));
         Assert::IsTrue(IsEqual(val, 0.00));
         Assert::AreEqual(S_FALSE, ss->ComputeStress(-0.00764, &val)); // exceeds concrete crushing strain -0.003
         Assert::IsTrue(IsEqual(val, -78333650.161053866));
         Assert::AreEqual(S_OK, ss->ComputeStress(-0.00245, &val));
         Assert::IsTrue(IsEqual(val, -86277115.080388337));

         CComQIPtr<ISupportErrorInfo> eInfo(ss);
         Assert::IsTrue(eInfo != nullptr);
         Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_IUnconfinedConcrete));
         Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_IStressStrain));
         Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_ISupportUnitServer));
         Assert::AreEqual(S_FALSE, eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo));
      }
	};
}
