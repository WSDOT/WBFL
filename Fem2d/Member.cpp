///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2016  Washington State Department of Transportation
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
// Member.cpp : Implementation of CMember
#include "stdafx.h"
#include "Member.h"
#include "ModelEvents.h"
#include "Matrix.h"
#include "MbrLoad.h"
#include "Beam.h"
#include "Model.h"

#include <cmath>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define ON_MBR_CHANGED() ATLASSERT(m_pModel!=0); m_pModel->OnMemberChanged(this);

/////////////////////////////////////////////////////////////////////////////
// CMember
CMember::CMember():
   m_pModel(0),
   m_ID(0),
   m_StartReleased(VARIANT_FALSE),
   m_EndReleased(VARIANT_FALSE),
   m_EA(0.0),
   m_EI(0.0),
   m_TransMatrix(TotalDOF,TotalDOF),
   m_Kglobal(TotalDOF,TotalDOF),
   m_Klocal(TotalDOF,TotalDOF),
   m_Fglobal(),
   m_Dlocal(),
   m_Rlocal(),
   m_JointKeeper(this)
{
#if defined DUMP_KMATRIX
   m_logfile.open("memberMatrix.log");
#endif
}

CMember::~CMember()
{
}

void CMember::OnCreate(IFem2dModel* pParent, ModelEvents* pEvents, MemberIDType ID, JointIDType startJoint, JointIDType endJoint, Float64 EA, Float64 EI)
{
   InitParent(pParent); // CCircularChild implementation

   m_pModel = pEvents;  // for C++ event handlers
   m_ID = ID;
   m_JointKeeper.PutStartJoint(startJoint);
   m_JointKeeper.PutEndJoint(endJoint);
   ATLASSERT(EA>=0.0);
   m_EA = EA;
   ATLASSERT(EI>=0.0);
   m_EI = EI;

}

static const Float64 MY_VER=1.0;

