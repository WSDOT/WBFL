#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RCCapacityUnitTest
{
	TEST_CLASS(TestRebarModel)
	{
	public:

		TEST_METHOD(Test)
		{
         CComPtr<IRebarModel> rebar;
         Assert::AreEqual(S_OK, rebar.CoCreateInstance(CLSID_RebarModel));

         Float64 val;
         Assert::AreEqual(E_POINTER, rebar->get_fy(nullptr));
         Assert::AreEqual(S_OK, rebar->get_fy(&val));
         Assert::IsTrue(IsEqual(val, 413685437.59020001));
         Assert::AreEqual(E_INVALIDARG, rebar->put_fy(-10));
         Assert::AreEqual(E_INVALIDARG, rebar->put_fy(0));
         Assert::AreEqual(S_OK, rebar->put_fy(val));

         Assert::AreEqual(E_POINTER, rebar->get_Es(nullptr));
         Assert::AreEqual(S_OK, rebar->get_Es(&val));
         Assert::IsTrue(IsEqual(val, 199947961501.93002));
         Assert::AreEqual(E_INVALIDARG, rebar->put_Es(-10));
         Assert::AreEqual(E_INVALIDARG, rebar->put_Es(0));
         Assert::AreEqual(S_OK, rebar->put_Es(val));

         CComQIPtr<IStressStrain> ss(rebar);
         Assert::IsTrue(ss != nullptr);

         Assert::AreEqual(E_POINTER, ss->ComputeStress(0.001, nullptr));
         Assert::AreEqual(S_OK, ss->ComputeStress(0.001, &val));
         Assert::IsTrue(IsEqual(val, 199947961.50193003));
         Assert::AreEqual(S_OK, ss->ComputeStress(-0.001, &val));
         Assert::IsTrue(IsEqual(val, -199947961.50193003));
         Assert::AreEqual(S_FALSE, ss->ComputeStress(0.1, &val)); // strain exceeds tensile fracture strain
         Assert::IsTrue(IsEqual(val, 413685437.59020001));
         Assert::AreEqual(S_OK, ss->ComputeStress(-0.1, &val));
         Assert::IsTrue(IsEqual(val, -413685437.59020001));

         CComQIPtr<ISupportErrorInfo> eInfo(rebar);
         Assert::IsTrue(eInfo != nullptr);
         Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_IRebarModel));
         Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_IStressStrain));
         Assert::AreEqual(S_FALSE, eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo));
      }
	};
}
