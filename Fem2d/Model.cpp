///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2015  Washington State Department of Transportation
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
// Model.cpp : Implementation of CModel
#include "stdafx.h"
#include "Model.h"

#include "JointCollection.h"
#include "MemberCollection.h"
#include "LoadingCollection.h"
#include "POICollection.h"
#include "stlTools.h"
#include "MathEx.h"

#include <stdlib.h> 


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModel
CModel::CModel()
{  
#if defined ENABLE_LOGGING
   logfile.open("fem.log");
   logfile << "Dump for Fem2d Model"<<std::endl;
#endif

   m_pF = 0;

#if defined _DEBUG
   m_pForig = 0;
#endif
   // Valid values for these parameters are >= 0
   // They are set to < 0 there so they may be asserted
   // later if invalid
   m_BandWidth       = -1;
   m_NumCondensedDOF = -1;
   m_NumGlobalDOF    = -1;

   SetEquilibriumCheckTolerance(EPS);

   m_ModelDirty = true;
}

CModel::~CModel()
{  
   ClearAnalysis();

#if defined ENABLE_LOGGING
   logfile.close();
#endif

}

HRESULT CModel::FinalConstruct()
{  

   // Joints
     CComObject<CJointCollection>* pj;
     HRESULT hr = CComObject<CJointCollection>::CreateInstance( &pj );
     if ( FAILED(hr) )
        return hr;

   pj->OnCreate(this,this);
   pj->AddRef();
   m_pJoints.Attach(pj);

   // Members
   CComObject<CMemberCollection>* pm;
   hr = CComObject<CMemberCollection>::CreateInstance( &pm );
   if ( FAILED(hr) )
      return hr;

   pm->OnCreate(this,this);
   pm->AddRef();
   m_pMembers.Attach(pm);

   // Loadings
   CComObject<CLoadingCollection>* plc;
   hr = CComObject<CLoadingCollection>::CreateInstance( &plc );
   if ( FAILED(hr) )
      return hr;

   plc->OnCreate(this,this);
   plc->AddRef();
   m_pLoadings.Attach(plc);

   // POIs
   CComObject<CPOICollection>* ppoi;
   hr = CComObject<CPOICollection>::CreateInstance( &ppoi );
   if ( FAILED(hr) )
      return hr;

   ppoi->OnCreate(this,this);
   ppoi->AddRef();
   m_pPOIs.Attach(ppoi);

   return S_OK;
}

