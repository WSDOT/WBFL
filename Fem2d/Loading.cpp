///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2021  Washington State Department of Transportation
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
// Loading.cpp : Implementation of CLoading
#include "stdafx.h"
#include "Loading.h"
#include "Model.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoading

STDMETHODIMP CLoading::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFem2dLoading
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CLoading::~CLoading()
{
    m_pJointLoads->Release();
    m_pDistributedLoads->Release();
    m_pJointDeflections->Release();
    m_pPointLoads->Release();
    m_pMemberStrains->Release();
}

HRESULT CLoading::OnCreate(IFem2dModel* pParent, ModelEvents* pEvents, LoadCaseIDType id)
{
   InitParent(pParent); // CCircularChild implementation
   m_pModel = pEvents;
   m_ID = id;

   // Joint loads
   CComObject<CJointLoadCollection>* pj;
   HRESULT hr = CComObject<CJointLoadCollection>::CreateInstance( &pj );
   if ( FAILED(hr) )
      return hr;

   pj->Init(pParent, m_pModel, this);
   m_pJointLoads = pj;
   m_pJointLoads->AddRef();

   // Distributed loads
   CComObject<CDistributedLoadCollection>* pw;
   hr = CComObject<CDistributedLoadCollection>::CreateInstance( &pw );
   if ( FAILED(hr) )
      return hr;

   pw->Init(pParent, m_pModel, this);
   m_pDistributedLoads = pw;
   m_pDistributedLoads->AddRef();

   // Joint Deflections
   CComObject<CJointDeflectionCollection>* pd;
   hr = CComObject<CJointDeflectionCollection>::CreateInstance( &pd );
   if ( FAILED(hr) )
      return hr;

   pd->Init(pParent, m_pModel, this);
   m_pJointDeflections = pd;
   m_pJointDeflections->AddRef();

   // Point loads
   CComObject<CPointLoadCollection>* pp;
   hr = CComObject<CPointLoadCollection>::CreateInstance( &pp );
   if ( FAILED(hr) )
      return hr;

   pp->Init(pParent, m_pModel, this);
   m_pPointLoads = pp;
   m_pPointLoads->AddRef();

   // Member Strains
   CComObject<CMemberStrainCollection>* ps;
   hr = CComObject<CMemberStrainCollection>::CreateInstance( &ps );
   if ( FAILED(hr) )
      return hr;

   ps->Init(pParent, m_pModel, this);
   m_pMemberStrains = ps;
   m_pMemberStrains->AddRef();

   return S_OK;
}

static const Float64 MY_VER=1.0;

