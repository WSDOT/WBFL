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
   m_Shapes.clear();
}

STDMETHODIMP CFlangedGirderEndBlockSegment::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISegment,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

////////////////////////////////////////////////////////////////////////
// ISuperstructureMemberSegment implementation
STDMETHODIMP CFlangedGirderEndBlockSegment::get_Section(StageIndexType stageIdx,Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,ISection** ppSection)
{
   CHECK_RETOBJ(ppSection);

   if (m_Shapes.size() == 0 )
   {
      *ppSection = 0;
      return S_OK;
   }

   CComPtr<IShape> primaryShape;
   HRESULT hr = get_PrimaryShape(Xs,sectionBias,coordinateSystem,&primaryShape);
   ATLASSERT(SUCCEEDED(hr));
   if ( FAILED(hr) )
      return hr;


   // create our section object
   CComPtr<ICompositeSectionEx> section;
   section.CoCreateInstance(CLSID_CompositeSectionEx);

   section->QueryInterface(IID_ISection,(void**)ppSection);
   ATLASSERT(*ppSection != nullptr);

   // add the primary shape
   Float64 Efg = 0;
   m_Shapes.front().FGMaterial->get_E(stageIdx,&Efg);
   
   Float64 Ebg = 0;
   if (m_Shapes.front().BGMaterial)
   {
      m_Shapes.front().BGMaterial->get_E(stageIdx, &Ebg);
   }

   Float64 Dfg = 0;
   m_Shapes.front().FGMaterial->get_Density(stageIdx,&Dfg);
   
   Float64 Dbg = 0;
   if (m_Shapes.front().BGMaterial)
   {
      m_Shapes.front().BGMaterial->get_Density(stageIdx, &Dbg);
   }

   section->AddSection(primaryShape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);

   // add all the secondary shapes
   std::vector<ShapeData>::iterator iter(m_Shapes.begin());
   std::vector<ShapeData>::iterator end(m_Shapes.end());
   iter++; // skip the first shape, we already processed it

   for ( ; iter != end; iter++ )
   {
      ShapeData& shapeData = *iter;

      Float64 Efg = 0;
      if (shapeData.FGMaterial)
      {
         shapeData.FGMaterial->get_E(stageIdx, &Efg);
      }

      Float64 Ebg;
      if (shapeData.BGMaterial)
      {
         shapeData.BGMaterial->get_E(stageIdx, &Ebg);
      }

      Float64 Dfg = 0;
      if (shapeData.FGMaterial)
      {
         shapeData.FGMaterial->get_Density(stageIdx, &Dfg);
      }

      Float64 Dbg = 0;
      if (shapeData.BGMaterial)
      {
         shapeData.BGMaterial->get_Density(stageIdx, &Dbg);
      }

      CComPtr<IShape> shape;
      shapeData.Shape->Clone(&shape);

      section->AddSection(shape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);
   }

   return S_OK;
}


STDMETHODIMP CFlangedGirderEndBlockSegment::get_PrimaryShape(Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem, IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   if (m_Shapes.size() == 0 )
   {
      *ppShape = 0;
      return S_OK;
   }

   CComQIPtr<IFlangedGirderSection> beam(m_Shapes.front().Shape);
   ATLASSERT(beam); // if this is nullptr... how did it get in the system????

   // This object reprsents a prismatic shape... all sections are the same
   HRESULT hr = S_OK;
   CComPtr<IPrecastBeam> pcBeam;
   beam->get_Beam(&pcBeam);

   // Adsut the shape for the end blocks
   Float64 Wt, Wb;
   GetEndBlockWidth(Xs,sectionBias,&Wt,&Wb);

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
   if (coordinateSystem == cstBridge)
   {
      CComPtr<IPoint2d> pntTopCenter;
      GB_GetSectionLocation(this, Xs, &pntTopCenter);

      CComQIPtr<IXYPosition> position(newFlangedBeam);
      position->put_LocatorPoint(lpTopCenter, pntTopCenter);
   }
   else
   {
      CComPtr<IPoint2d> pnt;
      pnt.CoCreateInstance(CLSID_Point2d);
      pnt->Move(0, 0);
      CComQIPtr<IXYPosition> position(newFlangedBeam);
      position->put_LocatorPoint(lpTopCenter, pnt);
   }

   *ppShape = newShape;
   (*ppShape)->AddRef();
   return S_OK;
}

