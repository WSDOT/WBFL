///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

// LinearCrossBeam.h : Declaration of the CLinearCrossBeam

#pragma once

#include "resource.h"       // main symbols
#include "ColumnLayout.h"

/////////////////////////////////////////////////////////////////////////////
// CLinearCrossBeam
class ATL_NO_VTABLE CLinearCrossBeam : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLinearCrossBeam, &CLSID_LinearCrossBeam>,
	public ISupportErrorInfo,
	public ILinearCrossBeam,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CLinearCrossBeam,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CLinearCrossBeam()
	{
      m_bIsLXBDirty = true;
      m_bIsUXBDirty = true;
      m_bIsBXBDirty = true;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void Invalidate();

DECLARE_REGISTRY_RESOURCEID(IDR_LINEARCROSSBEAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLinearCrossBeam)
	COM_INTERFACE_ENTRY(ICrossBeam)
   COM_INTERFACE_ENTRY(ILinearCrossBeam)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   IPier* m_pPier; // weak reference
   Float64 m_H1, m_H2, m_H3, m_H4, m_H5;
   Float64 m_X1, m_X2, m_X3, m_X4;
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

// ILinearCrossBeam
public:
   STDMETHOD(put_H1)(/*[in]*/Float64 H1) override;
   STDMETHOD(get_H1)(/*[out,retval]*/Float64* pH1) override;
   STDMETHOD(put_H2)(/*[in]*/Float64 H2) override;
   STDMETHOD(get_H2)(/*[out,retval]*/Float64* pH2) override;
   STDMETHOD(put_H3)(/*[in]*/Float64 H3) override;
   STDMETHOD(get_H3)(/*[out,retval]*/Float64* pH3) override;
   STDMETHOD(put_H4)(/*[in]*/Float64 H4) override;
   STDMETHOD(get_H4)(/*[out,retval]*/Float64* pH4) override;
   STDMETHOD(put_H5)(/*[in]*/Float64 H5) override;
   STDMETHOD(get_H5)(/*[out,retval]*/Float64* pH5) override;
   STDMETHOD(put_X1)(/*[in]*/Float64 X1) override;
   STDMETHOD(get_X1)(/*[out,retval]*/Float64* pX1) override;
   STDMETHOD(put_X2)(/*[in]*/Float64 X2) override;
   STDMETHOD(get_X2)(/*[out,retval]*/Float64* pX2) override;
   STDMETHOD(put_X3)(/*[in]*/Float64 X3) override;
   STDMETHOD(get_X3)(/*[out,retval]*/Float64* pX3) override;
   STDMETHOD(put_X4)(/*[in]*/Float64 X4) override;
   STDMETHOD(get_X4)(/*[out,retval]*/Float64* pX4) override;
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

