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


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICrossBeam
public:
   STDMETHOD(putref_Pier)(/*[in]*/IPier* pPier);
   STDMETHOD(get_Pier)(/*[out,retval]*/IPier** ppPier);
   STDMETHOD(get_Length)(/*[out,retval]*/ Float64* length);
   STDMETHOD(get_Depth)(/*[in]*/StageIndexType stageIdx,/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pDepth);
   STDMETHOD(get_FullDepth)(/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pDepth);
   STDMETHOD(get_Profile)(/*[in]*/StageIndexType stageIdx,/*[out,retval]*/IShape** ppShape);
   STDMETHOD(get_TopSurface)(/*[in]*/StageIndexType stageIdx,/*[out,retval]*/IPoint2dCollection** ppPoints);
   STDMETHOD(get_BottomSurface)(/*[in]*/StageIndexType stageIdx,/*[out,retval]*/IPoint2dCollection** ppPoints);
   STDMETHOD(get_BasicShape)(/*[in]*/Float64 Xxb,/*[out,retval]*/IShape** ppShape);
   STDMETHOD(get_Shape)(/*[in]*/StageIndexType stageIdx,/*[in]*/Float64 Xxb,/*[out,retval]*/IShape** ppShape);
   STDMETHOD(get_RebarLayout)(/*[out,retval]*/IRebarLayout** ppRebarLayout);
   STDMETHOD(putref_RebarLayout)(/*[in]*/IRebarLayout* pRebarLayout);

// ILinearCrossBeam
public:
   STDMETHOD(put_H1)(/*[in]*/Float64 H1);
   STDMETHOD(get_H1)(/*[out,retval]*/Float64* pH1);
   STDMETHOD(put_H2)(/*[in]*/Float64 H2);
   STDMETHOD(get_H2)(/*[out,retval]*/Float64* pH2);
   STDMETHOD(put_H3)(/*[in]*/Float64 H3);
   STDMETHOD(get_H3)(/*[out,retval]*/Float64* pH3);
   STDMETHOD(put_H4)(/*[in]*/Float64 H4);
   STDMETHOD(get_H4)(/*[out,retval]*/Float64* pH4);
   STDMETHOD(put_H5)(/*[in]*/Float64 H5);
   STDMETHOD(get_H5)(/*[out,retval]*/Float64* pH5);
   STDMETHOD(put_X1)(/*[in]*/Float64 X1);
   STDMETHOD(get_X1)(/*[out,retval]*/Float64* pX1);
   STDMETHOD(put_X2)(/*[in]*/Float64 X2);
   STDMETHOD(get_X2)(/*[out,retval]*/Float64* pX2);
   STDMETHOD(put_X3)(/*[in]*/Float64 X3);
   STDMETHOD(get_X3)(/*[out,retval]*/Float64* pX3);
   STDMETHOD(put_X4)(/*[in]*/Float64 X4);
   STDMETHOD(get_X4)(/*[out,retval]*/Float64* pX4);
   STDMETHOD(put_W1)(/*[in]*/Float64 W1);
   STDMETHOD(get_W1)(/*[out,retval]*/Float64* pW1);
   STDMETHOD(put_W2)(/*[in]*/Float64 W2);
   STDMETHOD(get_W2)(/*[out,retval]*/Float64* pW2);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);

private:
   HRESULT GetUpperXBeamProfile(IPoint2dCollection** ppPoints);
   HRESULT GetLowerXBeamProfile(IPoint2dCollection** ppPoints);
   HRESULT GetBottomXBeamProfile(IPoint2dCollection** ppPoints);
   HRESULT GetLowerXBeamShape(Float64 Xxb,IShape** ppShape);
   HRESULT GetUpperXBeamShape(Float64 Xxb,IShape** ppShape);

   HRESULT TrimLeftToLine(IPoint2dCollection* pPoints,ILine2d* pLine);
   HRESULT TrimRightToLine(IPoint2dCollection* pPoints,ILine2d* pLine);
};

