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

// MemberStrain.h : Declaration of the CMemberStrain

#pragma once

#include "resource.h"       // main symbols
#include "CircularChild.h"

class ModelEvents;
/////////////////////////////////////////////////////////////////////////////
// CMemberStrain
// Thin COM facade over WBFL::FEA2D::MemberStrain. The legacy MbrLoad
// interface is gone - see the note in PointLoad.h.
class ATL_NO_VTABLE CMemberStrain :
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CMemberStrain,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dMemberStrain
{
public:
   CMemberStrain():
   m_pModel(0),
   m_pLoading(0),
   m_pCore(0)
	{
	}

   virtual ~CMemberStrain()
   {}

   void Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, WBFL::FEA2D::MemberStrain* pCore);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMemberStrain)
	COM_INTERFACE_ENTRY(IFem2dMemberStrain)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IFem2dMemberStrain
public:
	STDMETHOD(get_Loading)(/*[out, retval]*/ LoadCaseIDType *pVal) override;
   STDMETHOD(get_StartLocation)(/*[out, retval]*/ Float64  *pVal) override;
	STDMETHOD(put_StartLocation)(/*[in]*/ Float64  newVal) override;
	STDMETHOD(get_EndLocation)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_EndLocation)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_CurvatureStrain)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_CurvatureStrain)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_AxialStrain)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_AxialStrain)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_MemberID)(/*[out, retval]*/ MemberIDType *pVal) override;
	STDMETHOD(put_MemberID)(/*[in]*/ MemberIDType newVal) override;
	STDMETHOD(get_ID)(/*[out, retval]*/ LoadIDType *pVal) override;

private:
   ModelEvents* m_pModel; // for sending events back to model
   IFem2dLoading* m_pLoading;
   WBFL::FEA2D::MemberStrain* m_pCore; // non-owning; owned by the FEA2D core Loading
};

