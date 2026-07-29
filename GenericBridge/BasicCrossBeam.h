///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2026  Washington State Department of Transportation
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

// BasicCrossBeam.h : Declaration of the CBasicCrossBeam

#pragma once

#include "resource.h"       // main symbols
#include "ColumnLayout.h"

/////////////////////////////////////////////////////////////////////////////
// CBasicCrossBeam
class ATL_NO_VTABLE CBasicCrossBeam : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBasicCrossBeam, &CLSID_BasicCrossBeam>,
	public ISupportErrorInfo,
	public IBasicCrossBeam,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CBasicCrossBeam,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CBasicCrossBeam()
	{
      m_bIsLXBDirty = true;
      m_bIsUXBDirty = true;
      m_bIsBXBDirty = true;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void Invalidate();

DECLARE_REGISTRY_RESOURCEID(IDR_BASICCROSSBEAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBasicCrossBeam)
	COM_INTERFACE_ENTRY(ICrossBeam)
   COM_INTERFACE_ENTRY(IBasicCrossBeam)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   IPier* m_pPier; // weak reference
   Float64 m_H1L, m_H1R, m_H2L, m_H2R, m_HU;
   Float64 m_X1L, m_X1R, m_X2L, m_X2R;
   Float64 m_W1, m_W2;
   CComPtr<IRebarLayout> m_RebarLayout;

   bool m_bIsLXBDirty;
   bool m_bIsUXBDirty;
   bool m_bIsBXBDirty;
   CComPtr<IPoint2dCollection> m_LXBProfile;
   CComPtr<IPoint2dCollection> m_UXBProfile;
   CComPtr<IPoint2dCollection> m_BXBProfile;

   CComPtr<IGeomUtil2d> m_GeomUtil;


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICrossBeam
public:
   STDMETHOD(putref_Pier)(/*[in]*/IPier* pPier) override;
   STDMETHOD(get_Pier)(/*[out,retval]*/IPier** ppPier) override;
   STDMETHOD(get_Length)(/*[in]*/XBeamLocation location,/*[out,retval]*/ Float64* length) override;
   STDMETHOD(get_Depth)(/*[in]*/StageIndexType stageIdx,/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pDepth) override;
   STDMETHOD(get_FullDepth)(/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pDepth) override;
   STDMETHOD(get_Profile)(/*[in]*/StageIndexType stageIdx,/*[out,retval]*/IShape** ppShape) override;
   STDMETHOD(get_TopSurface)(/*[in]*/StageIndexType stageIdx,/*[out,retval]*/IPoint2dCollection** ppPoints) override;
   STDMETHOD(get_BottomSurface)(/*[in]*/StageIndexType stageIdx,/*[out,retval]*/IPoint2dCollection** ppPoints) override;
   STDMETHOD(get_Surface)(/*[in]*/CrossBeamRebarDatum datum, /*[in]*/Float64 offset, /*[out, retval]*/IPoint2dCollection** ppPoints) override;
   STDMETHOD(get_BasicShape)(/*[in]*/Float64 Xxb,/*[out,retval]*/IShape** ppShape) override;
   STDMETHOD(get_Shape)(/*[in]*/StageIndexType stageIdx,/*[in]*/Float64 Xxb,/*[out,retval]*/IShape** ppShape) override;
   STDMETHOD(get_RebarLayout)(/*[out,retval]*/IRebarLayout** ppRebarLayout) override;
   STDMETHOD(putref_RebarLayout)(/*[in]*/IRebarLayout* pRebarLayout) override;

// IBasicCrossBeam
public:
   STDMETHOD(put_H1L)(/*[in]*/Float64 H1L) override;
   STDMETHOD(get_H1L)(/*[out,retval]*/Float64* pH1L) override;
   STDMETHOD(put_H1R)(/*[in]*/Float64 H1R) override;
   STDMETHOD(get_H1R)(/*[out,retval]*/Float64* pH1R) override;
   STDMETHOD(put_H2L)(/*[in]*/Float64 H2L) override;
   STDMETHOD(get_H2L)(/*[out,retval]*/Float64* pH2L) override;
   STDMETHOD(put_H2R)(/*[in]*/Float64 H2R) override;
   STDMETHOD(get_H2R)(/*[out,retval]*/Float64* pH2R) override;

   STDMETHOD(put_X1L)(/*[in]*/Float64 X1L) override;
   STDMETHOD(get_X1L)(/*[out,retval]*/Float64* pX1L) override;
   STDMETHOD(put_X1R)(/*[in]*/Float64 X1R) override;
   STDMETHOD(get_X1R)(/*[out,retval]*/Float64* pX1R) override;
   STDMETHOD(put_X2L)(/*[in]*/Float64 X2L) override;
   STDMETHOD(get_X2L)(/*[out,retval]*/Float64* pX2L) override;
   STDMETHOD(put_X2R)(/*[in]*/Float64 X2R) override;
   STDMETHOD(get_X2R)(/*[out,retval]*/Float64* pX2R) override;

   STDMETHOD(put_HU)(/*[in]*/Float64 HU) override;
   STDMETHOD(get_HU)(/*[out,retval]*/Float64* pHU) override;

   STDMETHOD(put_W1)(/*[in]*/Float64 W1) override;
   STDMETHOD(get_W1)(/*[out,retval]*/Float64* pW1) override;
   STDMETHOD(put_W2)(/*[in]*/Float64 W2) override;
   STDMETHOD(get_W2)(/*[out,retval]*/Float64* pW2) override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;

private:
   HRESULT GetUpperXBeamProfile(IPoint2dCollection** ppPoints,bool bClone = true);
   HRESULT GetLowerXBeamProfile(IPoint2dCollection** ppPoints, bool bClone = true);
   HRESULT GetBottomXBeamProfile(IPoint2dCollection** ppPoints, bool bClone = true);
   HRESULT GetLowerXBeamShape(Float64 Xxb,IShape** ppShape);
   HRESULT GetUpperXBeamShape(Float64 Xxb,IShape** ppShape);

   void GetUpperXBeamDeltas(Float64* pUXBleft, Float64* pUXBright);
};

