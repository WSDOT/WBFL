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

// JointDeflection.h : Declaration of the CJointDeflection

#pragma once

#include "resource.h"       // main symbols
#include "CircularChild.h"

class ModelEvents;
/////////////////////////////////////////////////////////////////////////////
// CJointDeflection
// Thin COM facade over WBFL::FEA2D::JointDisplacement.
class ATL_NO_VTABLE CJointDeflection :
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CJointDeflection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dJointDeflection
{
public:
   CJointDeflection():
   m_pModel(0),
   m_pLoading(0),
   m_pCore(0)
	{
	}

   virtual ~CJointDeflection()
   {}


   void Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, WBFL::FEA2D::JointDisplacement* pCore);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CJointDeflection)
	COM_INTERFACE_ENTRY(IFem2dJointDeflection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IFem2dJointDeflection
public:
	STDMETHOD(get_Loading)(/*[out, retval]*/ LoadCaseIDType *pVal) override;
	STDMETHOD(GetDeflection)(/*[out]*/Float64* Dx, /*[out]*/Float64* Dy, /*[out]*/Float64* Rz) override;
	STDMETHOD(SetDeflection)(/*[in]*/Float64 Dx, /*[in]*/Float64 Dy, /*[in]*/Float64 Rz) override;
	STDMETHOD(get_Rz)(/*[out, retval]*/ Float64  *pVal) override;
	STDMETHOD(put_Rz)(/*[in]*/ Float64  newVal) override;
	STDMETHOD(get_Dy)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Dy)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Dx)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Dx)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_JointID)(/*[out, retval]*/ JointIDType *pVal) override;
	STDMETHOD(put_JointID)(/*[in]*/ JointIDType newVal) override;
	STDMETHOD(get_ID)(/*[out, retval]*/ LoadIDType *pVal) override;

private:
   ModelEvents* m_pModel; // for sending events back to model
   IFem2dLoading* m_pLoading;
   WBFL::FEA2D::JointDisplacement* m_pCore; // non-owning; owned by the FEA2D core Loading

};