STDMETHODIMP CMember::Load(/*[in]*/ IStructuredLoad2 *pload)
{
   HRESULT hr;
   hr = pload->BeginUnit(CComBSTR("Member"));
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

      hr = pload->get_Property(CComBSTR("StartJoint"),&varlong);
      if (FAILED(hr))
         return hr;

      JointIDType jnt = varlong.lVal;
      m_JointKeeper.PutStartJoint(jnt);

      hr = pload->get_Property(CComBSTR("EndJoint"),&varlong);
      if (FAILED(hr))
         return hr;

      jnt = varlong.lVal;
      m_JointKeeper.PutEndJoint(jnt);

      CComVariant vardbl;
      vardbl.vt = VT_R8;
      hr = pload->get_Property(CComBSTR("EA"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_EA = vardbl.dblVal;

      hr = pload->get_Property(CComBSTR("EI"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_EI = vardbl.dblVal;

      CComVariant varbool;
      varbool.vt = VT_BOOL;
      hr = pload->get_Property(CComBSTR("StartRelease"),&varbool);
      if (FAILED(hr))
         return hr;

      m_StartReleased = (varbool.boolVal == VARIANT_TRUE ? true : false);

      hr = pload->get_Property(CComBSTR("EndRelease"),&varbool);
      if (FAILED(hr))
         return hr;

      m_EndReleased = (varbool.boolVal == VARIANT_TRUE ? true : false);
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CMember::Save(/*[in]*/ IStructuredSave2 *psave)
{
   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("Member"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      hr = psave->put_Property(CComBSTR("ID"),CComVariant(m_ID));
      if (FAILED(hr))
         return hr;

      JointIDType jnt = m_JointKeeper.GetStartJoint();
      hr = psave->put_Property(CComBSTR("StartJoint"),CComVariant(jnt));
      if (FAILED(hr))
         return hr;

      jnt = m_JointKeeper.GetEndJoint();
      hr = psave->put_Property(CComBSTR("EndJoint"),CComVariant(jnt));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("EA"),CComVariant(m_EA));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("EI"),CComVariant(m_EI));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("StartRelease"),CComVariant(m_StartReleased));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("EndRelease"),CComVariant(m_EndReleased));
      if (FAILED(hr))
         return hr;
   }

   hr = psave->EndUnit();
   if (FAILED(hr))
      return hr;

   return S_OK;
}

STDMETHODIMP CMember::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFem2dMember
	};
	for (long i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CMember::get_ID(MemberIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_ID;

	return S_OK;
}

STDMETHODIMP CMember::get_StartJoint(JointIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_JointKeeper.GetStartJoint();

	return S_OK;
}

STDMETHODIMP CMember::put_StartJoint(JointIDType newVal)
{
	if (m_JointKeeper.PutStartJoint( newVal ))
   {
      ON_MBR_CHANGED();
   }
	return S_OK;
}

STDMETHODIMP CMember::get_EndJoint(JointIDType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_JointKeeper.GetEndJoint();

	return S_OK;
}

STDMETHODIMP CMember::put_EndJoint(JointIDType newVal)
{
	if (m_JointKeeper.PutEndJoint( newVal ))
   {
      ON_MBR_CHANGED();
   }
	return S_OK;
}

STDMETHODIMP CMember::get_EA(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_EA;

	return S_OK;
}

STDMETHODIMP CMember::put_EA(Float64 newVal)
{
   if (newVal<0.0)
      return CComCoClass<CMember, &CLSID_Fem2dMember>::Error(IDS_E_STIFFNESS_MUST_BE_POSITIVE, IDH_E_STIFFNESS_MUST_BE_POSITIVE, GetHelpFile(), IID_IFem2dMember, FEM2D_E_STIFFNESS_MUST_BE_POSITIVE);
      
   if (m_EA != newVal)
   {
	   m_EA = newVal;
      ON_MBR_CHANGED();
   }
	return S_OK;
}

STDMETHODIMP CMember::get_EI(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_EI;

	return S_OK;
}

STDMETHODIMP CMember::put_EI(Float64 newVal)
{
   if (newVal<0.0)
      return CComCoClass<CMember, &CLSID_Fem2dMember>::Error(IDS_E_STIFFNESS_MUST_BE_POSITIVE, IDH_E_STIFFNESS_MUST_BE_POSITIVE, GetHelpFile(), IID_IFem2dMember, FEM2D_E_STIFFNESS_MUST_BE_POSITIVE);

   if (m_EI != newVal)
   {
	   m_EI = newVal;
      ON_MBR_CHANGED();
   }
	return S_OK;
}

STDMETHODIMP CMember::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	ATLASSERT(m_pModel!=0);

   // this method uses a different way of calculating lengths than the internal
   // jointkeeper class because this length must be correct in real-time (we don't 
   // watch to see if joints move).
   JointIDType startjoint = m_JointKeeper.GetStartJoint();
   JointIDType endjoint   = m_JointKeeper.GetEndJoint();
   
   if (startjoint==endjoint)
   {
      CComBSTR msg(CreateErrorMsg1(IDS_E_MEMBER_HAS_SAME_JOINTS, m_ID));
      return CComCoClass<CMember, &CLSID_Fem2dMember>::Error(msg, IDH_E_MEMBER_HAS_SAME_JOINTS, GetHelpFile(), IID_IFem2dMember, FEM2D_E_MEMBER_HAS_SAME_JOINTS);
   }

   // must first get a CModel - This cast is ugly, but is done to reduce physical coupling
   CModel* pModel;
   pModel = static_cast<CModel*>(m_pModel);

   CComPtr<IFem2dJointCollection> pJoints;
   HRESULT hr = pModel->get_Joints(&pJoints);
   if (FAILED(hr))
      return hr;

   CComPtr<IFem2dJoint> pStartJoint;
   hr = pJoints->Find(startjoint, &pStartJoint);
   if (FAILED(hr))
      return E_FAIL;
   else if (pStartJoint==0)
   {
      CComBSTR msg(JointDoesntExistError(metStart));
      return CComCoClass<CMember, &CLSID_Fem2dMember>::Error(msg, IDH_E_MEMBER_JOINT_NOT_EXISTS, GetHelpFile(), IID_IFem2dMember, FEM2D_E_MEMBER_JOINT_NOT_EXISTS);
   }

   CComPtr<IFem2dJoint> pEndJoint;
   hr = pJoints->Find(endjoint, &pEndJoint);
   if (FAILED(hr))
      return E_FAIL;
   else if (pEndJoint==0)
   {
      CComBSTR msg(JointDoesntExistError(metEnd));
      return CComCoClass<CMember, &CLSID_Fem2dMember>::Error(msg, IDH_E_MEMBER_JOINT_NOT_EXISTS, GetHelpFile(), IID_IFem2dMember, FEM2D_E_MEMBER_JOINT_NOT_EXISTS);
   }

   Float64 startX, startY, endX, endY;
   pStartJoint->get_X(&startX);
   pStartJoint->get_Y(&startY);
   pEndJoint->get_X(&endX);
   pEndJoint->get_Y(&endY);

   Float64 dx = startX-endX;
   Float64 dy = startY-endY;
   *pVal = sqrt(dx*dx + dy*dy);

   if (*pVal==0.0)
   {
      CComBSTR msg(::CreateErrorMsg1(IDS_E_ZERO_LENGTH_MEMBER, m_ID));
      return CComCoClass<CMember, &CLSID_Fem2dMember>::Error(msg, IDH_E_ZERO_LENGTH_MEMBER, GetHelpFile(), IID_IFem2dMember, FEM2D_E_ZERO_LENGTH_MEMBER);
   }

	return S_OK;
}

STDMETHODIMP CMember::IsReleased(Fem2dMbrEndType end, VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);

	if (end==metStart)
   {
      *pVal = (m_StartReleased ? VARIANT_TRUE : VARIANT_FALSE);
   }
   else
   {
      *pVal = (m_EndReleased ? VARIANT_TRUE : VARIANT_FALSE);
   }

	return S_OK;
}

STDMETHODIMP CMember::ReleaseEnd(Fem2dMbrEndType end, Fem2dMbrReleaseType rel)
{
	if (end==metStart)
   {
      m_StartReleased = (rel == mbrReleaseMz) ? true : false;
   }
   else
   {
      m_EndReleased = (rel == mbrReleaseMz) ? true : false;
   }

   ON_MBR_CHANGED();
	return S_OK;
}

Float64 CMember::GetRealLocation(Float64 length, Float64 loc)
{
   ATLASSERT(length>0.0);

   Float64 tloc = -1.0;

   if (loc<0.0)
   {
      // fractional location
      if (loc >= -1)
      {
         tloc = -loc * length;
      }
   }
   else
   {
      // explicit location specified
      if (loc <=length + EPS)
      {
         tloc = loc;
      }
   }

   return tloc;
}

