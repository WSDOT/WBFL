///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2012  Washington State Department of Transportation
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

// GenericBridgeImpl.h : Declaration of the CGenericBridge

#ifndef __GENERICBRIDGEIMPL_H_
#define __GENERICBRIDGEIMPL_H_

#include "resource.h"       // main symbols
#include "GenericBridgeCP.h"
#include <vector>
//#include "GirderSpacing.h" // for SpacingData

class CPierCollection;
class CSpanCollection;
class CPointOfInterestCollection;

/////////////////////////////////////////////////////////////////////////////
// CGenericBridge
class ATL_NO_VTABLE CGenericBridge :
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CGenericBridge,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CGenericBridge, &CLSID_GenericBridge>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CGenericBridge>,
   public IObjectSafetyImpl<CGenericBridge,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IGenericBridge,
   public IStructuredStorage2,
   public CProxyDGenericBridgeEvents< CGenericBridge >,
   public IPierCollectionEvents,
   public ISpanCollectionEvents,
   public IStageCollectionEvents,
   public IPathEvents,
   public IBridgeDeckEvents
{
public:
   friend CGenericBridge;

   CGenericBridge()
	{
      m_dwAlignmentCookie = 0;
      m_dwDeckCookie = 0;
      m_AlignmentOffset = 0;

      m_bHoldUpdate = true;
   }

   HRESULT FinalConstruct();
   void FinalRelease();

   // Causes the internal span/pier linkages pointers to be re-initialized
   void LinkSpansAndPiers();

DECLARE_REGISTRY_RESOURCEID(IDR_GENERICBRIDGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGenericBridge)
	COM_INTERFACE_ENTRY(IGenericBridge)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IPierCollectionEvents)
   COM_INTERFACE_ENTRY(ISpanCollectionEvents)
   COM_INTERFACE_ENTRY(IStageCollectionEvents)
   COM_INTERFACE_ENTRY(IPathEvents)
   COM_INTERFACE_ENTRY(IBridgeDeckEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CGenericBridge)
   CONNECTION_POINT_ENTRY(IID_IGenericBridgeEvents)
END_CONNECTION_POINT_MAP()

private:
   bool m_bHoldUpdate;

   void DoUpdateBridgeModel();
   HRESULT AdviseChild(IUnknown* punk,REFIID riid,DWORD* pdwCookie);
   HRESULT UnadviseChild(IUnknown* punk,REFIID riid,DWORD dwCookie);

   CComPtr<IPierCollection> m_Piers;
   DWORD m_dwPiersCookie;

   CComPtr<ISpanCollection> m_Spans;
   DWORD m_dwSpansCookie;

   CComPtr<IStageCollection> m_Stages;
   DWORD m_dwStagesCookie;

   CComPtr<ICogoModel> m_CogoModel;
   CComPtr<IAlignment> m_Alignment;
   DWORD m_dwAlignmentCookie;
   Float64 m_AlignmentOffset;

   CComPtr<IBridgeDeck> m_Deck;
   DWORD m_dwDeckCookie;

   CComPtr<ISidewalkBarrier> m_LeftBarrier;
   CComPtr<ISidewalkBarrier> m_RightBarrier;

   CComPtr<ICogoInfo> m_CogoInfo;
   CComPtr<ICogoEngine> m_CogoEngine;
   CComPtr<IGeomUtil2d> m_GeomUtil;

   // Backdoor access to collections
   void SetCollections(IStageCollection* stages,ISpanCollection* spans,IPierCollection* piers);
   CPierCollection* GetPierCollection();
   CSpanCollection* GetSpanCollection();

//   HRESULT SpanGirderLocationToAbsolute(long spanIdx,long gdrLineIdx,Float64 loc,Float64* dist);
//   HRESULT SegmentLocationToAbsolute(long gdrLineIdx,long ssmbrIdx,long segIdx,Float64 loc,Float64* dist);

   void UpdatePierGirderIntersectionPoints(SpanIndexType spanIdx,ISpan* pSpan);
   void UpdateGirderEndPoints(SpanIndexType spanIdx,GirderIndexType gdrIdx);
   void GetEndDistance(EndType end,CogoElementKey brgPntID,CogoElementKey pierPntID,CogoElementKey girderLineID,IConnection* connection,IPier* pier,Float64* endDist);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IGenericBridge
