///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

// TaperedGirderSegment.cpp : Implementation of CTaperedGirderSegment
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "TaperedGirderSegment.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaperedGirderSegment
HRESULT CTaperedGirderSegment::FinalConstruct()
{
   m_Length = 1.0;

   return S_OK;
}

void CTaperedGirderSegment::FinalRelease()
{
   m_Beam[etStart].Release();
   m_Beam[etEnd].Release();

   if ( m_Material )
   {
      InternalAddRef();

      AtlUnadvise(m_Material,IID_IMaterialEvents,m_dwMaterialCookie);
   }
   m_Material.Release();
}

STDMETHODIMP CTaperedGirderSegment::InterfaceSupportsErrorInfo(REFIID riid)
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
STDMETHODIMP CTaperedGirderSegment::putref_SegmentMeasure(ISegmentMeasure* sm)
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

STDMETHODIMP CTaperedGirderSegment::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   (*pVal) = m_Length;
	return S_OK;
}

STDMETHODIMP CTaperedGirderSegment::put_Length(Float64 length)
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

STDMETHODIMP CTaperedGirderSegment::get_SegmentLength(/*[out, retval]*/ Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   if ( m_Length < 0 )
   {
      // segment length is a fraction of the superstructure member length
      Float64 ssmbrLength = GetSuperstructureMemberLength();
      *pVal = -1*m_Length*ssmbrLength;
   }
   else
   {
      // segment lenght is an absolute value
      *pVal = m_Length;
   }
   return S_OK;
}

STDMETHODIMP CTaperedGirderSegment::get_Shape(Float64 distAlongSegment,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   // This object reprsents a prismatic shape... all sections are the same
   HRESULT hr = S_OK;
   if ( m_Beam[etStart] == 0 || m_Beam[etEnd] == 0 )
   {
      (*ppShape) = 0;
      return hr;
   }

   Float64 segLength;
   get_SegmentLength(&segLength);

   // get dimensions of beam shape at start and end of segment
   CComPtr<IPrecastBeam> pcBeam[2];

   Float64 W1[2], W2[2], W3[2], W4[2];
   Float64 D1[2], D2[2], D3[2], D4[2], D5[2], D6[2], D7[2];
   Float64 T1[2], T2[2];
   Float64 C1[2];

   for ( int i = 0; i < 2; i++ )
   {
      m_Beam[i]->get_Beam(&pcBeam[i]);

      pcBeam[i]->get_W1(&W1[i]);
      pcBeam[i]->get_W2(&W2[i]);
      pcBeam[i]->get_W3(&W3[i]);
      pcBeam[i]->get_W4(&W4[i]);

      pcBeam[i]->get_D1(&D1[i]);
      pcBeam[i]->get_D2(&D2[i]);
      pcBeam[i]->get_D3(&D3[i]);
      pcBeam[i]->get_D4(&D4[i]);
      pcBeam[i]->get_D5(&D5[i]);
      pcBeam[i]->get_D6(&D6[i]);
      pcBeam[i]->get_D7(&D7[i]);

      pcBeam[i]->get_T1(&T1[i]);
      pcBeam[i]->get_T2(&T2[i]);

      pcBeam[i]->get_C1(&C1[i]);
   }

   // linear interpolate dimensions
   Float64 w1 = ::LinInterp(distAlongSegment,W1[etStart],W1[etEnd],segLength);
   Float64 w2 = ::LinInterp(distAlongSegment,W2[etStart],W2[etEnd],segLength);
   Float64 w3 = ::LinInterp(distAlongSegment,W3[etStart],W3[etEnd],segLength);
   Float64 w4 = ::LinInterp(distAlongSegment,W4[etStart],W4[etEnd],segLength);

   Float64 d1 = ::LinInterp(distAlongSegment,D1[etStart],D1[etEnd],segLength);
   Float64 d2 = ::LinInterp(distAlongSegment,D2[etStart],D2[etEnd],segLength);
   Float64 d3 = ::LinInterp(distAlongSegment,D3[etStart],D3[etEnd],segLength);
   Float64 d4 = ::LinInterp(distAlongSegment,D4[etStart],D4[etEnd],segLength);
   Float64 d5 = ::LinInterp(distAlongSegment,D5[etStart],D5[etEnd],segLength);
   Float64 d6 = ::LinInterp(distAlongSegment,D6[etStart],D6[etEnd],segLength);
   Float64 d7 = ::LinInterp(distAlongSegment,D7[etStart],D7[etEnd],segLength);

   Float64 t1 = ::LinInterp(distAlongSegment,T1[etStart],T1[etEnd],segLength);
   Float64 t2 = ::LinInterp(distAlongSegment,T2[etStart],T2[etEnd],segLength);

   Float64 c1 = ::LinInterp(distAlongSegment,C1[etStart],C1[etEnd],segLength);

   // create a new shape that is a clone of the original
   CComQIPtr<IShape> shape(m_Beam[etStart]);
   CComPtr<IShape> newShape;
   hr = shape->Clone(&newShape);

   // set the dimensions
   CComQIPtr<IFlangedGirderSection> newFlangedBeam(newShape);
   CComPtr<IPrecastBeam> newBeam;
   newFlangedBeam->get_Beam(&newBeam);
   newBeam->put_C1(c1);
   newBeam->put_D1(d1);
   newBeam->put_D2(d2);
   newBeam->put_D3(d3);
   newBeam->put_D4(d4);
   newBeam->put_D5(d5);
   newBeam->put_D6(d6);
   newBeam->put_D7(d7);
   newBeam->put_W1(w1);
   newBeam->put_W2(w2);
   newBeam->put_W3(w3);
   newBeam->put_W4(w4);
   newBeam->put_T1(t1);
   newBeam->put_T2(t2);

   newFlangedBeam.QueryInterface(ppShape);

   return hr;
}