Float64 CMember::GetRealLocation(Float64 loc)
{
   Float64 length = m_JointKeeper.GetLength();

   return GetRealLocation(length,loc);
}


///////////////////
//// FE-Related local functions

void CMember::InitModel()
{
   // get model ready
   m_JointKeeper.m_Dirty = true;

   CJoint *StartJnt, *EndJnt;
   m_JointKeeper.GetJoints(&StartJnt, &EndJnt);
   StartJnt->Link(this);
   EndJnt->Link(this);

   BuildTransformationMatrix();
   BuildKlocal();
   BuildKglobal();

#if defined DUMP_KMATRIX
   m_logfile << "Member " << m_ID << std::endl;
   m_logfile << "Transformation Matrix" << std::endl;
   m_logfile << (m_TransMatrix) << std::endl;
   m_logfile << "Local K Matrix" << std::endl;
   m_logfile << m_Klocal << std::endl;
   m_logfile << "Global K Matrix" << std::endl;
   m_logfile << m_Kglobal << std::endl;
   m_logfile << std::endl;
#endif
}

void CMember::BuildTransformationMatrix()
{
   // Update for 3d
   Float64 s;
   Float64 c;
   Float64 Angle;

   // 2d Transformation matrix
   // [ c  s  0  0  0  0]
   // [-s  c  0  0  0  0]
   // [ 0  0  1  0  0  0]
   // [ 0  0  0  c  s  0]
   // [ 0  0  0 -s  c  0]
   // [ 0  0  0  0  0  1]

   Angle = m_JointKeeper.GetAngle();
   s = sin(Angle);
   c = cos(Angle);

   (m_TransMatrix)(0,0) = c;
   (m_TransMatrix)(0,1) = s;
   (m_TransMatrix)(0,2) = 0;
   (m_TransMatrix)(0,3) = 0;
   (m_TransMatrix)(0,4) = 0;
   (m_TransMatrix)(0,5) = 0;

   (m_TransMatrix)(1,0) = -s;
   (m_TransMatrix)(1,1) = c;
   (m_TransMatrix)(1,2) = 0;
   (m_TransMatrix)(1,3) = 0;
   (m_TransMatrix)(1,4) = 0;
   (m_TransMatrix)(1,5) = 0;

   (m_TransMatrix)(2,0) = 0;
   (m_TransMatrix)(2,1) = 0;
   (m_TransMatrix)(2,2) = 1;
   (m_TransMatrix)(2,3) = 0;
   (m_TransMatrix)(2,4) = 0;
   (m_TransMatrix)(2,5) = 0;

   (m_TransMatrix)(3,0) = 0;
   (m_TransMatrix)(3,1) = 0;
   (m_TransMatrix)(3,2) = 0;
   (m_TransMatrix)(3,3) = c;
   (m_TransMatrix)(3,4) = s;
   (m_TransMatrix)(3,5) = 0;

   (m_TransMatrix)(4,0) = 0;
   (m_TransMatrix)(4,1) = 0;
   (m_TransMatrix)(4,2) = 0;
   (m_TransMatrix)(4,3) = -s;
   (m_TransMatrix)(4,4) = c;
   (m_TransMatrix)(4,5) = 0;

   (m_TransMatrix)(5,0) = 0;
   (m_TransMatrix)(5,1) = 0;
   (m_TransMatrix)(5,2) = 0;
   (m_TransMatrix)(5,3) = 0;
   (m_TransMatrix)(5,4) = 0;
   (m_TransMatrix)(5,5) = 1;
}

void CMember::BuildKlocal()
{
   Float64 Length;
   Float64 A,D,G,H,J,K,L,N,O,P,S,T,U;
   Float64 vi,vj,v;

   Length = m_JointKeeper.GetLength();

   vi = m_StartReleased ? 0 : 1;
   vj = m_EndReleased   ? 0 : 1;
   v  = 4 - vi*vj;

   /* compute global stiffness matrix */

   A =  m_EA/Length;
   D = -m_EA/Length;
   G =  (12*m_EI/pow(Length,3)) * (vi + vi*vj + vj)/v;
   H =   (6*m_EI/pow(Length,2)) * (2*vi + vi*vj)/v;
   J = -(12*m_EI/pow(Length,3)) * (vi + vi*vj + vj)/v;
   K =   (6*m_EI/pow(Length,2)) * (2*vj + vi*vj)/v;
   L =   (4*m_EI/Length)        * (3*vi)/v;
   N =  -(6*m_EI/pow(Length,2)) * (2*vi + vi*vj)/v;
   O =   (2*m_EI/Length)        * (3*vi*vj)/v;
   P =  m_EA/Length;
   S =  (12*m_EI/pow(Length,3)) * (vi + vi*vj + vj)/v;
   T =  -(6*m_EI/pow(Length,2)) * (2*vj + vi*vj)/v;
   U =   (4*m_EI/Length)        * (3*vj)/v;

   // K local

   m_Klocal(0,0) = A;
   m_Klocal(0,1) = 0;
   m_Klocal(0,2) = 0;
   m_Klocal(0,3) = D;
   m_Klocal(0,4) = 0;
   m_Klocal(0,5) = 0;

   m_Klocal(1,0) = 0;
   m_Klocal(1,1) = G;
   m_Klocal(1,2) = H;
   m_Klocal(1,3) = 0;
   m_Klocal(1,4) = J;
   m_Klocal(1,5) = K;

   m_Klocal(2,0) = 0;
   m_Klocal(2,1) = H;
   m_Klocal(2,2) = L;
   m_Klocal(2,3) = 0;
   m_Klocal(2,4) = N;
   m_Klocal(2,5) = O;

   m_Klocal(3,0) = D;
   m_Klocal(3,1) = 0;
   m_Klocal(3,2) = 0;
   m_Klocal(3,3) = P;
   m_Klocal(3,4) = 0;
   m_Klocal(3,5) = 0;

   m_Klocal(4,0) = 0;
   m_Klocal(4,1) = J;
   m_Klocal(4,2) = N;
   m_Klocal(4,3) = 0;
   m_Klocal(4,4) = S;
   m_Klocal(4,5) = T;

   m_Klocal(5,0) = 0;
   m_Klocal(5,1) = K;
   m_Klocal(5,2) = O;
   m_Klocal(5,3) = 0;
   m_Klocal(5,4) = T;
   m_Klocal(5,5) = U;
}

