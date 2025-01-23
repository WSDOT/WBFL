///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

// Tendon.cpp : Implementation of CTendon
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "Tendon.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTendon
HRESULT CTendon::FinalConstruct()
{
   m_ID = 0.0;
   m_OD = 0.0;
   m_ND = 0.0;

   m_StrandCount    = 0;

   m_JackingEnd = jeLeft;

   m_pSSMbr = nullptr;
   m_pSSMbrSegment = nullptr;

   return S_OK;
}

void CTendon::FinalRelease()
{
}

STDMETHODIMP CTendon::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITendon,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
      {
			return S_OK;
      }
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////
// ITendon
STDMETHODIMP CTendon::AddSegment(ITendonSegment* segment)
{
   segment->putref_Tendon(this);
   return PersistentTendonSegmentCollection::Add(segment);
}

STDMETHODIMP CTendon::get_Segment(IndexType index,ITendonSegment** segment)
{
   return PersistentTendonSegmentCollection::get_Item(index,segment);
}

STDMETHODIMP CTendon::get_Count(IndexType* count)
{
   return PersistentTendonSegmentCollection::get_Count(count);
}

STDMETHODIMP CTendon::RemoveSegment(IndexType index)
{
   return PersistentTendonSegmentCollection::Remove(index);
}

STDMETHODIMP CTendon::ClearSegments()
{
   return PersistentTendonSegmentCollection::Clear();
}

STDMETHODIMP CTendon::get_OutsideDiameter(Float64* size)
{
   CHECK_RETVAL(size);
   *size = m_OD;
   return S_OK;
}

STDMETHODIMP CTendon::put_OutsideDiameter(Float64 size)
{
   if ( size < 0 )
   {
      return E_INVALIDARG;
   }

   m_OD = size;
   return S_OK;
}

STDMETHODIMP CTendon::get_OutsideDuctArea(Float64* Aduct)
{
   CHECK_RETVAL(Aduct);

   *Aduct = M_PI*m_OD*m_OD / 4;

   return S_OK;
}

STDMETHODIMP CTendon::get_InsideDiameter(Float64* size)
{
   CHECK_RETVAL(size);
   *size = m_ID;
   return S_OK;
}

STDMETHODIMP CTendon::put_InsideDiameter(Float64 size)
{
   if ( size < 0 )
   {
      return E_INVALIDARG;
   }

   m_ID = size;
   return S_OK;
}

STDMETHODIMP CTendon::get_NominalDiameter(Float64* size)
{
   CHECK_RETVAL(size);
   *size = m_ND;
   return S_OK;
}

STDMETHODIMP CTendon::put_NominalDiameter(Float64 size)
{
   if (size < 0)
   {
      return E_INVALIDARG;
   }

   m_ND = size;
   return S_OK;
}

STDMETHODIMP CTendon::get_StrandCount(StrandIndexType* count)
{
   CHECK_RETVAL(count);
   *count = m_StrandCount;
   return S_OK;
}

STDMETHODIMP CTendon::put_StrandCount(StrandIndexType count)
{
   if ( count < 0 )
   {
      return E_INVALIDARG;
   }

   m_StrandCount = count;
   return S_OK;
}

