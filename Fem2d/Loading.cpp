///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////
// Loading.cpp : Implementation of CLoading
#include "stdafx.h"
#include "Loading.h"
#include "Model.h"


/////////////////////////////////////////////////////////////////////////////
// CLoading

STDMETHODIMP CLoading::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IFem2dLoading
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CLoading::~CLoading()
{
    m_pJointLoads->Release();
    m_pDistributedLoads->Release();
    m_pJointDeflections->Release();
    m_pPointLoads->Release();
    m_pMemberStrains->Release();
}

HRESULT CLoading::OnCreate(IFem2dModel* pParent, ModelEvents* pEvents, WBFL::FEA2D::Loading* pCore)
{
   ATLASSERT(pCore!=0);

   InitParent(pParent); // CCircularChild implementation
   m_pModel = pEvents;
   m_pCore = pCore;

   // Joint loads
   CComObject<CJointLoadCollection>* pj;
   HRESULT hr = CComObject<CJointLoadCollection>::CreateInstance( &pj );
   if ( FAILED(hr) )
      return hr;

   pj->Init(pParent, m_pModel, this, pCore);
   m_pJointLoads = pj;
   m_pJointLoads->AddRef();

   // Distributed loads
   CComObject<CDistributedLoadCollection>* pw;
   hr = CComObject<CDistributedLoadCollection>::CreateInstance( &pw );
   if ( FAILED(hr) )
      return hr;

   pw->Init(pParent, m_pModel, this, pCore);
   m_pDistributedLoads = pw;
   m_pDistributedLoads->AddRef();

   // Joint Deflections
   CComObject<CJointDeflectionCollection>* pd;
   hr = CComObject<CJointDeflectionCollection>::CreateInstance( &pd );
   if ( FAILED(hr) )
      return hr;

   pd->Init(pParent, m_pModel, this, pCore);
   m_pJointDeflections = pd;
   m_pJointDeflections->AddRef();

   // Point loads
   CComObject<CPointLoadCollection>* pp;
   hr = CComObject<CPointLoadCollection>::CreateInstance( &pp );
   if ( FAILED(hr) )
      return hr;

   pp->Init(pParent, m_pModel, this, pCore);
   m_pPointLoads = pp;
   m_pPointLoads->AddRef();

   // Member Strains
   CComObject<CMemberStrainCollection>* ps;
   hr = CComObject<CMemberStrainCollection>::CreateInstance( &ps );
   if ( FAILED(hr) )
      return hr;

   ps->Init(pParent, m_pModel, this, pCore);
   m_pMemberStrains = ps;
   m_pMemberStrains->AddRef();

   return S_OK;
}

STDMETHODIMP CLoading::get_ID(LoadCaseIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetID();

	return S_OK;
}

STDMETHODIMP CLoading::get_JointLoads(IFem2dJointLoadCollection **pVal)
{
   CHECK_RETOBJ(pVal);
	*pVal = m_pJointLoads;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CLoading::get_DistributedLoads(IFem2dDistributedLoadCollection **pVal)
{
   CHECK_RETOBJ(pVal);
	*pVal = m_pDistributedLoads;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CLoading::get_JointDeflections(IFem2dJointDeflectionCollection **pVal)
{
   CHECK_RETOBJ(pVal);
	*pVal = m_pJointDeflections;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CLoading::get_PointLoads(IFem2dPointLoadCollection **pVal)
{
   CHECK_RETOBJ(pVal);
	*pVal = m_pPointLoads;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CLoading::get_MemberStrains(IFem2dMemberStrainCollection **pVal)
{
   CHECK_RETOBJ(pVal);
	*pVal = m_pMemberStrains;
   (*pVal)->AddRef();

	return S_OK;
}
