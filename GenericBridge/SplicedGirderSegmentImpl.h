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

// SplicedGirderSegmentImpl.h : Declaration of the ISplicedGirderSegmentImpl

#pragma once

#include "resource.h"       // main symbols
#include "ItemDataManager.h"

#include <Math\CompositeFunction2d.h>
#include <Math\LinFunc2d.h>
#include <Math\MathUtils.h>

#include <algorithm>

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
      m_pSSMbr       = nullptr;
      m_pGirderLine = nullptr;
      m_pPrevSegment = nullptr;
      m_pNextSegment = nullptr;

      m_Orientation = 0;

      m_HaunchDepth[0] = 0;
      m_HaunchDepth[1] = 0;
      m_HaunchDepth[2] = 0;

      m_Fillet = 0;

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
      
      m_bSegmentHeightProfile = false;
      m_bBottomFlangeHeightProfile = false;

      m_ClosureJointFgMaterial[etStart] = nullptr;
      m_ClosureJointFgMaterial[etEnd]   = nullptr;

      m_ClosureJointBgMaterial[etStart] = nullptr;
      m_ClosureJointBgMaterial[etEnd]   = nullptr;
   }

protected:
   IGirderLine* m_pGirderLine; // weak reference to the girder line in the geometry model that provies the geometry for this segment
   ISuperstructureMember* m_pSSMbr; // weak reference to parent superstructure member
   ISuperstructureMemberSegment* m_pPrevSegment; // weak reference to previous segment
   ISuperstructureMemberSegment* m_pNextSegment; // weak reference to next segment

   Float64 m_Orientation; // orientation of girder... plumb = 0... rotated CW is +... radians

   struct ShapeData
   {
      CComPtr<IShape> Shape;
      CComPtr<IMaterial> FGMaterial;
      CComPtr<IMaterial> BGMaterial;
   };
   std::vector<ShapeData> m_Shapes;

   CItemDataManager m_ItemDataMgr;

   // index is EndType
   Float64 m_HaunchDepth[3]; // depth from top of slab to top of girder at CL Bearing at start/end of girder

   Float64 m_Fillet;

   // index is EndType
   Float64 m_EndBlockLength[2]; // length of end block from end of girder to transitation
   Float64 m_EndBlockTransitionLength[2]; // length of transition
   Float64 m_EndBlockWidth[2]; // width of end block at end of girder... constant until transition
                               // then transitions to the section

   SegmentVariationType m_VariationType;
   Float64 m_VariationLength[4]; // index is the SegmentZoneType enum
   Float64 m_VariationHeight[4];
   Float64 m_VariationBottomFlangeDepth[4];

   // index is EndType
   CComPtr<IMaterial> m_ClosureJointFgMaterial[2]; // foreground material
   CComPtr<IMaterial> m_ClosureJointBgMaterial[2]; // background material

   bool m_bSegmentHeightProfile;
   mathCompositeFunction2d m_SegmentHeightProfile; // this function returns the segment height
                                                   // at various location along the segment.
                                                   // if you plot this function, it will be upside down
                                                   // from the actual girder segment

   bool m_bBottomFlangeHeightProfile;
   mathCompositeFunction2d m_BottomFlangeHeightProfile;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
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

