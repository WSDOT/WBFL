#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RCCapacityUnitTest
{
	TEST_CLASS(TestRCBeam2Ex)
	{
	public:

		TEST_METHOD(Test)
		{
         CComPtr<IRCBeam2Ex> beam;
         Assert::AreEqual(S_OK, beam.CoCreateInstance(CLSID_RCBeam2Ex));

         Float64 val;
         Float64 val1, val2, val3;
         IndexType count;
         Assert::AreEqual(E_INVALIDARG, beam->AddRebarLayer(-10, 10, 1.0));
         Assert::AreEqual(E_INVALIDARG, beam->AddRebarLayer(10, -10, 1.0));
         Assert::AreEqual(E_INVALIDARG, beam->AddRebarLayer(10, 10, -1.0));
         Assert::AreEqual(E_INVALIDARG, beam->AddRebarLayer(40, 40, 2.0));
         Assert::AreEqual(S_OK, beam->AddRebarLayer(10, 10, 1.0));
         Assert::AreEqual(S_OK, beam->AddRebarLayer(20, 20, 0.5));
         Assert::AreEqual(S_OK, beam->AddRebarLayer(30, 30, 0.0));
         Assert::AreEqual(E_POINTER, beam->get_RebarLayerCount(nullptr));
         Assert::AreEqual(S_OK, beam->get_RebarLayerCount(&count));
         Assert::AreEqual((IndexType)3, count);
         Assert::AreEqual(E_INVALIDARG, beam->get_RebarLayerDepth(-1, &val));
         Assert::AreEqual(E_POINTER, beam->get_RebarLayerDepth(0, nullptr));
         Assert::AreEqual(S_OK, beam->get_RebarLayerDepth(0, &val));
         Assert::IsTrue(IsEqual(val, 10.0));
         Assert::AreEqual(E_INVALIDARG, beam->get_RebarLayerSteel(-1, &val));
         Assert::AreEqual(E_INVALIDARG, beam->get_RebarLayerSteel(10, &val));
         Assert::AreEqual(E_POINTER, beam->get_RebarLayerSteel(0, nullptr));
         Assert::AreEqual(S_OK, beam->get_RebarLayerSteel(0, &val));
         Assert::IsTrue(IsEqual(val, 10.0));
         Assert::AreEqual(E_INVALIDARG, beam->get_RebarLayerDevFactor(-1, &val));
         Assert::AreEqual(E_INVALIDARG, beam->get_RebarLayerDevFactor(10, &val));
         Assert::AreEqual(E_POINTER, beam->get_RebarLayerDevFactor(0, nullptr));
         Assert::AreEqual(S_OK, beam->get_RebarLayerDevFactor(0, &val));
         Assert::IsTrue(IsEqual(val, 1.0));
         Assert::AreEqual(E_INVALIDARG, beam->GetRebarLayer(-1, &val1, &val2, &val3));
         Assert::AreEqual(E_INVALIDARG, beam->GetRebarLayer(10, &val1, &val2, &val3));
         Assert::AreEqual(E_POINTER, beam->GetRebarLayer(1, nullptr, &val2, &val3));
         Assert::AreEqual(E_POINTER, beam->GetRebarLayer(1, &val1, nullptr, &val3));
         Assert::AreEqual(E_POINTER, beam->GetRebarLayer(1, &val1, &val2, nullptr));
         Assert::AreEqual(S_OK, beam->GetRebarLayer(1, &val1, &val2, &val3));
         Assert::IsTrue(IsEqual(val1, 20.0));
         Assert::IsTrue(IsEqual(val2, 20.0));
         Assert::IsTrue(IsEqual(val3, 0.5));
         Assert::AreEqual(E_INVALIDARG, beam->RemoveRebarLayer(-1));
         Assert::AreEqual(E_INVALIDARG, beam->RemoveRebarLayer(10));
         Assert::AreEqual(S_OK, beam->RemoveRebarLayer(1));
         Assert::AreEqual(S_OK, beam->get_RebarLayerCount(&count));
         Assert::AreEqual((IndexType)2, count);
         Assert::AreEqual(S_OK, beam->ClearRebarLayers());
         Assert::AreEqual(S_OK, beam->get_RebarLayerCount(&count));
         Assert::AreEqual((IndexType)0, count);

         Assert::AreEqual(E_INVALIDARG, beam->AddStrandLayer(-10, 10, 1.0));
         Assert::AreEqual(E_INVALIDARG, beam->AddStrandLayer(10, -10, 1.0));
         Assert::AreEqual(E_INVALIDARG, beam->AddStrandLayer(10, 10, -1.0));
         Assert::AreEqual(E_INVALIDARG, beam->AddStrandLayer(40, 40, 2.0));
         Assert::AreEqual(S_OK, beam->AddStrandLayer(10, 10, 1.0));
         Assert::AreEqual(S_OK, beam->AddStrandLayer(20, 20, 0.5));
         Assert::AreEqual(S_OK, beam->AddStrandLayer(30, 30, 0.0));
         Assert::AreEqual(E_POINTER, beam->get_StrandLayerCount(nullptr));
         Assert::AreEqual(S_OK, beam->get_StrandLayerCount(&count));
         Assert::AreEqual((IndexType)3, count);
         Assert::AreEqual(E_INVALIDARG, beam->get_StrandLayerDepth(-1, &val));
         Assert::AreEqual(E_POINTER, beam->get_StrandLayerDepth(0, nullptr));
         Assert::AreEqual(S_OK, beam->get_StrandLayerDepth(0, &val));
         Assert::IsTrue(IsEqual(val, 10.0));
         Assert::AreEqual(E_INVALIDARG, beam->get_StrandLayerSteel(-1, &val));
         Assert::AreEqual(E_INVALIDARG, beam->get_StrandLayerSteel(10, &val));
         Assert::AreEqual(E_POINTER, beam->get_StrandLayerSteel(0, nullptr));
         Assert::AreEqual(S_OK, beam->get_StrandLayerSteel(0, &val));
         Assert::IsTrue(IsEqual(val, 10.0));
         Assert::AreEqual(E_INVALIDARG, beam->get_StrandLayerDevFactor(-1, &val));
         Assert::AreEqual(E_INVALIDARG, beam->get_StrandLayerDevFactor(10, &val));
         Assert::AreEqual(E_POINTER, beam->get_StrandLayerDevFactor(0, nullptr));
         Assert::AreEqual(S_OK, beam->get_StrandLayerDevFactor(0, &val));
         Assert::IsTrue(IsEqual(val, 1.0));
         Assert::AreEqual(E_INVALIDARG, beam->GetStrandLayer(-1, &val1, &val2, &val3));
         Assert::AreEqual(E_INVALIDARG, beam->GetStrandLayer(10, &val1, &val2, &val3));
         Assert::AreEqual(E_POINTER, beam->GetStrandLayer(1, nullptr, &val2, &val3));
         Assert::AreEqual(E_POINTER, beam->GetStrandLayer(1, &val1, nullptr, &val3));
         Assert::AreEqual(E_POINTER, beam->GetStrandLayer(1, &val1, &val2, nullptr));
         Assert::AreEqual(S_OK, beam->GetStrandLayer(1, &val1, &val2, &val3));
         Assert::IsTrue(IsEqual(val1, 20.0));
         Assert::IsTrue(IsEqual(val2, 20.0));
         Assert::IsTrue(IsEqual(val3, 0.5));
         Assert::AreEqual(E_INVALIDARG, beam->RemoveStrandLayer(-1));
         Assert::AreEqual(E_INVALIDARG, beam->RemoveStrandLayer(10));
         Assert::AreEqual(S_OK, beam->RemoveStrandLayer(1));
         Assert::AreEqual(S_OK, beam->get_StrandLayerCount(&count));
         Assert::AreEqual((IndexType)2, count);
         Assert::AreEqual(S_OK, beam->ClearStrandLayers());
         Assert::AreEqual(S_OK, beam->get_StrandLayerCount(&count));
         Assert::AreEqual((IndexType)0, count);

         Assert::AreEqual(E_INVALIDARG, beam->put_b(-10));
         Assert::AreEqual(S_OK, beam->put_b(10));
         Assert::AreEqual(E_POINTER, beam->get_b(nullptr));
         Assert::AreEqual(S_OK, beam->get_b(&val));
         Assert::IsTrue(IsEqual(val, 10.0));

         Assert::AreEqual(E_INVALIDARG, beam->put_hf(-10));
         Assert::AreEqual(S_OK, beam->put_hf(10));
         Assert::AreEqual(E_POINTER, beam->get_hf(nullptr));
         Assert::AreEqual(S_OK, beam->get_hf(&val));
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

         Assert::AreEqual(E_INVALIDARG, beam->putref_Beam(nullptr));
         Assert::AreEqual(E_POINTER, beam->get_Beam(nullptr));

         TestISupportUnitServer(beam);

         CComQIPtr<ISupportErrorInfo> eInfo(beam);
         Assert::IsTrue(eInfo != nullptr);
         Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_IRCBeam2Ex));
         Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_IStructuredStorage2));
         Assert::AreEqual(S_FALSE, eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo));
      }
	};
}
