///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

// GirderSpacing.h : Declaration of the CGirderSpacing

#ifndef __GIRDERSPACING_H_
#define __GIRDERSPACING_H_

#include "resource.h"       // main symbols
#include <vector>
#include "GenericBridgeCP.h"
#include <MathEx.h>

class CPier;

/////////////////////////////////////////////////////////////////////////////
// CGirderSpacing
class ATL_NO_VTABLE CGirderSpacing : 
	public CComObjectRootEx<CComSingleThreadModel>,
   //public CComRefCountTracer<CGirderSpacing,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CGirderSpacing, &CLSID_GirderSpacing>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CGirderSpacing>,
	public IGirderSpacing,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CGirderSpacing,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public CProxyIGirderSpacingEvents< CGirderSpacing >
{
public:
	CGirderSpacing()
	{
      m_MeasureType     = mtAlongItem;
      m_MeasureLocation = mlPierLine;

      m_RefGirderIdx    = ALL_GIRDERS;
      m_RefGirderOffset = 0;
      m_RefGirderOffsetType = otBridge;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_GIRDERSPACING)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGirderSpacing)
	COM_INTERFACE_ENTRY(IGirderSpacing)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IObjectSafety)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CGirderSpacing)
   CONNECTION_POINT_ENTRY(IID_IGirderSpacingEvents)
END_CONNECTION_POINT_MAP()

public:
   // some back door functions CSpan will call to manage the girder spacing count
   void SetBridge(IGenericBridge* pBridge);
   void SetPier(CPier* pPier,EndType end);
   void SetGirderCount(GirderIndexType nGirders);
   GirderIndexType GetGirderCount();
   void AddGirders(GirderIndexType nGirders);
   void RemoveGirders(GirderIndexType nGirders);

   void GetSpan(ISpan** ppSpan);

private:
   IGenericBridge* m_pBridge; // weak reference to parent
   CPier* m_pPier;
   EndType m_SpanEnd; // end of span this girder spacing is associted with
   MeasurementType m_MeasureType;
   MeasurementLocation m_MeasureLocation;
   GirderIndexType m_RefGirderIdx;
   Float64 m_RefGirderOffset;
   OffsetType m_RefGirderOffsetType;
   std::vector<Float64> m_Spacing; // spacing measured
   Float64 m_BearingOffset; // distance from CL pier to CL bearing measured normal to CL pier

   std::vector<Float64> m_Haunch; // distance from top of girder to bottom of slab at intersection of CL Bearing and CL Girder

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IGirderSpacing
public:
   STDMETHOD(SetRefGirder)(/*[in]*/GirderIndexType refGirderIdx,/*[in]*/Float64 refGirderOffset,/*[in]*/OffsetType refGirderOffsetType);
   STDMETHOD(put_RefGirder)(/*[in]*/GirderIndexType refGirderIdx);
	STDMETHOD(get_RefGirder)(/*[out,retval]*/GirderIndexType* refGirderIdx);
	STDMETHOD(put_RefGirderOffset)(/*[in]*/Float64 refGirderOffset);
	STDMETHOD(get_RefGirderOffset)(/*[out,retval]*/Float64* refGirderOffset);
	STDMETHOD(put_RefGirderOffsetType)(/*[in]*/OffsetType refGirderOffsetType);
	STDMETHOD(get_RefGirderOffsetType)(/*[out,retval]*/OffsetType* refGirderOffsetType);

   STDMETHOD(SetMeasurement)(/*[in]*/MeasurementLocation ml,/*[in]*/MeasurementType mt);
	STDMETHOD(get_MeasurementLocation)(/*[out,retval]*/MeasurementLocation* ml);
	STDMETHOD(put_MeasurementLocation)(/*[in]*/MeasurementLocation ml);
	STDMETHOD(get_MeasurementType)(/*[out,retval]*/MeasurementType* mt);
	STDMETHOD(put_MeasurementType)(/*[in]*/MeasurementType mt);
   STDMETHOD(get_Spacing)(/*[in]*/SpacingIndexType spaceIdx,/*[out,retval]*/Float64* spacing);
   STDMETHOD(put_Spacing)(/*[in]*/SpacingIndexType spaceIdx,/*[in]*/Float64 spacing);
   STDMETHOD(put_Spacings)(/*[in]*/IDblArray* spaces);
   STDMETHOD(get_Width)(/*[in]*/ Float64 distFromStartOfSpan,/*[in]*/MeasurementType measureType,/*[out,retval]*/Float64* width);
   STDMETHOD(get_WidthAtPier)(/*[in]*/MeasurementType measureType,/*[out,retval]*/Float64* width);
   STDMETHOD(get_WidthAtBearing)(/*[in]*/MeasurementType measureType,/*[out,retval]*/Float64* width);
   STDMETHOD(get_SpacingAlongGirder)(/*[in]*/ GirderIndexType gdrIdx, /*[in]*/ Float64 dist, /*[in]*/ DirectionType side,/*[out,retval]*/ Float64* space);
   STDMETHOD(get_GirderOffset)(/*[in]*/ GirderIndexType gdrIdx,/*[in]*/ MeasurementLocation measureLocation,/*[in]*/ MeasurementType measureType,/*[out,retval]*/Float64* offset);
   STDMETHOD(get_SpaceWidth)(/*[in]*/ SpacingIndexType spaceIdx,/*[in]*/ Float64 distFromStartOfSpan,/*[out,retval]*/Float64* space);
   STDMETHOD(get_GirderSpacing)(/*[in]*/SpacingIndexType spaceIdx,/*[in]*/MeasurementLocation ml,/*[in]*/MeasurementType mt,/*[out,retval]*/Float64* spacing);

   STDMETHOD(get_GirderHaunch)(/*[in]*/ GirderIndexType gdrIdx,/*[out,retval]*/Float64* pHaunch);
   STDMETHOD(put_GirderHaunch)(/*[in]*/ GirderIndexType gdrIdx,/*[in]*/Float64 haunch);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

private:
   HRESULT GetPierWidth(MeasurementLocation measureLocation,MeasurementType measureType,Float64* width);
};

#endif //__GIRDERSPACING_H_
