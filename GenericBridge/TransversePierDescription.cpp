///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

// TransversePierDescription.cpp : Implementation of CTransversePierDescription
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "TransversePierDescription.h"
#include "CrossBeam.h"
#include "ColumnSpacing.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransversePierDescription
HRESULT CTransversePierDescription::FinalConstruct()
{
   CComObject<CCrossBeam>* pCrossBeam;
   CComObject<CCrossBeam>::CreateInstance(&pCrossBeam);
   m_CrossBeam = pCrossBeam;
   AdviseChild(m_CrossBeam,IID_ICrossBeamEvents,&m_dwCrossBeamCookie);

   CComObject<CColumnSpacing>* pColumnSpacing;
   CComObject<CColumnSpacing>::CreateInstance(&pColumnSpacing);
   m_ColumnSpacing = pColumnSpacing;
   AdviseChild(m_ColumnSpacing,IID_IColumnSpacingEvents,&m_dwColumnSpacingCookie);

   pCrossBeam->SetColumnSpacing(pColumnSpacing);

   AdviseColumns();

   return S_OK;
}

void CTransversePierDescription::FinalRelease()
{
   UnadviseColumns();
   UnadviseChild(m_CrossBeam,IID_ICrossBeamEvents,m_dwCrossBeamCookie);
   UnadviseChild(m_ColumnSpacing,IID_IColumnSpacingEvents,m_dwColumnSpacingCookie);

   m_CrossBeam.Release();
   m_ColumnSpacing.Release();
}

STDMETHODIMP CTransversePierDescription::Clone(ITransversePierDescription* *clone)
{
   CComObject<CTransversePierDescription>* pClone;
   CComObject<CTransversePierDescription>::CreateInstance(&pClone);
   (*clone) = pClone;
   (*clone)->AddRef();

   CComPtr<IColumnSpacing> cloneColumnSpacing;
   dynamic_cast<CColumnSpacing*>(m_ColumnSpacing.p)->Clone(&cloneColumnSpacing);

   CComPtr<ICrossBeam> cloneCrossBeam;
   dynamic_cast<CCrossBeam*>(m_CrossBeam.p)->Clone(&cloneCrossBeam);

   dynamic_cast<CCrossBeam*>(cloneCrossBeam.p)->SetColumnSpacing(dynamic_cast<CColumnSpacing*>(cloneColumnSpacing.p));

   pClone->SetItems(cloneColumnSpacing,cloneCrossBeam);

   return S_OK;
}

void CTransversePierDescription::SetItems(IColumnSpacing* pSpacing,ICrossBeam* pCrossBeam)
{
   UnadviseColumns();
   UnadviseChild(m_CrossBeam,IID_ICrossBeamEvents,m_dwCrossBeamCookie);
   UnadviseChild(m_ColumnSpacing,IID_IColumnSpacingEvents,m_dwColumnSpacingCookie);

   m_CrossBeam.Release();
   m_ColumnSpacing.Release();

   m_CrossBeam     = pCrossBeam;
   m_ColumnSpacing = pSpacing;

   AdviseColumns();
   AdviseChild(m_CrossBeam,IID_ICrossBeamEvents,&m_dwCrossBeamCookie);
   AdviseChild(m_ColumnSpacing,IID_IColumnSpacingEvents,&m_dwColumnSpacingCookie);
}

void CTransversePierDescription::SetBridge(IGenericBridge* pBridge)
{
   m_pBridge = pBridge;

   dynamic_cast<CColumnSpacing*>(m_ColumnSpacing.p)->SetBridge(pBridge);
   dynamic_cast<CCrossBeam*>(m_CrossBeam.p)->SetBridge(pBridge);
}

STDMETHODIMP CTransversePierDescription::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITransversePierDescription,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CTransversePierDescription::AdviseChild(IUnknown* punk,REFIID riid,DWORD* pdwCookie)
{
   HRESULT hr;
   CComQIPtr<IConnectionPointContainer> pCPC(punk);
   CComPtr<IConnectionPoint> pCP;
   hr = pCPC->FindConnectionPoint(riid,&pCP);
   ATLASSERT(SUCCEEDED(hr));

   hr = pCP->Advise(GetUnknown(),pdwCookie);
   ATLASSERT(SUCCEEDED(hr));

   InternalRelease(); // Break circual reference
   return S_OK;
}

HRESULT CTransversePierDescription::UnadviseChild(IUnknown* punk,REFIID riid,DWORD dwCookie)
{
   InternalAddRef(); // Counter act call to InternalRelease in AdviseChild
   CComQIPtr<IConnectionPointContainer> pCPC(punk);
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint(riid,&pCP);

   pCP->Unadvise(dwCookie);

   return S_OK;
}

void CTransversePierDescription::AdviseColumns()
{
   ColumnIndexType nColumns;
   m_ColumnSpacing->get_ColumnCount(&nColumns);
   for ( ColumnIndexType i = 0; i < nColumns; i++ )
   {
      CComPtr<IColumn> column;
      get_Column(i,&column);

      DWORD dwCookie;
      AdviseChild(column,IID_IColumnEvents,&dwCookie);

      m_ColumnCookies.push_back(std::make_pair(dwCookie,column));
   }
}

void CTransversePierDescription::UnadviseColumns()
{
   std::vector<std::pair<DWORD,CComPtr<IColumn> > >::iterator iter;
   for ( iter = m_ColumnCookies.begin(); iter != m_ColumnCookies.end(); iter++ )
   {
      std::pair<DWORD,CComPtr<IColumn> >& item = *iter;
      UnadviseChild(item.second,IID_IColumnEvents,item.first);
   }

   m_ColumnCookies.clear();
}

/////////////////////////////////////////////////////////////////////////////
// ITransversePierDescription
STDMETHODIMP CTransversePierDescription::get_CrossBeam(ICrossBeam* *crossBeam)
{
   CHECK_RETOBJ(crossBeam);
   (*crossBeam) = m_CrossBeam;
   (*crossBeam)->AddRef();
   return S_OK;
}

STDMETHODIMP CTransversePierDescription::get_ColumnSpacing(IColumnSpacing* *columnSpacing)
{
   CHECK_RETOBJ(columnSpacing);
   (*columnSpacing) = m_ColumnSpacing;
   (*columnSpacing)->AddRef();
   return S_OK;
}

STDMETHODIMP CTransversePierDescription::get_Column(ColumnIndexType columnIdx,IColumn* *column)
{
   return m_ColumnSpacing->get_Column(columnIdx,column);
}

STDMETHODIMP CTransversePierDescription::get_Pier(/*[out,retval]*/IPier* *pier)
{
   CHECK_RETOBJ(pier);
   (*pier) = m_pPier;
   (*pier)->AddRef();
   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CTransversePierDescription::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);
   load->BeginUnit(CComBSTR("TransversePierDescription"));

   CComQIPtr<IStructuredStorage2> ssCrossBeam(m_CrossBeam);
   ssCrossBeam->Load(load);

   CComQIPtr<IStructuredStorage2> ssColumnSpacing(m_ColumnSpacing);
   ssColumnSpacing->Load(load);

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CTransversePierDescription::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("TransversePierDescription"),1.0);

   CComQIPtr<IStructuredStorage2> ssCrossBeam(m_CrossBeam);
   ssCrossBeam->Save(save);

   CComQIPtr<IStructuredStorage2> ssColumnSpacing(m_ColumnSpacing);
   ssColumnSpacing->Save(save);

   save->EndUnit();

   return S_OK;
}

