///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright � 1999-2025  Washington State Department of Transportation
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

// Pier.h : Declaration of the CPier
#pragma once

#include "resource.h"       // main symbols
#include "PierImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CPier
class ATL_NO_VTABLE CPier : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPier, &CLSID_Pier>,
	public ISupportErrorInfo,
	public IPierEx,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CPier,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CPier()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_PIER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPier)
   COM_INTERFACE_ENTRY(IPierEx)
	COM_INTERFACE_ENTRY(IPier)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   CPierImpl m_PierImpl;

   CComPtr<IPoint2dCollection> m_DeckProfile;
   Float64 m_tDeck;
   Float64 m_CurbLineOffset[2];

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPier
public:
   STDMETHOD(put_Type)(/*[in]*/PierType type) override { return m_PierImpl.put_Type(type); }
   STDMETHOD(get_Type)(/*[out,retval]*/PierType* type) override { return m_PierImpl.get_Type(type); }
   STDMETHOD(get_DeckProfile)(/*[out,retval]*/IPoint2dCollection** ppPoints) override;
   STDMETHOD(get_DeckThickness)(/*[out,retval]*/Float64* pTDeck) override;
   STDMETHOD(get_CurbLineOffset)(/*[in]*/DirectionType side,/*[in]*/CurbLineMeasurementType clMeasure,/*[out,retval]*/Float64* pCLO) override;
   STDMETHOD(get_CurbToCurbWidth)(/*[in]*/CurbLineMeasurementType clMeasure,/*[out,retval]*/Float64* pWcc) override;
   STDMETHOD(putref_SkewAngle)(/*[in]*/IAngle* pSkew) override { return m_PierImpl.putref_SkewAngle(pSkew); }
   STDMETHOD(get_SkewAngle)(/*[out,retval]*/IAngle** ppSkew) override { return m_PierImpl.get_SkewAngle(ppSkew); }
   STDMETHOD(putref_CrossBeam)(/*[in]*/ICrossBeam* pCrossBeam)  override { return m_PierImpl.putref_CrossBeam(pCrossBeam); }
   STDMETHOD(get_CrossBeam)(/*[out,retval]*/ICrossBeam** ppCrossBeam) override { return m_PierImpl.get_CrossBeam(ppCrossBeam); }
   STDMETHOD(putref_ColumnLayout)(/*[in]*/IColumnLayout* pColumnLayout) override { return m_PierImpl.putref_ColumnLayout(pColumnLayout); }
   STDMETHOD(putref_BearingLayout)(/*[in]*/IBearingLayout* pBearingLayout) override { return m_PierImpl.putref_BearingLayout(pBearingLayout); }
   STDMETHOD(get_BearingLayout)(/*[out,retval]*/IBearingLayout** ppBearingLayout) override { return m_PierImpl.get_BearingLayout(ppBearingLayout); }
   STDMETHOD(get_ColumnLayout)(/*[out,retval]*/IColumnLayout** ppColumnLayout) override { return m_PierImpl.get_ColumnLayout(ppColumnLayout); }
   STDMETHOD(get_Column)(/*[in]*/ ColumnIndexType columnIdx,/*[out,retval]*/IColumn* *column)  override { return m_PierImpl.get_Column(columnIdx,column); }
   STDMETHOD(ConvertCrossBeamToCurbLineCoordinate)(/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pXcl) override { return m_PierImpl.ConvertCrossBeamToCurbLineCoordinate(Xxb,pXcl); }
   STDMETHOD(ConvertCurbLineToCrossBeamCoordinate)(/*[in]*/Float64 Xcl,/*[out,retval]*/Float64* pXxb) override { return m_PierImpl.ConvertCurbLineToCrossBeamCoordinate(Xcl,pXxb); }
   STDMETHOD(ConvertPierToCrossBeamCoordinate)(/*[in]*/Float64 Xp,/*[out,retval]*/Float64* pXxb) override { return m_PierImpl.ConvertPierToCrossBeamCoordinate(Xp,pXxb); }
   STDMETHOD(ConvertCrossBeamToPierCoordinate)(/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pXp) override { return m_PierImpl.ConvertCrossBeamToPierCoordinate(Xxb,pXp); }
   STDMETHOD(ConvertPierToCurbLineCoordinate)(/*[in]*/Float64 Xp,/*[out,retval]*/Float64* pXcl) override { return m_PierImpl.ConvertPierToCurbLineCoordinate(Xp,pXcl); }
   STDMETHOD(ConvertCurbLineToPierCoordinate)(/*[in]*/Float64 Xcl,/*[out,retval]*/Float64* pXp) override { return m_PierImpl.ConvertCurbLineToPierCoordinate(Xcl,pXp); }
   STDMETHOD(get_Elevation)(/*[in]*/Float64 Xcl,/*[out,retval]*/Float64* pElev) override { return m_PierImpl.get_Elevation(Xcl,pElev); }
   STDMETHOD(get_CurbLineElevation)(/*[in]*/DirectionType side,/*[out,retval]*/Float64* pElev) override { return m_PierImpl.get_CurbLineElevation(side,pElev); }

// IPierEx
public:
   STDMETHOD(putref_DeckProfile)(/*[in]*/IPoint2dCollection* pPoints) override;
   STDMETHOD(put_DeckThickness)(/*[in]*/Float64 tDeck) override;
   STDMETHOD(put_CurbLineOffset)(/*[in]*/DirectionType side,/*[in]*/Float64 clo) override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};