void CMember::BuildKglobal()
{
   Matrix Temp(TotalDOF,TotalDOF);

   m_TransMatrix.Multiply(&m_Klocal,&Temp,ATB);
   Temp.Multiply(&m_TransMatrix,&m_Kglobal);
}

// ClearLoads
//
// Clears any loads applied to this member
void CMember::ClearLoads()
{
   // This object does not own it's loads... Do not delete them.
   // Simply empty the container.
   m_Loads.clear();
}

void CMember::ComputeResults()
{
   bool useClassic = true;
   long ndof;
   long dof;
   CJoint *StartJnt, *EndJnt;
   m_JointKeeper.GetJoints(&StartJnt, &EndJnt);

   ndof = CJoint::NumDof;

   for (dof = 0; dof < ndof && useClassic; dof++)
   {
      if (StartJnt->GetCondensedDOF(dof) >= 0)
         useClassic = false;
   }

   for (dof = 0; dof < ndof && useClassic; dof++)
   {
      if (EndJnt->GetCondensedDOF(dof) >= 0)
         useClassic = false;
   }

   if (useClassic)
      ComputeClassicResults();
   else
      ComputeFemResults();
}

void CMember::ComputeFemResults()
{
   // compute mbr end forces (local)
   ComputeForces();

   // compute mbr end displacements (local)
   ComputeDisplacements();
}

void CMember::ComputeClassicResults()
{
   Float64 dx1,dy1,rz1; // start displacements
   Float64 dx2,dy2,rz2; // end displacements
   Float64 Fx1,Fy1,Mz1; // start forces
   Float64 Fx2,Fy2,Mz2; // end forces
   Float64 force[TotalDOF];
   Float64 disp[TotalDOF];

   dx1=dy1=rz1 = 0;
   dx2=dy2=rz2 = 0;
   Fx1=Fy1=Mz1 = 0;
   Fx2=Fy2=Mz2 = 0;

   // for every load in the current Loading
   // compute member end displacements, rotations, and forces
   MbrLoadPointerIterator ld( m_Loads.begin() );
   MbrLoadPointerIterator ldend( m_Loads.end() );
   for (; ld!=ldend; ld++)
   {
      MbrLoad& mbrLd = **ld;

      Float64 angle = m_JointKeeper.GetAngle();
      Float64 length = m_JointKeeper.GetLength();
      mbrLd.GetForceVector(GetMemberType(),length,angle,force);
      mbrLd.GetDispVector(GetMemberType(),length,angle ,m_EA, m_EI, disp);

      // Rotations may need to be adjusted for global joint rotation...
      // ra = r + rb ???

      Fx1 += force[0];
      Fy1 += force[1];
      Mz1 += force[2];
      Fx2 += force[3];
      Fy2 += force[4];
      Mz2 += force[5];

      dx1 += disp[0];
      dy1 += disp[1];
      rz1 += disp[2];
      dx2 += disp[3];
      dy2 += disp[4];
      rz2 += disp[5];
   }

   // save displacements
   m_Dlocal(0) = dx1;
   m_Dlocal(1) = dy1;
   m_Dlocal(2) = rz1;
   m_Dlocal(3) = dx2;
   m_Dlocal(4) = dy2;
   m_Dlocal(5) = rz2;

   // save forces
   m_Rlocal(0) = Fx1;
   m_Rlocal(1) = Fy1;
   m_Rlocal(2) = Mz1;
   m_Rlocal(3) = Fx2;
   m_Rlocal(4) = Fy2;
   m_Rlocal(5) = Mz2;
}


MbrType CMember::GetMemberType()
{
   MbrType mbrType;

   if (m_StartReleased && m_EndReleased)
      mbrType = mtPinPin;
   else if (m_StartReleased)
      mbrType = mtPinFix;
   else if (m_EndReleased)
      mbrType = mtFixPin;
   else
      mbrType = mtFixFix;

   return mbrType;
}