STDMETHODIMP CTaperedGirderSegment::putref_Material(IMaterial* material)
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

STDMETHODIMP CTaperedGirderSegment::get_Material(IMaterial* *material)
{
   CHECK_RETVAL(material);

   (*material) = m_Material;

   if ( *material )
      (*material)->AddRef();

   return S_OK;
}

STDMETHODIMP CTaperedGirderSegment::put_Orientation(Float64 orientation)
{
   if ( IsEqual(m_Orientation,orientation) )
      return S_OK;

   m_Orientation = orientation;
   Fire_OnSegmentChanged(this);
   return S_OK;
}

STDMETHODIMP CTaperedGirderSegment::get_Orientation(Float64* orientation)
{
   CHECK_RETVAL(orientation);
   (*orientation) = m_Orientation;
   return S_OK;
}

STDMETHODIMP CTaperedGirderSegment::Clone(ISegment* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CTaperedGirderSegment>* pClone;
   CComObject<CTaperedGirderSegment>::CreateInstance(&pClone);
   (*clone) = pClone;
   (*clone)->AddRef();

   pClone->m_Length = m_Length;
   pClone->m_pSegmentMeasure = m_pSegmentMeasure;
   pClone->m_Orientation = m_Orientation;

   for ( int i = 0; i < 2; i++ )
   {
      if ( m_Beam[i] )
      {
         CComQIPtr<IShape> shape(m_Beam[i]);
         pClone->m_Beam[i].Release();

         CComPtr<IShape> cloneShape;
         shape->Clone(&cloneShape);

         cloneShape.QueryInterface(&pClone->m_Beam[i]);
      }
   }

   CComPtr<IMaterial> material;
   if ( m_Material )
      m_Material->Clone(&material);

   pClone->putref_Material(material);

   return S_OK;
}

////////////////////////////////////////////////////////////////////
// ITaperedGirderSegment implementation
STDMETHODIMP CTaperedGirderSegment::putref_FlangedGirderSection(EndType end,IFlangedGirderSection* pPrecastBeam)
{
   CHECK_IN(pPrecastBeam);

   if ( m_Beam[end].IsEqualObject(pPrecastBeam) )
      return S_OK;

   m_Beam[end] = pPrecastBeam;
   Fire_OnSegmentChanged(this);
   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CTaperedGirderSegment::Load(IStructuredLoad2* load)
{
   return E_NOTIMPL;
   //CComVariant var;
   //load->BeginUnit(CComBSTR("Segment"));

   //load->get_Property(CComBSTR("Length"),&var);
   //m_Length = var.dblVal;

   //m_Shape.Release();
   //load->get_Property(CComBSTR("Shape"),&var);
   //if ( var.vt == VT_UNKNOWN )
   //   var.punkVal->QueryInterface(&m_Shape);

   //VARIANT_BOOL bEnd;
   //load->EndUnit(&bEnd);
   //return S_OK;
}

STDMETHODIMP CTaperedGirderSegment::Save(IStructuredSave2* save)
{
   return E_NOTIMPL;
   //save->BeginUnit(CComBSTR("Segment"),1.0);

   //save->put_Property(CComBSTR("Length"),CComVariant(m_Length));
   //if ( m_Shape )
   //   save->put_Property(CComBSTR("Shape"),CComVariant(m_Shape));
   //else
   //   save->put_Property(CComBSTR("Shape"),CComVariant(0));

   //save->EndUnit();
   //return S_OK;
}

Float64 CTaperedGirderSegment::GetSuperstructureMemberLength()
{
   Float64 length;
   CComQIPtr<ISuperstructureMember> ssmbr(m_pSegmentMeasure);
   ATLASSERT(ssmbr);

   ssmbr->get_Length(&length);
   ATLASSERT( 0 <= length );
   return length;
}