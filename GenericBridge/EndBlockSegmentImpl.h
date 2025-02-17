///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright � 1999-2025, Washington State Department of Transportation, All Rights Reserved
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
#include <array>
#include "WBFLGenericBridge.h"
#include "ItemDataManager.h"
#include <GenericBridge\SuperstructureMemberSegmentImpl.h>


template<class T_IBeam>
class VoidedEndBlock
{
public:
   static void ModelEndBlockShape(T_IBeam* pBeam)
   {
      pBeam->put_VoidCount(0);
   }
};

template<class T_IBeam>
class OutlineEndBlock
{
public:
   static void ModelEndBlockShape(T_IBeam* pBeam)
   {
      pBeam->put_UseOutlineOnly(VARIANT_TRUE);
   }
};

/////////////////////////////////////////////////////////////////////////////
// TEndBlockSegmentImpl
//                                                             IDeckedSlabBeam
template<class T_IEndBlockSegment, class T_IBeamSection, class T_IBeam, const CLSID* T_CLSID, long T_IDR,class T_ENDBLOCK,class T_VolumeSurfaceAreaCalculator> 
class TEndBlockSegmentImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSegment,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass< TEndBlockSegmentImpl<T_IEndBlockSegment, T_IBeamSection, T_IBeam, T_CLSID, T_IDR, T_ENDBLOCK, T_VolumeSurfaceAreaCalculator>, T_CLSID>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<TEndBlockSegmentImpl<T_IEndBlockSegment, T_IBeamSection, T_IBeam, T_CLSID, T_IDR, T_ENDBLOCK, T_VolumeSurfaceAreaCalculator>, INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public T_IEndBlockSegment,
   public IItemData,
   public IStructuredStorage2
{
   friend TEndBlockSegmentImpl; // for easy cloning

protected:
   CSuperstructureMemberSegmentImpl m_Impl;
   T_VolumeSurfaceAreaCalculator m_VoidSurfaceAreaCalculator;
   friend T_VolumeSurfaceAreaCalculator;

   struct ShapeData
   {
      CComPtr<IShape> Shape;
      CComPtr<IMaterial> FGMaterial;
      CComPtr<IMaterial> BGMaterial;
   };
   std::vector<ShapeData> m_Shapes;

   bool m_bUpdateVolumeAndSurfaceArea;
   Float64 m_Volume;
   Float64 m_SurfaceArea;

   // Cached shapes in the end block and primary regions
   CComPtr<IShape> m_EndBlockShape;
   CComPtr<IShape> m_PrimaryShape;

   // index is EndType
   std::array<Float64,2> m_EndBlockLength; // length of end block from end of girder to transitation

   CItemDataManager m_ItemDataMgr;

public:
   TEndBlockSegmentImpl() : m_VoidSurfaceAreaCalculator(this)
	{
      m_bUpdateVolumeAndSurfaceArea = true;
      m_Volume = -1;
      m_SurfaceArea = -1;
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
      m_EndBlockLength[etStart] = 0;
      m_EndBlockLength[etEnd]   = 0;

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

   STDMETHOD(get_GirderShape)(Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem, IShape** ppShape)
   {
      CHECK_RETOBJ(ppShape);

      if (m_Shapes.size() == 0)
      {
         *ppShape = 0;
         return S_OK;
      }

      bool bIsInEndBlock = IsInEndBlock(Xs, sectionBias);

      CComPtr<IShape> newShape;

      // first check cached shapes
      if (bIsInEndBlock)
      {
         if (m_EndBlockShape)
         {
            m_EndBlockShape->Clone(&newShape);
         }
      }
      else
      {
         if (m_PrimaryShape)
         {
            m_PrimaryShape->Clone(&newShape);
         }
      }

      if (newShape == nullptr)
      {
         // shape is not cached... build it

         CComQIPtr<T_IBeamSection> beam(m_Shapes.front().Shape);
         ATLASSERT(beam); // if this is nullptr... how did it get in the system????

         HRESULT hr = S_OK;

         // create a new shape that is a clone of the original
         CComQIPtr<IShape> shape(beam);
         hr = shape->Clone(&newShape);

         // position the shape in girder coordiantes
         CComQIPtr<T_IBeamSection> newSection(newShape);
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance(CLSID_Point2d);
         pnt->Move(0, 0);
         CComQIPtr<IXYPosition> position(newSection);
         position->put_LocatorPoint(lpTopCenter, pnt);

         if (bIsInEndBlock)
         {
            // Section is in the end block so modify the shape for the end block region
            CComPtr<T_IBeam> newBeam;
            newSection->get_Beam(&newBeam);
            T_ENDBLOCK::ModelEndBlockShape(newBeam);

            // cache the end block shape so we don't have to compute it again
            newShape->Clone(&m_EndBlockShape);
         }
         else
         {
            // Section is in the main region... cache the shape so we don't have to compute it again
            newShape->Clone(&m_PrimaryShape);
         }

      }

      if (coordinateSystem == cstBridge)
      {
         // position the shape in bridge coordinates
         CComPtr<IPoint2d> pntTopCenter;
         GB_GetSectionLocation(this, Xs, &pntTopCenter);

         CComQIPtr<T_IBeamSection> newSection(newShape);
         CComQIPtr<IXYPosition> position(newSection);
         position->put_LocatorPoint(lpTopCenter, pntTopCenter);
      }

      *ppShape = newShape;
      (*ppShape)->AddRef();

      return S_OK;
   }

   STDMETHOD(get_Section)(StageIndexType stageIdx,Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,ISection** ppSection)
   {
      CHECK_RETOBJ(ppSection);

      if (m_Shapes.size() == 0 )
      {
         *ppSection = 0;
         return S_OK;
      }

      CComPtr<IShape> shape;
      get_GirderShape(Xs, sectionBias, coordinateSystem, &shape);

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

      section->AddSection(shape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);

      // add all the secondary shapes
      auto iter(m_Shapes.begin());
      auto end(m_Shapes.end());
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

   STDMETHOD(GetVolumeAndSurfaceArea)(Float64* pVolume, Float64* pSurfaceArea)
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
            Float64 L;
            get_Length(&L);
            std::vector<std::pair<Float64, SectionBias>> vCuts;

            vCuts.emplace_back(0.0, sbRight); // start of beam

            // left end block
            if (!IsZero(m_EndBlockLength[etStart]))
            {
               // end blocks have an abrupt change in section
               vCuts.emplace_back(m_EndBlockLength[etStart], sbLeft);
               vCuts.emplace_back(m_EndBlockLength[etStart], sbRight);
            }

            // right end block
            if (!IsZero(m_EndBlockLength[etEnd]))
            {
               // end blocks have an abrupt change in section
               vCuts.emplace_back(L - m_EndBlockLength[etEnd], sbLeft);
               vCuts.emplace_back(L - m_EndBlockLength[etEnd], sbRight);
            }

            // end of beam
            vCuts.emplace_back(L, sbLeft);

            auto iter(vCuts.begin());
            CComPtr<IShape> shape;
            get_GirderShape(iter->first, iter->second, cstGirder, &shape);
            Float64 prev_perimeter;
            shape->get_Perimeter(&prev_perimeter);
            CComPtr<IShapeProperties> shapeProps;
            shape->get_ShapeProperties(&shapeProps);
            Float64 start_area;
            shapeProps->get_Area(&start_area);
            Float64 prev_area = start_area;

            Float64 prevX = iter->first;

            Float64 V = 0;
            Float64 S = 0;

            iter++;
            auto end(vCuts.end());
            for (; iter != end; iter++)
            {
               Float64 X = iter->first;
               SectionBias bias = iter->second;

               shape.Release();
               get_GirderShape(X, bias, cstGirder, &shape);
               Float64 perimeter;
               shape->get_Perimeter(&perimeter);

               shapeProps.Release();
               shape->get_ShapeProperties(&shapeProps);
               Float64 area;
               shapeProps->get_Area(&area);

               Float64 dx = X - prevX;

               Float64 avg_perimeter = (prev_perimeter + perimeter)/* / 2*/; // save the divide by 2 for outside the loop
               Float64 avg_area = (prev_area + area) /* / 2*/; // save the divide by 2 for outside the loop

               S += avg_perimeter*dx;
               V += avg_area*dx;

               prev_perimeter = perimeter;
               prev_area = area;
               prevX = X;
            }

            // divide by 2 now
            S /= 2;
            V /= 2;

            Float64 end_area;
            shapeProps->get_Area(&end_area);
            S += start_area + end_area;

            m_Volume = V;
            m_SurfaceArea = S;
         }

         m_bUpdateVolumeAndSurfaceArea = false;
      }

      *pVolume = m_Volume;
      *pSurfaceArea = m_SurfaceArea;
      return S_OK;
   }

   STDMETHOD(get_InternalSurfaceAreaOfVoids)(Float64* pSurfaceArea) override
   {
      return m_VoidSurfaceAreaCalculator.CalculateVoidSurfaceArea(pSurfaceArea);
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
   STDMETHOD(SetHaunchDepthFunction)(/*[in]*/IHaunchDepthFunction* pFunction) override { return m_Impl.SetHaunchDepthFunction(pFunction); }
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

      m_bUpdateVolumeAndSurfaceArea = true;
      m_Volume = -1;
      m_SurfaceArea = -1;

      m_EndBlockShape.Release();
      m_PrimaryShape.Release();

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

   STDMETHOD(GetItemDataCount)(IndexType* count) override
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

