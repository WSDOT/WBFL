#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RCCapacityUnitTest
{
	TEST_CLASS(TestRCBeam)
	{
	public:

		TEST_METHOD(Test)
		{
         CComPtr<IRCBeam> beam;
         Assert::AreEqual(S_OK, beam.CoCreateInstance(CLSID_RCBeam));

         Float64 val;
         Assert::AreEqual(E_INVALIDARG, beam->put_Aps(-10));
         Assert::AreEqual(S_OK, beam->put_Aps(10));
         Assert::AreEqual(E_POINTER, beam->get_Aps(nullptr));
         Assert::AreEqual(S_OK, beam->get_Aps(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         Assert::AreEqual(E_INVALIDARG, beam->put_As(-10));
         Assert::AreEqual(S_OK, beam->put_As(10));
         Assert::AreEqual(E_POINTER, beam->get_As(nullptr));
         Assert::AreEqual(S_OK, beam->get_As(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         Assert::AreEqual(E_INVALIDARG, beam->put_b(-10));
         Assert::AreEqual(S_OK, beam->put_b(10));
         Assert::AreEqual(E_POINTER, beam->get_b(nullptr));
         Assert::AreEqual(S_OK, beam->get_b(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         Assert::AreEqual(E_INVALIDARG, beam->put_bw(-10));
         Assert::AreEqual(S_OK, beam->put_bw(10));
         Assert::AreEqual(E_POINTER, beam->get_bw(nullptr));
         Assert::AreEqual(S_OK, beam->get_bw(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         Assert::AreEqual(E_INVALIDARG, beam->put_dps(-10));
         Assert::AreEqual(S_OK, beam->put_dps(10));
         Assert::AreEqual(E_POINTER, beam->get_dps(nullptr));
         Assert::AreEqual(S_OK, beam->get_dps(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         Assert::AreEqual(E_INVALIDARG, beam->put_ds(-10));
         Assert::AreEqual(S_OK, beam->put_ds(10));
         Assert::AreEqual(E_POINTER, beam->get_ds(nullptr));
         Assert::AreEqual(S_OK, beam->get_ds(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         Assert::AreEqual(E_INVALIDARG, beam->put_Eps(-10));
         Assert::AreEqual(E_INVALIDARG, beam->put_Eps(0));
         Assert::AreEqual(S_OK, beam->put_Eps(10));
         Assert::AreEqual(E_POINTER, beam->get_Eps(nullptr));
         Assert::AreEqual(S_OK, beam->get_Eps(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         Assert::AreEqual(E_INVALIDARG, beam->put_Es(-10));
         Assert::AreEqual(E_INVALIDARG, beam->put_Es(0));
         Assert::AreEqual(S_OK, beam->put_Es(10));
         Assert::AreEqual(E_POINTER, beam->get_Es(nullptr));
         Assert::AreEqual(S_OK, beam->get_Es(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         Assert::AreEqual(E_INVALIDARG, beam->put_FcBeam(-10));
         Assert::AreEqual(E_INVALIDARG, beam->put_FcBeam(0));
         Assert::AreEqual(S_OK, beam->put_FcBeam(10));
         Assert::AreEqual(E_POINTER, beam->get_FcBeam(nullptr));
         Assert::AreEqual(S_OK, beam->get_FcBeam(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         Assert::AreEqual(E_INVALIDARG, beam->put_FcSlab(-10));
         Assert::AreEqual(E_INVALIDARG, beam->put_FcSlab(0));
         Assert::AreEqual(S_OK, beam->put_FcSlab(10));
         Assert::AreEqual(E_POINTER, beam->get_FcSlab(nullptr));
         Assert::AreEqual(S_OK, beam->get_FcSlab(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         Assert::AreEqual(E_INVALIDARG, beam->put_fpe(-10));
         Assert::AreEqual(S_OK, beam->put_fpe(10));
         Assert::AreEqual(E_POINTER, beam->get_fpe(nullptr));
         Assert::AreEqual(S_OK, beam->get_fpe(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         Assert::AreEqual(E_INVALIDARG, beam->put_fpu(-10));
         Assert::AreEqual(S_OK, beam->put_fpu(10));
         Assert::AreEqual(E_POINTER, beam->get_fpu(nullptr));
         Assert::AreEqual(S_OK, beam->get_fpu(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         Assert::AreEqual(E_INVALIDARG, beam->put_fpy(-10));
         Assert::AreEqual(S_OK, beam->put_fpy(10));
         Assert::AreEqual(E_POINTER, beam->get_fpy(nullptr));
         Assert::AreEqual(S_OK, beam->get_fpy(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         Assert::AreEqual(E_INVALIDARG, beam->put_fy(-10));
         Assert::AreEqual(S_OK, beam->put_fy(10));
         Assert::AreEqual(E_POINTER, beam->get_fy(nullptr));
         Assert::AreEqual(S_OK, beam->get_fy(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         Assert::AreEqual(E_INVALIDARG, beam->put_h(-10));
         Assert::AreEqual(S_OK, beam->put_h(10));
         Assert::AreEqual(E_POINTER, beam->get_h(nullptr));
         Assert::AreEqual(S_OK, beam->get_h(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         Assert::AreEqual(E_INVALIDARG, beam->put_hf(-10));
         Assert::AreEqual(S_OK, beam->put_hf(10));
         Assert::AreEqual(E_POINTER, beam->get_hf(nullptr));
         Assert::AreEqual(S_OK, beam->get_hf(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         TestISupportUnitServer(beam);

         CComQIPtr<ISupportErrorInfo> eInfo(beam);
         Assert::IsTrue(eInfo != nullptr);
         Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_IRCBeam));
         Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_IStructuredStorage2));
         Assert::AreEqual(S_FALSE, eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo));
      }
	};
}
