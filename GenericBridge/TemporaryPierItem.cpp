///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 2009  Washington State Department of Transportation
//                   Bridge and Structures Office
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

// TemporaryPierItem.cpp : Implementation of CTemporaryPierItem
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "TemporaryPierItem.h"
#include "Pier.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTemporaryPierItem
HRESULT CTemporaryPierItem::FinalConstruct()
{
   CComObject<CPier>* pPier;
   CComObject<CPier>::CreateInstance(&pPier);
   m_Pier = pPier;
   AdvisePier();
   return S_OK;
}

void CTemporaryPierItem::FinalRelease()
{
   UnadvisePier();
   m_Pier.Release();
}


void CTemporaryPierItem::Init(long id,Float64 location,BSTR bstrRemovalStage)
{
   m_ID = id;
   m_Location = location;
   m_bstrRemovalStage = bstrRemovalStage;
}

void CTemporaryPierItem::Init(long id,Float64 location,BSTR bstrRemovalStage,IPier* pier)
{
   Init(id,location,bstrRemovalStage);
   UnadvisePier();
   m_Pier = pier;
   AdvisePier();
}

STDMETHODIMP CTemporaryPierItem::InterfaceSupportsErrorInfo(REFIID riid)
{

	static const IID* arr[] = 
	{
		&IID_ITemporaryPierItem,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CTemporaryPierItem::Clone(ITemporaryPierItem* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CTemporaryPierItem>* pClone;
   CComObject<CTemporaryPierItem>::CreateInstance(&pClone);
   (*clone) = pClone;
   (*clone)->AddRef();

   CComPtr<IPier> clonePier;
   CPier* pPier = dynamic_cast<CPier*>(m_Pier.p);
   pPier->Clone(&clonePier);
   pClone->Init(m_ID,m_Location,m_bstrRemovalStage,clonePier);
   return S_OK;
}

///////////////////////////////////////////////////////////////////////
// ITemporaryPierItem Interface
STDMETHODIMP CTemporaryPierItem::get_ID(long* id)
{
   CHECK_RETVAL(id);
   (*id) = m_ID;
   return S_OK;
}

STDMETHODIMP CTemporaryPierItem::get_Location(Float64* location)
{
   CHECK_RETVAL(location);
   (*location) = m_Location;
   return S_OK;
}

STDMETHODIMP CTemporaryPierItem::put_Location(Float64 location)
{
   if ( IsEqual(m_Location,location) )
      return S_OK;

   m_Location = location;
   Fire_OnTemporaryPierChanged(m_ID);
   return S_OK;
}

STDMETHODIMP CTemporaryPierItem::get_RemovalStage(BSTR* bstrRemovalStage)
{
   CHECK_RETSTRING(bstrRemovalStage);
   (*bstrRemovalStage) = m_bstrRemovalStage.Copy();
   return S_OK;
}

STDMETHODIMP CTemporaryPierItem::put_RemovalStage(BSTR bstrRemovalStage)
{
   if ( m_bstrRemovalStage == bstrRemovalStage )
      return S_OK;

   // Verify the stage actually exists
   CComPtr<IStageCollection> stages;
   m_pBridge->get_Stages(&stages);

   CComPtr<IStage> stage;
   stages->Find(bstrRemovalStage,&stage);

   if ( stage == NULL )
      return Error(IDS_E_STAGE_NOT_FOUND,IID_ITemporaryPierItem,GB_E_STAGE_NOT_FOUND);

   m_bstrRemovalStage = bstrRemovalStage;
   Fire_OnTemporaryPierChanged(m_ID);

   return S_OK;
}

STDMETHODIMP CTemporaryPierItem::get_Pier(IPier* *pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_Pier;
   (*pVal)->AddRef();
   return S_OK;
}

HRESULT CTemporaryPierItem::AdvisePier()
{
   HRESULT hr = m_Pier.Advise(GetUnknown(),IID_IPierEvents,&m_dwCookie);
   ATLASSERT(SUCCEEDED(hr));

   InternalRelease(); // Break circular reference

   return hr;
}

HRESULT CTemporaryPierItem::UnadvisePier()
{
   InternalAddRef(); // conteract InternalRelease() in advise
   CComQIPtr<IConnectionPointContainer> pCPC(m_Pier);
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint(IID_IPierEvents,&pCP);

   HRESULT hr = pCP->Unadvise(m_dwCookie);
   ATLASSERT( SUCCEEDED(hr) );

   return hr;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CTemporaryPierItem::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("TemporaryPierItem"),1.0);

   pSave->put_Property(CComBSTR("ID"),CComVariant(m_ID));
   pSave->put_Property(CComBSTR("Location"),CComVariant(m_Location));
   pSave->put_Property(CComBSTR("RemovalStage"),CComVariant(m_bstrRemovalStage));

   CComQIPtr<IStructuredStorage2> ssPier(m_Pier);
   ssPier->Save(pSave);
   
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CTemporaryPierItem::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("TemporaryPierItem"));

   pLoad->get_Property(CComBSTR("ID"),&var);
   m_ID = var.lVal;

   pLoad->get_Property(CComBSTR("Location"),&var);
   m_Location = var.dblVal;

   pLoad->get_Property(CComBSTR("RemovalStage"),&var);
   m_bstrRemovalStage = var.bstrVal;

   CComQIPtr<IStructuredStorage2> ssPier(m_Pier);
   ssPier->Load(pLoad);

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