public:
   STDMETHOD(get_CogoModel)(/*[out,retval]*/ ICogoModel* *cogoModel);
   STDMETHOD(get_CogoInfo)(/*[out,retval]*/ ICogoInfo* *cogoInfo);
   STDMETHOD(get_Alignment)(/*[out,retval]*/ IAlignment* *alignment);
   STDMETHOD(putref_Alignment)(/*[in]*/ IAlignment *alignment);
   STDMETHOD(put_AlignmentOffset)(/*[in]*/Float64 alignmentOffset);
	STDMETHOD(get_AlignmentOffset)(/*[out,retval]*/Float64* alignmentOffset);
   STDMETHOD(get_Piers)(/*[out,retval]*/ IPierCollection* *piers);
   STDMETHOD(get_Spans)(/*[out,retval]*/ ISpanCollection* *spans);
   STDMETHOD(SpanFromStation)(/*[in]*/Float64 station,/*[out,retval]*/ISpan** ppSpan);
   STDMETHOD(SpanFromOffset)(/*[in]*/Float64 offsetFromStartOfBridge,/*[out,retval]*/ISpan** ppSpan);
   STDMETHOD(get_Stages)(/*[out, retval]*/ IStageCollection* *pVal);
   STDMETHOD(get_Length)(/*[out,retval]*/Float64* length);
   STDMETHOD(Move)(/*[in]*/ Float64 offset);
   STDMETHOD(MoveToStation)(/*[in]*/PierIndexType pierIdx,/*[in]*/ Float64 station);
   STDMETHOD(InsertSpanAndPier)(/*[in]*/ SpanIndexType spanIdx, /*[in]*/ Float64 spanLength,/*[in,defaultvalue(qcbAfter)]*/ PositionType pos, /*[in,defaultvalue(qcbRight)]*/ DirectionType side);
   STDMETHOD(RemoveSpanAndPier)(/*[in]*/ SpanIndexType spanIdx,/*[in]*/ DirectionType side);
   STDMETHOD(ResizeSpans)(/*[in]*/ VARIANT varArray);
//   STDMETHOD(CopySuperstructureMembersTo)(/*[in]*/ long fromIdx,/*[in]*/ long toIdx);
   STDMETHOD(Clone)(/*[out,retval]*/ IGenericBridge* *clone);
	STDMETHOD(putref_Deck)(/*[in]*/ IBridgeDeck* deck);
	STDMETHOD(get_Deck)(/*[out,retval]*/ IBridgeDeck** deck);
//	STDMETHOD(GetSuperstructureMemberSegment)(/*[in]*/ long spanIdx,/*[in]*/ long gdrLineIdx, /*[in]*/ Float64 dist, /*[out,retval]*/ ISegment** segment);
//   STDMETHOD(SpanGirderToSegment)(/*[in]*/ long spanIdx,/*[in]*/ long gdrLineIdx, /*[in]*/ Float64 location,/*[out]*/ long* ssmbrIdx, /*[out]*/ long* segmentIdx, /*[out]*/ Float64* dist);
//   STDMETHOD(SegmentToSpanGirder)(/*[in]*/ long gdrLineIdx, /*[in]*/ long ssmbrIdx,/*[in]*/ long segmentIdx, /*[in]*/ Float64 dist,/*[out]*/ long* spanIdx,/*[out]*/ Float64* location);
	STDMETHOD(get_LeftBarrier)(/*[out,retval]*/ ISidewalkBarrier** barrier);
	STDMETHOD(putref_LeftBarrier)(/*[in]*/ ISidewalkBarrier* barrier);
	STDMETHOD(get_RightBarrier)(/*[out,retval]*/ ISidewalkBarrier** barrier);
	STDMETHOD(putref_RightBarrier)(/*[in]*/ ISidewalkBarrier* barrier);

   STDMETHOD(UpdateBridgeModel)();

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);

// IPierCollectionEvents
public:
	STDMETHOD(OnPierChanged)(IPier * pier)
	{
      DoUpdateBridgeModel();
      Fire_OnBridgeChanged(this);
		return S_OK;
	}
   
   STDMETHOD(OnPierAdded)(/*[in]*/IPier* pier)
   {
      DoUpdateBridgeModel();
      Fire_OnBridgeChanged(this);
      return S_OK;
   }

   STDMETHOD(OnPierRemoved)(/*[in]*/PierIndexType idx)
   {
      DoUpdateBridgeModel();
      Fire_OnBridgeChanged(this);
      return S_OK;
   }

// ISpanCollectionEvents
public:
	STDMETHOD(OnSpanChanged)(ISpan * span)
	{
      DoUpdateBridgeModel();
      Fire_OnBridgeChanged(this);
		return S_OK;
	}

// IStageCollectionEvents
public:
   STDMETHOD(OnStageDescriptionChanged)(/*[in]*/IStage* stage)
   {
      // Do nothing... This really isn't an important event
      // If something needs to hear it, they can sink the events on the stage collection
      return S_OK;
   }
   STDMETHOD(OnStageRenamed)(/*[in]*/BSTR bstrOldName,/*[in]*/IStage* stage);
   STDMETHOD(OnStageAdded)(/*[in]*/CollectionIndexType idx);
   STDMETHOD(OnStageRemoved)(/*[in]*/CollectionIndexType idx,/*[in]*/BSTR name);
   STDMETHOD(OnStageMoved)(/*[in]*/BSTR name,/*[in]*/CollectionIndexType from,/*[in]*/CollectionIndexType to);

// IPathEvents
public:
   STDMETHOD(OnPathChanged)(/*[in]*/ IPath* path)
   {
      DoUpdateBridgeModel();
      Fire_OnBridgeChanged(this);
		return S_OK;
   }

	STDMETHOD(OnProfileChanged)(/*[in]*/ IProfile* profile)
   {
      DoUpdateBridgeModel();
      Fire_OnBridgeChanged(this);
		return S_OK;
   }

// IBridgeDeckEvents
public:
   STDMETHOD(OnBridgeDeckChanged)(IBridgeDeck* deck)
   {
      //DoUpdateBridgeModel();
      Fire_OnBridgeChanged(this);
		return S_OK;
   }
};

#endif //__GENERICBRIDGEIMPL_H_
