///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// FlangedGirderEndBlockSegment.cpp : Implementation of CFlangedGirderEndBlockSegment
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "FlangedGirderEndBlockSegment.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlangedGirderEndBlockSegment
HRESULT CFlangedGirderEndBlockSegment::FinalConstruct()
{
   m_Length = 1.0;

   m_EndBlockLength[etStart]           = 0;
   m_EndBlockLength[etEnd]             = 0;
   m_EndBlockTransitionLength[etStart] = 0;
   m_EndBlockTransitionLength[etEnd]   = 0;
   m_EndBlockWidth[etStart]            = 0;
   m_EndBlockWidth[etEnd]              = 0;

   return S_OK;
}

void CFlangedGirderEndBlockSegment::FinalRelease()
{
   m_Beam.Release();

   if ( m_Material )
   {
      InternalAddRef();

      AtlUnadvise(m_Material,IID_IMaterialEvents,m_dwMaterialCookie);
   }
   m_Material.Release();
}

STDMETHODIMP CFlangedGirderEndBlockSegment::InterfaceSupportsErrorInfo(REFIID riid)
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
STDMETHODIMP CFlangedGirderEndBlockSegment::putref_SegmentMeasure(ISegmentMeasure* sm)
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

STDMETHODIMP CFlangedGirderEndBlockSegment::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   (*pVal) = m_Length;
	return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::put_Length(Float64 length)
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

STDMETHODIMP CFlangedGirderEndBlockSegment::get_SegmentLength(/*[out, retval]*/ Float64 *pVal)
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

