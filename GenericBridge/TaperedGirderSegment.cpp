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
   return S_OK;
}

void CTaperedGirderSegment::FinalRelease()
{
   m_Shapes[etStart].clear();
   m_Shapes[etEnd].clear();
}

STDMETHODIMP CTaperedGirderSegment::InterfaceSupportsErrorInfo(REFIID riid)
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
STDMETHODIMP CTaperedGirderSegment::get_Section(StageIndexType stageIdx,Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,ISection** ppSection)
{
   CHECK_RETOBJ(ppSection);

   ATLASSERT(m_Shapes[etStart].size() == m_Shapes[etEnd].size());

   if (m_Shapes[etStart].size() == 0 )
   {
      *ppSection = 0;
      return S_OK;
   }

   CComPtr<IShape> primaryShape;
   HRESULT hr = get_PrimaryShape(Xs,sectionBias,coordinateSystem,&primaryShape);
   ATLASSERT(SUCCEEDED(hr));
   if ( FAILED(hr) )
   {
      return hr;
   }


   CComPtr<ICompositeSectionEx> section;
   section.CoCreateInstance(CLSID_CompositeSectionEx);
   section.QueryInterface(ppSection);
   ATLASSERT(ppSection != nullptr);

   // add the primary shape
   Float64 Efg = 0;
   m_Shapes[etStart].front().FGMaterial->get_E(stageIdx,&Efg);
   
   Float64 Ebg = 0;
   if ( m_Shapes[etStart].front().BGMaterial )
   {
      m_Shapes[etStart].front().BGMaterial->get_E(stageIdx,&Ebg);
   }

   Float64 Dfg = 0;
   m_Shapes[etStart].front().FGMaterial->get_Density(stageIdx,&Dfg);
   
   Float64 Dbg = 0;
   if ( m_Shapes[etStart].front().BGMaterial )
   {
      m_Shapes[etStart].front().BGMaterial->get_Density(stageIdx,&Dbg);
   }

   section->AddSection(primaryShape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);

   // add all the secondary shapes
   std::vector<ShapeData>::iterator startIter(m_Shapes[etStart].begin());
   std::vector<ShapeData>::iterator startIterEnd(m_Shapes[etStart].end());
   startIter++; // skip the first shape, we already processed it

   std::vector<ShapeData>::iterator endIter(m_Shapes[etEnd].begin());
   std::vector<ShapeData>::iterator endIterEnd(m_Shapes[etEnd].end());
   endIter++; // skip the first shape, we already processed it

   for ( ; startIter != startIterEnd; startIter++, endIter++ )
   {
      ShapeData& startShapeData = *startIter;
      ShapeData& endShapeData   = *endIter;

      Float64 Efg = 0;
      if ( startShapeData.FGMaterial )
      {
         startShapeData.FGMaterial->get_E(stageIdx,&Efg);
      }

      Float64 Ebg;
      if ( startShapeData.BGMaterial )
      {
         startShapeData.BGMaterial->get_E(stageIdx,&Ebg);
      }

      Float64 Dfg = 0;
      if ( startShapeData.FGMaterial )
      {
         startShapeData.FGMaterial->get_Density(stageIdx,&Dfg);
      }

      Float64 Dbg = 0;
      if ( startShapeData.BGMaterial )
      {
         startShapeData.BGMaterial->get_Density(stageIdx,&Dbg);
      }

      // Assuming that all the secondary shapes are prismatic, but could be at different locations at
      // either end of the segment. Locate the cg of the shape at each end and then use the average location

      CComPtr<IShape> shape;
      startShapeData.Shape->Clone(&shape);

      CComPtr<IShapeProperties> startProps;
      shape->get_ShapeProperties(&startProps);

      CComPtr<IPoint2d> startCG;
      startProps->get_Centroid(&startCG);
      Float64 x1,y1;
      startCG->Location(&x1,&y1);

      CComPtr<IShapeProperties> endProps;
      endShapeData.Shape->get_ShapeProperties(&endProps);
      CComPtr<IPoint2d> endCG;
      endProps->get_Centroid(&endCG);
      Float64 x2,y2;
      endCG->Location(&x2,&y2);

      Float64 x = (x1+x2)/2;
      Float64 y = (y1+y2)/2;

      CComQIPtr<IXYPosition> position(shape);
      position->Offset(x-x1,y-y1);


      section->AddSection(shape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);
   }

   return S_OK;
}

