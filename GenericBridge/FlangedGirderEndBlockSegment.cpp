///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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
   m_pGirderLine = NULL;

   m_Orientation = 0;

   m_HaunchDepth[etStart] = 0;
   m_HaunchDepth[etEnd]   = 0;

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
   m_pGirderLine = NULL;
   m_Shapes.clear();
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
STDMETHODIMP CFlangedGirderEndBlockSegment::putref_SuperstructureMember(ISuperstructureMember* ssMbr)
{
   CHECK_IN(ssMbr);
   m_pSSMbr = ssMbr;
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_SuperstructureMember(ISuperstructureMember** ssMbr)
{
   CHECK_RETOBJ(ssMbr);
   if ( m_pSSMbr )
   {
      (*ssMbr) = m_pSSMbr;
      (*ssMbr)->AddRef();
   }
   else
   {
      (*ssMbr) = NULL;
   }

   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::putref_GirderLine(IGirderLine* girderLine)
{
   CHECK_IN(girderLine);
   m_pGirderLine = girderLine;
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_GirderLine(IGirderLine** girderLine)
{
   CHECK_RETOBJ(girderLine);
   if ( m_pGirderLine )
   {
      (*girderLine) = m_pGirderLine;
      (*girderLine)->AddRef();
   }
   else
   {
      (*girderLine) = NULL;
   }

   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::putref_PrevSegment(ISegment* segment)
{
   CHECK_IN(segment);
   m_pPrevSegment = segment;
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_PrevSegment(ISegment** segment)
{
   CHECK_RETVAL(segment);
   *segment = m_pPrevSegment;
   if ( *segment )
      (*segment)->AddRef();

   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::putref_NextSegment(ISegment* segment)
{
   CHECK_IN(segment);
   m_pNextSegment = segment;
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_NextSegment(ISegment** segment)
{
   CHECK_RETVAL(segment);
   *segment = m_pNextSegment;
   if ( *segment )
      (*segment)->AddRef();

   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_Length(Float64 *pVal)
{
   return m_pGirderLine->get_GirderLength(pVal);
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_LayoutLength(Float64 *pVal)
{
   return m_pGirderLine->get_LayoutLength(pVal);
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_Section(StageIndexType stageIdx,Float64 distAlongSegment,ISection** ppSection)
{
   CHECK_RETOBJ(ppSection);

   if (m_Shapes.size() == 0 )
   {
      *ppSection = 0;
      return S_OK;
   }

   CComPtr<IShape> primaryShape;
   HRESULT hr = get_PrimaryShape(distAlongSegment,&primaryShape);
   ATLASSERT(SUCCEEDED(hr));
   if ( FAILED(hr) )
      return hr;


   // create our section object
   CComPtr<ICompositeSectionEx> section;
   section.CoCreateInstance(CLSID_CompositeSectionEx);

   section->QueryInterface(IID_ISection,(void**)ppSection);
   ATLASSERT(*ppSection != NULL);

   // add the primary shape
   Float64 Efg = 0;
   m_Shapes.front().FGMaterial->get_E(stageIdx,&Efg);
   
   Float64 Ebg = 0;
   if ( m_Shapes.front().BGMaterial )
      m_Shapes.front().BGMaterial->get_E(stageIdx,&Ebg);

   Float64 Dfg = 0;
   m_Shapes.front().FGMaterial->get_Density(stageIdx,&Dfg);
   
   Float64 Dbg = 0;
   if ( m_Shapes.front().BGMaterial )
      m_Shapes.front().BGMaterial->get_Density(stageIdx,&Dbg);

   section->AddSection(primaryShape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);

   // add all the secondary shapes
   std::vector<ShapeData>::iterator iter(m_Shapes.begin());
   std::vector<ShapeData>::iterator end(m_Shapes.end());
   iter++; // skip the first shape, we already processed it

   for ( ; iter != end; iter++ )
   {
      ShapeData& shapeData = *iter;

      Float64 Efg = 0;
      if ( shapeData.FGMaterial )
         shapeData.FGMaterial->get_E(stageIdx,&Efg);

      Float64 Ebg;
      if ( shapeData.BGMaterial )
         shapeData.BGMaterial->get_E(stageIdx,&Ebg);

      Float64 Dfg = 0;
      if ( shapeData.FGMaterial )
         shapeData.FGMaterial->get_Density(stageIdx,&Dfg);

      Float64 Dbg = 0;
      if ( shapeData.BGMaterial )
         shapeData.BGMaterial->get_Density(stageIdx,&Dbg);

      CComPtr<IShape> shape;
      shapeData.Shape->Clone(&shape);

      section->AddSection(shape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);
   }

   return S_OK;
}


STDMETHODIMP CFlangedGirderEndBlockSegment::get_PrimaryShape(Float64 distAlongSegment,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   if (m_Shapes.size() == 0 )
   {
      *ppShape = 0;
      return S_OK;
   }

   CComQIPtr<IFlangedGirderSection> beam(m_Shapes.front().Shape);
   ATLASSERT(beam); // if this is NULL... how did it get in the system????

   // This object reprsents a prismatic shape... all sections are the same
   HRESULT hr = S_OK;
   CComPtr<IPrecastBeam> pcBeam;
   beam->get_Beam(&pcBeam);

   // Adsut the shape for the end blocks
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
   CComQIPtr<IShape> shape(beam);
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

   // position the shape
   CComPtr<IPoint2d> pntTopCenter;
   GB_GetSectionLocation(this,distAlongSegment,&pntTopCenter);

   CComQIPtr<IXYPosition> position(newFlangedBeam);
   position->put_LocatorPoint(lpTopCenter,pntTopCenter);

   *ppShape = newShape;
   (*ppShape)->AddRef();
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_Profile(VARIANT_BOOL bIncludeClosure,IShape** ppShape)
{
   ATLASSERT(false); // not implemented yet
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::put_Orientation(Float64 orientation)
{
   if ( IsEqual(m_Orientation,orientation) )
      return S_OK;

   m_Orientation = orientation;
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_Orientation(Float64* orientation)
{
   CHECK_RETVAL(orientation);
   (*orientation) = m_Orientation;
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_HaunchDepth(EndType endType,Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_HaunchDepth[endType];
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::put_HaunchDepth(EndType endType,Float64 val)
{
   m_HaunchDepth[endType] = val;
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::GetHaunchDepth(Float64 distAlongSegment,Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = ::GB_GetHaunchDepth(this,distAlongSegment);
   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IFlangedGirderEndBlockSegment implementation

STDMETHODIMP CFlangedGirderEndBlockSegment::AddShape(IShape* pShape,IMaterial* pFGMaterial,IMaterial* pBGMaterial)
{
   CHECK_IN(pShape);

   if ( m_Shapes.size() == 0 )
   {
      CComQIPtr<IFlangedGirderSection> beam(pShape);
      if ( beam == NULL )
      {
         ATLASSERT(false); // first shape must be a flanged girder section
         return E_INVALIDARG;
      }
   }

   ShapeData shapeData;
   shapeData.Shape = pShape;
   shapeData.FGMaterial = pFGMaterial;
   shapeData.BGMaterial = pBGMaterial;

   m_Shapes.push_back(shapeData);

   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_ShapeCount(IndexType* nShapes)
{
   CHECK_RETVAL(nShapes);
   *nShapes = m_Shapes.size();
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_ForegroundMaterial(IndexType index,IMaterial* *material)
{
   if ( m_Shapes.size() <= index || index == INVALID_INDEX )
      return E_INVALIDARG;

   CHECK_RETVAL(material);
   (*material) = m_Shapes[index].FGMaterial;

   if ( *material )
      (*material)->AddRef();

   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_BackgroundMaterial(IndexType index,IMaterial* *material)
{
   if ( m_Shapes.size() <= index || index == INVALID_INDEX )
      return E_INVALIDARG;

   CHECK_RETVAL(material);
   (*material) = m_Shapes[index].BGMaterial;

   if ( *material )
      (*material)->AddRef();

   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::put_EndBlockLength(/*[in]*/EndType endType,/*[in]*/ Float64 length)
{
   m_EndBlockLength[endType] = length;
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
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_EndBlockWidth(/*[in]*/EndType endType,/*[out,retval]*/ Float64* pWidth)
{
   *pWidth = m_EndBlockWidth[endType];
   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IItemData implementation
STDMETHODIMP CFlangedGirderEndBlockSegment::AddItemData(BSTR name,IUnknown* data)
{
   return m_ItemDataMgr.AddItemData(name,data);
}

STDMETHODIMP CFlangedGirderEndBlockSegment::GetItemData(BSTR name,IUnknown** data)
{
   return m_ItemDataMgr.GetItemData(name,data);
}

STDMETHODIMP CFlangedGirderEndBlockSegment::RemoveItemData(BSTR name)
{
   return m_ItemDataMgr.RemoveItemData(name);
}

STDMETHODIMP CFlangedGirderEndBlockSegment::GetItemDataCount(CollectionIndexType* count)
{
   return m_ItemDataMgr.GetItemDataCount(count);
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
   get_Length(&segLength);

   CComQIPtr<IFlangedGirderSection> beam(m_Shapes.front().Shape);
   ATLASSERT(beam); // if this is NULL... how did it get in the system????

   CComPtr<IPrecastBeam> pcBeam;
   beam->get_Beam(&pcBeam);

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