STDMETHODIMP CLoading::Load(/*[in]*/ IStructuredLoad2 *pload)
{
   HRESULT hr;
   hr = pload->BeginUnit(CComBSTR("Loading"));
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

      hr = m_pJointLoads->Load(CComBSTR("JointLoads"), 1.0, pload);
      if (FAILED(hr))
         return hr;

      m_pDistributedLoads->Load(CComBSTR("DistributedLoads"), 1.0, pload);
      if (FAILED(hr))
         return hr;

      m_pMemberStrains->Load(CComBSTR("MemberStrains"), 1.0, pload);
      if (FAILED(hr))
         return hr;

      m_pJointDeflections->Load(CComBSTR("JointDeflections"), 1.0, pload);
      if (FAILED(hr))
         return hr;

      m_pPointLoads->Load(CComBSTR("PointLoads"), 1.0, pload);
      if (FAILED(hr))
         return hr;   

   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CLoading::Save(/*[in]*/ IStructuredSave2 *psave)
{
   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("Loading"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      hr = psave->put_Property(CComBSTR("ID"),CComVariant(m_ID));
      if (FAILED(hr))
         return hr;

      hr = m_pJointLoads->Save(CComBSTR("JointLoads"), 1.0, psave);
      if (FAILED(hr))
         return hr;

      m_pDistributedLoads->Save(CComBSTR("DistributedLoads"), 1.0, psave);
      if (FAILED(hr))
         return hr;

      m_pMemberStrains->Save(CComBSTR("MemberStrains"), 1.0, psave);
      if (FAILED(hr))
         return hr;

      m_pJointDeflections->Save(CComBSTR("JointDeflections"), 1.0, psave);
      if (FAILED(hr))
         return hr;

      m_pPointLoads->Save(CComBSTR("PointLoads"), 1.0, psave);
      if (FAILED(hr))
         return hr;   
   }

   hr = psave->EndUnit();
   if (FAILED(hr))
      return hr;

   return S_OK;
}

STDMETHODIMP CLoading::get_ID(LoadCaseIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_ID;

	return S_OK;
}

STDMETHODIMP CLoading::get_JointLoads(IFem2dJointLoadCollection **pVal)
{
   CHECK_RETOBJ(pVal);
	*pVal = m_pJointLoads;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CLoading::get_DistributedLoads(IFem2dDistributedLoadCollection **pVal)
{
   CHECK_RETOBJ(pVal);
	*pVal = m_pDistributedLoads;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CLoading::get_JointDeflections(IFem2dJointDeflectionCollection **pVal)
{
   CHECK_RETOBJ(pVal);
	*pVal = m_pJointDeflections;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CLoading::get_PointLoads(IFem2dPointLoadCollection **pVal)
{
   CHECK_RETOBJ(pVal);
	*pVal = m_pPointLoads;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CLoading::get_MemberStrains(IFem2dMemberStrainCollection **pVal)
{
   CHECK_RETOBJ(pVal);
	*pVal = m_pMemberStrains;
   (*pVal)->AddRef();

	return S_OK;
}


void CLoading::ApplyLoads(CModel *model)
{
   CJointCollection* joints = model->GetJoints();

   // apply joint loads
   JointLoadIterator jntLdIter( m_pJointLoads->begin() );
   JointLoadIterator jntLdIterEnd( m_pJointLoads->end() );
   while (jntLdIter!=jntLdIterEnd)
   {
      CJointLoad *jntLd = *(jntLdIter++);
      JointIDType id;
      jntLd->get_JointID(&id);
      CJoint *jnt = joints->Find(id);
      if (jnt == nullptr)
      {
         LoadIDType lid;
         jntLd->get_ID(&lid);
         CComBSTR msg = CreateErrorMsg2(IDS_E_JOINT_LOAD_REF_JOINT_NOT_EXISTS, lid, id);
         THROW_MSG(msg, FEM2D_E_JOINT_LOAD_REF_JOINT_NOT_EXISTS, IDH_E_JOINT_LOAD_REF_JOINT_NOT_EXISTS);
      }

      jnt->ApplyLoad(jntLd);
   }

   // apply joint Deflections
   JointDeflectionIterator jntDispIter( m_pJointDeflections->begin() );
   JointDeflectionIterator jntDispIterEnd( m_pJointDeflections->end() );
   while (jntDispIter!=jntDispIterEnd)
   {
      CJointDeflection *jntDisp = *(jntDispIter++);
      JointIDType id;
      jntDisp->get_JointID(&id);
      CJoint *jnt = joints->Find(id);
      if (jnt == nullptr)
      {
         LoadIDType lid;
         jntDisp->get_ID(&lid);
         CComBSTR msg = CreateErrorMsg2(IDS_E_JOINT_DISP_REF_JOINT_NOT_EXISTS, lid, id);
         THROW_MSG(msg, FEM2D_E_JOINT_DISP_REF_JOINT_NOT_EXISTS, IDH_E_JOINT_DISP_REF_JOINT_NOT_EXISTS);
      }

      jnt->ApplyLoad(jntDisp);
   }


   CMemberCollection* members = model->GetMembers();
   // point loads applied to members
   PointLoadIterator ptLdIter( m_pPointLoads->begin() );
   PointLoadIterator ptLdIterEnd( m_pPointLoads->end() );
   while(ptLdIter!=ptLdIterEnd)
   {
      CPointLoad *ptLd = *(ptLdIter++);
      MemberIDType id;
      ptLd->get_MemberID(&id);
      CMember *mbr = members->Find(id);
      if (mbr == nullptr)
      {
         LoadIDType lid;
         ptLd->get_ID(&lid);
         CComBSTR msg = CreateErrorMsg2(IDS_E_POINT_LOAD_REF_MEMBER_NOT_EXISTS, lid, id);
         THROW_MSG(msg, FEM2D_E_POINT_LOAD_REF_MEMBER_NOT_EXISTS, IDH_E_POINT_LOAD_REF_MEMBER_NOT_EXISTS);
      }

      mbr->ApplyLoad(ptLd);
   }

   // Distributed loads applied to members
   DistributedLoadIterator dstLdIter( m_pDistributedLoads->begin() );
   DistributedLoadIterator dstLdIterEnd( m_pDistributedLoads->end() );
   while(dstLdIter!=dstLdIterEnd)
   {
      CDistributedLoad *pdstLd = *(dstLdIter++);
      MemberIDType id;
      pdstLd->get_MemberID(&id);
      CMember *mbr = members->Find(id);
      if (mbr == nullptr)
      {
         LoadIDType lid;
         pdstLd->get_ID(&lid);
         CComBSTR msg = CreateErrorMsg2(IDS_E_DIST_LOAD_REF_MEMBER_NOT_EXISTS, lid, id);
         THROW_MSG(msg, FEM2D_E_DIST_LOAD_REF_MEMBER_NOT_EXISTS, IDH_E_DIST_LOAD_REF_MEMBER_NOT_EXISTS);
      }

      mbr->ApplyLoad(pdstLd);
   }

   // member strains
   MemberStrainIterator pmsIter( m_pMemberStrains->begin() );
   MemberStrainIterator pmsIterEnd( m_pMemberStrains->end() );
   while(pmsIter!=pmsIterEnd)
   {
      CMemberStrain *pms = *(pmsIter++);
      MemberIDType id;
      pms->get_MemberID(&id);
      CMember *mbr = members->Find(id);
      if (mbr == nullptr)
      {
         LoadIDType lid;
         pms->get_ID(&lid);
         CComBSTR msg = CreateErrorMsg2(IDS_E_POINT_LOAD_REF_MEMBER_NOT_EXISTS, lid, id);
         THROW_MSG(msg, FEM2D_E_POINT_LOAD_REF_MEMBER_NOT_EXISTS, IDH_E_POINT_LOAD_REF_MEMBER_NOT_EXISTS);
      }

      mbr->ApplyLoad(pms);
   }

}

// apply loads to a single member
void CLoading::ApplyLoads(CMember *pmbr)
{

   MemberIDType mid;
   pmbr->get_ID(&mid);

   // Point loads
   PointLoadIterator ptLdIter( m_pPointLoads->begin() );
   PointLoadIterator ptLdIterEnd( m_pPointLoads->end() );
   while(ptLdIter!=ptLdIterEnd)
   {
      CPointLoad *ptLd = *(ptLdIter++);
      MemberIDType id;
      ptLd->get_MemberID(&id);
      if (mid == id)
      {
         pmbr->ApplyLoad(ptLd);
      }
   }

   // Distributed loads
   DistributedLoadIterator dstLdIter( m_pDistributedLoads->begin() );
   DistributedLoadIterator dstLdIterEnd( m_pDistributedLoads->end() );
   while(dstLdIter!=dstLdIterEnd)
   {
      CDistributedLoad *ptLd = *(dstLdIter++);
      MemberIDType id;
      ptLd->get_MemberID(&id);
      if (mid == id)
      {
         pmbr->ApplyLoad(ptLd);
      }
   }

   // member strains
   MemberStrainIterator pmsIter( m_pMemberStrains->begin() );
   MemberStrainIterator pmsIterEnd( m_pMemberStrains->end() );
   while(pmsIter!=pmsIterEnd)
   {
      CMemberStrain *pms = *(pmsIter++);
      MemberIDType id;
      pms->get_MemberID(&id);
      if (mid == id)
      {
         pmbr->ApplyLoad(pms);
      }
   }
}