// ComputeDisplacements
//
// Computes the member joint displacements in local coordinates,
// making adjustments for member releases.
//
// This function should be moved to a higher level of abstraction
// as TFemModel matures.
void CMember::ComputeDisplacements()
{
   Float64 Dglobal[6];
   Vector6 Disp;
   CJoint *StartJnt, *EndJnt;
   m_JointKeeper.GetJoints(&StartJnt, &EndJnt);

   StartJnt->GetDisplacement(Dglobal);
   EndJnt->GetDisplacement(&Dglobal[3]);
   Disp(0) = Dglobal[0];
   Disp(1) = Dglobal[1];
   Disp(2) = Dglobal[2];
   Disp(3) = Dglobal[3];
   Disp(4) = Dglobal[4];
   Disp(5) = Dglobal[5];

   m_TransMatrix.Multiply(&Disp,&m_Dlocal);

   // adjust member end rotation at released ends.
   Float64 r1,r2;
   switch(GetMemberType())
      {
      case mtPinPin:
           // Joint rotations are incorrect for this member.
           // Adjust based on actual boundary condition.
           GetPinPinRotation(r1,r2);
           m_Dlocal(2) = r1;
           m_Dlocal(5) = r2;
           break;

      case mtPinFix:
           // Start joint rotation is incorrect for this member.
           // Adjust based on actual boundary condition.
           GetPinFixRotation(r1);
           m_Dlocal(2) = r1;
           break;

      case mtFixPin:
           // End joint rotation is incorrect for this member.
           // Adjust based on actual boundary condition.
           GetFixPinRotation(r2);
           m_Dlocal(5) = r2;
           break;
      }
}

// ComputeForces
//
// Computes the element forces at its joints.
// Assumes ComputeDisplacements have been called.
void CMember::ComputeForces()
{
   Float64 Dglobal[6];
   Vector6 Disp;
   Vector6 Rglobal;
   CJoint *StartJnt, *EndJnt;
   m_JointKeeper.GetJoints(&StartJnt, &EndJnt);

   StartJnt->GetDisplacement(Dglobal);
   EndJnt->GetDisplacement(&Dglobal[3]);
   Disp(0) = Dglobal[0];
   Disp(1) = Dglobal[1];
   Disp(2) = Dglobal[2];
   Disp(3) = Dglobal[3];
   Disp(4) = Dglobal[4];
   Disp(5) = Dglobal[5];

   m_Kglobal.Multiply(&Disp,&Rglobal);
   Rglobal -= m_Fglobal;
   m_TransMatrix.Multiply(&Rglobal,&m_Rlocal);
}

void CMember::ComputeJointDisplacementForce(iActLikeMatrix* pdf)
{
   // compute element forces due to a joint Deflection
   Vector6 Disp;
   Disp.Zero();
   CJoint *StartJnt, *EndJnt;
   m_JointKeeper.GetJoints(&StartJnt, &EndJnt);
   if (StartJnt->WasDisplacementLoadApplied())
   {
      Disp(0)=  StartJnt->m_dispLoad[0];
      Disp(1) = StartJnt->m_dispLoad[1];
      Disp(2) = StartJnt->m_dispLoad[2];
   }

   if (EndJnt->WasDisplacementLoadApplied())
   {
      Disp(3) = EndJnt->m_dispLoad[0];
      Disp(4) = EndJnt->m_dispLoad[1];
      Disp(5) = EndJnt->m_dispLoad[2];
   }

   m_Kglobal.Multiply(&Disp,pdf);

}


void CMember::GetGlobalJntForces(JointIDType jntId,Float64 *force)
{
   LONG i,count,start,end;
   Vector6 Rglobal;

   m_TransMatrix.Multiply(&m_Rlocal,&Rglobal,ATB);

   start = (LONG)jntId*TotalDOF/NumJoints;
   end = start + TotalDOF/NumJoints;

   for (i = start, count = 0; i < end; i++, count++)
   {
      force[count] = Rglobal(i);
   }
}

JointIDType CMember::GetJointNum(CJoint* j)
{

   CJoint *StartJnt, *EndJnt;
   m_JointKeeper.GetJoints(&StartJnt, &EndJnt);

   if (j == StartJnt)
      return 0;
   else if  (j == EndJnt)
      return 1;
   else
   {
      ATLASSERT(0); // "CMember::GetJointNum - Joint not found"
      return -1;
   }
}


void CMember::GetResults(MbrResult* pres)
{
   long i;
   for (i = 0; i < 6; i++)
       pres->SetDisplacement(i, m_Dlocal(i));

   for (i = 0; i < 6; i++)
       pres->SetForce(i,m_Rlocal(i));
}

void CMember::SetResults(const MbrResult& res)
{
   long i;
   for (i = 0; i < 6; i++)
      m_Dlocal(i) = res.GetDisplacement(i);

   for (i = 0; i < 6; i++)
      m_Rlocal(i) = res.GetForce(i);
}