STDMETHODIMP CFlangedGirderEndBlockSegment::get_Shape(Float64 distAlongSegment,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   // This object reprsents a prismatic shape... all sections are the same
   HRESULT hr = S_OK;
   if ( m_Beam )
   {
      CComPtr<IPrecastBeam> pcBeam;
      m_Beam->get_Beam(&pcBeam);

      Float64 Wt, Wb;
      GetEndBlockWidth(distAlongSegment,&Wt,&Wb);

      Float64 W1, W2, W3, W4;
      Float64 D1, D2, D3, D4, D5, D6, D7;
      Float64 T1, T2;
      Float64 C1;

      pcBeam->get_W1(&W1);
      pcBeam->get_W2(&W2);
      pcBeam->get_W3(&W3);
      pcBeam->get_W4(&W4);

      pcBeam->get_D1(&D1);
      pcBeam->get_D2(&D2);
      pcBeam->get_D3(&D3);
      pcBeam->get_D4(&D4);
      pcBeam->get_D5(&D5);
      pcBeam->get_D6(&D6);
      pcBeam->get_D7(&D7);

      pcBeam->get_T1(&T1);
      pcBeam->get_T2(&T2);

      pcBeam->get_C1(&C1);

      Float64 w1 = W1;
      Float64 w2 = W2;
      Float64 w3 = W3;
      Float64 w4 = W4;
      Float64 d1 = D1;
      Float64 d2 = D2;
      Float64 d3 = D3;
      Float64 d4 = D4;
      Float64 d5 = D5;
      Float64 d6 = D6;
      Float64 d7 = D7;
      Float64 t1 = T1;
      Float64 t2 = T2;
      Float64 c1 = C1;

      // adjust dimensions based on end block size

      // near top flange
      if ( 2*(W1+W2) + T1 < Wt )
      {
         // end block is wider than the top flange
         w1 = 0;
         w2 = 0;
         d1 = 0;
         d2 = 0;
         d3 = 0;
         d7 += D1 + D2 + D3;
         t1 = Wt;
      }
      else if ( W2 + T1/2 < Wt/2)
      {
         // end block extends beyond top fillet
         w2 = 0;
         w1 = W1 + W2 + T1/2 - Wt/2;
         w1 = (IsZero(w1) ? 0 : w1); // eliminate noise
         d2 = (D2/W1)*w1;
         d3 = D3 + (D2 - d2);
         t1 = Wt;
      }
      else if ( T1/2 < Wt/2)
      {
         // end block intersects top fillet
         w2 = W2 + T1/2 - Wt/2;
         d3 = (D3/W2)*w2;
         d7 += (D3 - d3);
         t1 = Wt;
      }

      // near bottom flange
      if ( 2*(W3+W4) + T2 < Wb )
      {
         // end block is wider than the bottom flange
         w3 = 0;
         w4 = 0;
         d4 = 0;
         d5 = 0;
         d6 = 0;
         d7 += D4 + D5 + D6;
         t2 = Wb;
      }
      else if ( W4 + T2/2 < Wb/2 )
      {
         // end block extends beyond bottom fillet
         w4 = 0;
         w3 = W3 + W4 + T2/2 - Wb/2;
         w3 = (IsZero(w3) ? 0 : w3); // eliminate noise
         d5 = (D5/W3)*w3;
         d6 = D6 + (D5 - d5);
         t2 = Wb;
      }
      else if ( T2/2 < Wb/2)
      {
         // end block intersects bottom fillet
         w4 = W4 + T2/2 - Wb/2;
         d6 = (D6/W4)*w4;
         d7 += D6 - d6;
         t2 = Wb;
      }

      // verify girder height is unchanged
      ATLASSERT(IsEqual(d1+d2+d3+d4+d5+d6+d7,D1+D2+D3+D4+D5+D6+D7));
      ATLASSERT(IsEqual(2*(w1+w2)+t1,2*(W1+W2)+T1) || IsEqual(2*(w1+w2)+t1,Wt));
      ATLASSERT(IsEqual(2*(w3+w4)+t2,2*(W3+W4)+T2) || IsEqual(2*(w3+w4)+t2,Wb));

      // create a new shape that is a clone of the original
      CComQIPtr<IShape> shape(m_Beam);
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
   }
   else
   {
      (*ppShape) = 0;
   }

   return hr;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::putref_Material(IMaterial* material)
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

STDMETHODIMP CFlangedGirderEndBlockSegment::get_Material(IMaterial* *material)
{
   CHECK_RETVAL(material);

   (*material) = m_Material;

   if ( *material )
      (*material)->AddRef();

   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::put_Orientation(Float64 orientation)
{
   if ( IsEqual(m_Orientation,orientation) )
      return S_OK;

   m_Orientation = orientation;
   Fire_OnSegmentChanged(this);
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_Orientation(Float64* orientation)
{
   CHECK_RETVAL(orientation);
   (*orientation) = m_Orientation;
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::Clone(ISegment* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CFlangedGirderEndBlockSegment>* pClone;
   CComObject<CFlangedGirderEndBlockSegment>::CreateInstance(&pClone);
   (*clone) = pClone;
   (*clone)->AddRef();

   pClone->m_Length = m_Length;
   pClone->m_pSegmentMeasure = m_pSegmentMeasure;
   pClone->m_Orientation = m_Orientation;

   pClone->m_EndBlockLength[etStart]           = m_EndBlockLength[etStart];
   pClone->m_EndBlockTransitionLength[etStart] = m_EndBlockTransitionLength[etStart];
   pClone->m_EndBlockWidth[etStart]            = m_EndBlockWidth[etStart];

   pClone->m_EndBlockLength[etEnd]           = m_EndBlockLength[etEnd];
   pClone->m_EndBlockTransitionLength[etEnd] = m_EndBlockTransitionLength[etEnd];
   pClone->m_EndBlockWidth[etEnd]            = m_EndBlockWidth[etEnd];

   if ( m_Beam )
   {
      CComQIPtr<IShape> shape(m_Beam);
      pClone->m_Beam.Release();

      CComPtr<IShape> cloneShape;
      shape->Clone(&cloneShape);

      cloneShape.QueryInterface(&pClone->m_Beam);
   }

   CComPtr<IMaterial> material;
   if ( m_Material )
      m_Material->Clone(&material);

   pClone->putref_Material(material);

   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IFlangedGirderEndBlockSegment implementation
STDMETHODIMP CFlangedGirderEndBlockSegment::putref_FlangedGirderSection(/*[in]*/ IFlangedGirderSection* pPrecastBeam)
{
   CHECK_IN(pPrecastBeam);

   if ( m_Beam.IsEqualObject(pPrecastBeam) )
      return S_OK;

   m_Beam = pPrecastBeam;
   Fire_OnSegmentChanged(this);
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::put_EndBlockLength(/*[in]*/EndType endType,/*[in]*/ Float64 length)
{
   m_EndBlockLength[endType] = length;
   Fire_OnSegmentChanged(this);
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_EndBlockLength(/*[in]*/EndType endType,/*[out,retval]*/ Float64* pLength)
{
   *pLength = m_EndBlockLength[endType];
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::put_EndBlockTransitionLength(/*[in]*/EndType endType,/*[in]*/ Float64 length)
{
   m_EndBlockTransitionLength[endType] = length;
   Fire_OnSegmentChanged(this);
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_EndBlockTransitionLength(/*[in]*/EndType endType,/*[out,retval]*/ Float64* pLength)
{
   *pLength = m_EndBlockTransitionLength[endType];
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::put_EndBlockWidth(/*[in]*/EndType endType,/*[in]*/ Float64 width)
{
   m_EndBlockWidth[endType] = width;
   Fire_OnSegmentChanged(this);
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_EndBlockWidth(/*[in]*/EndType endType,/*[out,retval]*/ Float64* pWidth)
{
   *pWidth = m_EndBlockWidth[endType];
   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CFlangedGirderEndBlockSegment::Load(IStructuredLoad2* load)
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

STDMETHODIMP CFlangedGirderEndBlockSegment::Save(IStructuredSave2* save)
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

void CFlangedGirderEndBlockSegment::GetEndBlockWidth(Float64 distAlongSegment,Float64* pWtop,Float64* pWbot)
{
   Float64 segLength;
   get_SegmentLength(&segLength);

   CComPtr<IPrecastBeam> pcBeam;
   m_Beam->get_Beam(&pcBeam);

   EndType endType;
   if ( distAlongSegment < segLength/2 )
   {
      // at the start end...
      endType = etStart;
   }
   else
   {
      endType = etEnd;
      distAlongSegment = segLength - distAlongSegment; // distAlongSegment is now measured from the left end
   }

   Float64 ebWidth       = m_EndBlockWidth[endType];
   Float64 ebLength      = m_EndBlockLength[endType];
   Float64 ebTransLength = m_EndBlockTransitionLength[endType];

   if ( distAlongSegment < ebLength )
   {
      // in the end block
      *pWtop = ebWidth;
      *pWbot = ebWidth;
   }
   else if ( ::InRange(ebLength,distAlongSegment,ebLength+ebTransLength) )
   {
      // in the end block transition
      Float64 t1, t2;
      pcBeam->get_T1(&t1);
      pcBeam->get_T2(&t2);
      *pWtop = ::LinInterp(distAlongSegment-ebLength,ebWidth,t1,ebTransLength);
      *pWbot = ::LinInterp(distAlongSegment-ebLength,ebWidth,t2,ebTransLength);
   }
   else
   {
      // after the end block
      Float64 t1, t2;
      pcBeam->get_T1(&t1);
      pcBeam->get_T2(&t2);
      *pWtop = t1;
      *pWbot = t2;
   }
}

Float64 CFlangedGirderEndBlockSegment::GetSuperstructureMemberLength()
{
   Float64 length;
   CComQIPtr<ISuperstructureMember> ssmbr(m_pSegmentMeasure);
   ATLASSERT(ssmbr);

   ssmbr->get_Length(&length);
   ATLASSERT( 0 <= length );
   return length;
}