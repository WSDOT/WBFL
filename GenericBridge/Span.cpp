///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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

// Span.cpp : Implementation of CSpan
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "Span.h"
#include "Pier.h"
#include "SuperstructureMember.h"
#include "TemporaryPierItemCollection.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpan
HRESULT CSpan::FinalConstruct()
{
   CComObject<CTemporaryPierItemCollection>* pTempPiers;
   CComObject<CTemporaryPierItemCollection>::CreateInstance(&pTempPiers);

   CComObject<CGirderSpacing>* pGirderSpacing;
   CComObject<CGirderSpacing>::CreateInstance(&pGirderSpacing);
   m_pGirderSpacing[etStart] = pGirderSpacing;
   m_GirderSpacing[etStart]  = pGirderSpacing;

   pGirderSpacing = 0;
   CComObject<CGirderSpacing>::CreateInstance(&pGirderSpacing);
   m_pGirderSpacing[etEnd] = pGirderSpacing;
   m_GirderSpacing[etEnd]  = pGirderSpacing;

   AdviseGirderSpacing();

   m_TemporaryPiers = pTempPiers;
   AdviseTemporaryPiers();

   return S_OK;
}

void CSpan::FinalRelease()
{
   UnadviseGirderSpacing();
   UnadviseTemporaryPiers();
   m_TemporaryPiers.Release();
}

STDMETHODIMP CSpan::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISpan,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


void CSpan::SetBridge(IGenericBridge* bridge)
{
   m_pBridge = bridge;
   CTemporaryPierItemCollection* pTempPiers = dynamic_cast<CTemporaryPierItemCollection*>(m_TemporaryPiers.p);
   pTempPiers->SetBridge(bridge);
   m_pGirderSpacing[etStart]->SetBridge(bridge);
   m_pGirderSpacing[etEnd]->SetBridge(bridge);
};

HRESULT CSpan::AdviseGirderSpacing()
{
   HRESULT hr;
   for ( int i = 0; i < 2; i++ )
   {
      hr = m_GirderSpacing[i].Advise(GetUnknown(),IID_IGirderSpacingEvents,&m_dwGirderSpacingCookie[i]);
      if ( FAILED(hr) )
      {
         ATLTRACE("Failed to establish connection point on GirderSpacing\n");
         ATLASSERT(false);
         return hr;
      }

      InternalRelease(); // Break circular reference
   }

   return hr;
}

HRESULT CSpan::UnadviseGirderSpacing()
{
   HRESULT hr;
   for ( int i = 0; i < 2; i++ )
   {
      InternalAddRef(); // conteract InternalRelease() in advise
      CComQIPtr<IConnectionPointContainer> pCPC(m_GirderSpacing[i]);
      CComPtr<IConnectionPoint> pCP;
      pCPC->FindConnectionPoint(IID_IGirderSpacingEvents,&pCP);

      hr = pCP->Unadvise(m_dwGirderSpacingCookie[i]);
      ATLASSERT( SUCCEEDED(hr) );
   }

   return hr;
}

HRESULT CSpan::AdviseTemporaryPiers()
{
   HRESULT hr = m_TemporaryPiers.Advise(GetUnknown(),IID_ITemporaryPierItemCollectionEvents,&m_dwCookie);
   if ( FAILED(hr) )
   {
      ATLTRACE("Failed to establish connection point on TemporaryPierCollection\n");
      return hr;
   }

   InternalRelease(); // Break circular reference

   return hr;
}

HRESULT CSpan::UnadviseTemporaryPiers()
{
   InternalAddRef(); // conteract InternalRelease() in advise
   CComQIPtr<IConnectionPointContainer> pCPC(m_TemporaryPiers);
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint(IID_ITemporaryPierItemCollectionEvents,&pCP);

   HRESULT hr = pCP->Unadvise(m_dwCookie);
   ATLASSERT( SUCCEEDED(hr) );

   return hr;
}

STDMETHODIMP CSpan::Clone(ISpan** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CSpan>* pClone;
   CComObject<CSpan>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   CComPtr<ITemporaryPierItemCollection> cloneTempPiers;
   CTemporaryPierItemCollection* pTempPiers = dynamic_cast<CTemporaryPierItemCollection*>(m_TemporaryPiers.p);
   pTempPiers->Clone(&cloneTempPiers);
   pClone->SetTemporaryPiers(cloneTempPiers);

   return S_OK;
}

void CSpan::SetTemporaryPiers(ITemporaryPierItemCollection* piers)
{
   UnadviseTemporaryPiers();
   m_TemporaryPiers = piers;
   AdviseTemporaryPiers();
}

void CSpan::SetLength(Float64 newVal)
{
   Float64 currLength;
   get_Length(&currLength);

   Float64 delta = newVal - currLength;

   // Move the "next pier" by delta... the rest of the piers will automatically move
   // Use the private SetStationValueEx method on pier so that addition events and 
   // transactions are not generated
   CPier* pNextPier = GetNextPier();
   CComPtr<IStation> objStation;
   pNextPier->get_Station(&objStation);
   Float64 station;
   objStation->get_Value(&station);
   station += delta;

   pNextPier->SetStationValueEx(station);
}

STDMETHODIMP CSpan::get_GirderLineLength(GirderIndexType gdrIdx,Float64* length)
{
   // Validate input
   CHECK_RETVAL(length);

   CComPtr<ICogoInfo> cogoInfo;
   m_pBridge->get_CogoInfo(&cogoInfo);

   CComPtr<ICogoModel> cogoModel;
   m_pBridge->get_CogoModel(&cogoModel);

   CogoElementKey gdrLineID;
   ::GB_GetGirderLineId(m_Index,gdrIdx,&gdrLineID);

   CComPtr<ILineSegmentCollection> lineSegments;
   cogoModel->get_LineSegments(&lineSegments);

   CComPtr<ILineSegment2d> ls;
   lineSegments->get_Item(gdrLineID,&ls);
   
   ATLASSERT(ls);

   return ls->get_Length(length);
}

