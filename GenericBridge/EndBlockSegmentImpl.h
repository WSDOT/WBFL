///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2019, Washington State Department of Transportation, All Rights Reserved
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

// TEndBlockSegmentImpl.h : Declaration of the CSegment

#pragma once

#include "stdafx.h"
#include "resource.h"       // main symbols
#include <MathEx.h>
#include "WBFLGenericBridge.h"
#include "ItemDataManager.h"
#include "SuperstructureMemberSegmentImpl.h"


template<class T_IBeam>
class VoidedEndBlock
{
public:
   static void InEndBlock(T_IBeam* pBeam)
   {
      pBeam->put_VoidCount(0);
   }
};

template<class T_IBeam>
class OutlineEndBlock
{
public:
   static void InEndBlock(T_IBeam* pBeam)
   {
      pBeam->put_UseOutlineOnly(VARIANT_TRUE);
   }
};

/////////////////////////////////////////////////////////////////////////////
// TEndBlockSegmentImpl
//                                                             IDeckedSlabBeam
template<class T_IEndBlockSegment, class T_IBeamSection, class T_IBeam, const CLSID* T_CLSID, long T_IDR,class T_ENDBLOCK> 
class TEndBlockSegmentImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSegment,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass< TEndBlockSegmentImpl<T_IEndBlockSegment, T_IBeamSection, T_IBeam, T_CLSID, T_IDR, T_ENDBLOCK>, T_CLSID>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<TEndBlockSegmentImpl<T_IEndBlockSegment, T_IBeamSection, T_IBeam, T_CLSID, T_IDR, T_ENDBLOCK>, INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public T_IEndBlockSegment,
   public IItemData,
   public IStructuredStorage2
{
   friend TEndBlockSegmentImpl; // for easy cloning

private:
   CSuperstructureMemberSegmentImpl m_Impl;

   struct ShapeData
   {
      CComPtr<IShape> Shape;
      CComPtr<IMaterial> FGMaterial;
      CComPtr<IMaterial> BGMaterial;
   };
   std::vector<ShapeData> m_Shapes;

   // index is EndType
   Float64 m_EndBlockLength[2]; // length of end block from end of girder to transitation

   CItemDataManager m_ItemDataMgr;

public:
   TEndBlockSegmentImpl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(T_IDR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(TEndBlockSegmentImpl)
	COM_INTERFACE_ENTRY(T_IEndBlockSegment)
   COM_INTERFACE_ENTRY(ISuperstructureMemberSegment)
	COM_INTERFACE_ENTRY(ISegment)
	COM_INTERFACE_ENTRY(IItemData)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

public:
   HRESULT FinalConstruct()
   {
      m_EndBlockLength[etStart]           = 0;
      m_EndBlockLength[etEnd]             = 0;

      return S_OK;
   }

   void FinalRelease()
   {
      m_Shapes.clear();
   }

// ISupportsErrorInfo
public:
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override
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

// ISuperstructureMemberSegment
public:
   STDMETHOD(putref_SuperstructureMember)(ISuperstructureMember* ssMbr) override { return m_Impl.putref_SuperstructureMember(ssMbr); }
   STDMETHOD(get_SuperstructureMember)(ISuperstructureMember** ssMbr) override { return m_Impl.get_SuperstructureMember(ssMbr); }
   STDMETHOD(putref_GirderLine)(IGirderLine* girderLine) override { return m_Impl.putref_GirderLine(girderLine); }
   STDMETHOD(get_GirderLine)(IGirderLine** girderLine) override { return m_Impl.get_GirderLine(girderLine); }
   STDMETHOD(putref_PrevSegment)(ISegment* segment) override { return m_Impl.putref_PrevSegment(segment); }
   STDMETHOD(get_PrevSegment)(ISegment** segment) override { return m_Impl.get_PrevSegment(segment); }
   STDMETHOD(putref_NextSegment)(ISegment* segment) override { return m_Impl.putref_NextSegment(segment); }
   STDMETHOD(get_NextSegment)(ISegment** segment) override { return m_Impl.get_NextSegment(segment); }

   bool IsInEndBlock(Float64 Xs, SectionBias sectionBias)
   {
      Float64 length;
      get_Length(&length);


      if (
         (0.0 < m_EndBlockLength[etStart] && (sectionBias == sbLeft ? IsLE(Xs, m_EndBlockLength[etStart]) : IsLT(Xs, m_EndBlockLength[etStart]))) ||
         (0.0 < m_EndBlockLength[etEnd] && (sectionBias == sbLeft ? IsLT(length - Xs, m_EndBlockLength[etEnd]) : IsLE(length - Xs, m_EndBlockLength[etEnd])))
         )
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   STDMETHOD(get_Section)(StageIndexType stageIdx,Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,ISection** ppSection)
   {
      CHECK_RETOBJ(ppSection);

      if (m_Shapes.size() == 0 )
      {
         *ppSection = 0;
         return S_OK;
      }

      CComQIPtr<T_IBeamSection> beam(m_Shapes.front().Shape);
      ATLASSERT(beam); // if this is nullptr... how did it get in the system????

      // This object reprsents a prismatic shape... all sections are the same
      HRESULT hr = S_OK;

      // create a new shape that is a clone of the original
      CComQIPtr<IShape> shape(beam);
      CComPtr<IShape> newShape;
      hr = shape->Clone(&newShape);

      // set the dimensions
      CComQIPtr<T_IBeamSection> newSection(newShape);
      CComPtr<T_IBeam> newBeam;
      newSection->get_Beam(&newBeam);

      Float64 length;
      get_Length(&length);

      // Section is in the end block so use the outline of the shape only
      if ( IsInEndBlock(Xs,sectionBias) )
      {
         T_ENDBLOCK::InEndBlock(newBeam);;
      }

      // position the shape
      if (coordinateSystem == cstBridge)
      {
         CComPtr<IPoint2d> pntTopCenter;
         GB_GetSectionLocation(this, Xs, &pntTopCenter);

         CComQIPtr<IXYPosition> position(newSection);
         position->put_LocatorPoint(lpTopCenter, pntTopCenter);
      }
      else
      {
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance(CLSID_Point2d);
         pnt->Move(0, 0);
         CComQIPtr<IXYPosition> position(newSection);
         position->put_LocatorPoint(lpTopCenter, pnt);
      }

      CComPtr<ICompositeSectionEx> section;
      section.CoCreateInstance(CLSID_CompositeSectionEx);

      section->QueryInterface(IID_ISection,(void**)ppSection);
      ATLASSERT(*ppSection != nullptr);

      // add the primary shape
      Float64 Efg = 0;
      m_Shapes.front().FGMaterial->get_E(stageIdx,&Efg);
      
      Float64 Ebg = 0;
      if ( m_Shapes.front().BGMaterial )
      {
         m_Shapes.front().BGMaterial->get_E(stageIdx,&Ebg);
      }

      Float64 Dfg = 0;
      m_Shapes.front().FGMaterial->get_Density(stageIdx,&Dfg);
      
      Float64 Dbg = 0;
      if ( m_Shapes.front().BGMaterial )
      {
         m_Shapes.front().BGMaterial->get_Density(stageIdx,&Dbg);
      }

      section->AddSection(newShape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);

      // add all the secondary shapes
      std::vector<ShapeData>::iterator iter(m_Shapes.begin());
      std::vector<ShapeData>::iterator end(m_Shapes.end());
      iter++; // skip the first shape, we already processed it

      for ( ; iter != end; iter++ )
      {
         ShapeData& shapeData = *iter;

         Float64 Efg = 0;
         if ( shapeData.FGMaterial )
         {
            shapeData.FGMaterial->get_E(stageIdx,&Efg);
         }

         Float64 Ebg;
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

         section->AddSection(shape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);
      }

      return S_OK;
   }

   STDMETHOD(get_PrimaryShape)(Float64 Xs,SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem, IShape** ppShape)
   {
      CHECK_RETOBJ(ppShape);

      if (m_Shapes.size() == 0 )
      {
         *ppShape = 0;
         return S_OK;
      }

      CComQIPtr<T_IBeamSection> beam(m_Shapes.front().Shape);
      ATLASSERT(beam); // if this is nullptr... how did it get in the system????

      // This object reprsents a prismatic shape... all sections are the same
      HRESULT hr = S_OK;

      // create a new shape that is a clone of the original
      CComQIPtr<IShape> shape(beam);
      CComPtr<IShape> newShape;
      hr = shape->Clone(&newShape);

      // set the dimensions
      CComQIPtr<T_IBeamSection> newSection(newShape);
      CComPtr<T_IBeam> newBeam;
      newSection->get_Beam(&newBeam);

      Float64 length;
      get_Length(&length);

      // Section is in the end block so use the outline of the shape only
      if (IsInEndBlock(Xs, sectionBias))
      {
         T_ENDBLOCK::InEndBlock(newBeam);;
      }

      // position the shape
      if (coordinateSystem == cstBridge)
      {
         CComPtr<IPoint2d> pntTopCenter;
         GB_GetSectionLocation(this, Xs, &pntTopCenter);

         CComQIPtr<IXYPosition> position(newSection);
         position->put_LocatorPoint(lpTopCenter, pntTopCenter);
      }
      else
      {
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance(CLSID_Point2d);
         pnt->Move(0, 0);
         CComQIPtr<IXYPosition> position(newSection);
         position->put_LocatorPoint(lpTopCenter, pnt);
      }

      *ppShape = newShape;
      (*ppShape)->AddRef();

      return S_OK;
   }

   STDMETHOD(get_Profile)(VARIANT_BOOL bIncludeClosure,IShape** ppShape) override
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
            Float64 y = m_Impl.ComputePrecamber(x, Ls);
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
            Float64 y = m_Impl.ComputePrecamber(x, Ls) + h;
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

   STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal) override { return m_Impl.get_Length(pVal); }
   STDMETHOD(get_LayoutLength)(/*[out, retval]*/ Float64 *pVal) override { return m_Impl.get_LayoutLength(pVal); }
   STDMETHOD(put_Orientation)(/*[in]*/Float64 orientation) override { return m_Impl.put_Orientation(orientation); }
   STDMETHOD(get_Orientation)(/*[out,retval]*/Float64* orientation) override { return m_Impl.get_Orientation(orientation); }
   STDMETHOD(GetHaunchDepth)(Float64* pStartVal, Float64* pMidVal, Float64* pEndVal) override { return m_Impl.GetHaunchDepth(pStartVal, pMidVal, pEndVal); }
   STDMETHOD(SetHaunchDepth)(Float64 startVal, Float64 midVal, Float64 endVal) override { return m_Impl.SetHaunchDepth(startVal, midVal, endVal); }
   STDMETHOD(ComputeHaunchDepth)(Float64 distAlongSegment, Float64* pVal) override { return m_Impl.ComputeHaunchDepth(distAlongSegment, pVal); }
   STDMETHOD(put_Fillet)(/*[in]*/Float64 Fillet) override { return m_Impl.put_Fillet(Fillet); }
   STDMETHOD(get_Fillet)(/*[out,retval]*/Float64* Fillet) override { return m_Impl.get_Fillet(Fillet); }
   STDMETHOD(put_FilletShape)(/*[in]*/FilletShape FilletShape) override { return m_Impl.put_FilletShape(FilletShape); }
   STDMETHOD(get_FilletShape)(/*[out,retval]*/FilletShape* FilletShape) override { return m_Impl.get_FilletShape(FilletShape); }
   STDMETHOD(put_Precamber)(/*[in]*/Float64 precamber) override { return m_Impl.put_Precamber(precamber); }
   STDMETHOD(get_Precamber)(/*[out,retval]*/Float64* pPrecamber) override { return m_Impl.get_Precamber(pPrecamber); }
   STDMETHOD(ComputePrecamber)(/*[in]*/Float64 distAlongSegment, /*[out,retval]*/Float64* pPrecamber) override { return m_Impl.ComputePrecamber(distAlongSegment, pPrecamber); }

// Functions to fulfill local class declaration
public:
	STDMETHOD(AddShape)(IShape* pShape,IMaterial* pFGMaterial,IMaterial* pBGMaterial) override
   {
      CHECK_IN(pShape);
      if ( m_Shapes.size() == 0 )
      {
         CComQIPtr<T_IBeamSection> beam(pShape);
         if ( beam == nullptr )
         {
            ATLASSERT(false); // first shape must implement the T_IBeamSection interfvace
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

   STDMETHOD(get_ShapeCount)(IndexType* nShapes) override
   {
      CHECK_RETVAL(nShapes);
      *nShapes = m_Shapes.size();
      return S_OK;
   }

   STDMETHOD(get_ForegroundMaterial)(IndexType index,IMaterial* *material) override
   {
      if ( m_Shapes.size() <= index || index == INVALID_INDEX )
      {
         return E_INVALIDARG;
      }

      CHECK_RETVAL(material);
      (*material) = m_Shapes[index].FGMaterial;

      if ( *material )
      {
         (*material)->AddRef();
      }

      return S_OK;
   }

   STDMETHOD(get_BackgroundMaterial)(IndexType index,IMaterial* *material) override
   {
      if ( m_Shapes.size() <= index || index == INVALID_INDEX )
      {
         return E_INVALIDARG;
      }

      CHECK_RETVAL(material);
      (*material) = m_Shapes[index].BGMaterial;

      if ( *material )
      {
         (*material)->AddRef();
      }

      return S_OK;
   }

   STDMETHOD(put_EndBlockLength)(/*[in]*/EndType endType,/*[in]*/ Float64 length) override
   {
      m_EndBlockLength[endType] = length;
      return S_OK;
   }

   STDMETHOD(get_EndBlockLength)(/*[in]*/EndType endType,/*[out,retval]*/ Float64* pLength) override
   {
      *pLength = m_EndBlockLength[endType];
      return S_OK;
   }

// IItemData
public:
   STDMETHOD(AddItemData)(BSTR name,IUnknown* data) override
   {
      return m_ItemDataMgr.AddItemData(name,data);
   }

   STDMETHOD(GetItemData)(BSTR name,IUnknown** data) override
   {
      return m_ItemDataMgr.GetItemData(name,data);
   }

   STDMETHOD(RemoveItemData)(BSTR name) override
   {
      return m_ItemDataMgr.RemoveItemData(name);
   }

   STDMETHOD(GetItemDataCount)(CollectionIndexType* count) override
   {
      return m_ItemDataMgr.GetItemDataCount(count);
   }

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override
   {
      return E_NOTIMPL;
   }

	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override
   {
      return E_NOTIMPL;
   }
};

