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

// Pier.h : Declaration of the CBridgePier

#ifndef __PIER_H_
#define __PIER_H_

#include "resource.h"       // main symbols
#include "PierImpl.h"

class CSpan;

/////////////////////////////////////////////////////////////////////////////
// CBridgePier
// This can be any kind of pier object... pier, bent, temporary support, etc
class ATL_NO_VTABLE CBridgePier : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CBridgePier,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CBridgePier, &CLSID_BridgePier>,
   public CPierImpl,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CBridgePier,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IBridgePier,
   public IStructuredStorage2
{
public:
   CBridgePier()
	{
      m_pPierLine = NULL;
      m_pBridge   = NULL;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void Init(IGenericBridge* pBridge,IPierLine* pPierLine);

   static HRESULT ValidateOrientation(BSTR bstrOrientation);

DECLARE_REGISTRY_RESOURCEID(IDR_BRIDGEPIER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBridgePier)
   COM_INTERFACE_ENTRY(IPier)
	COM_INTERFACE_ENTRY(IBridgePier)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   IPierLine* m_pPierLine; // weak reference
   IGenericBridge* m_pBridge; // weak reference to parent

   CPierImpl m_PierImpl; // provides most of the implemenation of IPier

   CComPtr<IStation> m_TestStation; // this object is only used when this BridgePier object is used as a test value
   // for std::lower_bound, or other such searches. 

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPier
public:
   STDMETHOD(get_Bridge)(/*[out,retval]*/IGenericBridge** ppBridge);
   STDMETHOD(put_Type)(/*[in]*/PierType type) { return m_PierImpl.put_Type(type); }
   STDMETHOD(get_Type)(/*[out,retval]*/PierType* type) { return m_PierImpl.get_Type(type); }
   STDMETHOD(get_DeckProfile)(/*[out,retval]*/IPoint2dCollection** ppPoints);
   STDMETHOD(get_DeckThickness)(/*[out,retval]*/Float64* pTDeck);
   STDMETHOD(get_CurbLineOffset)(/*[in]*/DirectionType side,/*[in]*/CurbLineMeasurementType clMeasure,/*[out,retval]*/Float64* pCLO);
   STDMETHOD(get_CurbToCurbWidth)(/*[in]*/CurbLineMeasurementType clMeasure,/*[out,retval]*/Float64* pWcc) { return m_PierImpl.get_CurbToCurbWidth(clMeasure,pWcc); }
   STDMETHOD(putref_SkewAngle)(/*[in]*/IAngle* pSkew) { return m_PierImpl.putref_SkewAngle(pSkew); }
   STDMETHOD(get_SkewAngle)(/*[out,retval]*/IAngle** ppSkew);
   STDMETHOD(putref_CrossBeam)(/*[in]*/ICrossBeam* pCrossBeam) { return m_PierImpl.putref_CrossBeam(pCrossBeam); }
   STDMETHOD(get_CrossBeam)(/*[out,retval]*/ICrossBeam** ppCrossBeam) { return m_PierImpl.get_CrossBeam(ppCrossBeam); }
   STDMETHOD(putref_BearingLayout)(/*[in]*/IBearingLayout* pBearingLayout) { return m_PierImpl.putref_BearingLayout(pBearingLayout); }
   STDMETHOD(get_BearingLayout)(/*[out,retval]*/IBearingLayout** ppBearingLayout) { return m_PierImpl.get_BearingLayout(ppBearingLayout); }
   STDMETHOD(putref_ColumnLayout)(/*[in]*/IColumnLayout* pColumnLayout) { return m_PierImpl.putref_ColumnLayout(pColumnLayout); }
   STDMETHOD(get_ColumnLayout)(/*[out,retval]*/IColumnLayout** ppColumnLayout) { return m_PierImpl.get_ColumnLayout(ppColumnLayout); }
   STDMETHOD(get_Column)(/*[in]*/ ColumnIndexType columnIdx,/*[out,retval]*/IColumn* *column) { return m_PierImpl.get_Column(columnIdx,column); }
   STDMETHOD(ConvertCrossBeamToCurbLineCoordinate)(/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pXcl) { return m_PierImpl.ConvertCrossBeamToCurbLineCoordinate(Xxb,pXcl); }
   STDMETHOD(ConvertCurbLineToCrossBeamCoordinate)(/*[in]*/Float64 Xcl,/*[out,retval]*/Float64* pXxb) { return m_PierImpl.ConvertCurbLineToCrossBeamCoordinate(Xcl,pXxb); }
   STDMETHOD(ConvertPierToCrossBeamCoordinate)(/*[in]*/Float64 Xp,/*[out,retval]*/Float64* pXxb) { return m_PierImpl.ConvertPierToCrossBeamCoordinate(Xp,pXxb); }
   STDMETHOD(ConvertCrossBeamToPierCoordinate)(/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pXp) { return m_PierImpl.ConvertCrossBeamToPierCoordinate(Xxb,pXp); }
   STDMETHOD(ConvertPierToCurbLineCoordinate)(/*[in]*/Float64 Xp,/*[out,retval]*/Float64* pXcl) { return m_PierImpl.ConvertPierToCurbLineCoordinate(Xp,pXcl); }
   STDMETHOD(ConvertCurbLineToPierCoordinate)(/*[in]*/Float64 Xcl,/*[out,retval]*/Float64* pXp) { return m_PierImpl.ConvertCurbLineToPierCoordinate(Xcl,pXp); }
   STDMETHOD(get_Elevation)(/*[in]*/Float64 Xcl,/*[out,retval]*/Float64* pElev) { return m_PierImpl.get_Elevation(Xcl,pElev); }
   STDMETHOD(get_CurbLineElevation)(/*[in]*/DirectionType side,/*[out,retval]*/Float64* pElev) { return m_PierImpl.get_CurbLineElevation(side,pElev); }

// IBridgePier
public:
   STDMETHOD(get_Index)(/*[out,retval]*/PierIndexType* pIndex);
   STDMETHOD(get_ID)(/*[out,retval]*/PierIDType* pID);
   STDMETHOD(get_Station)(/*[out,retval]*/IStation* *station);
   STDMETHOD(get_Direction)(/*[out,retval]*/ IDirection* *direction);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);
};

#endif //__PIER_H_