// ISegment
public:
   STDMETHOD(putref_SuperstructureMember)(ISuperstructureMember* ssMbr)
   {
      CHECK_IN(ssMbr);
      m_pSSMbr = ssMbr;
      return S_OK;
   }

   STDMETHOD(get_SuperstructureMember)(ISuperstructureMember** ssMbr)
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

   STDMETHOD(putref_GirderLine)(IGirderLine* girderLine)
   {
      CHECK_IN(girderLine);
      m_pGirderLine = girderLine;
      return S_OK;
   }

   STDMETHOD(get_GirderLine)(IGirderLine** girderLine)
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

   STDMETHOD(putref_PrevSegment)(ISegment* segment)
   {
      CHECK_IN(segment);
   #if defined _DEBUG
      CComQIPtr<ISplicedGirderSegment> prevSegment(segment);
      ATLASSERT(prevSegment); // all segments must be spliced girder segments
   #endif
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

   STDMETHOD(get_PrevSegment)(ISegment** segment)
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

   STDMETHOD(putref_NextSegment)(ISegment* segment)
   {
      CHECK_IN(segment);

   #if defined _DEBUG
      CComQIPtr<ISplicedGirderSegment> nextSegment(segment);
      ATLASSERT(nextSegment); // all segments must be spliced girder segments
   #endif

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

   STDMETHOD(get_NextSegment)(ISegment** segment)
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

	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal)
   {
      return m_pGirderLine->get_GirderLength(pVal);
   }

	STDMETHOD(get_LayoutLength)(/*[out, retval]*/ Float64 *pVal)
   {
      return m_pGirderLine->get_LayoutLength(pVal);
   }

	STDMETHOD(get_Section)(StageIndexType stageIdx,Float64 Xs,SectionBias sectionBias,ISection** ppSection)
   {
      return GetSection(stageIdx,Xs,sectionBias,ppSection);
   }

	STDMETHOD(get_PrimaryShape)(Float64 Xs, SectionBias sectionBias,IShape** ppShape)
   {
      return GetPrimaryShape(Xs,sectionBias,ppShape);
   }

   STDMETHOD(get_Profile)(VARIANT_BOOL bIncludeClosure,IShape** ppShape)
   {
      CComPtr<IPolyShape> polyShape;
      polyShape.CoCreateInstance(CLSID_PolyShape);

      // Start and end of the segment in Girder Path Coordinates
      Float64 xStart, xEnd;
      GetSegmentRange(&xStart,&xEnd);
      Float64 xStartSegment = xStart;
      Float64 xEndSegment   = xEnd;

      // if the closure joints are not to be included in the profile
      // move the start and end locations to the face of the segment
      if ( bIncludeClosure == VARIANT_FALSE )
      {
         CComPtr<IGirderLine> girderLine;
         get_GirderLine(&girderLine);
         Float64 brgOffset, endDist;
         girderLine->get_BearingOffset(etStart,&brgOffset);
         girderLine->get_EndDistance(etStart,&endDist);
         xStart += (brgOffset-endDist);

         girderLine->get_BearingOffset(etEnd,&brgOffset);
         girderLine->get_EndDistance(etEnd,&endDist);
         xEnd -= (brgOffset-endDist);
      }


      // determine key X-values (locations where the depth of the section changes)
      std::vector<Float64> xValues;
      if ( m_VariationType == svtLinear || m_VariationType == svtParabolic )
      {
         Float64 dist = xStartSegment + m_VariationLength[sztLeftPrismatic];
         if ( ::InRange(xStart,dist,xEnd) )
         {
            xValues.push_back(dist);
         }

         dist = xEndSegment - m_VariationLength[sztRightPrismatic];
         if ( ::InRange(xStart,dist,xEnd) )
         {
            xValues.push_back(dist);
         }
      }
      else if ( m_VariationType == svtDoubleLinear || m_VariationType == svtDoubleParabolic )
      {
         Float64 dist = xStartSegment + m_VariationLength[sztLeftPrismatic];
         if ( ::InRange(xStart,dist,xEnd) )
         {
            xValues.push_back(dist);
         }

         dist = xStartSegment + m_VariationLength[sztLeftPrismatic]  + m_VariationLength[sztLeftTapered];
         if ( ::InRange(xStart,dist,xEnd) )
         {
            xValues.push_back(dist);
         }

         dist = xEndSegment - m_VariationLength[sztRightPrismatic] - m_VariationLength[sztRightTapered];
         if ( ::InRange(xStart,dist,xEnd) )
         {
            xValues.push_back(dist);
         }

         dist = xEndSegment - m_VariationLength[sztRightPrismatic];
         if ( ::InRange(xStart,dist,xEnd) )
         {
            xValues.push_back(dist);
         }
      }

      for ( int i = 0; i < 11; i++ )
      {
         Float64 x = i*(xEnd - xStart)/10 + xStart;
         xValues.push_back(x);
      }

      std::sort(xValues.begin(),xValues.end());

      std::vector<Float64>::iterator iter(xValues.begin());
      std::vector<Float64>::iterator end(xValues.end());
      for ( ; iter != end; iter++ )
      {
         Float64 Xgp = *iter;
         Float64 Xs = ConvertToSegmentCoordinate(Xgp);
         Float64 H = GetSectionDepth(Xs);
         polyShape->AddPoint(Xgp,-H);
      }

      // points across the top of the segment
      polyShape->AddPoint(xEnd,0);
      polyShape->AddPoint(xStart,0);

      polyShape->get_Shape(ppShape);

      return S_OK;
   }

   STDMETHOD(put_Orientation)(/*[in]*/Float64 orientation)
   {
      if ( IsEqual(m_Orientation,orientation) )
         return S_OK;

      m_Orientation = orientation;
      return S_OK;
   }

	STDMETHOD(get_Orientation)(/*[out,retval]*/Float64* orientation)
   {
      CHECK_RETVAL(orientation);
      (*orientation) = m_Orientation;
      return S_OK;
   }

   STDMETHOD(GetHaunchDepth)(Float64* pStartVal,Float64* pMidVal,Float64* pEndVal)
   {
      CHECK_RETVAL(pStartVal);
      CHECK_RETVAL(pMidVal);
      CHECK_RETVAL(pEndVal);
      *pStartVal = m_HaunchDepth[0];
      *pMidVal   = m_HaunchDepth[1];
      *pEndVal   = m_HaunchDepth[2];
      return S_OK;
   }

   STDMETHOD(SetHaunchDepth)(Float64 startVal,Float64 midVal,Float64 endVal)
   {
      m_HaunchDepth[0] = startVal;
      m_HaunchDepth[1] = midVal;
      m_HaunchDepth[2] = endVal;
      return S_OK;
   }

   STDMETHOD(ComputeHaunchDepth)(Float64 distAlongSegment,Float64* pVal)
   {
      CHECK_RETVAL(pVal);
      *pVal = ::GB_GetHaunchDepth(this,distAlongSegment);
      return S_OK;
   }

   STDMETHOD(put_Fillet)(/*[in]*/Float64 Fillet)
   {
      if ( IsEqual(m_Fillet,Fillet) )
         return S_OK;

      m_Fillet = Fillet;
      return S_OK;
   }

	STDMETHOD(get_Fillet)(/*[out,retval]*/Float64* Fillet)
   {
      CHECK_RETVAL(Fillet);
      (*Fillet) = m_Fillet;
      return S_OK;
   }

// ISplicedGirderSegment
public:
	STDMETHOD(AddShape)(IShape* pShape,IMaterial* pFGMaterial,IMaterial* pBGMaterial)
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

   STDMETHOD(get_ShapeCount)(IndexType* nShapes)
   {
      CHECK_RETVAL(nShapes);
      *nShapes = m_Shapes.size();
      return S_OK;
   }

   STDMETHOD(get_ForegroundMaterial)(IndexType index,IMaterial* *material)
   {
      if ( m_Shapes.size() <= index || index == INVALID_INDEX )
         return E_INVALIDARG;

      CHECK_RETVAL(material);
      (*material) = m_Shapes[index].FGMaterial;

      if ( *material )
         (*material)->AddRef();

      return S_OK;
   }

   STDMETHOD(get_BackgroundMaterial)(IndexType index,IMaterial* *material)
   {
      if ( m_Shapes.size() <= index || index == INVALID_INDEX )
         return E_INVALIDARG;

      CHECK_RETVAL(material);
      (*material) = m_Shapes[index].BGMaterial;

      if ( *material )
         (*material)->AddRef();

      return S_OK;
   }

   STDMETHOD(put_EndBlockLength)(EndType endType,Float64 length)
   {
      m_EndBlockLength[endType] = length;
      return S_OK;
   }

   STDMETHOD(get_EndBlockLength)(EndType endType,Float64* pLength)
   {
      *pLength = m_EndBlockLength[endType];
      return S_OK;
   }

   STDMETHOD(put_EndBlockTransitionLength)(EndType endType,Float64 length)
   {
      m_EndBlockTransitionLength[endType] = length;
      return S_OK;
   }

   STDMETHOD(get_EndBlockTransitionLength)(EndType endType,Float64* pLength)
   {
      *pLength = m_EndBlockTransitionLength[endType];
      return S_OK;
   }

   STDMETHOD(put_EndBlockWidth)(EndType endType,Float64 width)
   {
      m_EndBlockWidth[endType] = width;
      return S_OK;
   }

   STDMETHOD(get_EndBlockWidth)(EndType endType,Float64* pWidth)
   {
      *pWidth = m_EndBlockWidth[endType];
      return S_OK;
   }

   STDMETHOD(put_VariationType)(SegmentVariationType variationType)
   {
      m_VariationType = variationType;
      m_bSegmentHeightProfile = false;
      return S_OK;
   }

   STDMETHOD(get_VariationType)(SegmentVariationType* variationType)
   {
      CHECK_RETVAL(variationType);
      *variationType = m_VariationType;
      return S_OK;
   }

   STDMETHOD(SetVariationParameters)(SegmentZoneType zone,Float64 length,Float64 height,Float64 bottomFlangeDepth)
   {
      m_VariationLength[zone] = length;
      m_VariationHeight[zone] = height;
      m_VariationBottomFlangeDepth[zone] = bottomFlangeDepth;
      m_bSegmentHeightProfile = false;
      return S_OK;
   }

   STDMETHOD(GetVariationParameters)(SegmentZoneType zone,Float64* length,Float64* height,Float64* bottomFlangeDepth)
   {
      CHECK_RETVAL(length);
      CHECK_RETVAL(height);
      CHECK_RETVAL(bottomFlangeDepth);

      *length = m_VariationLength[zone];
      *height = m_VariationHeight[zone];
      *bottomFlangeDepth = m_VariationBottomFlangeDepth[zone];
      return S_OK;
   }

   STDMETHOD(GetSegmentHeight)(Float64 Xs,Float64* pHeight)
   {
      CHECK_RETVAL(pHeight);
      *pHeight = GetSectionDepth(Xs);
      return S_OK;
   }

   STDMETHOD(get_BottomFlangeProfile)(IPoint2dCollection** ppPoints)
   {
      CHECK_RETOBJ(ppPoints);
      CComPtr<IPoint2dCollection> points;
      points.CoCreateInstance(CLSID_Point2dCollection);

      Float64 xStart, xEnd;
      GetSegmentRange(&xStart,&xEnd);

      std::vector<Float64> xValues;
      if ( m_VariationType == svtLinear || m_VariationType == svtParabolic )
      {
         xValues.push_back(xStart + m_VariationLength[sztLeftPrismatic]);
         xValues.push_back(xEnd   - m_VariationLength[sztRightPrismatic]);
      }
      else if ( m_VariationType == svtDoubleLinear || m_VariationType == svtDoubleParabolic )
      {
         xValues.push_back(xStart + m_VariationLength[sztLeftPrismatic]);
         xValues.push_back(xStart + m_VariationLength[sztLeftPrismatic]  + m_VariationLength[sztLeftTapered]);
         xValues.push_back(xEnd   - m_VariationLength[sztRightPrismatic] - m_VariationLength[sztRightTapered]);
         xValues.push_back(xEnd   - m_VariationLength[sztRightPrismatic]);
      }

      for ( int i = 0; i < 11; i++ )
      {
         Float64 x = i*(xEnd - xStart)/10 + xStart;
         xValues.push_back(x);
      }

      std::sort(xValues.begin(),xValues.end());

      std::vector<Float64>::iterator iter(xValues.begin());
      std::vector<Float64>::iterator end(xValues.end());
      for ( ; iter != end; iter++ )
      {
         Float64 x = *iter;
         Float64 section_depth = GetSectionDepth(x - xStart);
         Float64 bottom_flange_height = GetBottomFlangeHeight(x - xStart);
         Float64 y = section_depth - bottom_flange_height;

         CComPtr<IPoint2d> point;
         point.CoCreateInstance(CLSID_Point2d);
         point->Move(x,-y);
         points->Add(point);
      }
      points.CopyTo(ppPoints);

      return S_OK;
   }

   STDMETHOD(get_ClosureJointLength)(/*[in]*/EndType endType,/*[out,retval]*/Float64* pLength)
   {
      CHECK_RETVAL(pLength);

      if ( (m_pPrevSegment == nullptr && endType == etStart) || (m_pNextSegment == nullptr && endType == etEnd) )
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

   STDMETHOD(put_ClosureJointForegroundMaterial)(/*[in]*/EndType endType,/*[in]*/IMaterial* pFGMaterial)
   {
      CHECK_IN(pFGMaterial);
      m_ClosureJointFgMaterial[endType] = pFGMaterial;
      return S_OK;
   }

   STDMETHOD(get_ClosureJointForegroundMaterial)(/*[in]*/EndType endType,/*[out,retval]*/IMaterial** ppFGMaterial)
   {
      CHECK_RETOBJ(ppFGMaterial);
      m_ClosureJointFgMaterial[endType].CopyTo(ppFGMaterial);
      return S_OK;
   }

   STDMETHOD(put_ClosureJointBackgroundMaterial)(/*[in]*/EndType endType,/*[in]*/IMaterial* pBGMaterial)
   {
      CHECK_IN(pBGMaterial);
      m_ClosureJointBgMaterial[endType] = pBGMaterial;
      return S_OK;
   }

   STDMETHOD(get_ClosureJointBackgroundMaterial)(/*[in]*/EndType endType,/*[out,retval]*/IMaterial** ppBGMaterial)
   {
      CHECK_RETOBJ(ppBGMaterial);
      m_ClosureJointBgMaterial[endType].CopyTo(ppBGMaterial);
      return S_OK;
   }

// IItemData
public:
   STDMETHOD(AddItemData)(/*[in]*/BSTR name,/*[in]*/IUnknown* data)
   {
      return m_ItemDataMgr.AddItemData(name,data);
   }

   STDMETHOD(GetItemData)(/*[in]*/BSTR name,/*[out,retval]*/IUnknown** data)
   {
      return m_ItemDataMgr.GetItemData(name,data);
   }

   STDMETHOD(RemoveItemData)(/*[in]*/BSTR name)
   {
      return m_ItemDataMgr.RemoveItemData(name);
   }

   STDMETHOD(GetItemDataCount)(/*[out,retval]*/CollectionIndexType* count)
   {
      return m_ItemDataMgr.GetItemDataCount(count);
   }

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load)
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

	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save)
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

   Float64 GetBottomFlangeHeight(Float64 Xs)
   {
      Float64 XgpStart, XgpEnd;
      GetSegmentRange(&XgpStart,&XgpEnd);

      Float64 Xsp = ConvertToSegmentPathCoordinate(Xs);

      Float64 Xgp = XgpStart + Xsp;

      if ( m_bBottomFlangeHeightProfile )
      {
         return m_BottomFlangeHeightProfile.Evaluate(Xgp);
      }

      UpdateProfile(false,&m_BottomFlangeHeightProfile);

      m_bBottomFlangeHeightProfile = true;
      return m_BottomFlangeHeightProfile.Evaluate(Xgp);
   }

   Float64 GetSectionDepth(Float64 Xs)
   {
      Float64 XgpStart, XgpEnd;
      GetSegmentRange(&XgpStart,&XgpEnd);

      Float64 Xsp = ConvertToSegmentPathCoordinate(Xs);

      Float64 Xgp = XgpStart + Xsp;

      if ( m_bSegmentHeightProfile )
      {
         return m_SegmentHeightProfile.Evaluate(Xgp);
      }

      UpdateProfile(true,&m_SegmentHeightProfile);

      m_bSegmentHeightProfile = true;
      return m_SegmentHeightProfile.Evaluate(Xgp);
   }

   void UpdateProfile(bool bGirderProfile,mathCompositeFunction2d* pProfile)
   {
      // The profile is modeled as a composite math function. The independent variable, X,
      // is measured in the Girder Path Coordiante System. X = 0 is at the intersection of the
      // centerline of the first segment and the CL Pier at the start of the girder. The dependent
      // variable, Y, is the height of the section (bGirderProfile is true) or the 
      // height of the bottom flange (bGirderProfile is false).
      //
      // Clients will get information about this segment using the Segment Coordinate System.
      // Access to the composite math function must take this into account
      //
      // The range of the composite math function is between the faces of the girder at the start
      // and end of the girder. That means, from X=0 to X=XstartFace and X=XendFace to X=LengthGirder
      // the function is undefined.
      pProfile->Clear();

      Float64 xSegmentStart = 0; // start of segment
      Float64 xStart = 0; // start of curve section
      Float64 xEnd = 0; // end of curve section

      bool bParabola = false;
      Float64 xParabolaStart,xParabolaEnd;
      Float64 yParabolaStart,yParabolaEnd;
      Float64 slopeParabola;

      // Find the first segment in the girder
      CComPtr<ISuperstructureMemberSegment> segment1;
      m_pSSMbr->get_Segment(0,&segment1);
      CComQIPtr<ISplicedGirderSegment> firstSegment(segment1);

      // go down each segment and create piece-wise functions for each part of the girder profile
      CComPtr<ISplicedGirderSegment> currSegment( firstSegment );
      CComPtr<ISplicedGirderSegment> prevSegment;
      CComPtr<ISplicedGirderSegment> nextSegment;
      do
      {
         CComPtr<ISegment> prevSeg;
         CComPtr<ISegment> nextSeg;
         currSegment->get_PrevSegment(&prevSeg);
         currSegment->get_NextSegment(&nextSeg);

         CComQIPtr<ISuperstructureMemberSegment> ps(prevSeg);
         CComQIPtr<ISuperstructureMemberSegment> ns(nextSeg);

         SegmentVariationType prevVariationType,variationType,nextVariationType;
         Float64 prev_segment_length, segment_length, next_segment_length;
         if ( ps )
         {
            ps.QueryInterface(&prevSegment);
            prevSegment->get_VariationType(&prevVariationType);
            prevSegment->get_LayoutLength(&prev_segment_length);
         }

         currSegment->get_VariationType(&variationType);
         currSegment->get_LayoutLength(&segment_length);

         if ( ns )
         {
            ns.QueryInterface(&nextSegment);
            nextSegment->get_VariationType(&nextVariationType);
            nextSegment->get_LayoutLength(&next_segment_length);
         }

         if ( !ps )
         {
            // this is the first segment
            CComPtr<IGirderLine> girderLine;
            currSegment->get_GirderLine(&girderLine);
            Float64 end_distance, bearing_offset;
            girderLine->get_EndDistance(etStart,&end_distance);
            girderLine->get_BearingOffset(etStart,&bearing_offset);

            Float64 offset_dist = bearing_offset - end_distance;
            offset_dist = IsZero(offset_dist) ? 0 : offset_dist;
            segment_length -= offset_dist;

            // start at the face of the segment
            xSegmentStart = offset_dist;
         }

         if ( !ns )
         {
            // this is the last segment
            CComPtr<IGirderLine> girderLine;
            currSegment->get_GirderLine(&girderLine);
            Float64 end_distance, bearing_offset;
            girderLine->get_EndDistance(etEnd,&end_distance);
            girderLine->get_BearingOffset(etEnd,&bearing_offset);

            Float64 offset_dist = bearing_offset - end_distance;
            offset_dist = IsZero(offset_dist) ? 0 : offset_dist;

            // adjust the length of the last segment so we end at the end face of the segment
            segment_length -= offset_dist;
         }

         xStart = xSegmentStart;

         Float64 left_prismatic_length,  left_prismatic_height,  left_prismatic_bottom_flange_depth;
         Float64 left_tapered_length,    left_tapered_height,    left_tapered_bottom_flange_depth;
         Float64 right_tapered_length,   right_tapered_height,   right_tapered_bottom_flange_depth;
         Float64 right_prismatic_length, right_prismatic_height, right_prismatic_bottom_flange_depth;
         currSegment->GetVariationParameters(sztLeftPrismatic, &left_prismatic_length, &left_prismatic_height, &left_prismatic_bottom_flange_depth);
         currSegment->GetVariationParameters(sztLeftTapered,   &left_tapered_length,   &left_tapered_height,   &left_tapered_bottom_flange_depth);
         currSegment->GetVariationParameters(sztRightTapered,  &right_tapered_length,  &right_tapered_height,  &right_tapered_bottom_flange_depth);
         currSegment->GetVariationParameters(sztRightPrismatic,&right_prismatic_length,&right_prismatic_height,&right_prismatic_bottom_flange_depth);

         Float64 prev_segment_left_prismatic_length,  prev_segment_left_prismatic_height,  prev_segment_left_prismatic_bottom_flange_depth;
         Float64 prev_segment_left_tapered_length,    prev_segment_left_tapered_height,    prev_segment_left_tapered_bottom_flange_depth;
         Float64 prev_segment_right_tapered_length,   prev_segment_right_tapered_height,   prev_segment_right_tapered_bottom_flange_depth;
         Float64 prev_segment_right_prismatic_length, prev_segment_right_prismatic_height, prev_segment_right_prismatic_bottom_flange_depth;
         if ( prevSegment )
         {
            prevSegment->GetVariationParameters(sztLeftPrismatic, &prev_segment_left_prismatic_length, &prev_segment_left_prismatic_height, &prev_segment_left_prismatic_bottom_flange_depth);
            prevSegment->GetVariationParameters(sztLeftTapered,   &prev_segment_left_tapered_length,   &prev_segment_left_tapered_height,   &prev_segment_left_tapered_bottom_flange_depth);
            prevSegment->GetVariationParameters(sztRightTapered,  &prev_segment_right_tapered_length,  &prev_segment_right_tapered_height,  &prev_segment_right_tapered_bottom_flange_depth);
            prevSegment->GetVariationParameters(sztRightPrismatic,&prev_segment_right_prismatic_length,&prev_segment_right_prismatic_height,&prev_segment_right_prismatic_bottom_flange_depth);
         }

         Float64 next_segment_left_prismatic_length,  next_segment_left_prismatic_height,  next_segment_left_prismatic_bottom_flange_depth;
         Float64 next_segment_left_tapered_length,    next_segment_left_tapered_height,    next_segment_left_tapered_bottom_flange_depth;
         Float64 next_segment_right_tapered_length,   next_segment_right_tapered_height,   next_segment_right_tapered_bottom_flange_depth;
         Float64 next_segment_right_prismatic_length, next_segment_right_prismatic_height, next_segment_right_prismatic_bottom_flange_depth;
         if ( nextSegment )
         {
            nextSegment->GetVariationParameters(sztLeftPrismatic, &next_segment_left_prismatic_length, &next_segment_left_prismatic_height, &next_segment_left_prismatic_bottom_flange_depth);
            nextSegment->GetVariationParameters(sztLeftTapered,   &next_segment_left_tapered_length,   &next_segment_left_tapered_height,   &next_segment_left_tapered_bottom_flange_depth);
            nextSegment->GetVariationParameters(sztRightTapered,  &next_segment_right_tapered_length,  &next_segment_right_tapered_height,  &next_segment_right_tapered_bottom_flange_depth);
            nextSegment->GetVariationParameters(sztRightPrismatic,&next_segment_right_prismatic_length,&next_segment_right_prismatic_height,&next_segment_right_prismatic_bottom_flange_depth);
         }

         Float64 h1,h2,h3,h4;
         if ( bGirderProfile )
         {
            h1 = left_prismatic_height;
            h2 = right_prismatic_height;
            h3 = left_tapered_height;
            h4 = right_tapered_height;
         }
         else
         {
            h1 = left_prismatic_bottom_flange_depth;
            h2 = right_prismatic_bottom_flange_depth;
            h3 = left_tapered_bottom_flange_depth;
            h4 = right_tapered_bottom_flange_depth;
         }


         // add a dummy function before the start of the profile
         // so we don't have issues with points that are just a little bit off
         if ( pProfile->GetFunctionCount() == 0 )
         {
            mathLinFunc2d func(0.0,h1);
            pProfile->AddFunction(xStart - 100*fabs(xStart),xStart,func);
         }

         if ( variationType == svtNone || 0 < left_prismatic_length )
         {
            // create a prismatic segment
            mathLinFunc2d func(0.0, h1);
            xEnd = xStart + (variationType == svtNone ? segment_length/2 : left_prismatic_length);
            pProfile->AddFunction(xStart,xEnd,func);
            slopeParabola = 0;
            xStart = xEnd;
         }

         if ( variationType == svtLinear )
         {
            // create a linear taper segment
            Float64 taper_length = segment_length - left_prismatic_length - right_prismatic_length;
            Float64 slope = (h2 - h1)/taper_length;
            Float64 b = h1 - slope*xStart;

            mathLinFunc2d func(slope, b);
            xEnd = xStart + taper_length;
            pProfile->AddFunction(xStart,xEnd,func);
            xStart = xEnd;
            slopeParabola = slope;
         }
         else if ( variationType == svtDoubleLinear )
         {
            // create a linear taper for left side of segment
            Float64 slope = (h3 - h1)/left_tapered_length;
            Float64 b = h1 - slope*xStart;

            mathLinFunc2d left_func(slope, b);
            xEnd = xStart + left_tapered_length;
            pProfile->AddFunction(xStart,xEnd,left_func);
            xStart = xEnd;

            // create a linear segment between left and right tapers
            Float64 taper_length = segment_length - left_prismatic_length - left_tapered_length - right_prismatic_length - right_tapered_length;
            if ( !IsZero(taper_length) )
            {
               slope = (h4 - h3)/taper_length;
               b = h3 - slope*xStart;

               mathLinFunc2d middle_func(slope, b);
               xEnd = xStart + taper_length;
               pProfile->AddFunction(xStart,xEnd,middle_func);
               xStart = xEnd;
            }

            // create a linear taper for right side of segment
            slope = (h2 - h4)/right_tapered_length;
            b = h4 - slope*xStart;

            mathLinFunc2d right_func(slope, b);
            xEnd = xStart + right_tapered_length;
            pProfile->AddFunction(xStart,xEnd,right_func);
            xStart = xEnd;
            slopeParabola = slope;
         }
         else if ( variationType == svtParabolic )
         {
            if ( !bParabola )
            {
               // this is the start of a parabolic segment
               bParabola = true;
               xParabolaStart = xStart;
               yParabolaStart = h1;
            }

            // Parabola ends in this segment if
            // 1) this segment has a prismatic segment on the right end -OR-
            // 2) this is the last segment -OR-
            // 3) the next segment starts with a prismatic segment -OR-
            // 4) the next segment has a linear transition
            if (
                 0 < right_prismatic_length || // parabola ends in this segment -OR-
                 nextSegment == nullptr        || // this is the last segment (parabola ends here) -OR-
                 0 < next_segment_left_prismatic_length || // next segment starts with prismatic section -OR-
                 (nextVariationType == svtNone || nextVariationType == svtLinear || nextVariationType == svtDoubleLinear) // next segment is linear 
               )
            {
               // parabola ends in this segment
               Float64 xParabolaEnd = xStart + segment_length - right_prismatic_length;
               Float64 yParabolaEnd = h2;

               if ( yParabolaEnd < yParabolaStart )
               {
                  // slope at end is zero
                  mathPolynomial2d func = GenerateParabola2(xParabolaStart,yParabolaStart,xParabolaEnd,yParabolaEnd,0.0);
                  pProfile->AddFunction(xParabolaStart,xParabolaEnd,func);
               }
               else
               {
                  // slope at start is zero
                  mathPolynomial2d func = GenerateParabola1(xParabolaStart,yParabolaStart,xParabolaEnd,yParabolaEnd,slopeParabola);
                  pProfile->AddFunction(xParabolaStart,xParabolaEnd,func);
               }

               bParabola = false;
               xStart = xParabolaEnd;
            }
            else
            {
               // parabola ends further down the girderline
               // do nothing???
            }
         }
         else if ( variationType == svtDoubleParabolic )
         {
            // left parabola ends in this segment
            if ( !bParabola )
            {
               // not currently in a parabola, based the start point on this segment
               xParabolaStart = xSegmentStart + left_prismatic_length;
               yParabolaStart = h1;
            }

   #pragma Reminder("BUG: Assuming slope at start is zero, but it may not be if tangent to a linear segment")
            xParabolaEnd = xSegmentStart + left_prismatic_length + left_tapered_length;
            yParabolaEnd = h3;
            mathPolynomial2d func_left_parabola;
            if ( yParabolaEnd < yParabolaStart )
               func_left_parabola = GenerateParabola2(xParabolaStart,yParabolaStart,xParabolaEnd,yParabolaEnd,0.0);
            else
               func_left_parabola = GenerateParabola1(xParabolaStart,yParabolaStart,xParabolaEnd,yParabolaEnd,slopeParabola);

            pProfile->AddFunction(xParabolaStart,xParabolaEnd,func_left_parabola);

            // parabola on right side of this segment starts here
            xParabolaStart = xSegmentStart + segment_length - right_prismatic_length - right_tapered_length;
            yParabolaStart = h4;
            bParabola = true;

            if ( !IsZero(xParabolaStart - xParabolaEnd) )
            {
               // create a line segment between parabolas
               Float64 taper_length = segment_length - left_prismatic_length - left_tapered_length - right_prismatic_length - right_tapered_length;
               Float64 slope = -(h4 - h3)/taper_length;
               Float64 b = h3 - slope*xParabolaEnd;

               mathLinFunc2d middle_func(slope, b);
               pProfile->AddFunction(xParabolaEnd,xParabolaStart,middle_func);
               slopeParabola = slope;
            }

            // parabola ends in this segment if
            // 1) this is the last segment
            // 2) right prismatic section length > 0
            // 3) next segment is not parabolic
            if ( 0 < right_prismatic_length || 
                 nextSegment == nullptr        || 
                 (nextVariationType == svtNone || nextVariationType == svtLinear || nextVariationType == svtDoubleLinear) // next segment is linear 
               )
            {
               bParabola = false;
               xParabolaEnd = xSegmentStart + segment_length - right_prismatic_length;
               yParabolaEnd = h2;

        
               mathPolynomial2d func_right_parabola;
               if ( yParabolaEnd < yParabolaStart )
               {
                  // compute slope at end of parabola
                  if ( nextSegment )
                  {
                     if ( nextVariationType == svtLinear )
                     {
                        // next segment is linear
                        if ( IsZero(next_segment_left_prismatic_length) )
                        {
                           Float64 dist = next_segment_length - next_segment_left_prismatic_length - next_segment_right_prismatic_length;
                           slopeParabola = -(next_segment_right_prismatic_height - next_segment_left_prismatic_height)/dist;
                        }
                     }
                     else if ( nextVariationType == svtDoubleLinear )
                     {
                        if ( IsZero(next_segment_left_prismatic_length) )
                        {
                           Float64 dist = next_segment_left_tapered_length;
                           slopeParabola = -(next_segment_left_tapered_length - next_segment_left_prismatic_length)/dist;
                        }
                     }
                  }
                  else
                  {
                     slopeParabola = 0;
                  }
                  func_right_parabola = GenerateParabola2(xParabolaStart,yParabolaStart,xParabolaEnd,yParabolaEnd,slopeParabola);
               }
               else
               {
                  func_right_parabola = GenerateParabola1(xParabolaStart,yParabolaStart,xParabolaEnd,yParabolaEnd,slopeParabola);
               }

               pProfile->AddFunction(xParabolaStart,xParabolaEnd,func_right_parabola);
            }
            else
            {
               // parabola ends further down the girderline
               bParabola = true;
            }

            xStart = xSegmentStart + segment_length - right_prismatic_length;
         }

         if ( variationType == svtNone ||  0 < right_prismatic_length )
         {
            // create a prismatic segment
            mathLinFunc2d func(0.0, h2);
            xEnd = xStart + (variationType == svtNone ? segment_length/2 : right_prismatic_length);
            pProfile->AddFunction(xStart,xEnd,func);
            slopeParabola = 0;
            xStart = xEnd;
         }

         xSegmentStart += segment_length;

         currSegment = nextSegment;
         prevSegment.Release();
         nextSegment.Release();
      } while ( currSegment );


      // add a dummy run out function at the end so we don't crash
      // for points that are just a bit off the end
#pragma Reminder("UPDATE: this isn't the best technique... make this more deterministic")
      // for bridges with multiple groups, and the groups are made continuous or integral at the
      // common pier, the 10th point of the span falls between the girders and it isn't captured
      // in the profile. when we get the profile at these locations, *crash*
      IndexType nFunctions = pProfile->GetFunctionCount();
      const mathFunction2d* pLastFunction;
      Float64 xMin,xMax;
      pProfile->GetFunction(nFunctions-1,&pLastFunction,&xMin,&xMax);
      Float64 h = pLastFunction->Evaluate(xMax);
      mathLinFunc2d func(0.0,h);
      pProfile->AddFunction(xMax,xMax + 100*fabs(xMax-xMin),func);
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
   }
};
