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
// Joint.cpp : Implementation of CJoint
#include "stdafx.h"
#include "Joint.h"
#include "Model.h"
#include "Member.h"
#include "JointLoad.h"
#include "JointDisplacement.h"

#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define ON_JNT_CHANGED() ATLASSERT(m_pModel!=0); m_pModel->OnJointChanged(this);


/////////////////////////////////////////////////////////////////////////////
// CJoint
CJoint::CJoint():
m_ID(0),
m_X(0.0),
m_Y(0.0),
m_Releases(jrtAll),
m_pModel(0)
{
   Setup();
}

CJoint::~CJoint()
{
}

void CJoint::OnCreate(IFem2dModel* pParent, ModelEvents* pEvents, JointIDType ID, Float64 x, Float64 y)
{
   InitParent(pParent); // CCircularChild implementation

   m_pModel = pEvents;  //  C++ event handlers
   m_ID = ID;
   m_X = x;
   m_Y = y;

}

STDMETHODIMP CJoint::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFem2dJoint
	};
	for (long i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

static const Float64 MY_VER=1.0;

STDMETHODIMP CJoint::Load(/*[in]*/ IStructuredLoad2 *pload)
{
   HRESULT hr;
   hr = pload->BeginUnit(CComBSTR("Joint"));
   if (FAILED(hr))
      return hr;

   Float64 ver;
   hr = pload->get_Version(&ver);
   if (FAILED(hr))
      return hr;

   if (ver!=MY_VER)
      return STRLOAD_E_BADVERSION;

   {        
      CComVariant varlong;
      varlong.vt = VT_I4;
      hr = pload->get_Property(CComBSTR("ID"),&varlong);
      if (FAILED(hr))
         return hr;

      m_ID = varlong.lVal;

      CComVariant vardbl;
      vardbl.vt = VT_R8;
      hr = pload->get_Property(CComBSTR("X"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_X = vardbl.dblVal;

      hr = pload->get_Property(CComBSTR("Y"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_Y = vardbl.dblVal;

      hr = pload->get_Property(CComBSTR("Supports"),&varlong);
      if (FAILED(hr))
         return hr;

      m_Releases = varlong.lVal;
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CJoint::Save(/*[in]*/ IStructuredSave2 *psave)
{
   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("Joint"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      hr = psave->put_Property(CComBSTR("ID"),CComVariant(m_ID));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("X"),CComVariant(m_X));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Y"),CComVariant(m_Y));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Supports"),CComVariant(m_Releases));
      if (FAILED(hr))
         return hr;
   }

   hr = psave->EndUnit();
   if (FAILED(hr))
      return hr;

   return S_OK;
}


STDMETHODIMP CJoint::get_ID(JointIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_ID;

	return S_OK;
}

STDMETHODIMP CJoint::get_X(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_X;

	return S_OK;
}

STDMETHODIMP CJoint::put_X(Float64 newVal)
{
   if (m_X != newVal)
   {
	   m_X = newVal;
      ON_JNT_CHANGED();
   }
	return S_OK;
}

STDMETHODIMP CJoint::get_Y(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Y;

	return S_OK;
}

STDMETHODIMP CJoint::put_Y(Float64 newVal)
{
   if (m_Y != newVal)
   {
	   m_Y = newVal;
      ON_JNT_CHANGED();
   }
	return S_OK;
}

STDMETHODIMP CJoint::IsDofReleased(Fem2dJointReleaseType rel, VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   if (rel==jrtNone)
   {
      *pVal = (m_Releases==jrtNone ? VARIANT_TRUE : VARIANT_FALSE);
   }
   else
   {
      long st = m_Releases & rel;
	   *pVal = (st==rel ? VARIANT_TRUE : VARIANT_FALSE);
   }

	return S_OK;
}

STDMETHODIMP CJoint::IsDofSupported(Fem2dJointReleaseType rel, VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);

   if (rel==jrtNone)
   {
      return IsDofReleased(jrtAll, pVal);
   }
   else if (rel==jrtAll)
   {
      return IsDofReleased(jrtNone, pVal);
   }
   else
   {
      VARIANT_BOOL tst;
      HRESULT hr = IsDofReleased(rel, &tst);
      *pVal = (tst==VARIANT_TRUE ? VARIANT_FALSE : VARIANT_TRUE);
      return hr;
   }
}


STDMETHODIMP CJoint::IsSupport(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = (m_Releases==jrtAll ? VARIANT_FALSE : VARIANT_TRUE);
	return S_OK;
}

STDMETHODIMP CJoint::Support()
{
   if (m_Releases != jrtNone)
   {
	   m_Releases = jrtNone;
      ON_JNT_CHANGED();
   }

	return S_OK;
}

STDMETHODIMP CJoint::Free()
{
   if (m_Releases != jrtAll)
   {
	   m_Releases = jrtAll;
      ON_JNT_CHANGED();
   }

	return S_OK;
}

STDMETHODIMP CJoint::get_Members(IIDArray* *ppMemberIDs)
{
   CHECK_RETOBJ(ppMemberIDs);
   HRESULT hr = S_OK;

   // create collection
   CComPtr<IIDArray> pcoll;
   hr = pcoll.CoCreateInstance(CLSID_IDArray);
   ATLASSERT(SUCCEEDED(hr));
   if (FAILED(hr))
      return hr;

   // prep for client
   *ppMemberIDs = pcoll;
   (*ppMemberIDs)->AddRef();

   // now find the members that we are attached to. We can't use m_AttachedMembers
   // because it is transient and only valid during the model building process.
   // must first get a CModel - This cast is ugly, but is done to reduce physical coupling
   CModel* pModel;
   pModel = static_cast<CModel*>(m_pModel);

   CComPtr<IFem2dMemberCollection> members;
   hr = pModel->get_Members(&members);
   if (FAILED(hr))
      return hr;

   CollectionIndexType nMembers;
   hr = members->get_Count(&nMembers);

   for (CollectionIndexType mbrIdx = 0; mbrIdx < nMembers; mbrIdx++)
   {
      CComPtr<IFem2dMember> member;
      hr = members->get_Item(mbrIdx,&member);
      if (FAILED(hr))
         return hr;

      JointIDType jointID;
      hr = member->get_StartJoint(&jointID);
      if (FAILED(hr))
         return hr;

      if (jointID == m_ID)
      {
         MemberIDType mbrID;
         member->get_ID(&mbrID);
         pcoll->Add(mbrID);
      }
      else
      {
         hr = member->get_EndJoint(&jointID);
         if (FAILED(hr))
            return hr;

         if (jointID == m_ID)
         {
            MemberIDType mbrID;
            member->get_ID(&mbrID);
            pcoll->Add(mbrID);
         }

      }
   }

	return hr;
}


STDMETHODIMP CJoint::ReleaseDof(Fem2dJointReleaseType rel)
{
   VARIANT_BOOL bIsReleased;
   IsDofReleased(rel,&bIsReleased);

	if (bIsReleased == VARIANT_FALSE)
   {
      m_Releases |= rel;
      ON_JNT_CHANGED();
   }

	return S_OK;
}


//
// Common joint initialization needed by all constructors
void CJoint::Setup()
{
   long i;
   for (i = 0; i < 3; i++)
   {
      m_CondensedDOF[i] = -1; // constrained dof - condensed out of Kglobal
      m_GlobalDOF[i]    = -1; // Assertion check value...
   }

   ClearLoads();
}

// Init
//
// Initialize joint for analysis
void CJoint::InitModel(LONG nGDOF,LONG nCDOF,LONG &nGDOFused,LONG &nCDOFused)
{
   // Not attached to any elements yet
   m_AttachedMembers.clear();

   // no results yet
   ClearLoads();

   LONG count = 0;
   for (LONG i = 0; i < 3; i++)
   {
      m_GlobalDOF[i] = nGDOF + i;

      LONG n = 1<<i;
      if ( (n & m_Releases) == n ) // This dof is free
      {
         m_CondensedDOF[i] = nCDOF;
         nCDOF++;
         count++;
      }
      else
      {
         m_CondensedDOF[i] = -1;
      }
   }

   nGDOFused = 3;
   nCDOFused = count;
}

// GetCondensedDOF
//
// Retreives the condensed dof number corrosponding to one of the
// joints local dof's. 0 = dx, 1 = dy, and 2 = rz.
LONG CJoint::GetCondensedDOF(LONG dof) const
{
   // Update for 3d
   if (dof < 0 || dof > 2)
   {
      ATLASSERT(0);
      CComBSTR msg(CreateErrorMsg1(IDS_E_INVALID_CONDENSED_DOF, dof));
      THROW_MSG(msg, FEM2D_E_INVALID_CONDENSED_DOF, IDH_E_INVALID_CONDENSED_DOF);
   }

   return m_CondensedDOF[dof];
}

// GetGlobalDOF
//
// Retreives the global dof number corrosponding to one of the
// joints local dof's. 0 = dx, 1 = dy, and 2 = rz.
LONG CJoint::GetGlobalDOF(LONG dof) const
{
   // Update for 3d
   if (dof < 0 || dof > 2)
   {
      ATLASSERT(0);
      CComBSTR msg = CreateErrorMsg1(IDS_E_INVALID_GLOBAL_DOF, dof);
      THROW_MSG(msg, FEM2D_E_INVALID_GLOBAL_DOF, IDH_E_INVALID_GLOBAL_DOF);
   }

   return m_GlobalDOF[dof];
}


// ClearLoads
//
// Clears any loads applied to this joint
void CJoint::ClearLoads()
{
   m_jntLoad[0] = 0;
   m_jntLoad[1] = 0;
   m_jntLoad[2] = 0;

   m_dispLoadApplied = false;
   m_dispLoad[0] = 0;
   m_dispLoad[1] = 0;
   m_dispLoad[2] = 0;

   m_Reaction[0] = 0;
   m_Reaction[1] = 0;
   m_Reaction[2] = 0;

   m_Disp[0] = 0;
   m_Disp[1] = 0;
   m_Disp[2] = 0;
}

// ApplyLoad
//
// Applys a load to this joint
void CJoint::ApplyLoad(CJointLoad *ld)
{
   Float64 fx,fy,mz;
   ld->GetForce(&fx,&fy,&mz);
   m_jntLoad[0] += fx;
   m_jntLoad[1] += fy;
   m_jntLoad[2] += mz;
}

void CJoint::ApplyLoad(CJointDisplacement *ld)
{
   // displacements cannot be applied to released dofs
   Float64 dx, dy, rz;
   ld->GetDisplacement(&dx, &dy, &rz);
   if ((dx!=0.0 && m_CondensedDOF[0]!=-1) ||
       (dy!=0.0 && m_CondensedDOF[1]!=-1) ||
       (rz!=0.0 && m_CondensedDOF[2]!=-1))
   {
      LoadIDType id;
      ld->get_ID(&id);
      CComBSTR msg = CreateErrorMsg2(IDS_E_JOINT_DISP_TO_FIXED_DOF_ONLY, id, m_ID);
      THROW_MSG(msg, FEM2D_E_JOINT_DISP_TO_FIXED_DOF_ONLY, IDH_E_JOINT_DISP_TO_FIXED_DOF_ONLY);
   }

   m_dispLoadApplied = true;
   m_dispLoad[0] += dx;
   m_dispLoad[1] += dy;
   m_dispLoad[2] += rz;
}

void CJoint::GetFglobal(Float64 *v)
{
   v[0] = m_jntLoad[0];
   v[1] = m_jntLoad[1];
   v[2] = m_jntLoad[2];
}

// SetDisplacement
//
// Sets the joint displacement. To be called by TFemModel after a stiffness
// analysis.
void CJoint::SetDisplacement(const Float64 *disp)
{
   m_Disp[0] = disp[0];
   m_Disp[1] = disp[1];
   m_Disp[2] = disp[2];

   // this is a bit tricky and underhanded here, but set displacement 
   // values to those prescribed by settlement loads if applied
   if (m_dispLoadApplied)
   {
      for (long i=0; i<NumDof; i++)
      {
         if (m_dispLoad[i]!=0.0)
         {
            ATLASSERT(m_Disp[i]==0.0); // if a displacement load was applied, this node 
                                       // had better be fixed and the solution must be zero
            m_Disp[i] = m_dispLoad[i];
         }
      }
   }
}

// GetDisplacement
//
// Retreives the joint displacements.
void CJoint::GetDisplacement(Float64 *disp) const
{
   for (long i = 0; i < NumDof; i++)
      disp[i] = m_Disp[i];
}

void CJoint::ComputeReactions()
{
   // Reactions = unbalanced Member forces + loads applied directly
   //    to this joint
   JointIDType jntnum;
   Float64 react[3];
   m_Reaction[0] = 0;
   m_Reaction[1] = 0;
   m_Reaction[2] = 0;

   MemberPointerIterator e (m_AttachedMembers.begin() );
   MemberPointerIterator eend (m_AttachedMembers.end() );
   while(e != eend)
   {
      CMember *ele = *(e++);

      jntnum = ele->GetJointNum(this);
      ele->GetGlobalJntForces(jntnum,react);
      m_Reaction[0] += react[0];
      m_Reaction[1] += react[1];
      m_Reaction[2] += react[2];
   }
   m_Reaction[0] -= m_jntLoad[0];
   m_Reaction[1] -= m_jntLoad[1];
   m_Reaction[2] -= m_jntLoad[2];
}

// GetReactions
//
// Retreives the joint reactions.
void CJoint::GetReactions(Float64 *react) const
{
   for (long i = 0; i < 3; i++)
      react[i] = m_Reaction[i]; 
}

void CJoint::Link(CMember* pel)
{
   m_AttachedMembers.insert(pel);
}

bool CJoint::IsEquilibriumSatisfied(Float64 tolerance)
{
   Float64 Fx, Fy, Mz; // Forces from attached elements
   Float64 fx, fy, mz; // Externally applied loads and reactions

   // External forces
   fx = m_Reaction[0] + m_jntLoad[0];
   fy = m_Reaction[1] + m_jntLoad[1];
   mz = m_Reaction[2] + m_jntLoad[2];

   // Internal forces
   Fx = 0;
   Fy = 0;
   Mz = 0;
   MemberPointerIterator e (m_AttachedMembers.begin());
   MemberPointerIterator eend (m_AttachedMembers.end());
   while(e != eend)
   {
      CMember *ele = *e++;
      JointIDType jntId = ele->GetJointNum(this);
      Float64 eleEndForce[3];
      ele->GetGlobalJntForces(jntId,eleEndForce);
      Fx += eleEndForce[0];
      Fy += eleEndForce[1];
      Mz += eleEndForce[2];
   }

   Fx -= fx;
   Fy -= fy;
   Mz -= mz;

   // Check equilibrium
   if (!IsZero(Fx,tolerance))
   {
      ATLASSERT(false);
      return false;
   }

   if (!IsZero(Fy,tolerance))
   {
      ATLASSERT(false);
      return false;
   }

   if (!IsZero(Mz,tolerance))
   {
      ATLASSERT(false);
      return false;
   }

   return true;
}


