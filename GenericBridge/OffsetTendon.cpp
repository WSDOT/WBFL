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

// OffsetTendon.cpp : Implementation of COffsetTendon
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "OffsetTendon.h"
#include <MathEx.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COffsetTendon
HRESULT COffsetTendon::FinalConstruct()
{
   m_OD = 0.0;
   m_ID = 0.0;
   m_ND = 0.0;
   m_StrandCount  = 0;
   m_JackingEnd   = jeLeft;

   m_pSSMbr = nullptr;
   m_pSSMbrSegment = nullptr;

   return S_OK;
}

void COffsetTendon::FinalRelease()
{
}

STDMETHODIMP COffsetTendon::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_IOffsetTendon,
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
// IOffsetTendon
STDMETHODIMP COffsetTendon::putref_RefTendon(ITendon* tendon)
{
   CHECK_IN(tendon);
   m_RefTendon = tendon;
   return S_OK;
}

STDMETHODIMP COffsetTendon::AddOffset(Float64 z,Float64 offsetX,Float64 offsetY)
{
   Point p;
   p.z = z;
   p.offsetX = offsetX;
   p.offsetY = offsetY;
   m_Points.push_back(p);

   std::sort(m_Points.begin(),m_Points.end());
   return S_OK;
}

/////////////////////////////////////////////////////
// ITendon
STDMETHODIMP COffsetTendon::AddSegment(ITendonSegment* segment)
{
   ATLASSERT(false); // offset tendon doesn't use segments
   return E_FAIL;
}

STDMETHODIMP COffsetTendon::get_Segment(IndexType index,ITendonSegment** segment)
{
   ATLASSERT(false); // offset tendon doesn't use segments
   return E_FAIL;
}

STDMETHODIMP COffsetTendon::get_Count(IndexType* count)
{
   CHECK_RETVAL(count);
   *count = 0;
   return S_OK;
}

STDMETHODIMP COffsetTendon::RemoveSegment(IndexType index)
{
   ATLASSERT(false); // offset tendon doesn't use segments
   return E_FAIL;
}

STDMETHODIMP COffsetTendon::ClearSegments()
{
   ATLASSERT(false); // offset tendon doesn't use segments
   return E_FAIL;
}

STDMETHODIMP COffsetTendon::get_OutsideDiameter(Float64* size)
{
   CHECK_RETVAL(size);
   *size = m_OD;
   return S_OK;
}

STDMETHODIMP COffsetTendon::put_OutsideDiameter(Float64 size)
{
   if ( size < 0 )
   {
      return E_INVALIDARG;
   }

   m_OD = size;
   return S_OK;
}

STDMETHODIMP COffsetTendon::get_OutsideDuctArea(Float64* Aduct)
{
   CHECK_RETVAL(Aduct);
   *Aduct = M_PI*m_OD*m_OD / 4;
   return S_OK;
}

STDMETHODIMP COffsetTendon::get_InsideDiameter(Float64* size)
{
   CHECK_RETVAL(size);
   *size = m_ID;
   return S_OK;
}

STDMETHODIMP COffsetTendon::put_InsideDiameter(Float64 size)
{
   if ( size < 0 )
   {
      return E_INVALIDARG;
   }

   m_ID = size;
   return S_OK;
}

STDMETHODIMP COffsetTendon::get_NominalDiameter(Float64* size)
{
   CHECK_RETVAL(size);
   *size = m_ND;
   return S_OK;
}

STDMETHODIMP COffsetTendon::put_NominalDiameter(Float64 size)
{
   if (size < 0)
   {
      return E_INVALIDARG;
   }

   m_ND = size;
   return S_OK;
}

STDMETHODIMP COffsetTendon::get_StrandCount(StrandIndexType* count)
{
   CHECK_RETVAL(count);
   *count = m_StrandCount;
   return S_OK;
}

STDMETHODIMP COffsetTendon::put_StrandCount(StrandIndexType count)
{
   if ( count < 0 )
   {
      return E_INVALIDARG;
   }

   m_StrandCount = count;
   return S_OK;
}