STDMETHODIMP CTaperedGirderSegment::get_PrimaryShape(Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem, IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   ATLASSERT(m_Shapes[etStart].size() == m_Shapes[etEnd].size());

   if (m_Shapes[etStart].size() == 0 )
   {
      *ppShape = 0;
      return S_OK;
   }

   CComPtr<IShape> newShape;
   auto found = m_ShapeCache.find(Xs);
   if (found == m_ShapeCache.end())
   {
      std::array<CComQIPtr<IFlangedGirderSection>,2> beam;
      m_Shapes[etStart].front().Shape.QueryInterface(&beam[etStart]);
      m_Shapes[etEnd].front().Shape.QueryInterface(&beam[etEnd]);

      ATLASSERT(beam[etStart]); // if this is nullptr... how did it get in the system????
      ATLASSERT(beam[etEnd]);   // if this is nullptr... how did it get in the system????

      // This object reprsents a prismatic shape... all sections are the same
      HRESULT hr = S_OK;

      Float64 segLength;
      get_Length(&segLength);

      // get dimensions of beam shape at start and end of segment
      std::array<CComPtr<IPrecastBeam>,2> pcBeam;

      std::array<Float64, 2> W1, W2, W3, W4;
      std::array<Float64, 2> D1, D2, D3, D4, D5, D6, D7;
      std::array<Float64, 2> T1, T2;
      std::array<Float64, 2> C1;

      for (int i = 0; i < 2; i++)
      {
         beam[i]->get_Beam(&pcBeam[i]);

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
      Float64 w1 = ::LinInterp(Xs, W1[etStart], W1[etEnd], segLength);
      Float64 w2 = ::LinInterp(Xs, W2[etStart], W2[etEnd], segLength);
      Float64 w3 = ::LinInterp(Xs, W3[etStart], W3[etEnd], segLength);
      Float64 w4 = ::LinInterp(Xs, W4[etStart], W4[etEnd], segLength);

      Float64 d1 = ::LinInterp(Xs, D1[etStart], D1[etEnd], segLength);
      Float64 d2 = ::LinInterp(Xs, D2[etStart], D2[etEnd], segLength);
      Float64 d3 = ::LinInterp(Xs, D3[etStart], D3[etEnd], segLength);
      Float64 d4 = ::LinInterp(Xs, D4[etStart], D4[etEnd], segLength);
      Float64 d5 = ::LinInterp(Xs, D5[etStart], D5[etEnd], segLength);
      Float64 d6 = ::LinInterp(Xs, D6[etStart], D6[etEnd], segLength);
      Float64 d7 = ::LinInterp(Xs, D7[etStart], D7[etEnd], segLength);

      Float64 t1 = ::LinInterp(Xs, T1[etStart], T1[etEnd], segLength);
      Float64 t2 = ::LinInterp(Xs, T2[etStart], T2[etEnd], segLength);

      Float64 c1 = ::LinInterp(Xs, C1[etStart], C1[etEnd], segLength);

      // create a new shape that is a clone of the original
      CComQIPtr<IShape> shape(beam[etStart]);
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

      // position the shape in girder coordinates
      CComPtr<IPoint2d> pnt;
      pnt.CoCreateInstance(CLSID_Point2d);
      pnt->Move(0, 0);
      CComQIPtr<IXYPosition> position(newFlangedBeam);
      position->put_LocatorPoint(lpTopCenter, pnt);

      // copy the shape and put it in the cache
      CComPtr<IShape> cacheShape;
      newShape->Clone(&cacheShape);
      m_ShapeCache.emplace_hint(m_ShapeCache.end(), Xs, cacheShape);
   }
   else
   {
      CComPtr<IShape> cacheShape = found->second;
      cacheShape->Clone(&newShape);
   }

   if (coordinateSystem == cstBridge)
   {
      // position the shape in bridge coordinates
      CComPtr<IPoint2d> pntTopCenter;
      GB_GetSectionLocation(this, Xs, &pntTopCenter);

      CComQIPtr<IFlangedGirderSection> newFlangedBeam(newShape);
      CComQIPtr<IXYPosition> position(newFlangedBeam);
      position->put_LocatorPoint(lpTopCenter, pntTopCenter);
   }

   *ppShape = newShape;
   (*ppShape)->AddRef();

   return S_OK;
}

STDMETHODIMP CTaperedGirderSegment::GetVolumeAndSurfaceArea(Float64* pVolume, Float64* pSurfaceArea)
{
   if (m_bUpdateVolumeAndSurfaceArea)
   {
      Float64 start_perimeter;
      m_Shapes[etStart].front().Shape->get_Perimeter(&start_perimeter);

      CComPtr<IShapeProperties> shapeProps;
      m_Shapes[etStart].front().Shape->get_ShapeProperties(&shapeProps);

      Float64 start_area;
      shapeProps->get_Area(&start_area);

      Float64 end_perimeter;
      m_Shapes[etEnd].front().Shape->get_Perimeter(&end_perimeter);

      shapeProps.Release();
      m_Shapes[etEnd].front().Shape->get_ShapeProperties(&shapeProps);

      Float64 end_area;
      shapeProps->get_Area(&end_area);

      Float64 L;
      get_Length(&L);

      m_Volume = (start_area + end_area)*L/2;
      m_SurfaceArea = (start_perimeter + end_perimeter)*L/2 + start_area + end_area;

      m_bUpdateVolumeAndSurfaceArea = false;
   }

   *pVolume = m_Volume;
   *pSurfaceArea = m_SurfaceArea;
   return S_OK;
}

STDMETHODIMP CTaperedGirderSegment::get_InternalSurfaceAreaOfVoids(Float64* pSurfaceArea)
{
   CHECK_RETVAL(pSurfaceArea);
   *pSurfaceArea = 0;
   return S_OK;
}

STDMETHODIMP CTaperedGirderSegment::get_Profile(VARIANT_BOOL bIncludeClosure,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);
   CComPtr<IRect2d> rect[2];

   // it is assumed that the first shape is the main shape in the section and all
   // other shapes are inside of it
   m_Shapes[etStart].front().Shape->get_BoundingBox(&rect[etStart]);
   m_Shapes[etEnd  ].front().Shape->get_BoundingBox(&rect[etEnd]);

   Float64 h1, h2;
   rect[etStart]->get_Height(&h1);
   rect[etEnd  ]->get_Height(&h2);

   CComPtr<ISegment> nextSegment;
   get_NextSegment(&nextSegment);

   Float64 l;
   Float64 brgOffset, endDist;
   if (bIncludeClosure == VARIANT_TRUE && nextSegment)
   {
      m_Impl.m_pGirderLine->get_LayoutLength(&l);
      brgOffset = 0;
      endDist = 0;
   }
   else
   {
      m_Impl.m_pGirderLine->get_GirderLength(&l);
      m_Impl.m_pGirderLine->get_BearingOffset(etStart,&brgOffset);
      m_Impl.m_pGirderLine->get_EndDistance(etStart,&endDist);
   }

   CComPtr<IPolyShape> shape;
   shape.CoCreateInstance(CLSID_PolyShape);

   shape->AddPoint(0,0);
   shape->AddPoint(0,-h1);

   if (!IsZero(m_Impl.m_Precamber))
   {
      // work left to right along bottom of segment
      int nPoints = 11;
      int nSpaces = nPoints - 1;

      Float64 Ls;
      m_Impl.m_pGirderLine->get_GirderLength(&Ls);
      for (int i = 0; i < nPoints; i++)
      {
         Float64 x = i*Ls / nSpaces;
         Float64 y = m_Impl.ComputePrecamber(x, Ls);
         if (bIncludeClosure == VARIANT_TRUE && nextSegment)
         {
            x += (brgOffset - endDist);
         }
         Float64 dh = ::LinInterp(x, -h1, -h2, Ls);
         shape->AddPoint(x, y + dh);
      }

      // work right to left along top of segment
      for (int i = 0; i < nPoints; i++)
      {
         Float64 x = Ls - i*Ls / nSpaces;
         Float64 y = m_Impl.ComputePrecamber(x, Ls);
         if (bIncludeClosure == VARIANT_TRUE && nextSegment)
         {
            x += (brgOffset - endDist);
         }
         shape->AddPoint(x, y);
      }
   }

   shape->AddPoint(l,-h2);
   shape->AddPoint(l,0);

   // Shape is to be in girder path coordinates so (0,0) is at the CL Pier and at the elevation of the top of the shape
   //
   // CL Pier   Start of segment
   // |         |       CL Bearing
   // |(0,0)    |       |
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
// ITaperedGirderSegment implementation
STDMETHODIMP CTaperedGirderSegment::AddShape(IShape* pStartShape,IShape* pEndShape,IMaterial* pFGMaterial,IMaterial* pBGMaterial)
{
   CHECK_IN(pStartShape);
   CHECK_IN(pEndShape);

   ATLASSERT(m_Shapes[etStart].size() == m_Shapes[etEnd].size());
   if ( m_Shapes[etStart].size() == 0 )
   {
      CComQIPtr<IFlangedGirderSection> beam(pStartShape);
      if ( beam == nullptr )
      {
         ATLASSERT(false); // first shape must be a flanged girder section
         return E_INVALIDARG;
      }
   }

   if ( m_Shapes[etEnd].size() == 0 )
   {
      CComQIPtr<IFlangedGirderSection> beam(pEndShape);
      if ( beam == nullptr )
      {
         ATLASSERT(false); // first shape must be a flanged girder section
         return E_INVALIDARG;
      }
   }

   ShapeData startShapeData;
   startShapeData.Shape      = pStartShape;
   startShapeData.FGMaterial = pFGMaterial;
   startShapeData.BGMaterial = pBGMaterial;
   m_Shapes[etStart].push_back(startShapeData);

   ShapeData endShapeData;
   endShapeData.Shape      = pEndShape;
   endShapeData.FGMaterial = pFGMaterial;
   endShapeData.BGMaterial = pBGMaterial;
   m_Shapes[etEnd].push_back(endShapeData);

   m_bUpdateVolumeAndSurfaceArea = true;
   m_Volume = -1;
   m_SurfaceArea = -1;
   m_ShapeCache.clear();

   ATLASSERT(m_Shapes[etStart].size() == m_Shapes[etEnd].size());

   return S_OK;
}

STDMETHODIMP CTaperedGirderSegment::get_ShapeCount(IndexType* nShapes)
{
   CHECK_RETVAL(nShapes);
   ATLASSERT(m_Shapes[etStart].size() == m_Shapes[etEnd].size());
   *nShapes = m_Shapes[etStart].size();
   return S_OK;
}

STDMETHODIMP CTaperedGirderSegment::get_ForegroundMaterial(IndexType index,IMaterial* *material)
{
   ATLASSERT(m_Shapes[etStart].size() == m_Shapes[etEnd].size());
   if ( m_Shapes[etStart].size() <= index || index == INVALID_INDEX )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(material);
   (*material) = m_Shapes[etStart][index].FGMaterial;

   if ( *material )
   {
      (*material)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CTaperedGirderSegment::get_BackgroundMaterial(IndexType index,IMaterial* *material)
{
   ATLASSERT(m_Shapes[etStart].size() == m_Shapes[etEnd].size());
   if ( m_Shapes[etStart].size() <= index || index == INVALID_INDEX )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(material);
   (*material) = m_Shapes[etStart][index].BGMaterial;

   if ( *material )
   {
      (*material)->AddRef();
   }

   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IItemData implementation
STDMETHODIMP CTaperedGirderSegment::AddItemData(BSTR name,IUnknown* data)
{
   return m_ItemDataMgr.AddItemData(name,data);
}

STDMETHODIMP CTaperedGirderSegment::GetItemData(BSTR name,IUnknown** data)
{
   return m_ItemDataMgr.GetItemData(name,data);
}

STDMETHODIMP CTaperedGirderSegment::RemoveItemData(BSTR name)
{
   return m_ItemDataMgr.RemoveItemData(name);
}

STDMETHODIMP CTaperedGirderSegment::GetItemDataCount(CollectionIndexType* count)
{
   return m_ItemDataMgr.GetItemDataCount(count);
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
