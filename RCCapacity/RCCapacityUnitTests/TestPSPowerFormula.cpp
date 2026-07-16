#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RCCapacityUnitTest
{
	TEST_CLASS(TestPSPowerFormula)
	{
	public:

		TEST_METHOD(Test)
		{
         CComPtr<IStressStrain> ps;
         Assert::AreEqual(S_OK, ps.CoCreateInstance(CLSID_PSPowerFormula));

         TestISupportUnitServer(ps);

         CComQIPtr<IStressStrain> ss(ps);
         Assert::IsTrue(ss != nullptr);

         Float64 val;
         Assert::AreEqual(E_POINTER, ss->ComputeStress(0.00764, nullptr));
         Assert::AreEqual(S_OK, ss->ComputeStress(0.00764, &val));
         Assert::IsTrue(IsEqual(val, 1446556950.5987, 0.0001));
         Assert::AreEqual(S_OK, ss->ComputeStress(-0.00764, &val));
         Assert::IsTrue(IsEqual(val, -1446556950.5987, 0.0001));
         Assert::AreEqual(S_FALSE, ss->ComputeStress(0.1, &val)); // strain exceeds tension fracture strain
         Assert::IsTrue(IsEqual(val, 1861584469.1559, 0.0001));
         Assert::AreEqual(S_OK, ss->ComputeStress(-0.1, &val));
         Assert::IsTrue(IsEqual(val, -1861584469.1559, 0.0001));

         Assert::AreEqual(S_OK, ss->ComputeStress(0.035, &val));

         CComQIPtr<ISupportErrorInfo> eInfo(ss);
         Assert::IsTrue(eInfo != nullptr);
         Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_IStressStrain));
         Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_ISupportUnitServer));
         Assert::AreEqual(S_FALSE, eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo));
      }
	};
}
