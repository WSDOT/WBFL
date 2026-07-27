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

// Joint.h : Declaration of the CJoint

#pragma once

#include "stdafx.h"
#include "CircularChild.h"
#include <set>

class ModelEvents;
class CModel;
class CMember;
class CJointLoad;
class CJointDeflection;
class CLoading;

/////////////////////////////////////////////////////////////////////////////
// CJoint
// Thin COM facade over WBFL::FEA2D::Joint. All FE-solution data (condensed/
// global DOF numbers, joint loads, deflections, reactions, the attached-
// members working set) is gone - it lives entirely inside the FEA2D core
// now (Model/Joint/Member), private to FEA2D's own StiffnessAnalysis.
class ATL_NO_VTABLE CJoint :
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CJoint,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dJoint
{
public:
   CJoint();
   ~CJoint();

   // IMPORTANT!!!
   // OnCreate must be called once and only once by creator.
   void OnCreate(IFem2dModel* pParent, ModelEvents* pEvents, WBFL::FEA2D::Model* pCoreModel, WBFL::FEA2D::Joint* pCore);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CJoint)
	COM_INTERFACE_ENTRY(IFem2dJoint)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IFem2dJoint
public:
	STDMETHOD(ReleaseDof)(/*[in]*/ Fem2dJointReleaseType rel) override;
	STDMETHOD(Free)() override;
	STDMETHOD(Support)() override;
	STDMETHOD(IsSupport)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(IsDofReleased)(/*[in]*/Fem2dJointReleaseType rel, /*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(IsDofSupported)(/*[in]*/Fem2dJointReleaseType rel, /*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(get_Y)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Y)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_X)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_X)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_ID)(/*[out, retval]*/ JointIDType *pVal) override;
	STDMETHOD(get_Members)(/*[out, retval]*/ IIDArray* *ppVal) override;

private:
   ModelEvents* m_pModel; // for sending events back to model
   WBFL::FEA2D::Model* m_pCoreModel; // non-owning; for get_Members' Model::GetAttachedMembers() lookup
   WBFL::FEA2D::Joint* m_pCore; // non-owning; owned by the FEA2D core Model

   // could make functions public, but at least we know who our friends are
   friend CModel;
   friend CMember;
   friend CLoading;
};

