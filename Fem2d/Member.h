///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef __Member_H_
#define __Member_H_
#pragma once

#include "stdafx.h"
#include "CircularChild.h"
#include "Matrix.h"
#include "Result.h"
#include <list>


#if defined DUMP_KMATRIX
#include <fstream>
#endif

class CModel;
class ModelEvents;
class CMemberCollection;
class CJoint;
class MbrLoad;
class CLoading;

/////////////////////////////////////////////////////////////////////////////
// CMember
class ATL_NO_VTABLE CMember : 
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
// public CComRefCountTracer<CMember,CCircularChild<IFem2dModel, CComSingleThreadModel> >,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CMember,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dMember
{
public:
   enum {NumJoints=2, TotalDOF=6};
   typedef Result<NUM_DOF*2,NUM_DOF*2>         MbrResult;
   typedef ResultArray<MbrResult>   MbrResultArray;

   CMember();
   virtual ~CMember();

   // IMPORTANT!!!
   // OnCreate must be called once and only once by creator or bad memory 
   // things will happen.
   // (actually asserts will fire in debug mode, but I thought I'd scare you)
   void OnCreate(IFem2dModel* pModel, ModelEvents* pEvents, MemberIDType ID, JointIDType startJoint=-1, JointIDType endJoint=-1, Float64 EA=0.0, Float64 EI=0.0);

   // IStructuredStorage - sort of
   HRESULT Load(IStructuredLoad2 *load);
   HRESULT Save(IStructuredSave2 *save);

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


private:
   // error message functions
   CComBSTR JointDoesntExistError(Fem2dMbrEndType end);

private:
   // a little class to keep our joint information up to date and to optimize
   // length and angle calculations
   class JointKeeper
   {
   public:
      JointKeeper(CMember* m_pMember);
      bool PutStartJoint(JointIDType id);
      JointIDType GetStartJoint();
      bool PutEndJoint(JointIDType id);
      JointIDType GetEndJoint();
      void GetJoints(CJoint** pstart, CJoint** pEnd);
      Float64 GetLength();
      Float64 GetAngle();
      bool   m_Dirty;
   private:
      JointKeeper();
      void Compute();
      CMember*   m_pMember;
      JointIDType m_StartJoint;
      JointIDType m_EndJoint;
      CJoint*    m_pStartJoint;
      CJoint*    m_pEndJoint;
      Float64 m_Length;
      Float64 m_Angle;
   }; // JointKeeper
   friend JointKeeper;

   MemberIDType         m_ID;
   JointKeeper  m_JointKeeper;
   long         m_StartReleases;
   long         m_EndReleases;
   Float64       m_EA;
   Float64       m_EI;

   ModelEvents* m_pModel; // for sending events back to model


protected:
   // fe analysis-related functions
   void InitModel();
   void ClearLoads();
   void AssembleF();
   JointIDType GetJointNum(CJoint* pj);
   void GetGlobalJntForces(JointIDType jntId,Float64 *force);
   void ComputeResults();
   LONG GetNumDOF() const;
   LONG GetNumJoints() const;
   LONG GetCondensedDOF(LONG dof);
   Float64 GetKglobal(LONG DOFi,LONG DOFj);
   void GetFglobal(Float64 *f);

   void ApplyLoad(MbrLoad *load);

   void ComputeDeflections();
   void ComputeForces();
   void ComputeJointDeflectionForce(iActLikeMatrix* pdf);

   void GetResults(MbrResult* pres);
   void SetResults(const MbrResult& res);

   void GetInternalForces(Float64 loc,Fem2dMbrFaceType face,Float64 *force);
   void GetDeflection(Float64 loc,Float64 *disp);

   bool IsEquilibriumSatisfied(Float64 tolerance);

   long GetReleaseTypeFlag(Fem2dMbrReleaseType releaseType);
   bool IsReleased(Fem2dMbrEndType end,Fem2dMbrReleaseType releaseType);

private:
   void BuildTransformationMatrix();
   void BuildKlocal();
   void BuildKglobal();
   void ComputeFemResults();
   void ComputeClassicResults();
   void GetPinPinRotation(Float64 &rz1,Float64 &rz2);
   void GetPinFixRotation(Float64 &rz1);
   void GetFixPinRotation(Float64 &rz2);
   void Link(CJoint &jnt);
   void Unlink(CJoint &jnt);

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
   // fe related data

   Matrix m_Kglobal;
   Matrix m_Klocal;
   Vector6 m_Fglobal;
   Matrix m_TransMatrix;

   typedef std::list<MbrLoad*> MbrLoadPointerContainer;
   typedef MbrLoadPointerContainer::iterator MbrLoadPointerIterator;

   MbrLoadPointerContainer m_Loads;

   Vector6 m_Dlocal; // local Deflections
   Vector6 m_Rlocal; // local resultant forces

friend CJoint;
friend CLoading;
friend CModel;

};


#endif //__Member_H_