STDMETHODIMP COffsetTendon::get_Material(IPrestressingStrand** material)
{
   CHECK_RETOBJ(material);
   (*material) = m_Material;
   if ( m_Material )
   {
      (*material)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP COffsetTendon::putref_Material(IPrestressingStrand* psMaterial)
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

STDMETHODIMP COffsetTendon::get_MinimumRadiusOfCurvature(Float64* pMinRadiusOfCurvature)
{
   ATLASSERT(false); // this method isn't done yet
#pragma Reminder("FINISH: need to maximum radius of curvature for offset tendons")
   CHECK_RETVAL(pMinRadiusOfCurvature);
   *pMinRadiusOfCurvature = DBL_MAX;
   return S_OK;
}

STDMETHODIMP COffsetTendon::get_InsideDuctArea(Float64* Aduct)
{
   CHECK_RETVAL(Aduct);
   *Aduct = M_PI*m_ID*m_ID/4;
   return S_OK;
}

STDMETHODIMP COffsetTendon::get_NominalDuctArea(Float64* Aduct)
{
   CHECK_RETVAL(Aduct);
   *Aduct = M_PI*m_ND*m_ND / 4;
   return S_OK;
}

STDMETHODIMP COffsetTendon::get_TendonArea(Float64* Apt)
{
   CHECK_RETVAL(Apt);

   // area of one strand
   Float64 apt;
   m_Material->get_NominalArea(&apt);

   *Apt = m_StrandCount*apt;

   return S_OK;
}

STDMETHODIMP COffsetTendon::get_CG(Float64 z,TendonMeasure measure,IPoint3d** cg)
{
   HRESULT hr = m_RefTendon->get_CG(z,measure,cg);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 offsetX = GetOffsetX(z);
   Float64 offsetY = GetOffsetY(z);

   (*cg)->Offset(offsetX,offsetY,0);

   return S_OK;
}

STDMETHODIMP COffsetTendon::get_Slope(Float64 z,TendonMeasure measure,IVector3d** slope)
{
   HRESULT hr = m_RefTendon->get_Slope(z,measure,slope);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 slope_offset_x = GetOffsetSlopeX(z);
   Float64 slope_offset_y = GetOffsetSlopeY(z);

   Float64 x;
   (*slope)->get_X(&x);
   x += slope_offset_x;
   (*slope)->put_X(x);

   Float64 y;
   (*slope)->get_Y(&y);
   y += slope_offset_y;
   (*slope)->put_Y(y);

   (*slope)->Normalize();

   return S_OK;
}

STDMETHODIMP COffsetTendon::get_Length(Float64* length)
{
#pragma Reminder("UPDATE: need to account for length change due to un-even offsets")
   return m_RefTendon->get_Length(length);
}

STDMETHODIMP COffsetTendon::get_Start(IPoint3d** start)
{
   HRESULT hr = m_RefTendon->get_Start(start);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 z;
   (*start)->get_Z(&z);

   Float64 offsetX = GetOffsetX(z);
   Float64 offsetY = GetOffsetY(z);

   (*start)->Offset(offsetX,offsetY,0);

   return S_OK;
}

STDMETHODIMP COffsetTendon::get_End(IPoint3d** end)
{
   HRESULT hr = m_RefTendon->get_End(end);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 z;
   (*end)->get_Z(&z);

   Float64 offsetX = GetOffsetX(z);
   Float64 offsetY = GetOffsetY(z);

   (*end)->Offset(offsetX,offsetY,0);

   return S_OK;
}

STDMETHODIMP COffsetTendon::get_Centerline(TendonMeasure measure,IPoint3dCollection** ppPoints)
{
   ATLASSERT(false);
   return E_NOTIMPL;

   HRESULT hr = m_RefTendon->get_Centerline(measure,ppPoints);
   if ( FAILED(hr) )
   {
      return hr;
   }

   CComPtr<IPoint3d> point;
   CComPtr<IEnumPoint3d> enumPoints;
   (*ppPoints)->get__Enum(&enumPoints);
   while ( enumPoints->Next(0,&point,nullptr) != S_FALSE )
   {
      Float64 z;
      point->get_Z(&z);

      Float64 offsetX = GetOffsetX(z);
      Float64 offsetY = GetOffsetY(z);

      point->Offset(offsetX,offsetY,0);
   }

   return S_OK;
}

STDMETHODIMP COffsetTendon::get_JackingEnd(JackingEndType* type)
{
   CHECK_RETVAL(type);
   *type = m_JackingEnd;
   return S_OK;
}

STDMETHODIMP COffsetTendon::put_JackingEnd(JackingEndType type)
{
   m_JackingEnd = type;
   return S_OK;
}

STDMETHODIMP COffsetTendon::putref_SuperstructureMember(ISuperstructureMember* pSSMbr)
{
   CHECK_IN(pSSMbr);
#if defined _DEBUG
   ATLASSERT(m_pSSMbrSegment == nullptr); // can't be attached to both a SSMbr and a SSMbrSegment
#endif
   m_pSSMbr = pSSMbr;
   return S_OK;
}

STDMETHODIMP COffsetTendon::get_SuperstructureMember(ISuperstructureMember** ppSSMbr)
{
   (*ppSSMbr) = m_pSSMbr;
   if ( *ppSSMbr )
   {
      (*ppSSMbr)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP COffsetTendon::putref_SuperstructureMemberSegment(ISuperstructureMemberSegment* pSSMbrSegment)
{
   CHECK_IN(pSSMbrSegment);
#if defined _DEBUG
   ATLASSERT(m_pSSMbr == nullptr); // can't be attached to both a SSMbr and a SSMbrSegment
#endif
   m_pSSMbrSegment = pSSMbrSegment;
   return S_OK;
}

STDMETHODIMP COffsetTendon::get_SuperstructureMemberSegment(ISuperstructureMemberSegment** ppSSMbrSegment)
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
STDMETHODIMP COffsetTendon::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("OffsetTendon"));


#pragma Reminder("IMPLEMENT: Load") // need to load other data

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP COffsetTendon::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("OffsetTendon"),1.0);

#pragma Reminder("IMPLEMENT: Save") // need to save other data


   save->EndUnit();

   return S_OK;
}

Float64 COffsetTendon::GetOffsetX(Float64 z)
{
   if ( m_Points.size() == 0 )
   {
      return 0;
   }

   if ( m_Points.size() == 1 )
   {
      return m_Points.front().offsetX;
   }

   std::vector<Point>::const_iterator iter1(m_Points.begin());
   std::vector<Point>::const_iterator iter2(iter1+1);
   std::vector<Point>::const_iterator iterEnd(m_Points.end());

   Float64 z1 = iter1->z;
   if ( z < z1 )
   {
      return iter1->offsetX;
   }

   for (; iter2 != iterEnd; iter1++, iter2++ )
   {
      Float64 z2 = z1 + iter2->z;
      if ( InRange(z1,z,z2) )
      {
         Float64 offset1 = iter1->offsetX;
         Float64 offset2 = iter2->offsetX;

         Float64 offset = ::LinInterp(z-z1,offset1,offset2,z2-z1);
         return offset;
      }

      z1 = z2;
   }

   return m_Points.back().offsetX;
}

Float64 COffsetTendon::GetOffsetY(Float64 z)
{
   if ( m_Points.size() == 0 )
   {
      return 0;
   }

   if ( m_Points.size() == 1 )
   {
      return m_Points.front().offsetY;
   }

   std::vector<Point>::const_iterator iter1(m_Points.begin());
   std::vector<Point>::const_iterator iter2(iter1+1);
   std::vector<Point>::const_iterator iterEnd(m_Points.end());

   Float64 z1 = iter1->z;
   if ( z < z1 )
   {
      return iter1->offsetY;
   }

   for (; iter2 != iterEnd; iter1++, iter2++ )
   {
      Float64 z2 = z1 + iter2->z;
      if ( InRange(z1,z,z2) )
      {
         Float64 offset1 = iter1->offsetY;
         Float64 offset2 = iter2->offsetY;

         Float64 offset = ::LinInterp(z-z1,offset1,offset2,z2-z1);
         return offset;
      }

      z1 = z2;
   }

   return m_Points.back().offsetY;
}

Float64 COffsetTendon::GetOffsetSlopeX(Float64 z)
{
   if ( m_Points.size() <= 1 )
   {
      return 0.0;
   }

   std::vector<Point>::const_iterator iter1(m_Points.begin());
   std::vector<Point>::const_iterator iter2(iter1+1);
   std::vector<Point>::const_iterator iterEnd(m_Points.end());

   Float64 z1 = iter1->z;
   if ( z < z1 )
   {
      return 0.0; // before the first offset point
   }

   for (; iter2 != iterEnd; iter1++, iter2++ )
   {
      Float64 z2 = z1 + iter2->z;
      if ( InRange(z1,z,z2) )
      {
         // between offset points
         Float64 offset1 = iter1->offsetX;
         Float64 offset2 = iter2->offsetX;

         // compute slope of offset line
         Float64 slope = (offset2 - offset1)/(z2-z1);
         return slope;
      }

      z1 = z2;
   }

   // after last offset point
   return 0.0;
}

Float64 COffsetTendon::GetOffsetSlopeY(Float64 z)
{
   if ( m_Points.size() <= 1 )
   {
      return 0.0;
   }

   std::vector<Point>::const_iterator iter1(m_Points.begin());
   std::vector<Point>::const_iterator iter2(iter1+1);
   std::vector<Point>::const_iterator iterEnd(m_Points.end());

   Float64 z1 = iter1->z;
   if ( z < z1 )
   {
      return 0.0; // before the first offset point
   }

   for (; iter2 != iterEnd; iter1++, iter2++ )
   {
      Float64 z2 = z1 + iter2->z;
      if ( InRange(z1,z,z2) )
      {
         // between offset points
         Float64 offset1 = iter1->offsetY;
         Float64 offset2 = iter2->offsetY;

         // compute slope of offset line
         Float64 slope = (offset2 - offset1)/(z2-z1);
         return slope;
      }

      z1 = z2;
   }

   // after last offset point
   return 0.0;
}