// GetInternalForces
//
// Computes the internal member forces at the prescribed section.
// Assumes a stiffness analysis has been performed for the active
// Loading. Also assumes the active Loading is correct.
void CMember::GetInternalForces(Float64 loc,Fem2dMbrFaceType face,Float64 *force)
{
   Float64 fx, fy, mz; // Contribution of a single external load
   Float64 Fx, Fy, Mz; // Contribution of all external loads
   Float64 Rx, Ry, Rz; // Member End Forces

   // Initialize internal force resultants
   Fx = 0;
   Fy = 0;
   Mz = 0;

   Float64 angle  = m_JointKeeper.GetAngle();
   Float64 length = m_JointKeeper.GetLength();
   // Iterate over all loads on this member, for the active Loading
   MbrLoadPointerIterator ld( m_Loads.begin() );
   MbrLoadPointerIterator ldend( m_Loads.end() );
   for (; ld!=ldend; ld++)
   {
      // Member loads know how to compute their own internal force effects.
      MbrLoad *mbrLd = *ld;

      mbrLd->GetInternalForces(loc,length,angle,face,&fx,&fy,&mz);

      // Integrate the internal forces for this load into the resultant
      // internal force. The effect of the member end forces associated
      // with this load are not included.
      Fx += fx;
      Fy += fy;
      Mz += mz;
   }

   // Add effects of member end forces
   if (face == mftRight)
   {
      // right face
      Rx = m_Rlocal(3);
      Ry = m_Rlocal(4);
      Rz = m_Rlocal(5);
      force[0] =  Fx + Rx;
      force[1] =  Fy + Ry;
      force[2] =  Mz + Ry*(length - loc) + Rz;
   }
   else
   {
      // left face
      Rx = m_Rlocal(0);
      Ry = m_Rlocal(1);
      Rz = m_Rlocal(2);
      force[0] =  Fx +  Rx;
      force[1] =  Fy +  Ry;
      force[2] =  Mz + -Ry*loc + Rz;
   }
}

// GetDeflection
//
// Gets the deflection normal to the member at the specified location,
// in local coordinates.
//
// For now, this function only gets the dy deflection. It must be
// updated to compute the dx and rz deflections as well.
void CMember::GetDeflection(Float64 loc,Float64 *disp)
{
   Float64 dx, dy, rz;

   // Initialize internal force resultants
   disp[0] = 0;
   disp[1] = 0;
   disp[2] = 0;

   Float64 angle  = m_JointKeeper.GetAngle();
   Float64 length = m_JointKeeper.GetLength();

   // Iterate over all loads on this member, for the active Loading
   MbrLoadPointerIterator ld( m_Loads.begin() );
   MbrLoadPointerIterator ldend( m_Loads.end() );
   for (; ld!=ldend; ld++)
   {  
      // Member loads know how to compute their own internal displacements.
      MbrLoad *mbrLd = *ld;
      mbrLd->GetDisplacement(loc,mtFixFix,length,angle,
                             m_EA, m_EI,
                             &dx,&dy,&rz);

      // Integrate the internal displacements for this load into the resultant
      // internal displacement. The effect of the member end disp associated
      // with this load are not included.
      disp[0] += dx;
      disp[1] += dy;
      disp[2] += rz;
   }

   // displacements due to beam action
   // compute based on the fact that we know that the displacement
   // due to beam action at member ends will be in the form of a cubic along
   // the member.
   // Can write in the form y = ax^3  + bx^2 + cx + d
   //                       y'= 3ax^2 + 2bx  + c
   //
   // can then solve for boundary conditions: y(0)  = D0,   y(L)  = DL
   //                                         y'(0) = R0,   y'(L) = RL
   // and find that d = D0
   //               c = R0
   // can find a and b by substituting and solving
   Float64 L = length;
   Float64 D0 = m_Dlocal(1);
   Float64 DL = m_Dlocal(4);
   Float64 R0 = m_Dlocal(2);
   Float64 RL = m_Dlocal(5);

   Float64 a, b, c, d;
   a = (RL + R0)/(L*L) + 2.0*(D0-DL)/(L*L*L);
   b = (RL - R0)/(2.0*L) - (3.0*a*L)/2.0;
   c = R0;
   d = D0;

   // only affects y and y' deflection
   disp[1] += a*loc*loc*loc + b*loc*loc + c*loc + d;
   disp[2] += 3.0*a*loc*loc + 2.0*b*loc + c;

   // Compute axial effects of frame displacement
   disp[0] += m_Dlocal(0) + (m_Dlocal(3) - m_Dlocal(0))*loc/length;
}

// GetPinPinRotation
//
// Computes the member end rotations for a member with Pin-Pin
// internal boundary conditions. Uses the current element loads.
void CMember::GetPinPinRotation(Float64 &rz1,Float64 &rz2)
{
   Float64 vector[6];

   rz1 = 0;
   rz2 = 0;

   Float64 angle  = m_JointKeeper.GetAngle();
   Float64 length = m_JointKeeper.GetLength();

   MbrLoadPointerIterator i( m_Loads.begin() );
   MbrLoadPointerIterator iend( m_Loads.end() );
   for (; i!=iend; i++)
   {
      MbrLoad *load = *i;
      load->GetDispVector(mtPinPin,length,angle,
                          m_EA, m_EI,
                          vector);
      rz1 += vector[2];
      rz2 += vector[5];
   }

   // rigid body rotation only
   Float64 dy = m_Dlocal(4)-m_Dlocal(1);
   Float64 rot = dy/length; // small angle assumption - really is ATAN
   rz1 += rot;
   rz2 += rot;
}

