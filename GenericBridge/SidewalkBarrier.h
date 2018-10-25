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

// SidewalkBarrier.h : Declaration of the CSidewalkBarrier

#ifndef __SIDEWALKBARRIER_H_
#define __SIDEWALKBARRIER_H_

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CSidewalkBarrier
class ATL_NO_VTABLE CSidewalkBarrier : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSidewalkBarrier,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSidewalkBarrier, &CLSID_SidewalkBarrier>,
	public ISupportErrorInfo,
	public ISidewalkBarrier,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CSidewalkBarrier,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CSidewalkBarrier();
   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_SIDEWALKBARRIER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSidewalkBarrier)
	COM_INTERFACE_ENTRY(ISidewalkBarrier)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   CComPtr<IBarrier> m_ExtBarrier;
   CComPtr<IBarrier> m_IntBarrier;
   CComPtr<IPolyShape>   m_SidewalkShape;
   SidewalkPositionType m_SidewalkPosition;
   Float64 m_H1, m_H2, m_W;
   int m_Configuration;
   TrafficBarrierOrientation m_Orientation;
   VARIANT_BOOL m_bInteriorStructurallyContinuous;
   VARIANT_BOOL m_bSidewalkStructurallyContinuous;
   VARIANT_BOOL m_bExteriorStructurallyContinuous;

   CComPtr<IPath> m_Path;

   // ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISidewalkBarrier
public:
	STDMETHOD(put_Barrier1)(/*[in]*/IBarrier* extBarrier,/*[in]*/TrafficBarrierOrientation orientation) override;
	STDMETHOD(put_Barrier2)(/*[in]*/IBarrier* extBarrier,/*[in]*/Float64 h1,/*[in]*/Float64 h2,/*[in]*/Float64 swWidth,
                           /*[in]*/TrafficBarrierOrientation orientation,/*[in]*/ SidewalkPositionType swPosition);
	STDMETHOD(put_Barrier3)(/*[in]*/IBarrier* extBarrier,/*[in]*/Float64 h1,/*[in]*/Float64 h2,/*[in]*/Float64 swWidth,
                           /*[in]*/TrafficBarrierOrientation orientation,/*[in]*/ SidewalkPositionType swPosition,
                           /*[in]*/IBarrier* intBarrier);
   STDMETHOD(get_HasSidewalk)(/*[out,retval]*/VARIANT_BOOL *bHasSw) override;
   STDMETHOD(get_HasInteriorBarrier)(/*[out,retval]*/VARIANT_BOOL *bHasIb) override;
   STDMETHOD(get_SidewalkWidth)(/*[out,retval]*/Float64* width) override;
   STDMETHOD(get_ExteriorBarrier)(/*[out,retval]*/ IBarrier** barr) override;
   STDMETHOD(get_InteriorBarrier)(/*[out,retval]*/ IBarrier** barr) override;
   STDMETHOD(get_SidewalkShape)(/*[out,retval]*/ IShape** shape) override;
   STDMETHOD(get_Shape)(/*[out,retval]*/ IShape** shape) override;
   STDMETHOD(get_StructuralShape)(/*[out,retval]*/ IShape** shape) override;
	STDMETHOD(get_Path)(/*[out,retval]*/ IPath** path) override;
	STDMETHOD(put_Path)(/*[in]*/ IPath* path) override;
   STDMETHOD(put_IsInteriorStructurallyContinuous)(/*[in]*/VARIANT_BOOL bContinuous) override;
   STDMETHOD(put_IsSidewalkStructurallyContinuous)(/*[in]*/VARIANT_BOOL bContinuous) override;
	STDMETHOD(put_IsExteriorStructurallyContinuous)(/*[in]*/VARIANT_BOOL bContinuous) override;
	STDMETHOD(get_IsStructurallyContinuous)(/*[in]*/VARIANT_BOOL* pbContinuous) override;
	STDMETHOD(get_SidewalkPosition)(/*[out,retval]*/ SidewalkPositionType* posType) override;
	STDMETHOD(get_ExteriorCurbWidth)(/*[out,retval]*/ Float64* curbWidth) override;
	STDMETHOD(get_CurbWidth)(/*[out,retval]*/ Float64* curbWidth) override;
	STDMETHOD(get_OverlayToeWidth)(/*[out]*/ Float64* toeWidth) override;
   STDMETHOD(Clone)(/*[out,retval]*/ISidewalkBarrier** clone) override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};

#endif //__SIDEWALKBARRIER_H_
