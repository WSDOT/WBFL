///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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
   m_pGirderLine = nullptr;
   m_Orientation = 0;
   m_HaunchDepth[0] = 0;
   m_HaunchDepth[1] = 0;
   m_HaunchDepth[2] = 0;
   m_Fillet = 0;
   m_pPrevSegment = nullptr;
   m_pNextSegment = nullptr;
   return S_OK;
}

void CPrismaticSuperstructureMemberSegment::FinalRelease()
{
   m_pGirderLine = nullptr;
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
// ISegment implementation

STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_Length(Float64 *pVal)
{
   return m_pGirderLine->get_GirderLength(pVal);
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_LayoutLength(Float64 *pVal)
{
   return m_pGirderLine->get_LayoutLength(pVal);
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_Section(StageIndexType stageIdx,Float64 Xs, SectionBias sectionBias,ISection** ppSection)
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
      CComPtr<IPoint2d> pntTopCenter;
      GB_GetSectionLocation(this,Xs,&pntTopCenter);

      CComQIPtr<IXYPosition> position(shape);
      position->put_LocatorPoint(lpTopCenter,pntTopCenter);

      section->AddSection(shape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);
   }

   section->QueryInterface(IID_ISection,(void**)ppSection);
   ATLASSERT(*ppSection);

   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_PrimaryShape(Float64 Xs, SectionBias sectionBias,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);
   if ( m_Shapes.size() == 0 )
   {
      *ppShape = 0;
      return S_OK;
   }

   // this is a prismatic shape, so distAlongSegment doesn't matter
   m_Shapes.front().Shape->Clone(ppShape);

   // position the shape
   CComPtr<IPoint2d> pntTopCenter;
   GB_GetSectionLocation(this,Xs,&pntTopCenter);

   CComQIPtr<IXYPosition> position(*ppShape);
   position->put_LocatorPoint(lpTopCenter,pntTopCenter);

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

   Float64 l;
   Float64 brgOffset, endDist;
   if ( bIncludeClosure == VARIANT_TRUE )
   {
      m_pGirderLine->get_LayoutLength(&l);
      brgOffset = 0;
      endDist = 0;
   }
   else
   {
      m_pGirderLine->get_GirderLength(&l);
      m_pGirderLine->get_BearingOffset(etStart,&brgOffset);
      m_pGirderLine->get_EndDistance(etStart,&endDist);
   }

   CComPtr<IRectangle> shape;
   shape.CoCreateInstance(CLSID_Rect);
   shape->put_Height(h);
   shape->put_Width(l);

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
   topLeft->Move(brgOffset-endDist,0);
   position->put_LocatorPoint(lpTopLeft,topLeft);

   shape->QueryInterface(ppShape);

   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::putref_SuperstructureMember(ISuperstructureMember* ssMbr)
{
   CHECK_IN(ssMbr);
   m_pSSMbr = ssMbr;
   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_SuperstructureMember(ISuperstructureMember** ssMbr)
{
   CHECK_RETOBJ(ssMbr);
   if ( m_pSSMbr )
   {
      (*ssMbr) = m_pSSMbr;
      (*ssMbr)->AddRef();
   }
   else
   {
      (*ssMbr) = nullptr;
   }

   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::putref_GirderLine(IGirderLine* girderLine)
{
   CHECK_IN(girderLine);
   m_pGirderLine = girderLine;
   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_GirderLine(IGirderLine** girderLine)
{
   CHECK_RETOBJ(girderLine);
   if ( m_pGirderLine )
   {
      (*girderLine) = m_pGirderLine;
      (*girderLine)->AddRef();
   }
   else
   {
      (*girderLine) = nullptr;
   }

   return S_OK;

}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::putref_PrevSegment(ISegment* segment)
{
   CHECK_IN(segment);
   ISuperstructureMemberSegment* pMySeg = m_pPrevSegment; // weak references so no change in ref count
   m_pPrevSegment = nullptr;
   HRESULT hr = segment->QueryInterface(&m_pPrevSegment); // causes ref count to increment
   if ( FAILED(hr) )
   {
      m_pPrevSegment = pMySeg;
      return hr;
   }
   m_pPrevSegment->Release(); // need to decrement ref count causd by QueryInterface to maintain this as a weak reference
   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_PrevSegment(ISegment** segment)
{
   CHECK_RETVAL(segment);
   if ( m_pPrevSegment )
   {
      return m_pPrevSegment->QueryInterface(segment);
   }
   else
   {
      *segment = nullptr;
      return E_FAIL;
   }
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::putref_NextSegment(ISegment* segment)
{
   CHECK_IN(segment);
   ISuperstructureMemberSegment* pMySeg = m_pNextSegment; // weak references so no change in ref count
   m_pNextSegment = nullptr;
   HRESULT hr = segment->QueryInterface(&m_pNextSegment); // causes ref count to increment
   if ( FAILED(hr) )
   {
      m_pNextSegment = pMySeg;
      return hr;
   }
   m_pNextSegment->Release(); // need to decrement ref count causd by QueryInterface to maintain this as a weak reference
   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_NextSegment(ISegment** segment)
{
   CHECK_RETVAL(segment);
   if ( m_pNextSegment )
   {
      return m_pNextSegment->QueryInterface(segment);
   }
   else
   {
      *segment = nullptr;
      return E_FAIL;
   }
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::put_Orientation(Float64 orientation)
{
   m_Orientation = orientation;
   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_Orientation(Float64* orientation)
{
   CHECK_RETVAL(orientation);
   (*orientation) = m_Orientation;
   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::GetHaunchDepth(Float64* pStartVal,Float64* pMidVal,Float64* pEndVal)
{
   CHECK_RETVAL(pStartVal);
   CHECK_RETVAL(pMidVal);
   CHECK_RETVAL(pEndVal);
   *pStartVal = m_HaunchDepth[0];
   *pMidVal   = m_HaunchDepth[1];
   *pEndVal   = m_HaunchDepth[2];
   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::SetHaunchDepth(Float64 startVal,Float64 midVal,Float64 endVal)
{
   m_HaunchDepth[0] = startVal;
   m_HaunchDepth[1] = midVal;
   m_HaunchDepth[2] = endVal;
   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::ComputeHaunchDepth(Float64 distAlongSegment,Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = ::GB_GetHaunchDepth(this,distAlongSegment);
   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::put_Fillet(Float64 Fillet)
{
   m_Fillet = Fillet;
   return S_OK;
}

STDMETHODIMP CPrismaticSuperstructureMemberSegment::get_Fillet(Float64* Fillet)
{
   CHECK_RETVAL(Fillet);
   (*Fillet) = m_Fillet;
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
