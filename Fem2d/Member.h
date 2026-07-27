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

// Member.h : Declaration of the CMember

#pragma once

#include "stdafx.h"
#include "CircularChild.h"

class CModel;
class ModelEvents;
class CMemberCollection;
class CJoint;
class CLoading;

/////////////////////////////////////////////////////////////////////////////
// CMember
// Thin COM facade over WBFL::FEA2D::Member. All FE-solution data (the
// JointKeeper length/angle cache, local/global stiffness matrices, applied
// MbrLoad list, deflection/force results) is gone - it lives entirely
// inside the FEA2D core now, private to FEA2D's own StiffnessAnalysis.
class ATL_NO_VTABLE CMember :
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CMember,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dMember
{
public:
   CMember();
   virtual ~CMember();

   // IMPORTANT!!!
   // OnCreate must be called once and only once by creator or bad memory
   // things will happen.
   // (actually asserts will fire in debug mode, but I thought I'd scare you)
   void OnCreate(IFem2dModel* pModel, ModelEvents* pEvents, WBFL::FEA2D::Member* pCore);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMember)
	COM_INTERFACE_ENTRY(IFem2dMember)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IFem2dMember
public:
	STDMETHOD(ReleaseEnd)(/*[in]*/Fem2dMbrEndType, /*[in]*/Fem2dMbrReleaseType) override;
	STDMETHOD(IsReleased)(/*[in]*/Fem2dMbrEndType end, /*[in]*/Fem2dMbrReleaseType releaseType, /*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_EI)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_EI)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_EA)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_EA)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_EndJoint)(/*[out, retval]*/ JointIDType *pVal) override;
	STDMETHOD(put_EndJoint)(/*[in]*/ JointIDType newVal) override;
	STDMETHOD(get_StartJoint)(/*[out, retval]*/ JointIDType *pVal) override;
	STDMETHOD(put_StartJoint)(/*[in]*/ JointIDType newVal) override;
	STDMETHOD(get_ID)(/*[out, retval]*/ MemberIDType *pVal) override;

public:
   // functions to deal with location rule. if loc is positive, it is measured
   // directly along member, if -1.0<=loc<0.0, it is fractional
   // Function returns -1 if location is beyond end of beam.
   static Float64 GetRealLocation(Float64 length, Float64 loc);
   Float64 GetRealLocation(Float64 loc);

// Operators
public:
   bool operator == (const CMember &mbr) const;

private:
   ModelEvents* m_pModel; // for sending events back to model
   WBFL::FEA2D::Member* m_pCore; // non-owning; owned by the FEA2D core Model

friend CJoint;
friend CLoading;
friend CModel;

};

