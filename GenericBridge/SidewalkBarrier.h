///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 2009  Washington State Department of Transportation
//                   Bridge and Structures Office
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

// SidewalkBarrier.h : Declaration of the CSidewalkBarrier

#ifndef __SIDEWALKBARRIER_H_
#define __SIDEWALKBARRIER_H_

#include "resource.h"       // main symbols
#include "GenericBridgeCP.h"


/////////////////////////////////////////////////////////////////////////////
// CSidewalkBarrier
class ATL_NO_VTABLE CSidewalkBarrier : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSidewalkBarrier,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSidewalkBarrier, &CLSID_SidewalkBarrier>,
	public ISupportErrorInfo,
	public ISidewalkBarrier,
   public IStructuredStorage2,
//   public CProxyDSidewalkBarrierEvents< CSidewalkBarrier >,
//   public IConnectionPointContainerImpl<CSidewalkBarrier>,
   public IObjectSafetyImpl<CSidewalkBarrier,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CSidewalkBarrier()
	{
      m_Configuration = 0;
      m_ConnectionWidth = 0;
      m_bExteriorStructurallyContinuous = VARIANT_FALSE;
      m_bSidewalkStructurallyContinuous = VARIANT_FALSE;
      m_bInteriorStructurallyContinuous = VARIANT_FALSE;
      m_SidewalkPosition = swpBetweenBarriers;
      m_idxExteriorBarrier = 0;
      m_idxSidewalk = 1;
      m_idxInteriorBarrier = 2;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_SIDEWALKBARRIER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSidewalkBarrier)
	COM_INTERFACE_ENTRY(ISidewalkBarrier)
	COM_INTERFACE_ENTRY(IBarrier)

	COM_INTERFACE_ENTRY(IStructuredStorage2)

	COM_INTERFACE_ENTRY(ISupportErrorInfo)

//   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSidewalkBarrier)
//	CONNECTION_POINT_ENTRY(IID_ISidewalkBarrierEvents)
END_CONNECTION_POINT_MAP()

private:
   CComPtr<ICompositeShape> m_CompShape;
   CComPtr<IShape> m_ExtBarrier;
   CComPtr<IShape> m_IntBarrier;
   SidewalkPositionType m_SidewalkPosition;
   Float64 m_H1, m_H2, m_W;
   int m_Configuration;
   TrafficBarrierOrientation m_Orientation;
   Float64 m_ConnectionWidth;
   VARIANT_BOOL m_bInteriorStructurallyContinuous;
   VARIANT_BOOL m_bSidewalkStructurallyContinuous;
   VARIANT_BOOL m_bExteriorStructurallyContinuous;

   int m_idxExteriorBarrier;
   int m_idxSidewalk;
   int m_idxInteriorBarrier;

   CComPtr<IMaterial> m_Material;
   CComPtr<IPath> m_Path;

   // ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISidewalkBarrier
public:
	STDMETHOD(put_Barrier1)(/*[in]*/IShape* shape,/*[in]*/Float64 connectionWidth);
	STDMETHOD(put_Barrier2)(/*[in]*/IShape* shape,/*[in]*/Float64 h1,/*[in]*/Float64 h2,/*[in]*/Float64 w,/*[in]*/TrafficBarrierOrientation orientation,/*[in]*/ SidewalkPositionType swPosition,/*[in]*/Float64 connectionWidth);
	STDMETHOD(put_Barrier3)(/*[in]*/IShape* extShape,/*[in]*/Float64 h1,/*[in]*/Float64 h2,/*[in]*/Float64 w,/*[in]*/IShape* intShape,/*[in]*/TrafficBarrierOrientation orientation,/*[in]*/ SidewalkPositionType swPosition,/*[in]*/Float64 connectionWidth);
   STDMETHOD(get_SidewalkWidth)(/*[out,retval]*/Float64* width);
   STDMETHOD(get_ExteriorBarrierShape)(/*[out,retval]*/ IShape** shape);
   STDMETHOD(get_SidewalkShape)(/*[out,retval]*/ IShape** shape);
   STDMETHOD(get_InteriorBarrierShape)(/*[out,retval]*/ IShape** shape);
   STDMETHOD(put_IsInteriorStructurallyContinuous)(/*[in]*/VARIANT_BOOL bContinuous);
   STDMETHOD(put_IsSidewalkStructurallyContinuous)(/*[in]*/VARIANT_BOOL bContinuous);
	STDMETHOD(put_IsExteriorStructurallyContinuous)(/*[in]*/VARIANT_BOOL bContinuous);

// IBarrier
public:
   STDMETHOD(get_Shape)(/*[out,retval]*/ IShape** shape);
   STDMETHOD(get_StructuralShape)(/*[out,retval]*/ IShape** shape);
	STDMETHOD(get_Material)(/*[out,retval]*/ IMaterial** material);
	STDMETHOD(putref_Material)(/*[in]*/ IMaterial* material);
	STDMETHOD(get_Path)(/*[out,retval]*/ IPath** path);
	STDMETHOD(put_Path)(/*[in]*/ IPath* path);
   STDMETHOD(get_ConnectionWidth)(/*[in]*/ Float64 location,/*[out,retval]*/Float64* width);
   STDMETHOD(get_IsStructurallyContinuous)(/*[out,retval]*/VARIANT_BOOL* pbContinuous);
	STDMETHOD(put_IsStructurallyContinuous)(/*[in]*/VARIANT_BOOL bContinuous);
   STDMETHOD(Clone)(/*[out,retval]*/IBarrier** barrier);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);
};

#endif //__SIDEWALKBARRIER_H_
