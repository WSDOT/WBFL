///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2019  Washington State Department of Transportation
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
#include "SuperstructureMemberSegmentImpl.h"
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
   m_HaunchDepth[0] = 0;
   m_HaunchDepth[1] = 0;
   m_HaunchDepth[2] = 0;
   m_HaunchMode = hmPrismatic;

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
// STDMETHODIMP CSuperstructureMemberSegmentImpl::get_PrimaryShape(Float64 distAlongSegment, SectionCoordinateSystemType coordinateSystem, IShape** ppShape)
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

STDMETHODIMP CSuperstructureMemberSegmentImpl::GetHaunchDepth(Float64* pStartVal, Float64* pMidVal, Float64* pEndVal)
{
   CHECK_RETVAL(pStartVal);
   CHECK_RETVAL(pMidVal);
   CHECK_RETVAL(pEndVal);
   *pStartVal = m_HaunchDepth[0];
   *pMidVal = m_HaunchDepth[1];
   *pEndVal = m_HaunchDepth[2];
   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::SetHaunchDepth(Float64 startVal, Float64 midVal, Float64 endVal)
{
   m_HaunchDepth[0] = startVal;
   m_HaunchDepth[1] = midVal;
   m_HaunchDepth[2] = endVal;

   // determine how we are going to compute haunch depth
   if (startVal == midVal && midVal == endVal)
   {
      m_HaunchMode = hmPrismatic;
   }
   else if (IsEqual(midVal, (startVal+endVal)/2.0))
   {
      m_HaunchMode = hmLinear;
   }
   else
   {
      m_HaunchMode = hmParabolic;
   }

   return S_OK;
}

STDMETHODIMP CSuperstructureMemberSegmentImpl::ComputeHaunchDepth(Float64 distAlongSegment, Float64* pVal)
{
   CHECK_RETVAL(pVal);
   if (m_HaunchMode == hmPrismatic)
   {
      *pVal = m_HaunchDepth[0];
   }
   else
   {
      Float64 startHaunch(m_HaunchDepth[0]), midHaunch(m_HaunchDepth[1]), endHaunch(m_HaunchDepth[2]);

      Float64 segment_length;
      get_Length(&segment_length);

      // Shape can be linear or parabolic
      // Linear portion of haunch based on end values
      Float64 lin_haunch = ::LinInterp(distAlongSegment, startHaunch, endHaunch, segment_length);

      if (m_HaunchMode == hmLinear)
      {
         // Haunch is linear. just return
         *pVal = lin_haunch;
      }
      else
      {
         // haunch is parabolic. Compute height of bulge at location
         // Made an OPTIMIZATION here - this function is called many, many times.
         // Was using GenerateParabola() in MathUtils.h, but calls were costly. Refer to that derivation
         // for how we got here.
         Float64 mid_bulge = midHaunch - (startHaunch + endHaunch) / 2.0;
         Float64 Vx = (segment_length) / 2.0;   // X ordinate of peak
                                                // y = Ax^2 + Bx + C
         Float64 A = -mid_bulge / (Vx*Vx);
         Float64 B = 2 * mid_bulge / Vx;
         // Float64 C = 0.0;

         Float64 para_haunch = A*distAlongSegment*distAlongSegment + B*distAlongSegment;

         Float64 haunch = lin_haunch + para_haunch; // haunch is sum of linear part and parabolic sliver
         *pVal = haunch;
      }
   }

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
