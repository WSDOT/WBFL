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

// Segment.cpp : Implementation of CSegment
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "Segment.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSegment
HRESULT CSegment::FinalConstruct()
{
   m_Length = 1.0;

   return S_OK;
}

void CSegment::FinalRelease()
{
   m_Shape.Release();

   if ( m_Material )
   {
      InternalAddRef();

      AtlUnadvise(m_Material,IID_IMaterialEvents,m_dwMaterialCookie);
   }
   m_Material.Release();
}

STDMETHODIMP CSegment::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISegment,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

////////////////////////////////////////////////////////////////////////
// ISegment implementation
STDMETHODIMP CSegment::putref_SegmentMeasure(ISegmentMeasure* sm)
{
   m_pSegmentMeasure = sm;

#if defined _DEBUG
   // m_pSegmentMeasure is a weak references. This is so because
   // I expect the object implementing sm to also be a superstructure member
   // Assert this is true.
   if ( sm != NULL )
   {
      CComQIPtr<ISuperstructureMember> ssmbr(sm);
      CComQIPtr<ILongitudinalPierDescription> lpd(sm);
      CComQIPtr<ICrossBeam> cb(sm);
      CComQIPtr<IColumn> col(sm);
      ATLASSERT(ssmbr != NULL || lpd != NULL || cb != NULL || col != NULL);
   }
#endif // _DEBUG

   return S_OK;
}

STDMETHODIMP CSegment::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   (*pVal) = m_Length;
	return S_OK;
}

STDMETHODIMP CSegment::put_Length(Float64 length)
{
   if ( IsEqual(m_Length,length) )
      return S_OK;

   // Validate length
   if ( m_pSegmentMeasure )
   {
      bool bFractional = m_pSegmentMeasure->IsFractional() == S_OK ? true : false;
      if ( bFractional )
      {
         if ( length > 0 )
            return Error(IDS_E_FRACTIONAL_EXPECTED,IID_ISegment,GB_E_FRACTIONAL_EXPECTED);
      }
      else
      {
         if ( length < 0 )
            return Error(IDS_E_ABSOLUTE_EXPECTED,IID_ISegment,GB_E_ABSOLUTE_EXPECTED);
      }
   }

   m_Length = length;
   Fire_OnSegmentChanged(this);
   return S_OK;
}

STDMETHODIMP CSegment::get_SegmentLength(/*[out, retval]*/ Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   Float64 segLength;
   if ( m_Length < 0 )
   {
      // segment length is a fraction of the superstructure member length
      Float64 ssmbrLength = GetSuperstructureMemberLength();
      segLength = -1*m_Length*ssmbrLength;
   }
   else
   {
      // segment lenght is an absolute value
      *pVal = m_Length;
   }
   return S_OK;
}

STDMETHODIMP CSegment::get_Shape(Float64 distAlongSegment,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   // This object reprsents a prismatic shape... all sections are the same
   HRESULT hr = S_OK;
   if ( m_Shape )
   {
      hr = m_Shape->Clone(ppShape);
   }
   else
   {
      (*ppShape) = 0;
   }

   return hr;
}

STDMETHODIMP CSegment::putref_Shape(IShape* pShape)
{
   CHECK_IN(pShape);

#if defined _DEBUG
   CComQIPtr<IGirderSection> gdrSection(pShape);
   ATLASSERT(gdrSection != NULL); // shape must be a girder section
#endif

   if ( m_Shape.IsEqualObject(pShape) )
      return S_OK;

   m_Shape = pShape;
   Fire_OnSegmentChanged(this);
   return S_OK;
}

STDMETHODIMP CSegment::putref_Material(IMaterial* material)
{
   CHECK_IN(material);

   if ( m_Material.IsEqualObject(material) )
      return S_OK;

   CComPtr<IUnknown> punk;
   QueryInterface(IID_IUnknown,(void**)&punk);

   HRESULT hr;
   DWORD dwCookie;
   if ( material )
   {
      hr = AtlAdvise(material,punk,IID_IMaterialEvents,&dwCookie);
      if ( FAILED(hr) )
         return hr; // can't sink on material... get outta here before anything gets changed

      InternalRelease(); // break circular reference
   }

   // unsink on the older material (if there was one)
   if ( m_Material )
   {
      InternalAddRef();

      hr = AtlUnadvise(m_Material,IID_IMaterialEvents,m_dwMaterialCookie);
      ATLASSERT(SUCCEEDED(hr));
   }

   m_Material = material;

   if ( m_Material )
   {
      m_dwMaterialCookie = dwCookie;
   }

   Fire_OnSegmentChanged(this);
   return S_OK;
}

STDMETHODIMP CSegment::get_Material(IMaterial* *material)
{
   CHECK_RETVAL(material);

   (*material) = m_Material;

   if ( *material )
      (*material)->AddRef();

   return S_OK;
}

STDMETHODIMP CSegment::put_Orientation(Float64 orientation)
{
   if ( IsEqual(m_Orientation,orientation) )
      return S_OK;

   m_Orientation = orientation;
   Fire_OnSegmentChanged(this);
   return S_OK;
}

STDMETHODIMP CSegment::get_Orientation(Float64* orientation)
{
   CHECK_RETVAL(orientation);
   (*orientation) = m_Orientation;
   return S_OK;
}

STDMETHODIMP CSegment::Clone(ISegment* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CSegment>* pClone;
   CComObject<CSegment>::CreateInstance(&pClone);
   (*clone) = pClone;
   (*clone)->AddRef();

   pClone->m_Length = m_Length;
   pClone->m_pSegmentMeasure = m_pSegmentMeasure;
   pClone->m_Orientation = m_Orientation;

   if ( m_Shape )
      m_Shape->Clone(&pClone->m_Shape);

   CComPtr<IMaterial> material;
   if ( m_Material )
      m_Material->Clone(&material);

   pClone->putref_Material(material);

   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CSegment::Load(IStructuredLoad2* load)
{
   CComVariant var;
   load->BeginUnit(CComBSTR("Segment"));

   load->get_Property(CComBSTR("Length"),&var);
   m_Length = var.dblVal;

   m_Shape.Release();
   load->get_Property(CComBSTR("Shape"),&var);
   if ( var.vt == VT_UNKNOWN )
      var.punkVal->QueryInterface(&m_Shape);

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP CSegment::Save(IStructuredSave2* save)
{
   save->BeginUnit(CComBSTR("Segment"),1.0);

   save->put_Property(CComBSTR("Length"),CComVariant(m_Length));
   if ( m_Shape )
      save->put_Property(CComBSTR("Shape"),CComVariant(m_Shape));
   else
      save->put_Property(CComBSTR("Shape"),CComVariant(0));

   save->EndUnit();
   return S_OK;
}

Float64 CSegment::GetSuperstructureMemberLength()
{
   Float64 length;
   CComQIPtr<ISuperstructureMember> ssmbr(m_pSegmentMeasure);
   ATLASSERT(ssmbr);

   ssmbr->get_Length(&length);
   ATLASSERT( 0 <= length );
   return length;
}