STDMETHODIMP CModel::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFem2dModel
	};
	for (long i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


static const Float64 MY_VER=2.0;

// IStructuredStorage2
STDMETHODIMP CModel::Load(/*[in]*/ IStructuredLoad2 *pload)
{
   this->ClearAnalysis();

   HRESULT hr;
   hr = pload->BeginUnit(CComBSTR("Fem2d"));
   if (FAILED(hr))
      return hr;

   Float64 ver;
   hr = pload->get_Version(&ver);
   if (FAILED(hr))
      return hr;

   if (MY_VER < ver)
      return STRLOAD_E_BADVERSION;

   {
      // equilibrium tolerance
      if ( 1 < ver )
      {
         CComVariant var;
         var.vt = VT_BSTR;

         hr = pload->get_Property(CComBSTR("Name"),&var);
         if (FAILED(hr))
            return hr;

         m_Name = var.bstrVal;
      }

      CComVariant vardbl;
      vardbl.vt = VT_R8;
      hr = pload->get_Property(CComBSTR("EquilibriumTolerance"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_Tolerance = vardbl.dblVal;

      // joints
      hr = m_pJoints->Load(CComBSTR("Joints"), 1.0, pload);
      if (FAILED(hr))
         return hr;

      // members
      hr = m_pMembers->Load(CComBSTR("Members"), 1.0, pload);
      if (FAILED(hr))
         return hr;

      // pois
      hr = m_pPOIs->Load(CComBSTR("POIs"), 1.0, pload);
      if (FAILED(hr))
         return hr;

      // loadings
      hr = m_pLoadings->Load(CComBSTR("Loadings"), 1.0, pload);
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

STDMETHODIMP CModel::Save(/*[in]*/ IStructuredSave2 *psave)
{
   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("Fem2d"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      // equilibrium tolerance
      hr = psave->put_Property(CComBSTR("Name"),CComVariant(m_Name));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("EquilibriumTolerance"),CComVariant(m_Tolerance));
      if (FAILED(hr))
         return hr;

      // joints
      hr = m_pJoints->Save(CComBSTR("Joints"), 1.0, psave);
      if (FAILED(hr))
         return hr;

      // members
      hr = m_pMembers->Save(CComBSTR("Members"), 1.0, psave);
      if (FAILED(hr))
         return hr;

      // pois
      hr = m_pPOIs->Save(CComBSTR("POIs"), 1.0, psave);
      if (FAILED(hr))
         return hr;

      // loadings
      hr = m_pLoadings->Save(CComBSTR("Loadings"), 1.0, psave);
      if (FAILED(hr))
         return hr;
   }

   hr = psave->EndUnit();
   if (FAILED(hr))
      return hr;


   return S_OK;
}

STDMETHODIMP CModel::put_Name(BSTR name)
{
   m_Name = name;
   return S_OK;
}

STDMETHODIMP CModel::get_Name(BSTR* name)
{
   *name = m_Name.Copy();
   return S_OK;
}

STDMETHODIMP CModel::get_Joints(IFem2dJointCollection **pVal)
{
   CHECK_RETOBJ(pVal);
   ATLASSERT(m_pJoints!=0);

	*pVal = m_pJoints;
   (**pVal).AddRef();

   return S_OK;
}

STDMETHODIMP CModel::get_Members(IFem2dMemberCollection **pVal)
{
   CHECK_RETOBJ(pVal);
   ATLASSERT(m_pMembers!=0);

	*pVal = m_pMembers;
   (**pVal).AddRef();

   return S_OK;
}

STDMETHODIMP CModel::get_Loadings(IFem2dLoadingCollection **pVal)
{
   CHECK_RETOBJ(pVal);
   ATLASSERT(m_pLoadings!=0);

	*pVal = m_pLoadings;
   (**pVal).AddRef();

	return S_OK;
}

STDMETHODIMP CModel::get_POIs(IFem2dPOICollection **pVal)
{
   CHECK_RETOBJ(pVal);
   ATLASSERT(m_pPOIs!=0);

	*pVal = m_pPOIs;
   (**pVal).AddRef();

	return S_OK;
}

STDMETHODIMP CModel::Clear()
{
   m_pJoints->Clear();
   m_pMembers->Clear();
   m_pLoadings->Clear();
   m_pPOIs->Clear();

   ClearAnalysis();

	return S_OK;
}

void CModel::ClearAnalysis()
{
   RemoveAllResults();

   FreeFGlobal();

   m_BandWidth = -1;
   m_NumCondensedDOF = -1;
   m_NumGlobalDOF = -1;

   m_ModelDirty = true;
}

// generic function to deal with exceptions caught in compute functions
HRESULT CModel::DealWithExceptions()
{
   // now try to make sense out of what got thrown
   try
   {
      // if we're here, something got hosed during compute - clear 
      // matrices and results
      ClearAnalysis();

      throw; // throw whatever got thrown last to be caught immediately!
   }
   catch (CComException& re)
   {
      // somebody puked from way down deep. Build error message and crap out
      CComBSTR msg(re.GetErrorMessage());
      HRESULT hr = re.GetHresult();
      DWORD helpid = re.GetHelpID();
      return CComCoClass<CModel,&CLSID_Fem2dModel>::Error(msg, helpid, GetHelpFile(), IID_IFem2dModel, hr);
   }
   catch (...)
   {
      // could make up a custom message here, but we don't know what happened so why try?
      // the main point is not to let the exception out into the com world
      ATLASSERT(false);
      //return E_FAIL;
      throw;
   }
}



STDMETHODIMP CModel::ComputeJointDeflections(LoadCaseIDType lc, JointIDType jnt, Float64 *Dx, Float64 *Dy, Float64 *Rz)
{
   CHECK_RETVAL(Dx);
   CHECK_RETVAL(Dy);
   CHECK_RETVAL(Rz);

   try
   {
      // compute any outdated results
      Compute();

      // retrieve results
      JntResultIterator jit( m_JntResults.find(jnt) );
      if (jit == m_JntResults.end())
      {
         CComBSTR msg(::CreateErrorMsg1(IDS_E_JOINT_NOT_FOUND, jnt));
         return CComCoClass<CModel,&CLSID_Fem2dModel>::Error(msg, IDH_E_JOINT_NOT_FOUND, GetHelpFile(), IID_IFem2dModel, FEM2D_E_JOINT_NOT_FOUND);
      }
      JntResultArray* array = jit->second;

      const JntResult* jntResult = array->Find(lc);
      if (0 == jntResult)
      {
         CComBSTR msg(::CreateErrorMsg1(IDS_E_LOADING_NOT_FOUND, lc));
         return CComCoClass<CModel,&CLSID_Fem2dModel>::Error(msg, IDH_E_LOADING_NOT_FOUND, GetHelpFile(), IID_IFem2dModel, FEM2D_E_LOADING_NOT_FOUND);
      }

      *Dx = jntResult->GetDeflection(0);
      *Dy = jntResult->GetDeflection(1);
      *Rz = jntResult->GetDeflection(2);
   }
   catch (...)
   {
      //  use standard exception handler to deal with these pesky's
      return DealWithExceptions();
   }

	return S_OK;
}

STDMETHODIMP CModel::ComputeMemberDeflections(LoadCaseIDType lc, MemberIDType mbr, Float64 *startDx, Float64 *startDy, Float64 *startRz, Float64 *endDx, Float64 *endDy, Float64 *endRz)
{
   CHECK_RETVAL(startDx);
   CHECK_RETVAL(startDy);
   CHECK_RETVAL(startRz);
   CHECK_RETVAL(endDx);
   CHECK_RETVAL(endDy);
   CHECK_RETVAL(endRz);

   try
   {
      // compute any outdated results
      Compute();

         // retrieve results
      MbrResultIterator jit( m_MbrResults.find(mbr) );
      if (jit == m_MbrResults.end())
      {
         CComBSTR msg(::CreateErrorMsg1(IDS_E_MEMBER_NOT_FOUND, mbr));
         return CComCoClass<CModel,&CLSID_Fem2dModel>::Error(msg, IDH_E_MEMBER_NOT_FOUND, GetHelpFile(), IID_IFem2dModel, FEM2D_E_MEMBER_NOT_FOUND);
      }
      CMember::MbrResultArray* array = jit->second;

      const CMember::MbrResult* mbrResult = array->Find(lc);
      if (0 == mbrResult)
      {
         CComBSTR msg(::CreateErrorMsg1(IDS_E_LOADING_NOT_FOUND, lc));
         return CComCoClass<CModel,&CLSID_Fem2dModel>::Error(msg, IDH_E_LOADING_NOT_FOUND, GetHelpFile(), IID_IFem2dModel, FEM2D_E_LOADING_NOT_FOUND);
      }

      *startDx = mbrResult->GetDeflection(0);
      *startDy = mbrResult->GetDeflection(1);
      *startRz = mbrResult->GetDeflection(2);
      *endDx   = mbrResult->GetDeflection(3);
      *endDy   = mbrResult->GetDeflection(4);
      *endRz   = mbrResult->GetDeflection(5);

   }
   catch (...)
   {
      //  use standard exception handler to deal with these pesky's
      return DealWithExceptions();
   }

	return S_OK;
}


STDMETHODIMP CModel::ComputeReactions(LoadCaseIDType lc, JointIDType jnt, Float64 *Fx, Float64 *Fy, Float64 *Mz)
{
   CHECK_RETVAL(Fx);
   CHECK_RETVAL(Fy);
   CHECK_RETVAL(Mz);

   try
   {
      // compute any outdated results
      Compute();

         // retrieve results
      JntResultIterator jit( m_JntResults.find(jnt) );
      if (jit == m_JntResults.end())
      {
         CComBSTR msg(::CreateErrorMsg1(IDS_E_JOINT_NOT_FOUND, jnt));
         return CComCoClass<CModel,&CLSID_Fem2dModel>::Error(msg, IDH_E_JOINT_NOT_FOUND, GetHelpFile(), IID_IFem2dModel, FEM2D_E_JOINT_NOT_FOUND);
      }
      JntResultArray* array = jit->second;

      const JntResult* jntResult = array->Find(lc);
      if (0 == jntResult)
      {
         CComBSTR msg(::CreateErrorMsg1(IDS_E_LOADING_NOT_FOUND, lc));
         return CComCoClass<CModel,&CLSID_Fem2dModel>::Error(msg, IDH_E_LOADING_NOT_FOUND, GetHelpFile(), IID_IFem2dModel, FEM2D_E_LOADING_NOT_FOUND);
      }

      *Fx = jntResult->GetForce(0);
      *Fy = jntResult->GetForce(1);
      *Mz = jntResult->GetForce(2);
   }
   catch (...)
   {
      //  use standard exception handler to deal with these pesky's
      return DealWithExceptions();
   }

	return S_OK;
}

STDMETHODIMP CModel::ComputeMemberForces(LoadCaseIDType lc, MemberIDType mbr, Float64 *startFx, Float64 *startFy, Float64 *startMz, Float64 *endFx, Float64 *endFy, Float64 *endMz)
{
   return ComputeMemberForcesEx(lc, mbr, lotMember, startFx, startFy, startMz, endFx, endFy, endMz);
}

STDMETHODIMP CModel::ComputeMemberForcesEx(LoadCaseIDType lc, MemberIDType mid, Fem2dLoadOrientation orientation, Float64 *startFx, Float64 *startFy, Float64 *startMz, Float64 *endFx, Float64 *endFy, Float64 *endMz)
{
   CHECK_RETVAL(startFx);
   CHECK_RETVAL(startFy);
   CHECK_RETVAL(startMz);
   CHECK_RETVAL(endFx);
   CHECK_RETVAL(endFy);
   CHECK_RETVAL(endMz);

   try
   {
      // compute any outdated results
      Compute();

      // retrieve results
      MbrResultIterator jit( m_MbrResults.find(mid) );
      if (jit == m_MbrResults.end())
      {
         CComBSTR msg(::CreateErrorMsg1(IDS_E_MEMBER_NOT_FOUND, mid));
         return CComCoClass<CModel,&CLSID_Fem2dModel>::Error(msg, IDH_E_MEMBER_NOT_FOUND, GetHelpFile(), IID_IFem2dModel, FEM2D_E_MEMBER_NOT_FOUND);
      }
      CMember::MbrResultArray* array = jit->second;

      const CMember::MbrResult* mbrResult = array->Find(lc);
      if (0 == mbrResult)
      {
         CComBSTR msg(::CreateErrorMsg1(IDS_E_LOADING_NOT_FOUND, lc));
         return CComCoClass<CModel,&CLSID_Fem2dModel>::Error(msg, IDH_E_LOADING_NOT_FOUND, GetHelpFile(), IID_IFem2dModel, FEM2D_E_LOADING_NOT_FOUND);
      }

      if (orientation==lotMember)
      {
         // member results are stored in local coords
         *startFx = mbrResult->GetForce(0);
         *startFy = mbrResult->GetForce(1);
         *startMz = mbrResult->GetForce(2);
         *endFx   = mbrResult->GetForce(3);
         *endFy   = mbrResult->GetForce(4);
         *endMz   = mbrResult->GetForce(5);
      }
      else
      {
         // must be global or bogus
         CheckLoadOrientation(orientation);

         // orient results into global coords
         // get orientation of member and rotate results into global coord's
         CMember *mbr = m_pMembers->Find(mid);
         if (mbr==0)
         {
            ATLASSERT(false); // lookup above should have caught this
            CComBSTR msg(::CreateErrorMsg1(IDS_E_MEMBER_NOT_FOUND, mid));
            return CComCoClass<CModel,&CLSID_Fem2dModel>::Error(msg, IDH_E_MEMBER_NOT_FOUND, GetHelpFile(), IID_IFem2dModel, FEM2D_E_MEMBER_NOT_FOUND);
         }

         Float64 ang = mbr->m_JointKeeper.GetAngle();
         Float64 c = cos(ang);
         Float64 s = sin(ang);

         // start end
         Float64 fx, fy;
         fx = mbrResult->GetForce(0);
         fy = mbrResult->GetForce(1);

         *startFx = fx*c - fy*s;
         *startFy = fx*s + fy*c;
         *startMz = mbrResult->GetForce(2);

         // end end
         fx = mbrResult->GetForce(3);
         fy = mbrResult->GetForce(4);

         *endFx = fx*c - fy*s;
         *endFy = fx*s + fy*c;
         *endMz = mbrResult->GetForce(5);
      }
   }
   catch (...)
   {
      //  use standard exception handler to deal with these pesky's
      return DealWithExceptions();
   }

	return S_OK;
}

STDMETHODIMP CModel::ComputePOIDeflections(LoadCaseIDType lc, PoiIDType poiID, Fem2dLoadOrientation orientation, Float64 *Dx, Float64 *Dy, Float64 *Rz)
{
   CHECK_RETVAL(Dx);
   CHECK_RETVAL(Dy);
   CHECK_RETVAL(Rz);
   // POI results are computed differently than joint and member results. They 
   // are computed as-needed and then stored individually.
   try
   {
      const PoiResult* poiResult = 0;

      // look in simple cache first
      if ( m_SimplePOIResultCache.IsHit(poiID, lc) )
      {
         poiResult = &(m_SimplePOIResultCache.poiResult);
      }
      else
      {
         CheckLoadOrientation(orientation);

         // compute any outdated member/joint results
         Compute();

         // first see if results have already been calculated
         PoiResultIterator jit( m_PoiResults.find(poiID) );
         if (jit != m_PoiResults.end())
         {
            PoiResultArray* array = jit->second;
            poiResult = array->Find(lc);
         }

         if (0==poiResult)
         {
            // result not in store - we need to go out and calculate it
            poiResult = StorePoiResults(lc, poiID);
         }

         // should have thrown by here if problem
         if (poiResult==0)
         {
            ATLASSERT(0);
            THROW_MSG("Logic error computing poi result CModel::ComputePOIDisplacements",E_FAIL, IDH_E_LOGIC_ERROR); 
         }
      }

      // at this point, we have a result - map it to our return values
      if (orientation==lotMember)
      {
         *Dx = poiResult->GetDeflection(0);
         *Dy = poiResult->GetDeflection(1);
         *Rz = poiResult->GetDeflection(2);
      }
      else if (orientation==lotGlobal || orientation==lotGlobalProjected)
      {
         // have to rotate Deflections into global coord's
         // get poi and member
         CPOI *poi = m_pPOIs->Find(poiID);
         if (poi==0)
         {
            ATLASSERT(false); // this should never happen
            CComBSTR msg = ::CreateErrorMsg1(IDS_E_POI_NOT_FOUND, poiID);
            THROW_MSG(msg, FEM2D_E_POI_NOT_FOUND, IDH_E_POI_NOT_FOUND);
         }
         MemberIDType mid;
         poi->get_MemberID(&mid);
         CMember *mbr = m_pMembers->Find(mid);
         if (mbr==0)
         {
            // poi references a non-existent member
            ATLASSERT(false); // should not happen
            CComBSTR msg = CreateErrorMsg2(IDS_E_POI_REFERENCES_MEMBER_NOT_EXISTS, poiID, mid);
            THROW_MSG(msg, FEM2D_E_POI_REFERENCES_MEMBER_NOT_EXISTS, IDH_E_POI_REFERENCES_MEMBER_NOT_EXISTS);
         }

         Float64 ldx, ldy;
         ldx = poiResult->GetDeflection(0);
         ldy = poiResult->GetDeflection(1);

         // get orientation of member and rotate results into global coord's
         Float64 ang = mbr->m_JointKeeper.GetAngle();
         Float64 c = cos(ang);
         Float64 s = sin(ang);

         *Dx = ldx*c - ldy*s;
         *Dy = ldx*s + ldy*c;
         *Rz = poiResult->GetDeflection(2);
      }
      else
      {
         ATLASSERT(false); // new orientation type?
         return E_INVALIDARG;
      }
   }
   catch (...)
   {
      //  use standard exception handler to deal with these pesky's
      return DealWithExceptions();
   }

	return S_OK;
}

STDMETHODIMP CModel::ComputePOIForces(LoadCaseIDType lc, PoiIDType poiID, Fem2dMbrFaceType face, Fem2dLoadOrientation orientation, Float64 *Fx, Float64 *Fy, Float64 *Mz)
{
   CHECK_RETVAL(Fx);
   CHECK_RETVAL(Fy);
   CHECK_RETVAL(Mz);

   try
   {
      const PoiResult* poiResult = 0;

      // look in simple cache first
      if ( m_SimplePOIResultCache.IsHit(poiID, lc) )
      {
         poiResult = &(m_SimplePOIResultCache.poiResult);
      }
      else
      {
         CheckLoadOrientation(orientation);

         // compute any outdated member/joint results
         Compute();

         // first see if results have already been calculated
         PoiResultIterator jit( m_PoiResults.find(poiID) );
         if (jit != m_PoiResults.end())
         {
            PoiResultArray* array = jit->second;
            poiResult = array->Find(lc);
         }

         if (0 == poiResult)
         {
            // result not in store - we need to go out and calculate it
            poiResult = StorePoiResults(lc, poiID);
         }

         // should have thrown by here if problem
         if (poiResult==0)
         {
            ATLASSERT(0);
            THROW_MSG("Logic error computing poi result CModel::ComputePOIForces",E_FAIL,IDH_E_LOGIC_ERROR); 
         }
      }

      // at this point, we have a result - map it to our return values
      long offset;
      if (face == mftLeft)
         offset = 0;
      else
         offset = 3;

      if (orientation==lotMember)
      {
         // forces are stored in member local coord's
         *Fx = poiResult->GetForce(0+offset);
         *Fy = poiResult->GetForce(1+offset);
         *Mz = poiResult->GetForce(2+offset);
      }
      else if (orientation==lotGlobal || orientation==lotGlobalProjected)
      {
         // have to rotate forces into global coord's
         // get poi and member
         CPOI *poi = m_pPOIs->Find(poiID);
         if (poi==0)
         {
            ATLASSERT(false); // this should never happen
            CComBSTR msg = ::CreateErrorMsg1(IDS_E_POI_NOT_FOUND, poiID);
            THROW_MSG(msg, FEM2D_E_POI_NOT_FOUND, IDH_E_POI_NOT_FOUND);
         }
         MemberIDType mid;
         poi->get_MemberID(&mid);
         CMember *mbr = m_pMembers->Find(mid);
         if (mbr==0)
         {
            // poi references a non-existent member
            ATLASSERT(false); // should not happen
            CComBSTR msg = CreateErrorMsg2(IDS_E_POI_REFERENCES_MEMBER_NOT_EXISTS, poiID, mid);
            THROW_MSG(msg, FEM2D_E_POI_REFERENCES_MEMBER_NOT_EXISTS, IDH_E_POI_REFERENCES_MEMBER_NOT_EXISTS);
         }

         Float64 lfx, lfy;
         lfx = poiResult->GetForce(0+offset);
         lfy = poiResult->GetForce(1+offset);

         // get orientation of member and rotate results into global coord's
         Float64 ang = mbr->m_JointKeeper.GetAngle();
         Float64 c = cos(ang);
         Float64 s = sin(ang);

         *Fx = lfx*c - lfy*s;
         *Fy = lfx*s + lfy*c;
         *Mz = poiResult->GetForce(2+offset);
      }
      else
      {
         ATLASSERT(false); // new orientation we don't know about?
         return E_INVALIDARG;
      }
   }
   catch (...)
   {
      //  use standard exception handler to deal with these pesky's
      return DealWithExceptions();
   }


	return S_OK;
}

// IFem2dModelResultsForScriptingClients

STDMETHODIMP CModel::ComputePOIForces(/*[in]*/LoadCaseIDType loadingID, /*[in]*/PoiIDType poiID, /*[in]*/Fem2dMbrFaceType face, /*[in]*/Fem2dLoadOrientation orientation, /*[in]*/ Fem2dJointDOF dof,/*[out,retval]*/Float64* pVal)
{
   CHECK_RETVAL(pVal);

   Float64 dfx, dfy, dmz;
   HRESULT hr = ComputePOIForces(loadingID, poiID, face, orientation, &dfx, &dfy, &dmz);
   if (SUCCEEDED(hr))
   {
      switch(dof)
      {
      case jdofDx:
         *pVal = dfx;
         break;

      case jdofDy:
         *pVal = dfy;
         break;

      case jdofRz:
         *pVal = dmz;
         break;

      default:
         return E_INVALIDARG;
      }
   }

   return hr;
}

STDMETHODIMP CModel::ComputeMemberForces(/*[in]*/LoadCaseIDType loadingID, /*[in]*/MemberIDType memberID, /*[in]*/ Fem2dMbrDOF dof,/*[out,retval]*/Float64* pVal)
{
   CHECK_RETVAL(pVal);

   Float64 dsfx, dsfy, dsmz, defx, defy, demz;
   HRESULT hr = ComputeMemberForces(loadingID, memberID, &dsfx, &dsfy, &dsmz, &defx, &defy, &demz);
   if (SUCCEEDED(hr))
   {
      switch(dof)
      {
      case mdofDxStart:
         *pVal = dsfx;
         break;

      case mdofDyStart:
         *pVal = dsfy;
         break;

      case mdofRzStart:
         *pVal = dsmz;
         break;

      case mdofDxEnd:
         *pVal = defx;
         break;

      case mdofDyEnd:
         *pVal = defy;
         break;

      case mdofRzEnd:
         *pVal = demz;
         break;

      default:
         return E_INVALIDARG;
      }
   }

   return hr;

}

STDMETHODIMP CModel::ComputeReactions(/*[in]*/LoadCaseIDType loadingID, /*[in]*/JointIDType jointID, /*[in]*/ Fem2dJointDOF dof,/*[out,retval]*/Float64* pVal)
{
   CHECK_RETVAL(pVal);

   Float64 dfx, dfy, dmz;
   HRESULT hr = ComputeReactions(loadingID, jointID, &dfx, &dfy, &dmz);
   if (SUCCEEDED(hr))
   {
      switch(dof)
      {
      case jdofDx:
         *pVal = dfx;
         break;

      case jdofDy:
         *pVal = dfy;
         break;

      case jdofRz:
         *pVal = dmz;
         break;

      default:
         return E_INVALIDARG;
      }
   }

   return hr;
}

STDMETHODIMP CModel::ComputePOIDeflections(/*[in]*/LoadCaseIDType loadingID, /*[in]*/PoiIDType poiID, /*[in]*/Fem2dLoadOrientation orientation, /*[in]*/ Fem2dJointDOF dof,/*[out,retval]*/Float64* pVal)
{
   CHECK_RETVAL(pVal);
   Float64 ddx, ddy, drz;
   HRESULT hr = ComputePOIDeflections(loadingID, poiID, orientation, &ddx, &ddy, &drz);
   if (SUCCEEDED(hr))
   {
      switch(dof)
      {
      case jdofDx:
         *pVal = ddx;
         break;

      case jdofDy:
         *pVal = ddy;
         break;

      case jdofRz:
         *pVal = drz;
         break;

      default:
         return E_INVALIDARG;
      }
   }

   return hr;
}

STDMETHODIMP CModel::ComputeMemberDeflections(/*[in]*/LoadCaseIDType loadingID, /*[in]*/MemberIDType memberID, /*[in]*/ Fem2dMbrDOF dof,/*[out,retval]*/Float64* pVal)
{
   CHECK_RETVAL(pVal);

   Float64 dsdx, dsdy, dsrz, dedx, dedy, derz;
   HRESULT hr = ComputeMemberDeflections(loadingID, memberID, &dsdx, &dsdy, &dsrz, &dedx, &dedy, &derz);
   if (SUCCEEDED(hr))
   {
      switch(dof)
      {
      case mdofDxStart:
         *pVal = dsdx;
         break;

      case mdofDyStart:
         *pVal = dsdy;
         break;

      case mdofRzStart:
         *pVal = dsrz;
         break;

      case mdofDxEnd:
         *pVal = dedx;
         break;

      case mdofDyEnd:
         *pVal = dedy;
         break;

      case mdofRzEnd:
         *pVal = derz;
         break;

      default:
         return E_INVALIDARG;
      }
   }

   return hr;
}

STDMETHODIMP CModel::ComputeJointDeflections(/*[in]*/LoadCaseIDType loadingID, /*[in]*/JointIDType jointID, /*[in]*/ Fem2dJointDOF dof,/*[out,retval]*/Float64* pVal)
{
   CHECK_RETVAL(pVal);

   Float64 ddx, ddy, drz;
   HRESULT hr = ComputeJointDeflections(loadingID, jointID, &ddx, &ddy, &drz);
   if (SUCCEEDED(hr))
   {
      switch(dof)
      {
      case jdofDx:
         *pVal = ddx;
         break;

      case jdofDy:
         *pVal = ddy;
         break;

      case jdofRz:
         *pVal = drz;
         break;

      default:
         return E_INVALIDARG;
      }
   }

   return hr;
}

CJointCollection* CModel::GetJoints()
{
   return m_pJoints;
}

CMemberCollection* CModel::GetMembers()
{
   return m_pMembers;
}

STDMETHODIMP CModel::get_Results(/*[out, retval]*/ IFem2dModelResultsForScriptingClients* *pVal)
{
   return this->QueryInterface(IID_IFem2dModelResultsForScriptingClients,(void**)pVal);
}

STDMETHODIMP CModel::get_StructuredStorage(/*[out, retval]*/ IStructuredStorage2* *pVal)
{
   return this->QueryInterface(IID_IStructuredStorage2,(void**)pVal);
}


////////////////////////////////////////////////////////////////////////////////
/////////// Change Management Related Functions ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void CModel::OnJointChanged(IFem2dJoint*)
{
   m_ModelDirty = true;
   Fire_OnModelChanged();
}

void CModel::OnJointAdded(JointIDType)
{
   m_ModelDirty = true;
   Fire_OnModelChanged();
}

void CModel::OnJointRemoved(JointIDType)
{
   m_ModelDirty = true;
   Fire_OnModelChanged();
}

void CModel::OnJointsCleared()
{
   m_ModelDirty = true;
   Fire_OnModelChanged();
}

void CModel::OnMemberChanged(IFem2dMember*)
{
   m_ModelDirty = true;
   Fire_OnModelChanged();
}

void CModel::OnMemberAdded(MemberIDType)
{
   m_ModelDirty = true;
   Fire_OnModelChanged();
}

void CModel::OnMemberRemoved(MemberIDType )
{
   m_ModelDirty = true;
   Fire_OnModelChanged();
}

void CModel::OnMembersCleared( )
{
   m_ModelDirty = true;
   Fire_OnModelChanged();
}

void CModel::OnJointLoadChanged(IFem2dJointLoad*, LoadCaseIDType loadingID)
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnJointLoadAdded(LoadIDType loadID, LoadCaseIDType loadingID)
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnJointLoadRemoved(LoadIDType loadID, LoadCaseIDType loadingID )
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnJointLoadsCleared(LoadCaseIDType loadingID )
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnJointDeflectionChanged(IFem2dJointDeflection*, LoadCaseIDType loadingID)
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnJointDeflectionAdded(LoadIDType loadID, LoadCaseIDType loadingID)
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnJointDeflectionRemoved(LoadIDType loadID, LoadCaseIDType loadingID )
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnJointDeflectionsCleared(LoadCaseIDType loadingID )
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnPointLoadChanged(IFem2dPointLoad*, LoadCaseIDType loadingID)
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnPointLoadAdded(LoadIDType loadID, LoadCaseIDType loadingID)
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnPointLoadRemoved(LoadIDType loadID, LoadCaseIDType loadingID )
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnPointLoadsCleared(LoadCaseIDType loadingID )
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnDistributedLoadChanged(IFem2dDistributedLoad*, LoadCaseIDType loadingID)
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnDistributedLoadAdded(LoadIDType loadID, LoadCaseIDType loadingID)
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnDistributedLoadRemoved(LoadIDType loadID, LoadCaseIDType loadingID )
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnDistributedLoadsCleared(LoadCaseIDType loadingID )
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnMemberStrainChanged(IFem2dMemberStrain*, LoadCaseIDType loadingID)
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnMemberStrainAdded(LoadIDType loadID, LoadCaseIDType loadingID)
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnMemberStrainRemoved(LoadIDType loadID, LoadCaseIDType loadingID )
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnMemberStrainsCleared(LoadCaseIDType loadingID )
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnLoadingAdded(LoadCaseIDType loadingID)
{
   m_DirtyLoadings.insert(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnLoadingRemoved(LoadCaseIDType loadingID )
{
   m_DirtyLoadings.erase(loadingID);
   RemoveResults(loadingID);
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnLoadingsCleared()
{
   m_DirtyLoadings.clear();
   RemoveAllResults();
   Fire_OnModelChanged();
}

void CModel::OnPOIChanged(IFem2dPOI* pp)
{
   PoiIDType id;
   pp->get_ID(&id);
   RemovePoiResults(id);
}

void CModel::OnPOIAdded(PoiIDType id)
{
   // new pois take care of themselves
}

void CModel::OnPOIRemoved(PoiIDType id)
{
   RemovePoiResults(id);
}

void CModel::OnPOIsCleared()
{
   RemoveAllPoiResults();
}

////////////////////////////////////////////////////////////////////////////////
/////////// FEM Analysis Related Functions /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// FreeFGlobal
//
// Frees the memory allocation for the global force vector
void CModel::FreeFGlobal()
{
   if (m_pF != NULL)
      delete[] m_pF;
   m_pF = NULL;

#if defined _DEBUG
   if (m_pForig != NULL)
      delete[] m_pForig;
   m_pForig = NULL;
#endif
}

void CModel::AllocateKGlobal()
{
   // size K matrices and zero them out
   m_K.Resize(m_NumCondensedDOF,m_BandWidth);
   m_K.Zero();

#if defined _DEBUG
   m_Korig.Resize(m_NumCondensedDOF,m_BandWidth);
   m_Korig.Zero();
#endif
}


// AllocateFGlobal
//
// Allocates memory for the global force vector. All entries are
// initialized to 0.0
void CModel::AllocateFGlobal()
{
   ATLASSERT(m_NumCondensedDOF >= 0); //"CModel::AllocateFGlobal() : NumCondensedDOF < 0");

   long i;

   // only need to allocate first time through. changes to model should be handled by
   // ClearAnalysis which frees fglobal

   if (m_pF==0)
      m_pF = new Float64[m_NumCondensedDOF];

   // initialize the vector
   for (i = 0; i < m_NumCondensedDOF; i++)
      m_pF[i] = 0.0;

#if defined _DEBUG
   if (m_pForig==0)
      m_pForig = new Float64[m_NumCondensedDOF];

   // initialize the vector
   for (i = 0; i < m_NumCondensedDOF; i++)
      m_pForig[i] = 0.0;
#endif
}

// ComputeBandWidth
//
// Computes the semi-bandwidth of the structure.
// The semi-band with it the maximum difference between global dof's on
// a single element + 1.
//
// This function could be improved by allowing CModel to re-order or
// re-index the joints to produce a smaller bandwidth. A smaller bandwidth
// would reduce memory requirements and allow for faster solutions.
LONG CModel::ComputeBandWidth()
{
   LONG bw = 1;
   LONG j,k;
   LONG dof1, dof2;

   MemberIterator i( m_pMembers->begin() );
   MemberIterator iend( m_pMembers->end() );
   while(i != iend)
   {
      LONG nDOF;
      CMember* mbr = *(i++);

      nDOF = mbr->GetNumDOF();
      for (j = 0; j < nDOF; j++)
      {
         for (k = 0; k < nDOF; k++)
         {
            dof1 = mbr->GetCondensedDOF(j);
            dof2 = mbr->GetCondensedDOF(k);
            if (dof1 >= 0 && dof2 >= 0)
               bw = _cpp_max(bw,(LONG)(_abs64(dof1-dof2) + 1));
         }
      }
   }

   return bw;
}

// Compute
// Main computational loop
void CModel::Compute()
{
   if (m_ModelDirty)
   {
      // do some simple error checking on model
      CheckModel();

      // something changed to change the stiffness
      StiffnessAnalysis();

      // need to recalculate all loadings
      m_DirtyLoadings.clear();

      LoadingIterator ldIter( m_pLoadings->begin() );
      LoadingIterator ldIterEnd( m_pLoadings->end() );
      while(ldIter != ldIterEnd)
      {
         LoadCaseIDType id;
         ldIter->get_ID(&id);
         m_DirtyLoadings.insert(id);
         ++ldIter;
      }

      // model is calculated up to date
      m_ModelDirty = false;
   }

   // stiffness is factored - calculate results for loadings
   ComputeLoadings();

}

// CheckModel
// checks model for any obvious problems
void CModel::CheckModel()
{
   // must have at least two joints to have a model
   CollectionIndexType count;
   m_pJoints->get_Count(&count);
   if (count < 2)
      THROW_IDS(IDS_E_MODEL_HAS_NO_JOINTS, FEM2D_E_MODEL_HAS_NO_JOINTS, IDH_E_MODEL_HAS_NO_JOINTS);


   // must have at least one member
   m_pMembers->get_Count(&count);
   if (count < 1)
      THROW_IDS(IDS_E_MODEL_HAS_NO_MEMBERS, FEM2D_E_MODEL_HAS_NO_MEMBERS, IDH_E_MODEL_HAS_NO_MEMBERS);
}

// StiffnessAnalysis
//
// Performs a stiffness analysis.
void CModel::StiffnessAnalysis()
{
   ClearAnalysis();
   InitModel();

   if (0 < m_NumCondensedDOF)
      FemAnalysis();
}

void CModel::FemAnalysis()
{
   m_BandWidth = ComputeBandWidth();

   AssembleGlobalStiffnessMatrix();

#if defined ENABLE_LOGGING
   logfile << "Condensed Global Stiffness Matrix: Size =" << m_K.NumRows()<<"  Bandwidth = "<<m_K.BandWidth() << std::endl;
   logfile << m_K << std::endl;
#endif

   // Triangularize Global Stiffness Matrix
   try
   {
      m_K.Factor();
   }
   catch(SymBandedMatrix::SymBandedSolverException& e)
   {
      LONG dof = e.m_OffendingDof;
      JointIDType joint;
      LONG jdof;
      GetJointFromDof(dof, &joint, &jdof);
      CComBSTR msg = CreateErrorMsg2(IDS_E_MATRIX_FACTORING, joint, jdof+1);
      THROW_MSG(msg, FEM2D_E_MATRIX_FACTORING, IDH_E_MATRIX_FACTORING);
   }
   catch(...)
   {
      ATLASSERT(false); // something getting thrown that shouldn't be
      throw;
   }

#if defined ENABLE_LOGGING
   logfile <<std::endl<<"Factored Condensed Global Stiffness Matrix: Size =" << m_K.NumRows()<<"  Bandwidth = "<<m_K.BandWidth() << std::endl;
   logfile << m_K << std::endl;
#endif

}


void CModel::ComputeLoadings()
{
   DirtyLoadingsIterator ldIter( m_DirtyLoadings.begin() );
   DirtyLoadingsIterator ldIterEnd( m_DirtyLoadings.end() );
   while(ldIter != ldIterEnd)
   {
      ClearLoads(); // clear any previously applied loadings

      LoadCaseIDType lid = *(ldIter++);
      CLoading *loading = m_pLoadings->Find(lid);
      ATLASSERT(loading!=0);

      loading->ApplyLoads(this);

      if (m_NumCondensedDOF > 0)
      {
         AssembleGlobalForceVector();

#if defined ENABLE_LOGGING
         logfile << "Global Force Vector: Loading =" << lid << std::endl;
         for (LONG fi=0; fi<m_NumCondensedDOF; fi++)
            logfile << m_pF[fi] << std::endl;
#endif
         try
         {
            m_K.Solve(m_pF);
         }
         catch(SymBandedMatrix::SymBandedSolverException& e)
         {
            LONG dof = e.m_OffendingDof;
            JointIDType joint;
            LONG jdof;
            GetJointFromDof(dof, &joint, &jdof);
            CComBSTR msg = CreateErrorMsg2(IDS_E_MATRIX_BACK_SUBSTITUTION, joint, jdof+1);
            THROW_MSG(msg, FEM2D_E_MATRIX_BACK_SUBSTITUTION, IDH_E_MATRIX_BACK_SUBSTITUTION);
         }
         catch(...)
         {
            ATLASSERT(false); // something getting thrown that shouldn't be
            throw;
         }
#if defined ENABLE_LOGGING
         logfile << "Solution: Loading =" << lid << std::endl;
         for (LONG fi=0; fi<m_NumCondensedDOF; fi++)
            logfile << m_pF[fi] << std::endl;
#endif


#if defined _DEBUG
         CheckSolution();
#endif
         ApplyJntDeflections();
      }
      else
      {
         SolveDeflectionsClassical();
      }

      try
      {
      ComputeMemberResults();
      ComputeReactions();
      CheckEquilibrium();
      StoreJntResults(lid);
      StoreMbrResults(lid);
      }
#if defined _DEBUG
      catch(CComException& /*e*/)
      {
         throw;
      }
#endif
      catch(...)
      {
         throw;
      }
   }

   // loadings are all up to date
   m_DirtyLoadings.clear();
}


// AssembleGlobalForceVector
//
// Assembles the global force vector.
void CModel::AssembleGlobalForceVector()
{
   AllocateFGlobal();

   AssembleJointLoads();
   AssembleElementLoads();
}

// AssembleJointLoads
//
// Assemble joint loads into the global force vector
void CModel::AssembleJointLoads()
{
   Float64 f[CJoint::NumDof];
   LONG ndof = CJoint::NumDof;

   JointIterator j( m_pJoints->begin() );
   JointIterator jend( m_pJoints->end() );

   while(j != jend)
   {
      CJoint *jnt = *(j++);

      jnt->GetFglobal(f);

      for (LONG i = 0; i < ndof; i++)
      {
         LONG dof;
         dof = jnt->GetCondensedDOF(i);
         if (dof >= 0)
         {
            m_pF[dof] += f[i];

#if defined _DEBUG
            m_pForig[dof] += f[i];
#endif

         }
      }
   }
}

// AssembleElementLoads
//
// Assembles element loads into the global force vector.
void CModel::AssembleElementLoads()
{
   Float64 f[MAX_ELEMENT_DOF];

   MemberIterator e( m_pMembers->begin() );
   MemberIterator eend( m_pMembers->end() );

   while(e != eend)
   {
      CMember *mbr = *(e++);
      LONG ndof = mbr->GetNumDOF();

      ATLASSERT(ndof<=MAX_ELEMENT_DOF); // added a new element type?

      // Each element has to assemble its force vector in global coordinates
      // before it can be integrated into the global force vector.
      mbr->AssembleF();

      LONG dof, cdof;
      mbr->GetFglobal(f);
      for (dof = 0; dof < ndof; dof++)
      {
         cdof = mbr->GetCondensedDOF(dof);
         if (cdof >= 0)
         {
            m_pF[cdof] += f[dof];
#if defined _DEBUG
            m_pForig[cdof] += f[dof];
#endif
         }
      }
   }
}

// AssembleGlobalStiffnessMatrix
//
// Assembles the global stiffness matrix by adding the stiffness
// contribution of each enabled element in the model.
void CModel::AssembleGlobalStiffnessMatrix()
{
   AllocateKGlobal();

   MemberIterator iter( m_pMembers->begin() );
   MemberIterator iterend( m_pMembers->end() );

   while(iter != iterend)
   {
      LONG i,j;
      LONG dof;
      CMember *mbr = *(iter++);

      dof = mbr->GetNumDOF();

      for (i = 0; i < dof; i++)
      {
         for (j = 0; j < dof; j++)
         {
            LONG CDOFi,CDOFj;
            LONG I,J;
            Float64 k;

            CDOFi = mbr->GetCondensedDOF(i);
            CDOFj = mbr->GetCondensedDOF(j);

            if (CDOFi >= 0 && CDOFj >= 0)
            {
               I = CDOFi;
               J = CDOFj;

               if (J >= I) // only map symmetrical values (upper triangle)
               {
                  k = mbr->GetKglobal(i,j);
                  m_K.SumVal(I, J, k);
#if defined _DEBUG
                  m_Korig.SumVal(I,J, k);
#endif
               }
            }
         }  // End j loop
      } // End i loop
   } // End of while
}

void CModel::InitModel()
{
   // Initialize joints by assigning global and condensed dof numbers
   m_NumCondensedDOF = 0;
   m_NumGlobalDOF    = 0;

   JointIterator j( m_pJoints->begin() );
   JointIterator jend( m_pJoints->end() );
   while(j!=jend)
   {
      LONG nGDOFused,nCDOFused;
      CJoint *jnt = *(j++);
      jnt->InitModel(m_NumGlobalDOF,m_NumCondensedDOF,nGDOFused,nCDOFused);
      m_NumGlobalDOF    += nGDOFused;
      m_NumCondensedDOF += nCDOFused;
   }

   // Allow all the elements a chance to initialize themselves
   MemberIterator m( m_pMembers->begin() );
   MemberIterator mend( m_pMembers->end() );
   while(m != mend)
   {
      CMember *mbr = *(m++);
      mbr->InitModel();
   }
}

void CModel::ClearLoads()
{
   JointIterator i( m_pJoints->begin() );
   JointIterator iend( m_pJoints->end() );
   while(i != iend)
   {
      CJoint *jnt = *(i++);
      jnt->ClearLoads();
   }

   MemberIterator j( m_pMembers->begin() );
   MemberIterator jend( m_pMembers->end() );
   while(j != jend)
   {
      CMember *mbr = *(j++);
      mbr->ClearLoads();
   }
}

// ApplyJntDeflections
//
// Applies the global joint Deflections to the structure
void CModel::ApplyJntDeflections()
{
   Float64 disp[CJoint::NumDof];
   LONG ndof = CJoint::NumDof;

   JointIterator j( m_pJoints->begin() );
   JointIterator jend( m_pJoints->end() );
   while(j != jend)
   {
      LONG cdof, dof;
      CJoint *jnt = *(j++);

      for (dof = 0; dof < ndof; dof++)
      {
         cdof = jnt->GetCondensedDOF(dof);
         disp[dof] = (cdof < 0) ? 0.0 : m_pF[cdof];
      }

      // Apply the Deflection to the joint for use in further
      // results processing.
      //
      // This implies a shorting coming in TJoint
      jnt->SetDeflection(disp);

   }
}

void CModel::ComputeMemberResults()
{
   MemberIterator i( m_pMembers->begin() );
   MemberIterator iend( m_pMembers->end() );
   while(i != iend)
   {
      CMember *mbr = *(i++);
      mbr->ComputeResults();
   }
}

void CModel::ComputeReactions()
{
   JointIterator j( m_pJoints->begin() );
   JointIterator jend( m_pJoints->end() );

   while (j != jend)
   {
      CJoint *jnt = *(j++);
      jnt->ComputeReactions();
   }
}

// SolveDeflectionsClassical
//
// Solves global Deflections using classical Roark beam formulas.
void CModel::SolveDeflectionsClassical()
{
   // Since all global dof's are constrained, all global Deflections
   // are zero. This function simply assigns 0.0 to all joint Deflections.
   // Individual elements shall modify member end Deflections based upon
   // member end boundary conditions

   JointIterator j( m_pJoints->begin() );
   JointIterator jend( m_pJoints->end() );

   const Float64 disp[3]={0,0,0};

   while(j != jend)
   {
      CJoint *jnt = *(j++);
      jnt->SetDeflection(disp);
   }
}

void CModel::CheckEquilibrium()
{

   Float64 tol = GetEquilibriumCheckTolerance();

   JointIterator j( m_pJoints->begin() );
   JointIterator jend( m_pJoints->end() );
   while(j != jend)
   {
      CJoint *jnt = *(j++);
      if (!jnt->IsEquilibriumSatisfied(tol))
      {
         JointIDType id;
         jnt->get_ID(&id);
         CComBSTR msg = CreateErrorMsg1(IDS_E_JOINT_EQUILIBRIUM_NOT_SATISFIED, id);
         ATLASSERT(false);
         THROW_MSG(msg, FEM2D_E_JOINT_EQUILIBRIUM_NOT_SATISFIED, IDH_E_JOINT_EQUILIBRIUM_NOT_SATISFIED);
      }
   }

   MemberIterator i( m_pMembers->begin() );
   MemberIterator iend( m_pMembers->end() );
   while(i != iend )
   {
      CMember *ele = *(i++);
      if (!ele->IsEquilibriumSatisfied(tol))
      {
         MemberIDType id;
         ele->get_ID(&id);
         CComBSTR msg = CreateErrorMsg1(IDS_E_MEMBER_EQUILIBRIUM_NOT_SATISFIED, id);
         ATLASSERT(false);
         THROW_MSG(msg, FEM2D_E_MEMBER_EQUILIBRIUM_NOT_SATISFIED, IDH_E_MEMBER_EQUILIBRIUM_NOT_SATISFIED);
      }
   }
}

#if defined _DEBUG

void CModel::CheckSolution()
{
   Float64 tol = GetEquilibriumCheckTolerance();
   Float64  error;
   long l,m;

   for (l = 0; l < m_NumCondensedDOF; l++)
   {
      error = 0.;
      for (m = 0; m < m_NumCondensedDOF; m++)
      {
         error += m_Korig(l,m) * m_pF[m];
      }
      error -= m_pForig[l];

      if (!IsZero(error,tol))
      {
         // something's not right here
         CComBSTR msg = CreateErrorMsg1(IDS_E_SOLVING_GLOBAL_STIFFNESS, l);
         ATLASSERT(false);
         THROW_MSG(msg, FEM2D_E_SOLVING_GLOBAL_STIFFNESS, IDH_E_SOLVING_GLOBAL_STIFFNESS);
      }
   }
}

#endif

//////////// Results storeage and retrieval

void CModel::StoreJntResults(LoadCaseIDType lcase)
{
   Float64 force[3];
   Float64 disp[3];

#if defined ENABLE_LOGGING
   logfile << "Loading " << lcase << std::endl;
#endif

   JointIterator j( m_pJoints->begin() );
   JointIterator jend( m_pJoints->end() );
   while(j != jend)
   {
      CJoint *jnt = *(j++);

      jnt->GetReactions(force);
      jnt->GetDeflection(disp);

      JointIDType id;
      jnt->get_ID(&id);

#if defined ENABLE_LOGGING
      logfile << "Joint " << id << std::endl;
      logfile << "Fx = " << force[0] << " Fy = " << force[1] << " Mz = " << force[2] << std::endl;
      logfile << "Dx = " <<  disp[0] << " Dy = " <<  disp[1] << " Dz = " <<  disp[2] << std::endl;
#endif

      JntResultArray* array;
      JntResultIterator ir( m_JntResults.find(id) );
      if (ir != m_JntResults.end())
      {
         array = ir->second;
      }
      else
      {
         array = new JntResultArray(id);
         m_JntResults.insert(JntResultContainer::value_type(id, array));
      }

      JntResult* pres = array->Find(lcase);
      if (pres!=0)
      {
         pres->SetActions(force,disp);
      }
      else
      {
         JntResult result(lcase,force,disp);
         array->Add(result);
      }
   }
}

void CModel::StoreMbrResults(LoadCaseIDType lcase)
{

#if defined ENABLE_LOGGING
   logfile << "StoreMbrResults::Loading = " << lcase << std::endl;
#endif

   MemberIterator i( m_pMembers->begin() );
   MemberIterator iend( m_pMembers->end() );
   while(i != iend)
   {
      CMember *mbr = *(i++);
      MemberIDType mid;
      mbr->get_ID(&mid);

      MbrResultIterator rit( m_MbrResults.find(mid) );
      CMember::MbrResultArray* array = (rit == m_MbrResults.end()) ? 0 : rit->second;
      if (!array)
      {
         array = new CMember::MbrResultArray(mid);
         m_MbrResults.insert(MbrResultContainer::value_type(mid,array));
      }

      CMember::MbrResult result(lcase);
      mbr->GetResults(&result);

#if defined ENABLE_LOGGING
      logfile << "Member " << mid << " Start End" << std::endl;
      logfile << "Fx = " << result.GetForce(0) << " Fy = " << result.GetForce(1) << " Mz = " << result.GetForce(2) << std::endl;
      logfile << "Dx = " <<  result.GetDeflection(0) << " Dy = " <<  result.GetDeflection(1) << " Dz = " <<  result.GetDeflection(2) << std::endl;

      logfile << "Member " << mid << " End End" << std::endl;
      logfile << "Fx = " << result.GetForce(3) << " Fy = " << result.GetForce(4) << " Mz = " << result.GetForce(5) << std::endl;
      logfile << "Dx = " <<  result.GetDeflection(3) << " Dy = " <<  result.GetDeflection(4) << " Dz = " <<  result.GetDeflection(5) << std::endl;
#endif
      CMember::MbrResult* pres = array->Find(lcase);
      if (pres!=0)
      {
         *pres = result;
      }
      else
      {
         array->Add(result);
      }
   }
}

// This function was very innefficent, but may be useful for later schemes
/*
void CModel::StorePoiResults(LoadCaseIDType lcase)
{
#if defined ENABLE_LOGGING
   logfile << "StorePoiResults::Loading = " << lcase << std::endl;
#endif

   // Don't store results for load cases with negative values. These are load cases that probably
   // only will be used once (e.g., influence line loads)
   if (lcase < 0)
      return;

   // loop over all pois and calc and store results
   POIIterator i (m_pPOIs->begin() );
   POIIterator iend (m_pPOIs->end() );
   while(i != iend)
   {
      // get poi and member
      CPOI *poi = *(i++);

      PoiIDType poiid;
      poi->get_ID(&poiid);

      MemberIDType mid;
      poi->get_MemberID(&mid);
      CMember *mbr = m_pMembers->Find(mid);
      if (mbr==0)
      {
         // poi references a non-existent member
         CComBSTR msg = CreateErrorMsg2(IDS_E_POI_REFERENCES_MEMBER_NOT_EXISTS, poiid, mid);
         THROW_MSG(msg, FEM2D_E_POI_REFERENCES_MEMBER_NOT_EXISTS, IDH_E_POI_REFERENCES_MEMBER_NOT_EXISTS);
      }

      // poi location
      Float64 pl, poiloc;
      poi->get_Location(&pl); // in input coord's
      poiloc = mbr->GetRealLocation(pl);
      if (poiloc==-1.0)
      {
         // poi is located in lala land
         if (pl<0.0)
         {
            CComBSTR msg = CreateErrorMsg1(IDS_E_POI_FRACTIONAL_OUT_OF_RANGE, poiid);
            THROW_MSG(msg, FEM2D_E_POI_FRACTIONAL_OUT_OF_RANGE, IDH_E_POI_FRACTIONAL_OUT_OF_RANGE);
         }
         else
         {
            CComBSTR msg = CreateErrorMsg2(IDS_E_POI_LOCATED_OFF_MEMBER_END, poiid, mid);
            THROW_MSG(msg, FEM2D_E_POI_LOCATED_OFF_MEMBER_END, IDH_E_POI_LOCATED_OFF_MEMBER_END);
         }
      }

      // next pull results from element
      Float64 force[6];
      Float64 disp[3];
      mbr->GetInternalForces(poiloc, mftLeft, force);
      mbr->GetInternalForces(poiloc, mftRight, &force[3]);
      // reverse sign of forces to comply to sign conventions
      for (long i=0; i<6; i++)
         force[i] = -1.0 * force[i];

      mbr->GetDeflection(poiloc,disp);

#if defined ENABLE_LOGGING
      logfile << "poi " << poiid << " Left Face" << std::endl;
      logfile << "Fx = " << force[0] << " Fy = " << force[1] << " Mz = " << force[2] << std::endl;
      logfile << "poi " << poiid << " Right Face" << std::endl;
      logfile << "Fx = " << force[3] << " Fy = " << force[4] << " Mz = " << force[5] << std::endl;
      logfile << "Dx = " << disp[0] << " Dy = " << disp[1] << " Rz = " << disp[2] << std::endl;
#endif

      PoiResult result(lcase,force,disp);

      PoiResultIterator rit( m_PoiResults.find(poiid) );
      PoiResultArray* parray = (rit == m_PoiResults.end()) ? 0 : rit->second;
      if (!parray)
      {
         parray = new PoiResultArray(poiid);
         m_PoiResults.insert(PoiResultContainer::value_type(poiid,parray));
      }

      PoiResult* pres = parray->Find(lcase);
      if (pres!=0)
      {
         *pres = result;
      }
      else
      {
         parray->Add(result);
      }
   }
}
*/

const CModel::PoiResult* CModel::StorePoiResults(LoadCaseIDType lcase, PoiIDType poiid)
{
   // Simple, fast caching scheme for negative load case values. Found that LBAM functions for getting influence lines
   // and functions to compute points of inflection made multiple sequential calls for same results, then no need to cache long term
   if ( m_SimplePOIResultCache.IsHit(poiid, lcase) )
   {
      ATLASSERT(0); // outer code should prevent hits here
      return &(m_SimplePOIResultCache.poiResult);
   }

   // get poi and member
   CPOI *poi = m_pPOIs->Find(poiid);
   if (poi==0)
   {
      CComBSTR msg = ::CreateErrorMsg1(IDS_E_POI_NOT_FOUND, poiid);
      THROW_MSG(msg, FEM2D_E_POI_NOT_FOUND, IDH_E_POI_NOT_FOUND);
   }

   MemberIDType mid;
   poi->get_MemberID(&mid);
   CMember *mbr = m_pMembers->Find(mid);
   if (mbr==0)
   {
      // poi references a non-existent member
      CComBSTR msg = CreateErrorMsg2(IDS_E_POI_REFERENCES_MEMBER_NOT_EXISTS, poiid, mid);
      THROW_MSG(msg, FEM2D_E_POI_REFERENCES_MEMBER_NOT_EXISTS, IDH_E_POI_REFERENCES_MEMBER_NOT_EXISTS);
   }

   // next step is to restore element state where is was fresh after solution for this load case
   // need to get loading
   CLoading *loading = m_pLoadings->Find(lcase);
   if (loading==0)
   {
      // references a non-existent loading
      CComBSTR msg = CreateErrorMsg1(IDS_E_LOADING_NOT_FOUND, lcase);
      THROW_MSG(msg, FEM2D_E_LOADING_NOT_FOUND, IDH_E_LOADING_NOT_FOUND);
   }

   // next raw member results for this loading
   MbrResultIterator mrit( m_MbrResults.find(mid) );
   if (mrit == m_MbrResults.end())
   {
      CComBSTR msg = ::CreateErrorMsg1(IDS_E_MEMBER_NOT_FOUND, mid);
      THROW_MSG(msg, FEM2D_E_MEMBER_NOT_FOUND, IDH_E_MEMBER_NOT_FOUND);
   }
   CMember::MbrResultArray* array = mrit->second;

   const CMember::MbrResult* mbrResult = array->Find(lcase);
   if (0 == mbrResult)
   {
      CComBSTR msg = ::CreateErrorMsg1(IDS_E_LOADING_NOT_FOUND, lcase);
      THROW_MSG(msg, FEM2D_E_LOADING_NOT_FOUND,IDH_E_LOADING_NOT_FOUND);
   }

   // poi location
   Float64 pl, poiloc;
   poi->get_Location(&pl); // in input coord's
   poiloc = mbr->GetRealLocation(pl);
   if (poiloc==-1.0)
   {
      // poi is located in lala land
      if (pl<0.0)
      {
         CComBSTR msg = CreateErrorMsg1(IDS_E_POI_FRACTIONAL_OUT_OF_RANGE, poiid);
         THROW_MSG(msg, FEM2D_E_POI_FRACTIONAL_OUT_OF_RANGE, IDH_E_POI_FRACTIONAL_OUT_OF_RANGE);
      }
      else
      {
         CComBSTR msg = CreateErrorMsg2(IDS_E_POI_LOCATED_OFF_MEMBER_END, poiid, mid);
         THROW_MSG(msg, FEM2D_E_POI_LOCATED_OFF_MEMBER_END, IDH_E_POI_LOCATED_OFF_MEMBER_END);
      }
   }

   // now we have all of the stuff we need to restore element state
   mbr->ClearLoads();
   loading->ApplyLoads(mbr);
   mbr->SetResults(*mbrResult);

   // next pull results from element
   Float64 force[6];
   Float64 disp[6];
   mbr->GetInternalForces(poiloc, mftLeft, force);
   mbr->GetInternalForces(poiloc, mftRight, &force[3]);

   // reverse sign of forces to comply to sign conventions
   for (long i=0; i<6; i++)
      force[i] = -1.0 * force[i];


#if defined ENABLE_LOGGING
   logfile << "poi " << poiid << " Left Face" << std::endl;
   logfile << "Fx = " << force[0] << " Fy = " << force[1] << " Mz = " << force[2] << std::endl;
   logfile << "poi " << poiid << " Right Face" << std::endl;
   logfile << "Fx = " << force[3] << " Fy = " << force[4] << " Mz = " << force[5] << std::endl;
#endif

   mbr->GetDeflection(poiloc,disp);
   PoiResult result(lcase,force,disp);

   if (lcase > 0)
   {
      // Positive load cases get long term caching

      PoiResultIterator rit( m_PoiResults.find(poiid) );
      PoiResultArray* parray = (rit == m_PoiResults.end()) ? 0 : rit->second;
      if (!parray)
      {
         parray = new PoiResultArray(poiid);
         m_PoiResults.insert(PoiResultContainer::value_type(poiid,parray));
      }
      
      const PoiResult* cpres;
      PoiResult* pres = parray->Find(lcase);
      if (pres!=0)
      {
         *pres = result;
         cpres = pres;
      }
      else
      {
         cpres = parray->Add(result);
      }

      return cpres;
   }
   else
   {
      // Negative Load cases go in simple cache to avoid container overhead
      m_SimplePOIResultCache.Update(poiid, lcase, result);
      return &(m_SimplePOIResultCache.poiResult);
   }
}

void CModel::RemoveAllResults()
{
   map_delete(m_JntResults.begin(), m_JntResults.end());
   m_JntResults.clear();
   map_delete(m_MbrResults.begin(), m_MbrResults.end());
   m_MbrResults.clear();
   map_delete(m_PoiResults.begin(), m_PoiResults.end());
   m_PoiResults.clear();

   m_SimplePOIResultCache.ClearCache();
}

void CModel::RemoveResults(LoadCaseIDType lcase)
{
   // remove all results for a given load case
   // ignore return code since we don't know (care) if loading results exist
   CollectionIndexType st;

   JntResultIterator ji( m_JntResults.begin() );
   JntResultIterator jiend( m_JntResults.end() );
   for (; ji!=jiend; ji++)
   {
      st = ji->second->Remove(lcase);
   }

   MbrResultIterator mi( m_MbrResults.begin() );
   MbrResultIterator miend( m_MbrResults.end() );
   for (; mi!=miend; mi++)
   {
      st = mi->second->Remove(lcase);
   }

   PoiResultIterator pi( m_PoiResults.begin() );
   PoiResultIterator piend( m_PoiResults.end() );
   for (; pi!=piend; pi++)
   {
      st = pi->second->Remove(lcase);
   }

   m_SimplePOIResultCache.ClearCache();

}

void CModel::RemovePoiResults(PoiIDType poiid)
{
   // zap results for given poi
   PoiResultIterator jit( m_PoiResults.find(poiid) );
   if (jit != m_PoiResults.end())
   {
      PoiResultArray* array = jit->second;
      delete array;
   }

   m_SimplePOIResultCache.ClearCache();
}

void CModel::RemoveAllPoiResults()
{
   map_delete(m_PoiResults.begin(), m_PoiResults.end());
   m_PoiResults.clear();

   m_SimplePOIResultCache.ClearCache();
}

void CModel::GetJointFromDof(LONG dof, JointIDType* joint, LONG* jdof)
{
   *joint = -1; // assume the worst
   *jdof = -1;

   JointIterator j( m_pJoints->begin() );
   JointIterator jend( m_pJoints->end() );
   while(j != jend)
   {
      CJoint *jnt = *(j++);

      LONG ndof = CJoint::NumDof;
      for (LONG idof = 0; idof < ndof; idof++)
      {
         LONG cdof = jnt->GetCondensedDOF(idof);
         if (cdof == dof)
         {
            jnt->get_ID(joint);
            *jdof = idof;
            return; // harsh, but effective. we've got what we came for
         }
      }
   }
}

