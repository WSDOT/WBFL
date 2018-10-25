///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef __Joint_H_
#define __Joint_H_
#pragma once

#include "stdafx.h"
#include "CircularChild.h"
#include <set>

class ModelEvents;
class CModel;
class CMember;
class CJointLoad;
class CJointDisplacement;
class CLoading;

/////////////////////////////////////////////////////////////////////////////
// CJoint
class ATL_NO_VTABLE CJoint : 
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
   //public CComRefCountTracer<CJoint,CCircularChild<IFem2dModel, CComSingleThreadModel> >,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CJoint,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dJoint
{
public:
   enum {NumDof=NUM_DOF};

   CJoint();
   ~CJoint();

   // IMPORTANT!!!
   // OnCreate must be called once and only once by creator.
   void OnCreate(IFem2dModel* pModel, ModelEvents* pEvents, JointIDType ID, Float64 x=0.0, Float64 y=0.0);

   // IStructuredStorage - sort of
   STDMETHOD(Load)(/*[in]*/ IStructuredLoad2 *load);
   STDMETHOD(Save)(/*[in]*/ IStructuredSave2 *save);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CJoint)
	COM_INTERFACE_ENTRY(IFem2dJoint)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IFem2dJoint
public:
	STDMETHOD(ReleaseDof)(/*[in]*/ Fem2dJointReleaseType rel);
	STDMETHOD(Free)();
	STDMETHOD(Support)();
	STDMETHOD(IsSupport)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(IsDofReleased)(/*[in]*/Fem2dJointReleaseType rel, /*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(IsDofSupported)(/*[in]*/Fem2dJointReleaseType rel, /*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Y)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Y)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_X)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_X)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_ID)(/*[out, retval]*/ JointIDType *pVal);
	STDMETHOD(get_Members)(/*[out, retval]*/ IIDArray* *ppVal);


private:
   // data members for interface-based functions
   JointIDType m_ID;
   Float64 m_X;
   Float64 m_Y;
   long m_Releases; // a bit value of true means dof is free
   ModelEvents* m_pModel; // for sending events back to model

private:
   // data members used for fe solution
   LONG   m_CondensedDOF[NumDof];         // Condensed DOF numbers
   LONG   m_GlobalDOF[NumDof];            // Global DOF numbers
   Float64 m_jntLoad[NumDof];              // Joint loads
   Float64 m_dispLoad[NumDof];             // Joint displacement load
   bool   m_dispLoadApplied;              //  was applied?
   Float64 m_Disp[NumDof];                 // displacements
   Float64 m_Reaction[NumDof];             // reactions

   typedef std::set<CMember*>               MemberPointerContainer;
   typedef MemberPointerContainer::iterator MemberPointerIterator;

   MemberPointerContainer m_AttachedMembers;  // reference to all Members attached to this
                                              // joint. 
                                              // Only valid during analysis!!!

private:
   void Link(CMember* pel);
   void Setup();
   void InitModel(LONG nGDOF,LONG nCDOF,LONG &nGDOFused,LONG &nCDOFused);
   LONG  GetGlobalDOF(LONG dof) const;
   LONG  GetCondensedDOF(LONG dof) const;

   void ClearLoads();
   void ApplyLoad(CJointLoad *ld);
   void ApplyLoad(CJointDisplacement *ld);
   bool WasDisplacementLoadApplied() const 
   { return m_dispLoadApplied; }
   void GetFglobal(Float64 *v);
   void ComputeJointDisplacementForces(Float64* f);

   void SetDisplacement(const Float64 *disp);
   void GetDisplacement(Float64 *disp) const;

   void ComputeReactions();
   void GetReactions(Float64 *react) const;

   bool IsEquilibriumSatisfied(Float64 tolerance);

   // could make functions public, but at least we know who our friends are
   friend CModel;
   friend CMember;
   friend CLoading;
};

#endif //__Joint_H_