STDMETHODIMP CSpan::get_Length(Float64* length)
{
   CHECK_RETVAL(length);

   CComPtr<IStation> objPrevStation;
   CComPtr<IStation> objNextStation;
   Float64 prevSta, nextSta;

   m_pPrevPier->get_Station(&objPrevStation);
   m_pNextPier->get_Station(&objNextStation);

   objPrevStation->get_Value(&prevSta);
   objNextStation->get_Value(&nextSta);

   *length = nextSta - prevSta;

   return S_OK;
}

STDMETHODIMP CSpan::put_Length(Float64 length)
{
   if ( length <= 0.0 )
      return E_INVALIDARG;

   Float64 curLength;
   get_Length(&curLength);
   if ( IsEqual(curLength,length) )
      return S_OK;  // Not actually a change... do nothing

   SetLength(length);
   Fire_OnSpanChanged(this);
   return S_OK;
}

STDMETHODIMP CSpan::get_TemporaryPiers(ITemporaryPierItemCollection* *tempPiers)
{
   CHECK_RETOBJ(tempPiers);
   (*tempPiers) = m_TemporaryPiers;
   (*tempPiers)->AddRef();
   return S_OK;
}

STDMETHODIMP CSpan::put_GirderCount(GirderIndexType nGirders)
{
   if ( nGirders < (GirderIndexType)m_SuperstructureMembers.size() )
      return RemoveGirders( m_SuperstructureMembers.size() - nGirders );
   else
      return AddGirders( nGirders - m_SuperstructureMembers.size() );
}

STDMETHODIMP CSpan::get_GirderCount(GirderIndexType* nGirders)
{
   CHECK_RETVAL(nGirders);
   *nGirders = m_SuperstructureMembers.size();
   return S_OK;
}

STDMETHODIMP CSpan::AddGirders(GirderIndexType nGirders)
{
   if ( m_SuperstructureMembers.size() == 0 )
   {
      for ( GirderIndexType i = 0; i < nGirders; i++ )
      {
         CComObject<CSuperstructureMember>* pSSM;
         CComObject<CSuperstructureMember>::CreateInstance(&pSSM);

         CComPtr<ISuperstructureMember> ssm = pSSM;

         m_SuperstructureMembers.push_back(ssm);
      }
   }
   else
   {
      CComPtr<ISuperstructureMember> ssm = m_SuperstructureMembers.back();
      for ( GirderIndexType i = 0; i < nGirders; i++ )
      {
         CComPtr<ISuperstructureMember> clone;
         if ( ssm )
            ssm->Clone(&clone);

         m_SuperstructureMembers.push_back(clone);
      }
   }

   m_pGirderSpacing[etStart]->AddGirders(nGirders);
   m_pGirderSpacing[etEnd]->AddGirders(nGirders);

   Fire_OnSpanChanged(this);

   return S_OK;
}

STDMETHODIMP CSpan::RemoveGirders(GirderIndexType nGirders)
{
   std::vector<CComPtr<ISuperstructureMember> >::iterator last  = m_SuperstructureMembers.end();
   std::vector<CComPtr<ISuperstructureMember> >::iterator first = last - nGirders;

   m_SuperstructureMembers.erase(first,last);

   m_pGirderSpacing[etStart]->RemoveGirders(nGirders);
   m_pGirderSpacing[etEnd]->RemoveGirders(nGirders);

   Fire_OnSpanChanged(this);

   return S_OK;
}

STDMETHODIMP CSpan::get_SuperstructureMember(GirderIndexType gdrIdx,ISuperstructureMember** ppSSM)
{
   if ( gdrIdx < 0 || (GirderIndexType)m_SuperstructureMembers.size() <= gdrIdx )
      return E_INVALIDARG;

   CHECK_RETOBJ(ppSSM);

   (*ppSSM) = m_SuperstructureMembers[gdrIdx];
   (*ppSSM)->AddRef();

   return S_OK;
}

STDMETHODIMP CSpan::get_GirderSpacing(EndType endType,IGirderSpacing** ppGirderSpacing)
{
   CHECK_RETVAL(ppGirderSpacing);
   (*ppGirderSpacing) = m_GirderSpacing[endType];
   (*ppGirderSpacing)->AddRef();
   return S_OK;
}

STDMETHODIMP CSpan::get_PrevPier(IPier** ppPrevPier)
{
   CHECK_RETVAL(ppPrevPier);
   (*ppPrevPier) = m_pPrevPier;
   (*ppPrevPier)->AddRef();
   return S_OK;
}

STDMETHODIMP CSpan::get_NextPier(IPier** ppNextPier)
{
   CHECK_RETVAL(ppNextPier);
   (*ppNextPier) = m_pNextPier;
   (*ppNextPier)->AddRef();
   return S_OK;
}

STDMETHODIMP CSpan::get_Index(SpanIndexType* pIndex)
{
   CHECK_RETVAL(pIndex);
   *pIndex = m_Index;
   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CSpan::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);
   load->BeginUnit(CComBSTR("Span"));

   CComQIPtr<IStructuredStorage2> ssTempPiers(m_TemporaryPiers);
   ssTempPiers->Load(load);

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CSpan::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("Span"),1.0);

   CComQIPtr<IStructuredStorage2> ssTempPiers(m_TemporaryPiers);
   ssTempPiers->Save(save);

   save->EndUnit();

   return S_OK;
}
