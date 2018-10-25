///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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
   m_Orientation = 0;
   m_pPrevSegment = nullptr;
   m_pNextSegment = nullptr;
   return S_OK;
}

void CSegment::FinalRelease()
{
   m_Shapes.clear();
}

STDMETHODIMP CSegment::InterfaceSupportsErrorInfo(REFIID riid)
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

STDMETHODIMP CSegment::get_Length(Float64 *pVal)
{
#pragma Reminder("IMPLEMENT")
   return S_OK;
}

STDMETHODIMP CSegment::get_Section(StageIndexType stageIdx,Float64 distAlongSegment,ISection** ppSection)
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
      if ( shapeData.FGMaterial )
      {
         shapeData.FGMaterial->get_E(stageIdx,&Efg);
      }

      Float64 Ebg = 0;
      if ( shapeData.BGMaterial )
      {
         shapeData.BGMaterial->get_E(stageIdx,&Ebg);
      }

      Float64 Dfg = 0;
      if ( shapeData.FGMaterial )
      {
         shapeData.FGMaterial->get_Density(stageIdx,&Dfg);
      }

      Float64 Dbg = 0;
      if ( shapeData.BGMaterial )
      {
         shapeData.BGMaterial->get_Density(stageIdx,&Dbg);
      }

      CComPtr<IShape> shape;
      shapeData.Shape->Clone(&shape);

      // position the shape
#pragma Reminder("REVIEW - does this need to be fixed?")
      //CComPtr<IPoint2d> pntTopCenter;
      //GB_GetSectionLocation(this,distAlongSegment,&pntTopCenter);

      //CComQIPtr<IXYPosition> position(shape);
      //position->put_LocatorPoint(lpTopCenter,pntTopCenter);

      section->AddSection(shape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);
   }

   section->QueryInterface(IID_ISection,(void**)ppSection);
   ATLASSERT(*ppSection);

   return S_OK;
}

STDMETHODIMP CSegment::get_PrimaryShape(Float64 distAlongSegment,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);
   if ( m_Shapes.size() == 0 )
   {
      *ppShape = 0;
      return S_OK;
   }

   // this is a prismatic shape, so distAlongSegment doesn't matter
   m_Shapes.front().Shape->Clone(ppShape);

#pragma Reminder("REVIEW - does this need to be fixed?")
   //// position the shape
   //CComPtr<IPoint2d> pntTopCenter;
   //GB_GetSectionLocation(this,distAlongSegment,&pntTopCenter);

   //CComQIPtr<IXYPosition> position(*ppShape);
   //position->put_LocatorPoint(lpTopCenter,pntTopCenter);

   return S_OK;
}

STDMETHODIMP CSegment::putref_PrevSegment(ISegment* segment)
{
   CHECK_IN(segment);
   m_pPrevSegment = segment;
   return S_OK;
}

STDMETHODIMP CSegment::get_PrevSegment(ISegment** segment)
{
   CHECK_RETVAL(segment);
   *segment = m_pPrevSegment;
   if ( *segment )
   {
      (*segment)->AddRef();
      return S_OK;
   }

   return E_FAIL;
}

STDMETHODIMP CSegment::putref_NextSegment(ISegment* segment)
{
   CHECK_IN(segment);
   m_pNextSegment = segment;
   return S_OK;
}

STDMETHODIMP CSegment::get_NextSegment(ISegment** segment)
{
   CHECK_RETVAL(segment);
   *segment = m_pNextSegment;
   if ( *segment )
   {
      (*segment)->AddRef();
      return S_OK;
   }

   return E_FAIL;
}

////////////////////////////////////////////////////////////////////
// IPrismaticSection implementation

STDMETHODIMP CSegment::AddShape(IShape* pShape,IMaterial* pFGMaterial,IMaterial* pBGMaterial)
{
   CHECK_IN(pShape);

   ShapeData shapeData;
   shapeData.Shape = pShape;
   shapeData.FGMaterial = pFGMaterial;
   shapeData.BGMaterial = pBGMaterial;

   m_Shapes.push_back(shapeData);

   return S_OK;
}

STDMETHODIMP CSegment::get_ShapeCount(IndexType* nShapes)
{
   CHECK_RETVAL(nShapes);
   *nShapes = m_Shapes.size();
   return S_OK;
}

STDMETHODIMP CSegment::get_ForegroundMaterial(IndexType index,IMaterial* *material)
{
   if ( m_Shapes.size() <= index || index == INVALID_INDEX )
      return E_INVALIDARG;

   CHECK_RETVAL(material);
   (*material) = m_Shapes[index].FGMaterial;

   if ( *material )
      (*material)->AddRef();

   return S_OK;
}

STDMETHODIMP CSegment::get_BackgroundMaterial(IndexType index,IMaterial* *material)
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
STDMETHODIMP CSegment::AddItemData(BSTR name,IUnknown* data)
{
   return m_ItemDataMgr.AddItemData(name,data);
}

STDMETHODIMP CSegment::GetItemData(BSTR name,IUnknown** data)
{
   return m_ItemDataMgr.GetItemData(name,data);
}

STDMETHODIMP CSegment::RemoveItemData(BSTR name)
{
   return m_ItemDataMgr.RemoveItemData(name);
}

STDMETHODIMP CSegment::GetItemDataCount(CollectionIndexType* count)
{
   return m_ItemDataMgr.GetItemDataCount(count);
}

////////////////////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CSegment::Load(IStructuredLoad2* load)
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

STDMETHODIMP CSegment::Save(IStructuredSave2* save)
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
