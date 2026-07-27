///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// Fem2dTestUtil.cpp
#include "pch.h"

CComModule _Module;

Fem2dModelFixture::Fem2dModelFixture() :
   m_pSink(nullptr)
{
   HRESULT hr = Model.CoCreateInstance(CLSID_Fem2dModel);
   Assert::AreEqual(S_OK, hr, L"CoCreateInstance(CLSID_Fem2dModel) failed");

   CComObject<CFem2dTestEventSink>::CreateInstance(&m_pSink);
   m_pSink->AddRef();

   hr = AtlAdvise(Model, m_pSink, IID_IFem2dModelEvents, &m_pSink->m_dwCookie);
   Assert::AreEqual(S_OK, hr, L"AtlAdvise(IID_IFem2dModelEvents) failed");
}

Fem2dModelFixture::~Fem2dModelFixture()
{
   AtlUnadvise(Model, IID_IFem2dModelEvents, m_pSink->m_dwCookie);
   m_pSink->Release();
}

bool Fem2dModelFixture::PassedModelChangedTest()
{
   return m_pSink->PassedModelChangedTest();
}

bool Fem2dModelFixture::PassedLoadingChangedTest()
{
   return m_pSink->PassedLoadingChangedTest();
}