// GetPinFixRotation
//
// Computes the member end rotations for a member with Pin-Fix
// internal boundary conditions. Uses the current element loads.
void CMember::GetPinFixRotation(Float64 &rz1)
{
   Float64 disp_vector[6];
   rz1 = 0;

   Float64 angle  = m_JointKeeper.GetAngle();
   Float64 length = m_JointKeeper.GetLength();

   // rotation due to internal forces
   MbrLoadPointerIterator i( m_Loads.begin() );
   MbrLoadPointerIterator iend( m_Loads.end() );
   for (; i!=iend; i++)
   {
      MbrLoad *load = *i;
      load->GetDispVector(mtPinFix,length,angle,
                          m_EA, m_EI,
                          disp_vector);
      rz1 += disp_vector[2];
   }

   // compute rotation at start end due to overall y deflection
   Float64 dy = m_Dlocal(1)-m_Dlocal(4);
   Float64 r  = -3*dy/(2*length);
   rz1 += r;

   // rigid body rotation
   rz1 -= m_Dlocal(5)/2.0;
}

// GetFixPinRotation
//
// Computes the member end rotations for a member with Fix-Pin
// internal boundary conditions. Uses the current element loads.
void CMember::GetFixPinRotation(Float64 &rz2)
{
   Float64 vector[6];
   rz2 = 0;

   Float64 angle  = m_JointKeeper.GetAngle();
   Float64 length = m_JointKeeper.GetLength();

   MbrLoadPointerIterator i( m_Loads.begin() );
   MbrLoadPointerIterator iend( m_Loads.end() );
   for (; i!=iend; i++)
   {
      MbrLoad *load = *i;
      load->GetDispVector(mtFixPin,length,angle,
                          m_EA, m_EI,
                          vector);
      rz2 += vector[5];
   }

   // compute rotation at end end due to overall y deflection
   Float64 dy = m_Dlocal(4)-m_Dlocal(1);
   Float64 r  = 3*dy/(2*length);
   rz2 += r;

   // rigid body rotation
   rz2 -= m_Dlocal(2)/2.0;
}

void CMember::AssembleF()
{
   // Assembles the local and global force vectors for the applied loads.
   // Loads should have been applied from TFemModel for the active load case.
   Vector6 Flocal;

   // Initialize the local force vector
   Flocal(0) = 0;
   Flocal(1) = 0;
   Flocal(2) = 0;
   Flocal(3) = 0;
   Flocal(4) = 0;
   Flocal(5) = 0;

   Float64 angle  = m_JointKeeper.GetAngle();
   Float64 length = m_JointKeeper.GetLength();
   bool was_loaded = false;

   // Iterate over all loads on this member
   // Point Loads
   Float64 vector[TotalDOF];

   MbrLoadPointerIterator ld( m_Loads.begin() );
   MbrLoadPointerIterator ldend( m_Loads.end() );
   for (; ld!=ldend; ld++)
   {
      was_loaded = true;
      MbrLoad *mbrLd = *ld;
      mbrLd->GetForceVector(GetMemberType(),length,angle,vector);

      // Integrate the force vector into this member's local force vector
      for (long i = 0; i < TotalDOF; i++)
         Flocal(i) -= vector[i];
   }


   // Compute Global Force Vector
   if (angle !=0.0)
   {
      m_TransMatrix.Multiply(&Flocal,&m_Fglobal,ATB);
   }
   else
   {
      m_Fglobal = Flocal;
   }
}

LONG CMember::GetNumDOF() const
{
   return TotalDOF;
}

LONG CMember::GetNumJoints() const
{
   return NumJoints;
}

LONG CMember::GetCondensedDOF(LONG dof)
{
   LONG retval;
   CJoint *StartJnt, *EndJnt;
   m_JointKeeper.GetJoints(&StartJnt, &EndJnt);

   if (dof < 3)
      retval = StartJnt->GetCondensedDOF(dof);
   else
      retval = EndJnt->GetCondensedDOF(dof - 3);

   return retval;
}

Float64 CMember::GetKglobal(LONG DOFi,LONG DOFj)
{
   return m_Kglobal(DOFi,DOFj);
}

bool CMember::operator == (const CMember &mbr) const
{
   return (m_ID == mbr.m_ID);
}

void CMember::ApplyLoad(MbrLoad *load)
{
   m_Loads.push_back(load);
}

void CMember::GetFglobal(Float64 *f) 
{
   // first compute member forces due to joint displacements
   // forces are transient since they are not needed later
   Vector6 dforce;
   ComputeJointDisplacementForce(&dforce);

   for (long i = 0; i < TotalDOF; i++)
      f[i] = m_Fglobal(i) - dforce(i);
}

