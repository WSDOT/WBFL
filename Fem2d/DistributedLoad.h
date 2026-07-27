///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
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

// DistributedLoad.h : Declaration of the CDistributedLoad

#pragma once

#include "resource.h"       // main symbols
#include "CircularChild.h"

class ModelEvents;
/////////////////////////////////////////////////////////////////////////////
// CDistributedLoad
// Thin COM facade over WBFL::FEA2D::DistributedLoad. The legacy MbrLoad
// interface is gone - see the note in PointLoad.h.
class ATL_NO_VTABLE CDistributedLoad :
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CDistributedLoad,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dDistributedLoad
{
public:
   CDistributedLoad():
   m_pModel(0),
   m_pLoading(0),
   m_pCore(0)
	{
	}

   virtual ~CDistributedLoad()
	{
	}

   void Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, WBFL::FEA2D::DistributedLoad* pCore);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDistributedLoad)
	COM_INTERFACE_ENTRY(IFem2dDistributedLoad)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IFem2dDistributedLoad
public:
	STDMETHOD(get_WEnd)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_WEnd)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_WStart)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_WStart)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_EndLocation)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_EndLocation)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_StartLocation)(/*[out, retval]*/ Float64  *pVal) override;
	STDMETHOD(put_StartLocation)(/*[in]*/ Float64  newVal) override;
	STDMETHOD(get_Direction)(/*[out, retval]*/ Fem2dLoadDirection *pVal) override;
	STDMETHOD(put_Direction)(/*[in]*/ Fem2dLoadDirection newVal) override;
	STDMETHOD(get_Orientation)(/*[out, retval]*/ Fem2dLoadOrientation *pVal) override;
	STDMETHOD(put_Orientation)(/*[in]*/ Fem2dLoadOrientation newVal) override;
	STDMETHOD(get_MemberID)(/*[out, retval]*/ MemberIDType *pVal) override;
	STDMETHOD(put_MemberID)(/*[in]*/ MemberIDType newVal) override;
	STDMETHOD(get_ID)(/*[out, retval]*/ LoadIDType *pVal) override;
	STDMETHOD(get_Loading)(/*[out, retval]*/ LoadCaseIDType *pVal) override;

private:
   ModelEvents* m_pModel; // for sending events back to model
   IFem2dLoading* m_pLoading;
   WBFL::FEA2D::DistributedLoad* m_pCore; // non-owning; owned by the FEA2D core Loading
};

