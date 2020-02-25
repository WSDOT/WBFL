///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2020  Washington State Department of Transportation
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

// PrismaticSuperstructureMemberSegment.cpp : Implementation of CPrismaticSuperstructureMemberSegment
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "PrismaticSuperstructureMemberSegment.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrismaticSuperstructureMemberSegment
HRESULT CPrismaticSuperstructureMemberSegment::FinalConstruct()
{
   return S_OK;
}

void CPrismaticSuperstructureMemberSegment::FinalRelease()
{
   m_Shapes.clear();
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::InterfaceSupportsErrorInfo(REFIID riid)
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
STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_Section(StageIndexType stageIdx,Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,ISection** ppSection)
{
   CHECK_RETOBJ(ppSection);

   if ( m_Shapes.size() == 0 )
   {
      *ppSection = nullptr;
      return S_OK;
   }

   // This object reprsents a prismatic shape... all sections are the same
   CComPtr<ICompositeSectionEx> section;
   section.CoCreateInstance(CLSID_CompositeSectionEx);

   std::vector<ShapeData>::iterator iter(m_Shapes.begin());
   std::vector<ShapeData>::iterator end(m_Shapes.end());
   for ( ; iter != end; iter++ )
   {
      ShapeData& shapeData = *iter;

      Float64 Efg = 0;
      if (shapeData.FGMaterial)
      {
         shapeData.FGMaterial->get_E(stageIdx, &Efg);
      }

      Float64 Ebg = 0;
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

      // position the shape
      if (coordinateSystem == cstBridge)
      {
         CComPtr<IPoint2d> pntTopCenter;
         GB_GetSectionLocation(this, Xs, &pntTopCenter);

         CComQIPtr<IXYPosition> position(shape);
         position->put_LocatorPoint(lpTopCenter, pntTopCenter);
      }
      else
      {
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance(CLSID_Point2d);
         pnt->Move(0, 0);
         CComQIPtr<IXYPosition> position(shape);
         position->put_LocatorPoint(lpTopCenter, pnt);
      }

      section->AddSection(shape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);
   }

   section->QueryInterface(IID_ISection,(void**)ppSection);
   ATLASSERT(*ppSection);

   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_PrimaryShape(Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem, IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);
   if ( m_Shapes.size() == 0 )
   {
      *ppShape = 0;
      return S_OK;
   }

   // this is a prismatic shape, so Xs doesn't matter
   m_Shapes.front().Shape->Clone(ppShape);

   // position the shape
   if (coordinateSystem == cstBridge)
   {
      CComPtr<IPoint2d> pntTopCenter;
      GB_GetSectionLocation(this, Xs, &pntTopCenter);

      CComQIPtr<IXYPosition> position(*ppShape);
      position->put_LocatorPoint(lpTopCenter, pntTopCenter);
   }
   else
   {
      CComPtr<IPoint2d> pnt;
      pnt.CoCreateInstance(CLSID_Point2d);
      pnt->Move(0, 0);
      CComQIPtr<IXYPosition> position(*ppShape);
      position->put_LocatorPoint(lpTopCenter, pnt);
   }

   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::GetVolumeAndSurfaceArea(Float64* pVolume, Float64* pSurfaceArea)
{
   CHECK_RETVAL(pVolume);
   CHECK_RETVAL(pSurfaceArea);

   if (m_bUpdateVolumeAndSurfaceArea)
   {
      if (m_Shapes.size() == 0)
      {
         m_Volume = 0;
         m_SurfaceArea = 0;
      }
      else
      {
         Float64 perimeter;
         m_Shapes.front().Shape->get_Perimeter(&perimeter);

         CComPtr<IShapeProperties> shapeProps;
         m_Shapes.front().Shape->get_ShapeProperties(&shapeProps);

         Float64 area;
         shapeProps->get_Area(&area);

         Float64 L;
         get_Length(&L);

         m_Volume = area*L;
         m_SurfaceArea = perimeter*L + 2 * area;
      }

      m_bUpdateVolumeAndSurfaceArea = false;
   }

   *pVolume = m_Volume;
   *pSurfaceArea = m_SurfaceArea;
   return S_OK;
}

Float64 GetInternalVoidPerimeter(ICompositeShape* pCompShape)
{
   Float64 P = 0;
   IndexType nItems;
   pCompShape->get_Count(&nItems);
   for (IndexType idx = 0; idx < nItems; idx++)
   {
      CComPtr<ICompositeShapeItem> item;
      pCompShape->get_Item(idx, &item);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      VARIANT_BOOL vbIsVoid;
      item->get_Void(&vbIsVoid);
      if (vbIsVoid == VARIANT_TRUE)
      {
         Float64 perimeter;
         shape->get_Perimeter(&perimeter);
         P += perimeter;
      }
      else
      {
         CComQIPtr<ICompositeShape> compShape(shape);
         if (compShape)
         {
            P += GetInternalVoidPerimeter(compShape);
         }
      }
   }
   return P;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_InternalSurfaceAreaOfVoids(Float64* pSurfaceArea)
{
   CHECK_RETVAL(pSurfaceArea);
   if (m_Shapes.size() == 0)
   {
      *pSurfaceArea = 0;
   }
   else
   {
      Float64 L;
      get_Length(&L);

      *pSurfaceArea = 0;
      for (const auto& shp : m_Shapes)
      {
         CComQIPtr<ICompositeShape> composite(shp.Shape);
         if (composite)
         {
            Float64 P = GetInternalVoidPerimeter(composite);
            *pSurfaceArea += P*L;
         }
      }
   }
   return S_OK;
}


STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_Profile(VARIANT_BOOL bIncludeClosure,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);
   CComPtr<IRect2d> rect;

   // it is assumed that the first shape is the main shape in the section and all
   // other shapes are inside of it
   m_Shapes[0].Shape->get_BoundingBox(&rect);

   Float64 h;
   rect->get_Height(&h);

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
      profile->AddPoint(0, 0); // bottom left corner

      CComPtr<ISegment> pPrevSegment, pNextSegment;
      get_PrevSegment(&pPrevSegment);
      get_NextSegment(&pNextSegment);

      // work left to right along bottom of segment
      int nPoints = 11;
      int nSpaces = nPoints - 1;

      Float64 Ls;
      m_Impl.m_pGirderLine->get_GirderLength(&Ls);
      for (int i = 0; i < nPoints; i++)
      {
         Float64 x = i*Ls / nSpaces;
         Float64 y = m_Impl.ComputePrecamber(x,Ls);
         if (bIncludeClosure == VARIANT_TRUE && pPrevSegment != nullptr)
         {
            x += (brgOffset - endDist);
         }
         profile->AddPoint(x, y);
      }

      profile->AddPoint(Ls, 0);

      if (bIncludeClosure == VARIANT_TRUE && pNextSegment != nullptr)
      {
         profile->AddPoint(l, 0);
      }

      // work right to left along the top of the segment
      for (int i = 0; i < nPoints; i++)
      {
         Float64 x = Ls - i*Ls / nSpaces;
         Float64 y = m_Impl.ComputePrecamber(x, Ls) + h;
         if (bIncludeClosure == VARIANT_TRUE && pPrevSegment != nullptr)
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
   position->get_LocatorPoint(lpTopLeft, &topLeft);
   if (0 < m_Impl.m_Precamber)
   {
      topLeft->Move(brgOffset - endDist, m_Impl.m_Precamber);
   }
   else
   {
      topLeft->Move(brgOffset - endDist, 0);
   }
   position->put_LocatorPoint(lpTopLeft, topLeft);

   shape->QueryInterface(ppShape);

   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IPrismaticSection implementation

STDMETHODIMP CPrismaticSuperstructureMemberSegment::AddShape(IShape* pShape,IMaterial* pFGMaterial,IMaterial* pBGMaterial)
{
   CHECK_IN(pShape);

   ShapeData shapeData;
   shapeData.Shape = pShape;
   shapeData.FGMaterial = pFGMaterial;
   shapeData.BGMaterial = pBGMaterial;

   m_Shapes.push_back(shapeData);

   m_bUpdateVolumeAndSurfaceArea = true;
   m_Volume = -1;
   m_SurfaceArea = -1;

   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_ShapeCount(IndexType* nShapes)
{
   CHECK_RETVAL(nShapes);
   *nShapes = m_Shapes.size();
   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_ForegroundMaterial(IndexType index,IMaterial* *material)
{
   if ( m_Shapes.size() <= index || index == INVALID_INDEX )
      return E_INVALIDARG;

   CHECK_RETVAL(material);
   (*material) = m_Shapes[index].FGMaterial;

   if ( *material )
      (*material)->AddRef();

   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_BackgroundMaterial(IndexType index,IMaterial* *material)
{
   if ( m_Shapes.size() <= index || index == INVALID_INDEX )
      return E_INVALIDARG;

   CHECK_RETVAL(material);
   (*material) = m_Shapes[index].BGMaterial;

   if ( *material )
      (*material)->AddRef();

   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IItemData implementation
STDMETHODIMP CPrismaticSuperstructureMemberSegment::AddItemData(BSTR name,IUnknown* data)
{
   return m_ItemDataMgr.AddItemData(name,data);
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::GetItemData(BSTR name,IUnknown** data)
{
   return m_ItemDataMgr.GetItemData(name,data);
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::RemoveItemData(BSTR name)
{
   return m_ItemDataMgr.RemoveItemData(name);
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::GetItemDataCount(CollectionIndexType* count)
{
   return m_ItemDataMgr.GetItemDataCount(count);
}

////////////////////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CPrismaticSuperstructureMemberSegment::Load(IStructuredLoad2* load)
{
   CComVariant var;
   load->BeginUnit(CComBSTR("Segment"));

   ATLASSERT(false); // not implemented

   m_Shapes.clear();

   //load->get_Property(CComBSTR("Shape"),&var);
   //if ( var.vt == VT_UNKNOWN )
   //   var.punkVal->QueryInterface(&m_Shape);

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::Save(IStructuredSave2* save)
{
   save->BeginUnit(CComBSTR("Segment"),1.0);

   ATLASSERT(false); // not implemented

   //if ( m_Shape )
   //   save->put_Property(CComBSTR("Shape"),CComVariant(m_Shape));
   //else
   //   save->put_Property(CComBSTR("Shape"),CComVariant(0));

   save->EndUnit();
   return S_OK;
}