bool CMember::IsEquilibriumSatisfied(Float64 tolerance)
{
   Float64 _fx, _fy, _mz; // Contribution of a single external load
   Float64 fx, fy, mz; // Contribution of all external loads on the member
   Float64 Fx, Fy, Mz; // Resultant forces at right end of member
   Float64 fx1,fy1,mz1; // Member end forces at start of member
   Float64 fx2,fy2,mz2; // Member end forces at end of member
   Float64 length;   // Member length
   Float64 angle; // Member orientation

   // Initialize internal force resultants
   fx = 0;
   fy = 0;
   mz = 0;

   length = m_JointKeeper.GetLength();
   angle = m_JointKeeper.GetAngle();

   // Iterate over all loads on this member, for the active Loading
   // Get force effects at start of member from the applied loads.
   MbrLoadPointerIterator iter( m_Loads.begin() );
   MbrLoadPointerIterator iterend( m_Loads.end() );
   while(iter!=iterend)
   {
      // Member loads know how to compute their own internal force effects.
      MbrLoad *mbrLd = *(iter++);
      mbrLd->GetOriginForces(length,angle,&_fx,&_fy,&_mz);
      fx += _fx;
      fy += _fy;
      mz += _mz;
   }

   fx1 = m_Rlocal(0);
   fy1 = m_Rlocal(1);
   mz1 = m_Rlocal(2);
   fx2 = m_Rlocal(3);
   fy2 = m_Rlocal(4);
   mz2 = m_Rlocal(5);
   Fx = fx + fx1 + fx2;
   Fy = fy + fy1 + fy2;
   Mz = mz + mz1 + mz2 + length*fy2;


   if (!((-tolerance <= Fx) && (Fx <= tolerance)))
      return false;
   if (!((-tolerance <= Fy) && (Fy <= tolerance)))
      return false;
   if (!((-tolerance <= Mz) && (Mz <= tolerance)))
      return false;

   return true;
}
////////////////// The JointKeeper

CMember::JointKeeper::JointKeeper(CMember* pMember):
m_pMember(pMember),
m_StartJoint(-1),
m_EndJoint(-1),
m_pStartJoint(0),
m_pEndJoint(0),
m_Length(0.0),
m_Angle(0.0),
m_Dirty(true)
{
}

bool CMember::JointKeeper::PutStartJoint(JointIDType id)
{
   if (m_StartJoint != id)
   {
      m_StartJoint = id;
      m_Dirty = true;
      return true;
   }
   else
      return false;
}

JointIDType CMember::JointKeeper::GetStartJoint()
{
   return m_StartJoint;
}

bool CMember::JointKeeper::PutEndJoint(JointIDType id)
{
   if (m_EndJoint != id)
   {
      m_EndJoint = id;
      m_Dirty = true;
      return true;
   }
   else
      return false;
}

JointIDType CMember::JointKeeper::GetEndJoint()
{
   return m_EndJoint;
}

void CMember::JointKeeper::GetJoints(CJoint** pStart, CJoint** pEnd)
{
   if (m_Dirty)
   {
      Compute();
   }

   ATLASSERT(m_pStartJoint!=0);
   ATLASSERT(m_pEndJoint!=0);

   *pStart = m_pStartJoint;
   *pEnd   = m_pEndJoint;
}

Float64 CMember::JointKeeper::GetLength()
{
   if (m_Dirty)
   {
      Compute();
   }
   ATLASSERT(m_pStartJoint!=0);
   ATLASSERT(m_pEndJoint!=0);

   return m_Length;
}

Float64 CMember::JointKeeper::GetAngle()
{
   if (m_Dirty)
   {
      Compute();
   }
   ATLASSERT(m_pStartJoint!=0);
   ATLASSERT(m_pEndJoint!=0);

   return m_Angle;
}

void CMember::JointKeeper::Compute()
{
   // joints
   m_pStartJoint = 0;
   m_pEndJoint = 0;

   // must first get a CModel - This cast is ugly, but is done to reduce physical coupling
   CModel* pModel;
   pModel = static_cast<CModel*>(m_pMember->m_pModel);

   CJointCollection* pcoll = pModel->GetJoints();
   ATLASSERT(pcoll!=0);
   
   m_pStartJoint = pcoll->Find(m_StartJoint);
   if (m_pStartJoint==0)
   {
      CComBSTR msg = m_pMember->JointDoesntExistError(metStart);
      THROW_MSG(msg, FEM2D_E_MEMBER_JOINT_NOT_EXISTS, IDH_E_MEMBER_JOINT_NOT_EXISTS);
   }

   m_pEndJoint = pcoll->Find(m_EndJoint);
   if (m_pEndJoint==0)
   {
      CComBSTR msg = m_pMember->JointDoesntExistError(metEnd);
      THROW_MSG(msg, FEM2D_E_MEMBER_JOINT_NOT_EXISTS, IDH_E_MEMBER_JOINT_NOT_EXISTS);
   }

   // length
   Float64 startX, startY, endX, endY;
   m_pStartJoint->get_X(&startX);
   m_pStartJoint->get_Y(&startY);
   m_pEndJoint->get_X(&endX);
   m_pEndJoint->get_Y(&endY);

   Float64 dx = startX-endX;
   Float64 dy = startY-endY;
   m_Length = sqrt(dx*dx + dy*dy);

   if (m_Length==0.0)
   {
      CComBSTR msg = CreateErrorMsg1(IDS_E_ZERO_LENGTH_MEMBER, m_pMember->m_ID);
      THROW_MSG(msg, FEM2D_E_ZERO_LENGTH_MEMBER, IDH_E_ZERO_LENGTH_MEMBER);
   }

   // angle
   m_Angle = atan2(endY-startY,endX-startX);

   m_Dirty = false;
}


///////////// Errors


CComBSTR CMember::JointDoesntExistError(Fem2dMbrEndType end)
{
   JointIDType jntid;
   if (end==metStart)
      jntid = m_JointKeeper.GetStartJoint();
   else
      jntid = m_JointKeeper.GetEndJoint();

   return CreateErrorMsg2(IDS_E_MEMBER_JOINT_NOT_EXISTS, m_ID, jntid);
}




