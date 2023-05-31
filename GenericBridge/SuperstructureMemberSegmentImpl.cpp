///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include "stdafx.h"
#include <GenericBridge\SuperstructureMemberSegmentImpl.h>
#include <GenericBridge\Helpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSuperstructureMemberSegmentImpl::CSuperstructureMemberSegmentImpl()
{
   m_pSSMbr = nullptr;
   m_pPrevSegment = nullptr;
   m_pNextSegment = nullptr;
   m_pGirderLine = nullptr;
   m_Orientation = 0;

   m_Fillet = 0;
   m_FilletShape = flsSquared;
   m_Precamber = 0;
}

////////////////////////////////////////////////////////////////////////
// ISuperstructureMemberSegment implementation
STDMETHODIMP CSuperstructureMemberSegmentImpl::putref_SuperstructureMember(ISuperstructureMember* ssMbr)
{
   CHECK_IN(ssMbr);
   m_pSSMbr = ssMbr;
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::get_SuperstructureMember(ISuperstructureMember** ssMbr)
{
   CHECK_RETOBJ(ssMbr);
   if (m_pSSMbr)
   {
      (*ssMbr) = m_pSSMbr;
      (*ssMbr)->AddRef();
   }
   else
   {
      (*ssMbr) = nullptr;
   }

   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::putref_GirderLine(IGirderLine* girderLine)
{
   m_pGirderLine = girderLine;
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::get_GirderLine(IGirderLine** girderLine)
{
   CHECK_RETOBJ(girderLine);
   if (m_pGirderLine)
   {
      (*girderLine) = m_pGirderLine;
      (*girderLine)->AddRef();
   }
   else
   {
      (*girderLine) = nullptr;
   }

   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::putref_PrevSegment(ISegment* segment)
{
   CHECK_IN(segment);
   ISuperstructureMemberSegment* pMySeg = m_pPrevSegment; // weak references so no change in ref count
   m_pPrevSegment = nullptr;
   HRESULT hr = segment->QueryInterface(&m_pPrevSegment); // causes ref count to increment
   if (FAILED(hr))
   {
      m_pPrevSegment = pMySeg;
      return hr;
   }
   m_pPrevSegment->Release(); // need to decrement ref count causd by QueryInterface to maintain this as a weak reference
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::get_PrevSegment(ISegment** segment)
{
   CHECK_RETVAL(segment);
   if (m_pPrevSegment)
   {
      return m_pPrevSegment->QueryInterface(segment);
   }
   else
   {
      *segment = nullptr;
      return E_FAIL;
   }
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::putref_NextSegment(ISegment* segment)
{
   CHECK_IN(segment);
   ISuperstructureMemberSegment* pMySeg = m_pNextSegment; // weak references so no change in ref count
   m_pNextSegment = nullptr;
   HRESULT hr = segment->QueryInterface(&m_pNextSegment); // causes ref count to increment
   if (FAILED(hr))
   {
      m_pNextSegment = pMySeg;
      return hr;
   }
   m_pNextSegment->Release(); // need to decrement ref count causd by QueryInterface to maintain this as a weak reference
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::get_NextSegment(ISegment** segment)
{
   CHECK_RETVAL(segment);
   if (m_pNextSegment)
   {
      return m_pNextSegment->QueryInterface(segment);
   }
   else
   {
      *segment = nullptr;
      return E_FAIL;
   }
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::get_Length(Float64 *pVal)
{
   return m_pGirderLine->get_GirderLength(pVal);
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::get_LayoutLength(Float64 *pVal)
{
   return m_pGirderLine->get_LayoutLength(pVal);
}

// Not implemented
// STDMETHODIMP CSuperstructureMemberSegmentImpl::get_Section(StageIndexType stageIdx, Float64 distAlongSegment, ISection** ppSection)
// STDMETHODIMP CSuperstructureMemberSegmentImpl::get_GirderShape(Float64 distAlongSegment, SectionCoordinateSystemType coordinateSystem, IShape** ppShape)
//STDMETHODIMP CSuperstructureMemberSegmentImpl::get_Profile(VARIANT_BOOL bIncludeClosure, IShape** ppShape)

STDMETHODIMP CSuperstructureMemberSegmentImpl::put_Orientation(Float64 orientation)
{
   m_Orientation = orientation;
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::get_Orientation(Float64* orientation)
{
   CHECK_RETVAL(orientation);
   (*orientation) = m_Orientation;
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::GetHaunchDepth(IDblArray** pVal)
{
   CHECK_RETOBJ(pVal);
   CComPtr<IDblArray> vals;
   vals.CoCreateInstance(CLSID_DblArray);
   for (auto val : m_vHaunchDepths)
   {
      vals->Add(val);
   }

   return vals.CopyTo(pVal);
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::SetHaunchDepth(IDblArray* haunchVals)
{
   m_vHaunchDepths.clear();

   CComPtr<IEnumDblArray> enum_dbls;
   HRESULT hr = haunchVals->get__EnumElements(&enum_dbls);
   Float64 dbl;
   while (enum_dbls->Next(1,&dbl,nullptr) != S_FALSE)
   {
      m_vHaunchDepths.push_back(dbl);
   }

   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::ComputeHaunchDepth(Float64 distAlongSegment, Float64* pVal)
{
   CHECK_RETVAL(pVal);

      Float64 segment_length;
      get_Length(&segment_length);

   *pVal = ::ComputeHaunchDepthAlongSegment(distAlongSegment, segment_length, m_vHaunchDepths);
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::put_Fillet(Float64 Fillet)
{
   m_Fillet = Fillet;
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::get_Fillet(Float64* Fillet)
{
   CHECK_RETVAL(Fillet);
   (*Fillet) = m_Fillet;
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::put_FilletShape(FilletShape filletShape)
{
   m_FilletShape = filletShape;
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::get_FilletShape(FilletShape* filletShape)
{
   CHECK_RETVAL(filletShape);
   (*filletShape) = m_FilletShape;
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::put_Precamber(Float64 precamber)
{
   m_Precamber = precamber;
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::get_Precamber(Float64* pPrecamber)
{
   CHECK_RETVAL(pPrecamber);
   *pPrecamber = m_Precamber;
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::ComputePrecamber(Float64 distAlongSegment, Float64* pPrecamber)
{
   Float64 Ls;
   get_Length(&Ls);

   Float64 x = distAlongSegment;
   *pPrecamber = ComputePrecamber(x, Ls);
   return S_OK;
}

Float64 CSuperstructureMemberSegmentImpl::ComputePrecamber(Float64 Xs, Float64 Ls)
{
   return ::ComputePrecamber(Xs, Ls, m_Precamber);
}
