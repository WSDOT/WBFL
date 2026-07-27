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

// PointLoad.h : Declaration of the CPointLoad

#pragma once

#include "resource.h"       // main symbols
#include "CircularChild.h"

class ModelEvents;
/////////////////////////////////////////////////////////////////////////////
// CPointLoad
// Thin COM facade over WBFL::FEA2D::PointLoad. The legacy MbrLoad interface
// (GetForceVector/GetInternalForces/GetDispVector/GetDeflection/
// GetOriginForces - fixed-end-force computation for the stiffness solver) is
// gone: that numerics now lives entirely inside WBFL::FEA2D::Member/Beam,
// private to the FEA2D core, so CPointLoad no longer needs to implement it.
class ATL_NO_VTABLE CPointLoad :
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPointLoad,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dPointLoad
{
public:
	CPointLoad():
   m_pModel(0),
   m_pLoading(0),
   m_pCore(0)
	{
	}

	virtual ~CPointLoad()
	{
	}

   void Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, WBFL::FEA2D::PointLoad* pCore);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPointLoad)
	COM_INTERFACE_ENTRY(IFem2dPointLoad)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IFem2dPointLoad
public:
	STDMETHOD(get_Location)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Location)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(GetForce)(/*[out]*/Float64* Fx, /*[out]*/Float64* Fy, /*[out]*/Float64* Mz) override;
	STDMETHOD(SetForce)(/*[in]*/Float64 Fx, /*[in]*/Float64 Fy, /*[in]*/Float64 Mz) override;
	STDMETHOD(get_Mz)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Mz)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Fy)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Fy)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Fx)(/*[out, retval]*/ Float64  *pVal) override;
	STDMETHOD(put_Fx)(/*[in]*/ Float64  newVal) override;
	STDMETHOD(get_Orientation)(/*[out, retval]*/ Fem2dLoadOrientation *pVal) override;
	STDMETHOD(put_Orientation)(/*[in]*/ Fem2dLoadOrientation newVal) override;
	STDMETHOD(get_MemberID)(/*[out, retval]*/ MemberIDType *pVal) override;
	STDMETHOD(put_MemberID)(/*[in]*/ MemberIDType newVal) override;
	STDMETHOD(get_ID)(/*[out, retval]*/ LoadIDType *pVal) override;
	STDMETHOD(get_Loading)(/*[out, retval]*/ LoadCaseIDType *pVal) override;

private:
   ModelEvents* m_pModel; // for sending events back to model
   IFem2dLoading* m_pLoading;
   WBFL::FEA2D::PointLoad* m_pCore; // non-owning; owned by the FEA2D core Loading
};

