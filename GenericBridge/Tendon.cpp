///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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
   m_TendonSize     = 0.0;
   m_StrandSize     = 0.0;
   m_StrandCount    = 0;
   m_MaxStrandCount = 0;

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
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////
// ITendon
STDMETHODIMP CTendon::AddSegment(ITendonSegment* segment)
{
   return PersistentTendonSegmentCollection::Add(segment);
}

STDMETHODIMP CTendon::get_Segment(CollectionIndexType index,ITendonSegment** segment)
{
   return PersistentTendonSegmentCollection::get_Item(index,segment);
}

STDMETHODIMP CTendon::get_Count(CollectionIndexType* count)
{
   return PersistentTendonSegmentCollection::get_Count(count);
}

STDMETHODIMP CTendon::RemoveSegment(CollectionIndexType index)
{
   return PersistentTendonSegmentCollection::Remove(index);
}

STDMETHODIMP CTendon::ClearSegments()
{
   return PersistentTendonSegmentCollection::Clear();
}

STDMETHODIMP CTendon::get_TendonSize(Float64* size)
{
   CHECK_RETVAL(size);
   *size = m_TendonSize;
   return S_OK;
}

STDMETHODIMP CTendon::put_TendonSize(Float64 size)
{
   if ( size < 0 )
      return E_INVALIDARG;

   m_TendonSize = size;
   return S_OK;
}

STDMETHODIMP CTendon::get_StrandSize(Float64* size)
{
   CHECK_RETVAL(size);
   *size = m_StrandSize;
   return S_OK;
}

STDMETHODIMP CTendon::put_StrandSize(Float64 size)
{
   if ( size < 0 )
      return E_INVALIDARG;

   m_StrandSize = size;
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
      return E_INVALIDARG;

   if ( m_MaxStrandCount < count )
      return E_FAIL;

   m_StrandCount = count;
   return S_OK;
}

STDMETHODIMP CTendon::get_Material(IPrestressingStrand** material)
{
   CHECK_RETOBJ(material);
   (*material) = m_Material;
   if ( m_Material )
      (*material)->AddRef();

   return S_OK;
}

STDMETHODIMP CTendon::putref_Material(IPrestressingStrand* material)
{
   CHECK_IN(material);
   m_Material = material;
   return S_OK;
}

STDMETHODIMP CTendon::get_MaxStrandCount(StrandIndexType* count)
{
   CHECK_RETVAL(count);
   *count = m_MaxStrandCount;
   return S_OK;
}

STDMETHODIMP CTendon::put_MaxStrandCount(StrandIndexType count)
{
   if ( count < 0 )
      return E_INVALIDARG;

   m_MaxStrandCount = count;
   return S_OK;
}

STDMETHODIMP CTendon::get_CG(Float64 x,TendonMeasure measure,IPoint3d** cg)
{
   CHECK_RETOBJ(cg);

   CComPtr<ITendonSegment> segment;
   bool bSuccess = GetTendonSegment(x,&segment);
   if ( !bSuccess )
      return E_FAIL;

   segment->get_Position(x,cg);

   if ( measure == tmTendon )
   {
#pragma Reminder("Need to account for strand being off center from the cg")
   }

   return S_OK;
}

STDMETHODIMP CTendon::get_Slope(Float64 x,TendonMeasure measure,IVector3d** slope)
{
   CHECK_RETOBJ(slope);

   CComPtr<ITendonSegment> segment;
   bool bSuccess = GetTendonSegment(x,&segment);
   if ( !bSuccess )
      return E_FAIL;

   segment->get_Slope(x,slope);

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


bool CTendon::GetTendonSegment(Float64 x,ITendonSegment** segment)
{
   iterator iter;
   Float64 start = 0;
   for ( iter = begin(); iter != end(); iter++ )
   {
      CComPtr<ITendonSegment> seg = iter->second;
      Float64 dx,dy,dz;
      seg->ProjectedLength(&dx,&dy,&dz);

      if ( InRange(start,x,start+dx) )
      {
         // found
         (*segment) = seg;
         (*segment)->AddRef();
         return true;
      }

      start += dx;
   }

   return false;
}
