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

// JointLoad.h : Declaration of the CJointLoad

#pragma once

#include "resource.h"       // main symbols
#include "CircularChild.h"

class ModelEvents;
/////////////////////////////////////////////////////////////////////////////
// CJointLoad
// Thin COM facade over WBFL::FEA2D::JointLoad. Holds no state of its own -
// every getter/setter delegates to the non-owning core pointer, and setters
// fire the legacy ON_LOAD_CHANGED event only when the core mutator reports
// an actual change (mirroring the original m_Fx != newVal guard).
class ATL_NO_VTABLE CJointLoad :
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CJointLoad,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dJointLoad
{
public:
   CJointLoad():
   m_pModel(0),
   m_pLoading(0),
   m_pCore(0)
	{
	}

   virtual ~CJointLoad()
   {;}


   // Binds this facade to an already-existing FEA2D core JointLoad - either
   // one just created via Loading::CreateJointLoad(), or one discovered while
   // rehydrating the COM wrappers after CModel::Load().
   void Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, WBFL::FEA2D::JointLoad* pCore);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CJointLoad)
	COM_INTERFACE_ENTRY(IFem2dJointLoad)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IFem2dJointLoad
public:
	STDMETHOD(get_Loading)(/*[out, retval]*/ LoadCaseIDType *pVal) override;
	STDMETHOD(GetForce)(/*[out]*/Float64* Fx, /*[out]*/Float64* Fy, /*[out]*/Float64* Mz) override;
	STDMETHOD(SetForce)(/*[in]*/Float64 Fx, /*[in]*/Float64 Fy, /*[in]*/Float64 Mz) override;
	STDMETHOD(get_Mz)(/*[out, retval]*/ Float64  *pVal) override;
	STDMETHOD(put_Mz)(/*[in]*/ Float64  newVal) override;
	STDMETHOD(get_Fy)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Fy)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Fx)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Fx)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_JointID)(/*[out, retval]*/ JointIDType *pVal) override;
	STDMETHOD(put_JointID)(/*[in]*/ JointIDType newVal) override;
	STDMETHOD(get_ID)(/*[out, retval]*/ LoadIDType *pVal) override;

private:
   ModelEvents* m_pModel; // for sending events back to model
   IFem2dLoading* m_pLoading;
   WBFL::FEA2D::JointLoad* m_pCore; // non-owning; owned by the FEA2D core Loading

};

