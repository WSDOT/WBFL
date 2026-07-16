#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RCCapacityUnitTest
{
	TEST_CLASS(TestUHPConcrete)
	{
	public:

		TEST_METHOD(Test)
		{
         CComPtr<IUHPConcrete> concrete;
         Assert::AreEqual(S_OK, concrete.CoCreateInstance(CLSID_UHPConcrete));

         concrete->put_ftcr(8273708.7518); // 1.2 KSI
         concrete->put_ftloc(8273708.7518); // 1.2 KSI
         concrete->put_etloc(0.0045);
         concrete->put_gamma(0.85);

         Float64 val;
         Assert::AreEqual(E_INVALIDARG, concrete->put_fc(0));
         Assert::AreEqual(E_INVALIDARG, concrete->put_fc(-10));
         Assert::AreEqual(S_OK, concrete->put_fc(151684660.45)); // 22 KSI
         Assert::AreEqual(E_POINTER, concrete->get_fc(nullptr));

         Assert::AreEqual(S_OK, concrete->get_fc(&val));
         Assert::IsTrue(IsEqual(val, 151684660.45));

         TestISupportUnitServer(concrete);

         CComQIPtr<IStressStrain> ss(concrete);
         Assert::IsTrue(ss != nullptr);

         // compute stress for tension strains

         // elastic region
         Assert::AreEqual(E_POINTER, ss->ComputeStress(0.00005, nullptr));
         Assert::AreEqual(S_OK, ss->ComputeStress(0.00005, &val));
         Assert::IsTrue(IsEqual(val, 2390168.2910847836));

         // plastic region
         Assert::AreEqual(S_OK, ss->ComputeStress(0.0010, &val));
         Assert::IsTrue(IsEqual(val, 0.85 * 8273708.7518)); // gamma*ft,cr

         // after crack localization
         Assert::AreEqual(S_OK, ss->ComputeStress(0.0050, &val));
         Assert::IsTrue(IsEqual(val, 0.0));

         // compute stress for compression strain

         // elastic region
         Assert::AreEqual(S_OK, ss->ComputeStress(-0.001, &val));
         Assert::IsTrue(IsEqual(val, -47803365.821695670));

         // plastic region
         Assert::AreEqual(S_OK, ss->ComputeStress(-0.003, &val));
         Assert::IsTrue(IsEqual(val, -0.85 * 151684660.45)); // stress plateau at alpha*f'c

         // after crushing
         Assert::AreEqual(S_FALSE, ss->ComputeStress(-0.004, &val)); // -0.0035 is crushing
         Assert::IsTrue(IsEqual(val, -0.85 * 151684660.45));

         CComQIPtr<ISupportErrorInfo> eInfo(ss);
         Assert::IsTrue(eInfo != nullptr);
         Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_IUHPConcrete));
         Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_IStressStrain));
         Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_ISupportUnitServer));
         Assert::AreEqual(S_FALSE, eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo));
      }
	};
}
