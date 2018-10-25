///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2017, Washington State Department of Transportation, All Rights Reserved
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

   Float64 m_HaunchDepth[3];

   Float64 m_Fillet;

   // index is EndType
   Float64 m_EndBlockLength[2]; // length of end block from end of girder to transitation

   CItemDataManager m_ItemDataMgr;

public:
   TEndBlockSegmentImpl()
	{
      m_pSSMbr       = NULL;
      m_pPrevSegment = NULL;
      m_pNextSegment = NULL;
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
      m_pGirderLine = NULL;

      m_Orientation = 0;

      m_HaunchDepth[0] = 0;
      m_HaunchDepth[1] = 0;
      m_HaunchDepth[2] = 0;

      m_Fillet = 0;

      m_EndBlockLength[etStart]           = 0;
      m_EndBlockLength[etEnd]             = 0;

      return S_OK;
   }

   void FinalRelease()
   {
      m_pGirderLine = NULL;
      m_Shapes.clear();
   }

// ISupportsErrorInfo
public:
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
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

// ISegment
public:
   STDMETHOD(putref_SuperstructureMember)(ISuperstructureMember* ssMbr)
   {
      m_pSSMbr = ssMbr;
      return S_OK;
   }

   STDMETHOD(get_SuperstructureMember)(ISuperstructureMember** ssMbr)
   {
      CHECK_RETVAL(ssMbr);
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

   STDMETHOD(putref_GirderLine)(IGirderLine* girderLine)
   {
      m_pGirderLine = girderLine;
      return S_OK;
   }

   STDMETHOD(get_GirderLine)(IGirderLine** girderLine)
   {
      CHECK_RETVAL(girderLine);
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

   STDMETHOD(putref_PrevSegment)(ISegment* segment)
   {
      CHECK_IN(segment);
      ISuperstructureMemberSegment* pMySeg = m_pPrevSegment; // weak references so no change in ref count
      m_pPrevSegment = NULL;
      HRESULT hr = segment->QueryInterface(&m_pPrevSegment);
      if ( FAILED(hr) )
      {
         m_pPrevSegment = pMySeg;
      }
      return hr;
   }

   STDMETHOD(get_PrevSegment)(ISegment** segment)
   {
      CHECK_RETVAL(segment);
      return m_pPrevSegment->QueryInterface(segment);
   }

   STDMETHOD(putref_NextSegment)(ISegment* segment)
   {
      ISuperstructureMemberSegment* pMySeg = m_pNextSegment; // weak references so no change in ref count
      m_pNextSegment = NULL;
      HRESULT hr = segment->QueryInterface(&m_pNextSegment);
      if ( FAILED(hr) )
      {
         m_pNextSegment = pMySeg;
      }
      return hr;
   }

   STDMETHOD(get_NextSegment)(ISegment** segment)
   {
      CHECK_RETVAL(segment);
      return m_pNextSegment->QueryInterface(segment);
   }

   STDMETHOD(get_Length)(Float64 *pVal)
   {
      ATLASSERT(m_pGirderLine != NULL);
      return m_pGirderLine->get_GirderLength(pVal);
   }

   STDMETHOD(get_LayoutLength)(Float64 *pVal)
   {
      ATLASSERT(m_pGirderLine != NULL);
      return m_pGirderLine->get_LayoutLength(pVal);
   }

   STDMETHOD(get_Section)(StageIndexType stageIdx,Float64 Xs,ISection** ppSection)
   {
      CHECK_RETOBJ(ppSection);

      if (m_Shapes.size() == 0 )
      {
         *ppSection = 0;
         return S_OK;
      }

      CComQIPtr<T_IBeamSection> beam(m_Shapes.front().Shape);
      ATLASSERT(beam); // if this is NULL... how did it get in the system????

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
      if ( (0.0 < m_EndBlockLength[etStart] && IsLE(Xs,m_EndBlockLength[etStart])) || 
           (0.0 < m_EndBlockLength[etEnd]   && IsLE(length - Xs,m_EndBlockLength[etEnd])) )
      {
         T_ENDBLOCK::InEndBlock(newBeam);;
      }

      // position the shape
      CComPtr<IPoint2d> pntTopCenter;
      GB_GetSectionLocation(this,Xs,&pntTopCenter);

      CComQIPtr<IXYPosition> position(newSection);
      position->put_LocatorPoint(lpTopCenter,pntTopCenter);

      CComPtr<ICompositeSectionEx> section;
      section.CoCreateInstance(CLSID_CompositeSectionEx);

      section->QueryInterface(IID_ISection,(void**)ppSection);
      ATLASSERT(*ppSection != NULL);

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

   STDMETHOD(get_PrimaryShape)(Float64 Xs,IShape** ppShape)
   {
      CHECK_RETOBJ(ppShape);

      if (m_Shapes.size() == 0 )
      {
         *ppShape = 0;
         return S_OK;
      }

      CComQIPtr<T_IBeamSection> beam(m_Shapes.front().Shape);
      ATLASSERT(beam); // if this is NULL... how did it get in the system????

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
      if ( (0.0 < m_EndBlockLength[etStart] && IsLE(Xs,m_EndBlockLength[etStart])) || 
           (0.0 < m_EndBlockLength[etEnd]   && IsLE(length - Xs,m_EndBlockLength[etEnd])) )
      {
         T_ENDBLOCK::InEndBlock(newBeam);;
      }

      // position the shape
      CComPtr<IPoint2d> pntTopCenter;
      GB_GetSectionLocation(this,Xs,&pntTopCenter);

      CComQIPtr<IXYPosition> position(newSection);
      position->put_LocatorPoint(lpTopCenter,pntTopCenter);

      *ppShape = newShape;
      (*ppShape)->AddRef();

      return S_OK;
   }

   STDMETHOD(get_Profile)(VARIANT_BOOL bIncludeClosure,IShape** ppShape)
   {
      CHECK_RETOBJ(ppShape);
      CComPtr<IRect2d> rect;

      // it is assumed that the first shape is the main shape in the section and all
      // other shapes are inside of it
      m_Shapes[0].Shape->get_BoundingBox(&rect);

      Float64 h;
      rect->get_Height(&h);

      Float64 l;
      Float64 brgOffset,endDist;
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

      // CL Pier/Top Shape is at (0,0)
      //
      // CL Pier   End of segment
      // |         |       CL Bearing
      // | (0,0)   |       |
      // *         +-------+---------------\  
      // |         |       .               /
      // |         +-------+---------------\  

      CComQIPtr<IXYPosition> position(shape);
      CComPtr<IPoint2d> topLeft;
      position->get_LocatorPoint(lpTopLeft,&topLeft);
      topLeft->Move(brgOffset-endDist,0);
      position->put_LocatorPoint(lpTopLeft,topLeft);

      shape->QueryInterface(ppShape);

      return S_OK;
   }

   STDMETHOD(put_Orientation)(Float64 orientation)
   {
      if ( IsEqual(m_Orientation,orientation) )
      {
         return S_OK;
      }

      m_Orientation = orientation;
      return S_OK;
   }

   STDMETHOD(get_Orientation)(Float64* orientation)
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

   STDMETHOD(put_Fillet)(Float64 Fillet)
   {
      if ( IsEqual(m_Fillet,Fillet) )
      {
         return S_OK;
      }

      m_Fillet = Fillet;
      return S_OK;
   }

   STDMETHOD(get_Fillet)(Float64* Fillet)
   {
      CHECK_RETVAL(Fillet);
      (*Fillet) = m_Fillet;
      return S_OK;
   }

// Functions to fulfill local class declaration
public:
	STDMETHOD(AddShape)(IShape* pShape,IMaterial* pFGMaterial,IMaterial* pBGMaterial)
   {
      CHECK_IN(pShape);
      if ( m_Shapes.size() == 0 )
      {
         CComQIPtr<T_IBeamSection> beam(pShape);
         if ( beam == NULL )
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

   STDMETHOD(get_ShapeCount)(IndexType* nShapes)
   {
      CHECK_RETVAL(nShapes);
      *nShapes = m_Shapes.size();
      return S_OK;
   }

   STDMETHOD(get_ForegroundMaterial)(IndexType index,IMaterial* *material)
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

   STDMETHOD(get_BackgroundMaterial)(IndexType index,IMaterial* *material)
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

   STDMETHOD(put_EndBlockLength)(/*[in]*/EndType endType,/*[in]*/ Float64 length)
   {
      m_EndBlockLength[endType] = length;
      return S_OK;
   }

   STDMETHOD(get_EndBlockLength)(/*[in]*/EndType endType,/*[out,retval]*/ Float64* pLength)
   {
      *pLength = m_EndBlockLength[endType];
      return S_OK;
   }

// IItemData
public:
   STDMETHOD(AddItemData)(BSTR name,IUnknown* data)
   {
      return m_ItemDataMgr.AddItemData(name,data);
   }

   STDMETHOD(GetItemData)(BSTR name,IUnknown** data)
   {
      return m_ItemDataMgr.GetItemData(name,data);
   }

   STDMETHOD(RemoveItemData)(BSTR name)
   {
      return m_ItemDataMgr.RemoveItemData(name);
   }

   STDMETHOD(GetItemDataCount)(CollectionIndexType* count)
   {
      return m_ItemDataMgr.GetItemDataCount(count);
   }

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load)
   {
      return E_NOTIMPL;
   }

	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save)
   {
      return E_NOTIMPL;
   }
};