STDMETHODIMP CTendon::get_Material(IPrestressingStrand** material)
{
   CHECK_RETOBJ(material);
   (*material) = m_Material;
   if ( m_Material )
   {
      (*material)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CTendon::putref_Material(IPrestressingStrand* psMaterial)
{
   CHECK_IN(psMaterial);
   CComQIPtr<IMaterial> material(psMaterial);
   if ( material == nullptr )
   {
      ATLASSERT(false); // psMaterial must implement IMaterial
      return E_INVALIDARG;
   }

   m_Material = psMaterial;
   return S_OK;
}

STDMETHODIMP CTendon::get_InsideDuctArea(Float64* Aduct)
{
   CHECK_RETVAL(Aduct);

   *Aduct = M_PI*m_ID*m_ID/4;

   return S_OK;
}

STDMETHODIMP CTendon::get_NominalDuctArea(Float64* Aduct)
{
   CHECK_RETVAL(Aduct);

   *Aduct = M_PI*m_ND*m_ND / 4;

   return S_OK;
}

STDMETHODIMP CTendon::get_TendonArea(Float64* Apt)
{
   CHECK_RETVAL(Apt);

   // area of one strand
   Float64 apt;
   m_Material->get_NominalArea(&apt);

   *Apt = m_StrandCount*apt;

   return S_OK;
}

STDMETHODIMP CTendon::get_MinimumRadiusOfCurvature(Float64* pMinRadiusOfCurvature)
{
   CHECK_RETVAL(pMinRadiusOfCurvature);

   iterator iter;
   Float64 start = 0;
   Float64 minRadiusOfCurvature = DBL_MAX;
   for ( iter = begin(); iter != end(); iter++ )
   {
      CComPtr<ITendonSegment> tendonSegment = iter->second;
      Float64 radiusOfCurvature;
      tendonSegment->get_MinimumRadiusOfCurvature(&radiusOfCurvature);
      minRadiusOfCurvature = Min(minRadiusOfCurvature,radiusOfCurvature);
   }

   *pMinRadiusOfCurvature = minRadiusOfCurvature;
   return S_OK;
}

STDMETHODIMP CTendon::get_CG(Float64 z,TendonMeasure measure,IPoint3d** cg)
{
   CHECK_RETOBJ(cg);

   CComPtr<ITendonSegment> segment;
   bool bSuccess = GetTendonSegment(z,&segment);
   if ( !bSuccess )
   {
      return E_FAIL;
   }

   segment->get_Position(measure,z,cg);

   return S_OK;
}

STDMETHODIMP CTendon::get_Slope(Float64 z,TendonMeasure measure,IVector3d** slope)
{
   CHECK_RETOBJ(slope);

   CComPtr<ITendonSegment> segment;
   bool bSuccess = GetTendonSegment(z,&segment);
   if ( !bSuccess )
   {
      return E_FAIL;
   }

   segment->get_Slope(z,slope);

   if ( measure == tmTendon )
   {
#pragma Reminder("Need to account for strand being off center from the cg")
   }

   return S_OK;
}

STDMETHODIMP CTendon::get_Length(Float64* length)
{
   CHECK_RETVAL(length);

   iterator iter;
   Float64 L = 0;
   for ( iter = begin(); iter != end(); iter++ )
   {
      CComPtr<ITendonSegment> seg = iter->second;
      Float64 l;
      seg->get_Length(&l);
      L += l;
   }

   *length = L;
   return S_OK;
}

STDMETHODIMP CTendon::get_Start(IPoint3d** start)
{
   ATLASSERT(m_coll.size() != 0);
   CComPtr<ITendonSegment> segment = m_coll.front().second.m_T;
   return segment->get_Start(start);
}

STDMETHODIMP CTendon::get_End(IPoint3d** end)
{
   ATLASSERT(m_coll.size() != 0);
   CComPtr<ITendonSegment> segment = m_coll.back().second.m_T;
   return segment->get_End(end);
}

STDMETHODIMP CTendon::get_Centerline(TendonMeasure measure,IPoint3dCollection** ppPoints)
{
   CComPtr<IPoint3dCollection> centerline;
   centerline.CoCreateInstance(CLSID_Point3dCollection);

   IndexType startIdx = 0; // the first time through, we want the start point of the first segment
   // all other times we want to start at point 1 because the end of one segment is the start of the next
   ContainerIteratorType iter(m_coll.begin());
   ContainerIteratorType end(m_coll.end());
   for ( ; iter != end; iter++ )
   {
      CComPtr<ITendonSegment> segment = (*iter).second.m_T;
      CComPtr<IPoint3dCollection> segmentCenterline;
      segment->get_Centerline(measure,&segmentCenterline);

      IndexType nPoints;
      segmentCenterline->get_Count(&nPoints);
      for ( IndexType idx = startIdx; idx < nPoints; idx++ )
      {
         CComPtr<IPoint3d> point;
         segmentCenterline->get_Item(idx,&point);
         centerline->Add(point);
      }

      startIdx = 1;
   }

   centerline.CopyTo(ppPoints);
   return S_OK;
}

STDMETHODIMP CTendon::get_JackingEnd(JackingEndType* type)
{
   CHECK_RETVAL(type);
   *type = m_JackingEnd;
   return S_OK;
}

STDMETHODIMP CTendon::put_JackingEnd(JackingEndType type)
{
   m_JackingEnd = type;
   return S_OK;
}

STDMETHODIMP CTendon::putref_SuperstructureMember(ISuperstructureMember* pSSMbr)
{
   CHECK_IN(pSSMbr);
#if defined _DEBUG
   ATLASSERT(m_pSSMbrSegment == nullptr); // can't be attached to both a SSMbr and a SSMbrSegment
#endif
   m_pSSMbr = pSSMbr;
   return S_OK;
}

STDMETHODIMP CTendon::get_SuperstructureMember(ISuperstructureMember** ppSSMbr)
{
   (*ppSSMbr) = m_pSSMbr;
   if ( *ppSSMbr )
   {
      (*ppSSMbr)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CTendon::putref_SuperstructureMemberSegment(ISuperstructureMemberSegment* pSSMbrSegment)
{
   CHECK_IN(pSSMbrSegment);
#if defined _DEBUG
   ATLASSERT(m_pSSMbr == nullptr); // can't be attached to both a SSMbr and a SSMbrSegment
#endif
   m_pSSMbrSegment = pSSMbrSegment;
   return S_OK;
}

STDMETHODIMP CTendon::get_SuperstructureMemberSegment(ISuperstructureMemberSegment** ppSSMbrSegment)
{
   CHECK_RETOBJ(ppSSMbrSegment);
   (*ppSSMbrSegment) = m_pSSMbrSegment;
   if (*ppSSMbrSegment)
   {
      (*ppSSMbrSegment)->AddRef();
   }

   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CTendon::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("Tendon"));

   PersistentTendonSegmentCollection::Load(load);


#pragma Reminder("IMPLEMENT: Load") // need to load other data

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CTendon::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("Tendon"),1.0);

   PersistentTendonSegmentCollection::Save(save);

#pragma Reminder("IMPLEMENT: Save") // need to save other data


   save->EndUnit();

   return S_OK;
}


bool CTendon::GetTendonSegment(Float64 z,ITendonSegment** segment)
{
   iterator begin_iter = begin();
   iterator end_iter = end();
   CComPtr<IPoint3d> pntStart;
   begin_iter->second->get_Start(&pntStart);
   Float64 start;
   pntStart->get_Z(&start);

   for ( auto iter = begin_iter; iter != end_iter; iter++ )
   {
      CComPtr<ITendonSegment> seg = iter->second;
      Float64 dx,dy,dz;
      seg->ProjectedLength(&dx,&dy,&dz);

      if ( InRange(start,z,start+dz) )
      {
         // found
         (*segment) = seg;
         (*segment)->AddRef();
         return true;
      }

      start += dz;
   }

   return false;
}

#if defined _DEBUG
// verify that the next segment starts where the previous segment ends
HRESULT CTendon::OnBeforeAdd( StoredType* pVal)
{
   if ( m_coll.size() == 0 )
   {
      return S_OK;
   }

   CComPtr<ITendonSegment> newSegment = pVal->second.m_T;
   CComPtr<ITendonSegment> lastSegment = m_coll.back().second.m_T;

   CComPtr<IPoint3d> pntStart,pntEnd;
   lastSegment->get_End(&pntEnd);
   newSegment->get_Start(&pntStart);

   ATLASSERT( pntStart->SameLocation(pntEnd) == S_OK );

   return S_OK;
}
#endif
