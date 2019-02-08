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

// SplicedGirderSegmentImpl.h : Declaration of the ISplicedGirderSegmentImpl

#pragma once

#include "resource.h"       // main symbols
#include "ItemDataManager.h"
#include "SuperstructureMemberSegmentImpl.h"

#include <GenericBridge\Helpers.h>

#include <Math\CompositeFunction2d.h>
#include <Math\LinFunc2d.h>
#include <Math\MathUtils.h>

#include <algorithm>
#include <array>


inline bool IsParabolicVariation(SegmentVariationType variationType)
{
   return (variationType == svtParabolic || variationType == svtDoubleParabolic ? true : false);
}


/////////////////////////////////////////////////////////////////////////////
// ISplicedGirderSegmentImpl
template <class T,class T_IBeamSection>
class ATL_NO_VTABLE ISplicedGirderSegmentImpl :
   public ISplicedGirderSegment,
	public ISupportErrorInfo,
   public IItemData,
   public IStructuredStorage2
{
public:
   ISplicedGirderSegmentImpl()
   {
      m_EndBlockLength[etStart]           = 0;
      m_EndBlockLength[etEnd]             = 0;
      m_EndBlockTransitionLength[etStart] = 0;
      m_EndBlockTransitionLength[etEnd]   = 0;
      m_EndBlockWidth[etStart]            = 0;
      m_EndBlockWidth[etEnd]              = 0;

      for ( int i = 0; i < 4; i++ )
      {
         m_VariationLength[i] = 0;
         m_VariationHeight[i] = 0;
         m_VariationBottomFlangeDepth[i] = 0;
      }
      
      m_bSegmentRange = false;
      m_XgpStart = DBL_MAX;
      m_XgpEnd = -DBL_MAX;

      m_ClosureJointFgMaterial[etStart] = nullptr;
      m_ClosureJointFgMaterial[etEnd]   = nullptr;

      m_ClosureJointBgMaterial[etStart] = nullptr;
      m_ClosureJointBgMaterial[etEnd]   = nullptr;
   }

protected:
   CSuperstructureMemberSegmentImpl m_Impl;

   struct ShapeData
   {
      CComPtr<IShape> Shape;
      CComPtr<IMaterial> FGMaterial;
      CComPtr<IMaterial> BGMaterial;
   };
   std::vector<ShapeData> m_Shapes;

   CItemDataManager m_ItemDataMgr;

   // cached segment range values
   bool m_bSegmentRange;
   Float64 m_XgpStart;
   Float64 m_XgpEnd;

   // index is EndType
   std::array<Float64, 2> m_EndBlockLength; // length of end block from end of girder to transitation
   std::array<Float64, 2> m_EndBlockTransitionLength; // length of transition
   std::array<Float64, 2> m_EndBlockWidth; // width of end block at end of girder... constant until transition
                               // then transitions to the section

   SegmentVariationType m_VariationType;
   std::array<Float64, 4> m_VariationLength; // index is the SegmentZoneType enum
   std::array<Float64, 4> m_VariationHeight;
   std::array<Float64, 4> m_VariationBottomFlangeDepth;

   // index is EndType
   std::array<CComPtr<IMaterial>, 2> m_ClosureJointFgMaterial; // foreground material
   std::array<CComPtr<IMaterial>, 2> m_ClosureJointBgMaterial; // background material

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override
   {
	   static const IID* arr[] = 
	   {
		   &IID_ISegment,
		   &IID_ISplicedGirderSegment,
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

	STDMETHOD(get_Section)(StageIndexType stageIdx,Float64 Xs,SectionBias sectionBias,ISection** ppSection) override
   {
      return GetSection(stageIdx,Xs,sectionBias,ppSection);
   }

	STDMETHOD(get_PrimaryShape)(Float64 Xs,SectionBias sectionBias,IShape** ppShape) override
   {
      return GetPrimaryShape(Xs,sectionBias,ppShape);
   }

   STDMETHOD(get_Profile)(VARIANT_BOOL bIncludeClosure,IShape** ppShape) override
   {
      CComPtr<IPolyShape> polyShape;
      polyShape.CoCreateInstance(CLSID_PolyShape);

      std::vector<Float64> xValues;
      GetProfilePointLocations(bIncludeClosure, VARIANT_FALSE, &xValues); // want girder path coordinates

      for ( const auto Xgp: xValues)
      {
         Float64 Xs = ConvertToSegmentCoordinate(Xgp);
         Float64 H = GetSectionDepth(Xs);
         polyShape->AddPoint(Xgp,-H);
      }

      // points across the top of the segment
      polyShape->AddPoint(xValues.back(),0);
      polyShape->AddPoint(xValues.front(),0);

      polyShape->get_Shape(ppShape);

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

// ISplicedGirderSegment
public:
	STDMETHOD(AddShape)(IShape* pShape,IMaterial* pFGMaterial,IMaterial* pBGMaterial) override
   {
      CHECK_IN(pShape);
      if ( m_Shapes.size() == 0 )
      {
         CComQIPtr<T_IBeamSection> beam(pShape);
         if ( beam == nullptr )
         {
            ATLASSERT(false); // first shape must implement the IFlangedSplicedGirderSegment interfvace
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
         return E_INVALIDARG;

      CHECK_RETVAL(material);
      (*material) = m_Shapes[index].FGMaterial;

      if ( *material )
         (*material)->AddRef();

      return S_OK;
   }

   STDMETHOD(get_BackgroundMaterial)(IndexType index,IMaterial* *material) override
   {
      if (m_Shapes.size() <= index || index == INVALID_INDEX)
      {
         return E_INVALIDARG;
      }

      CHECK_RETVAL(material);
      (*material) = m_Shapes[index].BGMaterial;

      if (*material)
      {
         (*material)->AddRef();
      }

      return S_OK;
   }

   STDMETHOD(put_EndBlockLength)(EndType endType,Float64 length) override
   {
      m_EndBlockLength[endType] = length;
      return S_OK;
   }

   STDMETHOD(get_EndBlockLength)(EndType endType,Float64* pLength) override
   {
      *pLength = m_EndBlockLength[endType];
      return S_OK;
   }

   STDMETHOD(put_EndBlockTransitionLength)(EndType endType,Float64 length) override
   {
      m_EndBlockTransitionLength[endType] = length;
      return S_OK;
   }

   STDMETHOD(get_EndBlockTransitionLength)(EndType endType,Float64* pLength) override
   {
      *pLength = m_EndBlockTransitionLength[endType];
      return S_OK;
   }

   STDMETHOD(put_EndBlockWidth)(EndType endType,Float64 width) override
   {
      m_EndBlockWidth[endType] = width;
      return S_OK;
   }

   STDMETHOD(get_EndBlockWidth)(EndType endType,Float64* pWidth) override
   {
      *pWidth = m_EndBlockWidth[endType];
      return S_OK;
   }

   STDMETHOD(put_VariationType)(SegmentVariationType variationType) override
   {
      m_VariationType = variationType;
      return S_OK;
   }

   STDMETHOD(get_VariationType)(SegmentVariationType* variationType) override
   {
      CHECK_RETVAL(variationType);
      *variationType = m_VariationType;
      return S_OK;
   }

   STDMETHOD(SetVariationParameters)(SegmentZoneType zone,Float64 length,Float64 height,Float64 bottomFlangeDepth) override
   {
      m_VariationLength[zone] = length;
      m_VariationHeight[zone] = height;
      m_VariationBottomFlangeDepth[zone] = bottomFlangeDepth;
      return S_OK;
   }

   STDMETHOD(GetVariationParameters)(SegmentZoneType zone,Float64* length,Float64* height,Float64* bottomFlangeDepth) override
   {
      CHECK_RETVAL(length);
      CHECK_RETVAL(height);
      CHECK_RETVAL(bottomFlangeDepth);

      *length = m_VariationLength[zone];
      *height = m_VariationHeight[zone];
      *bottomFlangeDepth = m_VariationBottomFlangeDepth[zone];
      return S_OK;
   }

   STDMETHOD(GetSegmentHeight)(Float64 Xs,Float64* pHeight) override
   {
      CHECK_RETVAL(pHeight);
      *pHeight = GetSectionDepth(Xs);
      return S_OK;
   }

   STDMETHOD(get_BottomFlangeProfile)(IPoint2dCollection** ppPoints) override
   {
      CHECK_RETOBJ(ppPoints);
      CComPtr<IPoint2dCollection> points;
      points.CoCreateInstance(CLSID_Point2dCollection);

      std::vector<Float64> xValues;
      GetProfilePointLocations(VARIANT_FALSE, VARIANT_FALSE, &xValues); // exclude closure, want girder path coordinates

      for (const auto Xgp : xValues)
      {
         Float64 Xs = ConvertToSegmentCoordinate(Xgp);
         Float64 section_depth = GetSectionDepth(Xs);
         Float64 bottom_flange_height = GetBottomFlangeHeight(Xs);
         Float64 y = section_depth - bottom_flange_height;

         CComPtr<IPoint2d> point;
         point.CoCreateInstance(CLSID_Point2d);
         point->Move(Xgp,-y);
         points->Add(point);
      }
      points.CopyTo(ppPoints);

      return S_OK;
   }

   STDMETHOD(GetProfileControlPoints)(VARIANT_BOOL bIncludeClosure, VARIANT_BOOL bSegmentCoordinates, IDblArray** ppArray) override
   {
      CHECK_RETOBJ(ppArray);
      std::vector<Float64> xValues;
      GetProfilePointLocations(bIncludeClosure, bSegmentCoordinates, &xValues);

      CComPtr<IDblArray> array;
      array.CoCreateInstance(CLSID_DblArray);
      for (const auto& x : xValues)
      {
         array->Add(x);
      }

      return array.CopyTo(ppArray);
   }

   STDMETHOD(get_ClosureJointLength)(/*[in]*/EndType endType,/*[out,retval]*/Float64* pLength) override
   {
      CHECK_RETVAL(pLength);

      if ( (m_Impl.m_pPrevSegment == nullptr && endType == etStart) || (m_Impl.m_pNextSegment == nullptr && endType == etEnd) )
      {
         // if this the start of the first segment or the end of the last segment there there isn't a closure
         *pLength = 0;
         return S_OK;
      }

      CComPtr<IGirderLine> girderLine;
      get_GirderLine(&girderLine);

      Float64 end_distance, bearing_offset;
      girderLine->get_EndDistance(endType,&end_distance);
      girderLine->get_BearingOffset(endType,&bearing_offset);
      *pLength = bearing_offset - end_distance;
      return S_OK;
   }

   STDMETHOD(put_ClosureJointForegroundMaterial)(/*[in]*/EndType endType,/*[in]*/IMaterial* pFGMaterial) override
   {
      CHECK_IN(pFGMaterial);
      m_ClosureJointFgMaterial[endType] = pFGMaterial;
      return S_OK;
   }

   STDMETHOD(get_ClosureJointForegroundMaterial)(/*[in]*/EndType endType,/*[out,retval]*/IMaterial** ppFGMaterial) override
   {
      CHECK_RETOBJ(ppFGMaterial);
      m_ClosureJointFgMaterial[endType].CopyTo(ppFGMaterial);
      return S_OK;
   }

   STDMETHOD(put_ClosureJointBackgroundMaterial)(/*[in]*/EndType endType,/*[in]*/IMaterial* pBGMaterial) override
   {
      CHECK_IN(pBGMaterial);
      m_ClosureJointBgMaterial[endType] = pBGMaterial;
      return S_OK;
   }

   STDMETHOD(get_ClosureJointBackgroundMaterial)(/*[in]*/EndType endType,/*[out,retval]*/IMaterial** ppBGMaterial) override
   {
      CHECK_RETOBJ(ppBGMaterial);
      m_ClosureJointBgMaterial[endType].CopyTo(ppBGMaterial);
      return S_OK;
   }

// IItemData
public:
   STDMETHOD(AddItemData)(/*[in]*/BSTR name,/*[in]*/IUnknown* data) override
   {
      return m_ItemDataMgr.AddItemData(name,data);
   }

   STDMETHOD(GetItemData)(/*[in]*/BSTR name,/*[out,retval]*/IUnknown** data) override
   {
      return m_ItemDataMgr.GetItemData(name,data);
   }

   STDMETHOD(RemoveItemData)(/*[in]*/BSTR name) override
   {
      return m_ItemDataMgr.RemoveItemData(name);
   }

   STDMETHOD(GetItemDataCount)(/*[out,retval]*/CollectionIndexType* count) override
   {
      return m_ItemDataMgr.GetItemDataCount(count);
   }

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override
   {
      ATLASSERT(false);
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

	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override
   {
      ATLASSERT(false);
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

protected:
   virtual HRESULT GetPrimaryShape(Float64 Xs, SectionBias sectionBias,IShape** ppShape) = 0;

   virtual HRESULT GetSection(StageIndexType stageIdx,Float64 Xs, SectionBias sectionBias,ISection** ppSection)
   {
      CHECK_RETOBJ(ppSection);

      if (m_Shapes.size() == 0 )
      {
         *ppSection = 0;
         return S_OK;
      }

      HRESULT hr;
      CComPtr<IShape> primaryShape;
      hr = GetPrimaryShape(Xs,sectionBias,&primaryShape);
      ATLASSERT(SUCCEEDED(hr));
      if ( FAILED(hr) )
         return hr;

      // create our section object
      CComPtr<ICompositeSectionEx> section;
      section.CoCreateInstance(CLSID_CompositeSectionEx);

      section->QueryInterface(IID_ISection,(void**)ppSection);
      ATLASSERT(*ppSection != nullptr);

      int isClosureJoint = IsClosureJoint(Xs);

      // add the primary shape
      Float64 Efg = 0;
      if ( isClosureJoint == 0 )
      {
         m_Shapes.front().FGMaterial->get_E(stageIdx,&Efg);
      }
      else
      {
         EndType endType(isClosureJoint < 0 ? etStart : etEnd);
         if ( m_ClosureJointFgMaterial[endType] == nullptr )
         {
            m_Shapes.front().FGMaterial->get_E(stageIdx,&Efg);
         }
         else
         {
            m_ClosureJointFgMaterial[endType]->get_E(stageIdx,&Efg);
         }
      }
      
      Float64 Ebg = 0;
      if ( isClosureJoint == 0 )
      {
         if ( m_Shapes.front().BGMaterial )
         {
            m_Shapes.front().BGMaterial->get_E(stageIdx,&Ebg);
         }
      }
      else
      {
         EndType endType(isClosureJoint < 0 ? etStart : etEnd);
         if ( m_ClosureJointBgMaterial[endType] )
         {
            m_ClosureJointBgMaterial[endType]->get_E(stageIdx,&Ebg);
         }
      }

      Float64 Dfg = 0;
      if ( isClosureJoint == 0 )
      {
         m_Shapes.front().FGMaterial->get_Density(stageIdx,&Dfg);
      }
      else
      {
         EndType endType(isClosureJoint < 0 ? etStart : etEnd);
         if ( m_ClosureJointFgMaterial[endType] == nullptr )
         {
            m_Shapes.front().FGMaterial->get_Density(stageIdx,&Dfg);
         }
         else
         {
            m_ClosureJointFgMaterial[endType]->get_Density(stageIdx,&Dfg);
         }
      }
      
      Float64 Dbg = 0;
      if ( isClosureJoint == 0 )
      {
         if ( m_Shapes.front().BGMaterial )
         {
            m_Shapes.front().BGMaterial->get_Density(stageIdx,&Dbg);
         }
      }
      else
      {
         EndType endType(isClosureJoint < 0 ? etStart : etEnd);
         if ( m_ClosureJointBgMaterial[endType] )
         {
            m_ClosureJointBgMaterial[endType]->get_Density(stageIdx,&Dbg);
         }
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

   int IsClosureJoint(Float64 Xs)
   {
      CComPtr<IGirderLine> girderLine;
      get_GirderLine(&girderLine);

      Float64 segment_length;
      girderLine->get_GirderLength(&segment_length);

      if ( ::InRange(0.0,Xs,segment_length) )
      {
         return 0; 
      }

      if ( Xs < 0.0 )
      {
         return -1; // Xs is in the start closure
      }

      if ( segment_length < Xs )
      {
         return 1; // Xs is in the end closure
      }
 
      ATLASSERT(false); // should not get here
      return 0; // Xs is not in a closure
   }

   std::array<Float64, 4> GetTransitionPoints()
   {
      Float64 Lg;
      get_Length(&Lg);

      std::array<Float64, 4> X;

      if (m_VariationType == svtNone)
      {
         X[ZoneBreakType::Start] = 0;
         X[ZoneBreakType::LeftBreak] = Lg / 2;
         X[ZoneBreakType::RightBreak] = Lg / 2;
         X[ZoneBreakType::End] = Lg;
      }
      else if (m_VariationType == svtLinear)
      {
         X[ZoneBreakType::Start] = m_VariationLength[ZoneBreakType::Start];
         X[ZoneBreakType::LeftBreak] = Lg / 2;
         X[ZoneBreakType::RightBreak] = Lg / 2;
         X[ZoneBreakType::End] = Lg - m_VariationLength[ZoneBreakType::End];
      }
      else
      {
         X[ZoneBreakType::Start] = m_VariationLength[ZoneBreakType::Start];
         X[ZoneBreakType::LeftBreak] = m_VariationLength[ZoneBreakType::Start] + m_VariationLength[ZoneBreakType::LeftBreak];
         X[ZoneBreakType::RightBreak] = Lg - m_VariationLength[ZoneBreakType::RightBreak] - m_VariationLength[ZoneBreakType::End];
         X[ZoneBreakType::End] = Lg - m_VariationLength[ZoneBreakType::End];
      }

      return X;
   }

   Float64 GetSectionDepth(Float64 Xs)
   {
      Float64 Lg;
      get_Length(&Lg);

      bool bParabolas = IsParabolicVariation(m_VariationType);

      std::array<Float64, 4> X = GetTransitionPoints();
      Float64 Xl, Yl, Xr, Yr;
      ZoneType zone = ::GetControlPoints(Xs, Lg, X, m_VariationHeight, &Xl, &Yl, &Xr, &Yr);
      Float64 H = ::GetSectionDepth(Xs, Xl, Yl, Xr, Yr, TransitionTypeFromZone(zone, bParabolas));
      return H;
   }

   Float64 GetBottomFlangeHeight(Float64 Xs)
   {
      Float64 Lg;
      get_Length(&Lg);

      bool bParabolas = IsParabolicVariation(m_VariationType);

      std::array<Float64, 4> X = GetTransitionPoints();
      Float64 Xl, Yl, Xr, Yr;
      ZoneType zone = ::GetControlPoints(Xs, Lg, X, m_VariationBottomFlangeDepth, &Xl, &Yl, &Xr, &Yr);
      Float64 H = ::GetSectionDepth(Xs, Xl, Yl, Xr, Yr, TransitionTypeFromZone(zone, bParabolas));
      return H;
   }
   
   Float64 ConvertToSegmentPathCoordinate(Float64 Xs)
   {
      CComPtr<IGirderLine> girderLine;
      get_GirderLine(&girderLine);
      Float64 brgOffset, endDist;
      girderLine->get_BearingOffset(etStart,&brgOffset);
      girderLine->get_EndDistance(etStart,&endDist);
      Float64 offset = brgOffset - endDist;
      Float64 Xsp = Xs + offset;
      return Xsp;
   }

   Float64 ConvertToSegmentCoordinate(Float64 Xgp)
   {
      Float64 XgpStart, XgpEnd;
      GetSegmentRange(&XgpStart,&XgpEnd);
      Float64 Xsp = Xgp - XgpStart;
      CComPtr<IGirderLine> girderLine;
      get_GirderLine(&girderLine);
      Float64 brgOffset, endDist;
      girderLine->get_BearingOffset(etStart,&brgOffset);
      girderLine->get_EndDistance(etStart,&endDist);
      Float64 offset = brgOffset - endDist;
      Float64 Xs = Xsp - offset;
      return Xs;
   }

   void GetSegmentRange(Float64* pXgpStart,Float64* pXgpEnd)
   {
      if (m_bSegmentRange)
      {
         *pXgpStart = m_XgpStart;
         *pXgpEnd = m_XgpEnd;
         return;
      }

      // Returns the start and end of the segment in Girder Path Coordinates.
      // This is the start/end of the segment path coordinate system in
      // girder path coordinates

      *pXgpStart = 0; // start at zero

      // sum the layout length of all the previous segments
      CComPtr<ISegment> segment;
      get_PrevSegment(&segment);
      CComQIPtr<ISuperstructureMemberSegment> prevSegment(segment);
      while ( prevSegment )
      {
         CComPtr<IGirderLine> girderLine;
         prevSegment->get_GirderLine(&girderLine);

         Float64 layout_length;
         girderLine->get_LayoutLength(&layout_length);

         *pXgpStart += layout_length;

         CComPtr<ISegment> s;
         prevSegment->get_PrevSegment(&s);
         prevSegment.Release();
         prevSegment = s;
      }

      // locate end of range
      CComPtr<IGirderLine> girderLine;
      get_GirderLine(&girderLine);

      Float64 layout_length;
      girderLine->get_LayoutLength(&layout_length);
      *pXgpEnd = *pXgpStart + layout_length;

      m_XgpStart = *pXgpStart;
      m_XgpEnd = *pXgpEnd;
   }


   void GetProfilePointLocations(VARIANT_BOOL bIncludeClosure, VARIANT_BOOL bSegmentCoordinates, std::vector<Float64>* pvXvalues)
   {
      pvXvalues->clear();
      pvXvalues->reserve(20);

      // Start and end of the segment in Girder Path Coordinates
      Float64 xStart, xEnd;
      if (bSegmentCoordinates == VARIANT_FALSE)
      {
         // we are working in girder path coordinates so get the
         // start and end in this coordinate system
         GetSegmentRange(&xStart, &xEnd);
      }
      else
      {
         xStart = 0;
         get_Length(&xEnd);
      }
      Float64 xStartSegment = xStart;
      Float64 xEndSegment = xEnd;

      // if the closure joints are not to be included in the profile
      // move the start and end locations to the face of the segment
      Float64 leftClosureAdj(0); // the left/right prismatic variation length are measured from the CL Closure... when skipping the closure, an adjustment is required
      Float64 rightClosureAdj(0);
      CComPtr<IGirderLine> girderLine;
      get_GirderLine(&girderLine);
      Float64 brgOffset, endDist;
      girderLine->get_BearingOffset(etStart, &brgOffset);
      girderLine->get_EndDistance(etStart, &endDist);
      leftClosureAdj = (brgOffset - endDist);

      girderLine->get_BearingOffset(etEnd, &brgOffset);
      girderLine->get_EndDistance(etEnd, &endDist);
      rightClosureAdj = (brgOffset - endDist);

      if (bIncludeClosure == VARIANT_FALSE && bSegmentCoordinates == VARIANT_FALSE)
      {
         xStart += leftClosureAdj;
         xEnd -= rightClosureAdj;
      }

      pvXvalues->push_back(xStart);

      // determine key X-values (locations where the depth of the section changes)
      if (m_VariationType == svtLinear || m_VariationType == svtParabolic)
      {
         Float64 dist = xStartSegment + (m_VariationLength[sztLeftPrismatic] - leftClosureAdj);
         if (::InRange(xStart, dist, xEnd))
         {
            pvXvalues->push_back(dist);
         }

         dist = xEndSegment - (m_VariationLength[sztRightPrismatic] - rightClosureAdj);
         if (::InRange(xStart, dist, xEnd))
         {
            pvXvalues->push_back(dist);
         }
      }
      else if (m_VariationType == svtDoubleLinear || m_VariationType == svtDoubleParabolic)
      {
         Float64 dist = xStartSegment + (m_VariationLength[sztLeftPrismatic] - leftClosureAdj);
         if (::InRange(xStart, dist, xEnd))
         {
            pvXvalues->push_back(dist);
         }

         dist = xStartSegment + (m_VariationLength[sztLeftPrismatic] - leftClosureAdj) + m_VariationLength[sztLeftTapered];
         if (::InRange(xStart, dist, xEnd))
         {
            pvXvalues->push_back(dist);
         }

         dist = xEndSegment - (m_VariationLength[sztRightPrismatic] - rightClosureAdj) - m_VariationLength[sztRightTapered];
         if (::InRange(xStart, dist, xEnd))
         {
            pvXvalues->push_back(dist);
         }

         dist = xEndSegment - (m_VariationLength[sztRightPrismatic] - rightClosureAdj);
         if (::InRange(xStart, dist, xEnd))
         {
            pvXvalues->push_back(dist);
         }
      }

      if (IsParabolicVariation(m_VariationType))
      {
         if (m_VariationType == svtParabolic)
         {
            Float64 start = xStart + (m_VariationLength[sztLeftPrismatic] - leftClosureAdj);
            Float64 end = xEnd - (m_VariationLength[sztRightPrismatic] - rightClosureAdj);
            Float64 dx = (end - start) / 10;
            for (int i = 0; i < 11; i++)
            {
               Float64 x = i*dx + start;
               pvXvalues->push_back(x);
            }
         }
         else
         {
            // double parabolic
            Float64 leftStart = xStart + (m_VariationLength[sztLeftPrismatic] - leftClosureAdj);
            Float64 leftEnd = leftStart + m_VariationLength[sztLeftTapered];
            Float64 rightEnd = xEnd - (m_VariationLength[sztRightPrismatic] - rightClosureAdj);
            Float64 rightStart = rightEnd - m_VariationLength[sztRightTapered];
            Float64 leftDX = (leftEnd - leftStart) / 10;
            Float64 rightDX = (rightEnd - rightStart) / 10;
            for (int i = 0; i < 11; i++)
            {
               Float64 Xl = i*leftDX + leftStart;
               Float64 Xr = i*rightDX + rightStart;
               pvXvalues->push_back(Xl);
               pvXvalues->push_back(Xr);
            }
         }
      }

      pvXvalues->push_back(xEnd);

      std::sort(pvXvalues->begin(), pvXvalues->end());
      pvXvalues->erase(std::unique(pvXvalues->begin(), pvXvalues->end()), pvXvalues->end());
   }
};