STDMETHODIMP CFlangedGirderEndBlockSegment::get_Profile(VARIANT_BOOL bIncludeClosure,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);
   CComPtr<IRect2d> rect;

   // it is assumed that the first shape is the main shape in the section and all
   // other shapes are inside of it
   m_Shapes[0].Shape->get_BoundingBox(&rect);

   Float64 h;
   rect->get_Height(&h);

   Float64 l;
   Float64 brgOffset, endDist;
   if (bIncludeClosure == VARIANT_TRUE)
   {
      m_Impl.m_pGirderLine->get_LayoutLength(&l);
      brgOffset = 0;
      endDist = 0;
   }
   else
   {
      m_Impl.m_pGirderLine->get_GirderLength(&l);
      m_Impl.m_pGirderLine->get_BearingOffset(etStart, &brgOffset);
      m_Impl.m_pGirderLine->get_EndDistance(etStart, &endDist);
   }

   CComPtr<IShape> shape;
   if (IsZero(m_Impl.m_Precamber))
   {
      CComPtr<IRectangle> profile;
      profile.CoCreateInstance(CLSID_Rect);
      profile->put_Height(h);
      profile->put_Width(l);

      profile.QueryInterface(&shape);
   }
   else
   {
      CComPtr<IPolyShape> profile;
      profile.CoCreateInstance(CLSID_PolyShape);
      profile->AddPoint(0, 0);

      Float64 Ls;
      m_Impl.m_pGirderLine->get_GirderLength(&Ls);
      for (int i = 0; i < 11; i++)
      {
         Float64 x = i*Ls / 10;
         Float64 y = m_Impl.ComputePrecamber(x,Ls);
         if (bIncludeClosure == VARIANT_TRUE)
         {
            x += (brgOffset - endDist);
         }
         profile->AddPoint(x, y);
      }

      profile->AddPoint(l, 0);

      for (int i = 0; i < 11; i++)
      {
         Float64 x = Ls - i*Ls / 10;
         Float64 y = m_Impl.ComputePrecamber(x,Ls) + h;
         if (bIncludeClosure == VARIANT_TRUE)
         {
            x += (brgOffset - endDist);
         }
         profile->AddPoint(x, y);
      }

      profile->AddPoint(0, h);

      profile.QueryInterface(&shape);
   }

   // CL Pier/Top Shape is at (0,0)
   //
   // CL Pier   End of segment
   // |         |       CL Bearing
   // | (0,0)   |       |
   // *         +-------+---------------\  
   // |         |       .               /
   // |         +-------+---------------\  
   //
   //          Elevation View

   CComQIPtr<IXYPosition> position(shape);
   CComPtr<IPoint2d> topLeft;
   position->get_LocatorPoint(lpTopLeft,&topLeft);
   if (0 < m_Impl.m_Precamber)
   {
      topLeft->Move(brgOffset - endDist, m_Impl.m_Precamber);
   }
   else
   {
      topLeft->Move(brgOffset - endDist, 0);
   }
   position->put_LocatorPoint(lpTopLeft,topLeft);

   shape->QueryInterface(ppShape);

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
      if ( beam == nullptr )
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

void CFlangedGirderEndBlockSegment::GetEndBlockWidth(Float64 Xs, SectionBias sectionBias,Float64* pWtop,Float64* pWbot)
{
   Float64 segLength;
   get_Length(&segLength);

   CComQIPtr<IFlangedGirderSection> beam(m_Shapes.front().Shape);
   ATLASSERT(beam); // if this is nullptr... how did it get in the system????

   CComPtr<IPrecastBeam> pcBeam;
   beam->get_Beam(&pcBeam);

   // the end blocks for this girder type of a smooth transitions
   // so sectionBias doesn't have any impact

   EndType endType;
   if ( Xs < segLength/2 )
   {
      // at the start end...
      endType = etStart;
   }
   else
   {
      endType = etEnd;
      Xs = segLength - Xs; // Xs is now measured from the left end
   }

   Float64 ebWidth       = m_EndBlockWidth[endType];
   Float64 ebLength      = m_EndBlockLength[endType];
   Float64 ebTransLength = m_EndBlockTransitionLength[endType];

   if ( Xs < ebLength )
   {
      // in the end block
      *pWtop = ebWidth;
      *pWbot = ebWidth;
   }
   else if ( ::InRange(ebLength,Xs,ebLength+ebTransLength) )
   {
      // in the end block transition
      Float64 t1, t2;
      pcBeam->get_T1(&t1);
      pcBeam->get_T2(&t2);
      *pWtop = ::LinInterp(Xs-ebLength,ebWidth,t1,ebTransLength);
      *pWbot = ::LinInterp(Xs-ebLength,ebWidth,t2,ebTransLength);
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
