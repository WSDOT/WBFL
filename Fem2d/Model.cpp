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
// Model.cpp : Implementation of CModel
#include "stdafx.h"
#include "Model.h"

#include <WBFLTools\ComStructuredStorageAdapter.h>

#include "JointCollection.h"
#include "MemberCollection.h"
#include "LoadingCollection.h"
#include "POICollection.h"

/////////////////////////////////////////////////////////////////////////////
// CModel
CModel::CModel()
{
}

CModel::~CModel()
{
}

HRESULT CModel::FinalConstruct()
{
   m_pCore = std::make_unique<WBFL::FEA2D::Model>();

   return RebuildComWrappersFromCore();
}

HRESULT CModel::RebuildComWrappersFromCore()
{
   // Joints
   CComObject<Joints>* pj;
   HRESULT hr = CComObject<Joints>::CreateInstance(&pj);
   if (FAILED(hr))
      return hr;
   pj->OnCreate(this, this, m_pCore.get());
   pj->AddRef();
   m_pJoints.Attach(pj);

   for (IndexType i = 0; i < m_pCore->GetJointCount(); i++)
   {
      m_pJoints->AdoptCore(m_pCore->FindJointByIndex(i));
   }

   // Members
   CComObject<Members>* pm;
   hr = CComObject<Members>::CreateInstance(&pm);
   if (FAILED(hr))
      return hr;
   pm->OnCreate(this, this, m_pCore.get());
   pm->AddRef();
   m_pMembers.Attach(pm);

   for (IndexType i = 0; i < m_pCore->GetMemberCount(); i++)
   {
      m_pMembers->AdoptCore(m_pCore->FindMemberByIndex(i));
   }

   // Loadings (and each loading's five sub-collections)
   CComObject<Loadings>* plc;
   hr = CComObject<Loadings>::CreateInstance(&plc);
   if (FAILED(hr))
      return hr;
   plc->OnCreate(this, this, m_pCore.get());
   plc->AddRef();
   m_pLoadings.Attach(plc);

   for (IndexType i = 0; i < m_pCore->GetLoadingCount(); i++)
   {
      WBFL::FEA2D::Loading* pCoreLoading = m_pCore->FindLoadingByIndex(i);
      CLoading* pLoading = m_pLoadings->AdoptCore(pCoreLoading);

      for (IndexType j = 0; j < pCoreLoading->GetJointLoadCount(); j++)
         pLoading->m_pJointLoads->AdoptCore(pCoreLoading->FindJointLoadByIndex(j));

      for (IndexType j = 0; j < pCoreLoading->GetDistributedLoadCount(); j++)
         pLoading->m_pDistributedLoads->AdoptCore(pCoreLoading->FindDistributedLoadByIndex(j));

      for (IndexType j = 0; j < pCoreLoading->GetMemberStrainCount(); j++)
         pLoading->m_pMemberStrains->AdoptCore(pCoreLoading->FindMemberStrainByIndex(j));

      for (IndexType j = 0; j < pCoreLoading->GetJointDisplacementCount(); j++)
         pLoading->m_pJointDeflections->AdoptCore(pCoreLoading->FindJointDisplacementByIndex(j));

      for (IndexType j = 0; j < pCoreLoading->GetPointLoadCount(); j++)
         pLoading->m_pPointLoads->AdoptCore(pCoreLoading->FindPointLoadByIndex(j));
   }

   // POIs
   CComObject<POIs>* ppoi;
   hr = CComObject<POIs>::CreateInstance(&ppoi);
   if (FAILED(hr))
      return hr;
   ppoi->OnCreate(this, this, m_pCore.get());
   ppoi->AddRef();
   m_pPOIs.Attach(ppoi);

   for (IndexType i = 0; i < m_pCore->GetPOICount(); i++)
   {
      m_pPOIs->AdoptCore(m_pCore->FindPOIByIndex(i));
   }

   return S_OK;
}

STDMETHODIMP CModel::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IFem2dModel
	};
	for (long i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CModel::put_ForceEquilibriumTolerance(Float64 tol)
{
   m_pCore->SetForceEquilibriumTolerance(tol);
   return S_OK;
}

STDMETHODIMP CModel::get_ForceEquilibriumTolerance(Float64* tol)
{
   CHECK_RETVAL(tol);
   *tol = m_pCore->GetForceEquilibriumTolerance();
   return S_OK;
}

STDMETHODIMP CModel::put_MomentEquilibriumTolerance(Float64 tol)
{
   m_pCore->SetMomentEquilibriumTolerance(tol);
   return S_OK;
}

STDMETHODIMP CModel::get_MomentEquilibriumTolerance(Float64* tol)
{
   CHECK_RETVAL(tol);
   *tol = m_pCore->GetMomentEquilibriumTolerance();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CModel::Load(/*[in]*/ IStructuredLoad2 *pload)
{
   HRESULT hr = S_OK;
   try
   {
      ComStructuredLoadAdapter adapter(pload);
      m_pCore->Load(&adapter);
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      switch (ex.GetReasonCode())
      {
      case WBFL::FEA2D::ReasonCode::PersistenceBadVersion:
         hr = STRLOAD_E_BADVERSION;
         break;
      case WBFL::FEA2D::ReasonCode::PersistenceInvalidFormat:
         hr = STRLOAD_E_INVALIDFORMAT;
         break;
      default:
         hr = E_FAIL;
         break;
      }
   }

   // Model::Load() clears the core before parsing anything, even when it
   // ultimately throws (bad version, or a corrupt record mid-parse) - the
   // core's contents changed either way, so every pre-existing COM wrapper
   // is bound to a now-freed core object regardless of whether Load()
   // itself succeeded. Always rehydrate to avoid leaving dangling wrappers.
   HRESULT rehydrateHr = RebuildComWrappersFromCore();

   return FAILED(hr) ? hr : rehydrateHr;
}

STDMETHODIMP CModel::Save(/*[in]*/ IStructuredSave2 *psave)
{
   try
   {
      ComStructuredSaveAdapter adapter(psave);
      m_pCore->Save(&adapter);
   }
   catch (const WBFL::FEA2D::XFEA2D&)
   {
      return E_FAIL;
   }

   return S_OK;
}

STDMETHODIMP CModel::put_Name(BSTR name)
{
   m_pCore->SetName(std::_tstring(name != nullptr ? name : L""));
   return S_OK;
}

STDMETHODIMP CModel::get_Name(BSTR* name)
{
   CHECK_RETVAL(name);
   CComBSTR bstr(m_pCore->GetName().c_str());
   *name = bstr.Detach();
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
   // each collection's own Clear() clears both the ATL map and the
   // matching FEA2D core collection, and fires the matching On*Cleared
   // event - same sequence as the legacy engine
   m_pJoints->Clear();
   m_pMembers->Clear();
   m_pLoadings->Clear();
   m_pPOIs->Clear();

	return S_OK;
}

STDMETHODIMP CModel::get_Results(/*[out, retval]*/ IFem2dModelResultsForScriptingClients* *pVal)
{
   return this->QueryInterface(IID_IFem2dModelResultsForScriptingClients,(void**)pVal);
}

STDMETHODIMP CModel::get_StructuredStorage(/*[out, retval]*/ IStructuredStorage2* *pVal)
{
   return this->QueryInterface(IID_IStructuredStorage2,(void**)pVal);
}

CJointCollection* CModel::GetJoints()
{
   return m_pJoints;
}

CMemberCollection* CModel::GetMembers()
{
   return m_pMembers;
}

////////////////////////////////////////////////////////////////////////////////
/////////// IFem2dModelResults / IFem2dModelResultsEx ///////////////////////////
////////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CModel::ComputeJointDeflections(LoadCaseIDType lc, JointIDType jnt, Float64 *Dx, Float64 *Dy, Float64 *Rz)
{
   CHECK_RETVAL(Dx);
   CHECK_RETVAL(Dy);
   CHECK_RETVAL(Rz);

   try
   {
      m_pCore->ComputeJointDeflections(lc, jnt, Dx, Dy, Rz);
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dModel, IID_IFem2dModel);
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
      m_pCore->ComputeMemberDeflections(lc, mbr, startDx, startDy, startRz, endDx, endDy, endRz);
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dModel, IID_IFem2dModel);
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
      m_pCore->ComputeReactions(lc, jnt, Fx, Fy, Mz);
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dModel, IID_IFem2dModel);
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
      m_pCore->ComputeMemberForces(lc, mid, static_cast<WBFL::FEA2D::LoadOrientation>(orientation), startFx, startFy, startMz, endFx, endFy, endMz);
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dModel, IID_IFem2dModel);
   }

	return S_OK;
}

STDMETHODIMP CModel::ComputePOIDeflections(LoadCaseIDType lc, PoiIDType poiID, Fem2dLoadOrientation orientation, Float64 *Dx, Float64 *Dy, Float64 *Rz)
{
   CHECK_RETVAL(Dx);
   CHECK_RETVAL(Dy);
   CHECK_RETVAL(Rz);

   try
   {
      m_pCore->ComputePOIDeflections(lc, poiID, static_cast<WBFL::FEA2D::LoadOrientation>(orientation), Dx, Dy, Rz);
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dModel, IID_IFem2dModel);
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
      m_pCore->ComputePOIForces(lc, poiID, static_cast<WBFL::FEA2D::MemberFaceType>(face), static_cast<WBFL::FEA2D::LoadOrientation>(orientation), Fx, Fy, Mz);
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dModel, IID_IFem2dModel);
   }

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
/////////// IFem2dModelResultsForScriptingClients ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Simple pass-throughs to the 3/6-tuple versions above - unchanged from legacy.

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

////////////////////////////////////////////////////////////////////////////////
/////////// Change Management Related Functions ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// FEA2D::Model tracks its own dirtiness now (see the design note on
// Model::EnsureAnalyzed() in FEA2D\Model.cpp) - these handlers exist purely
// to fire the legacy connection-point events for VBA/Excel subscribers.
// Fire_OnModelChanged()/Fire_OnLoadingChanged() firing is unchanged from
// the legacy engine.

void CModel::OnJointChanged(IFem2dJoint*)
{
   Fire_OnModelChanged();
}

void CModel::OnJointAdded(JointIDType)
{
   Fire_OnModelChanged();
}

void CModel::OnJointRemoved(JointIDType)
{
   Fire_OnModelChanged();
}

void CModel::OnJointsCleared()
{
   Fire_OnModelChanged();
}

void CModel::OnMemberChanged(IFem2dMember*)
{
   Fire_OnModelChanged();
}

void CModel::OnMemberAdded(MemberIDType)
{
   Fire_OnModelChanged();
}

void CModel::OnMemberRemoved(MemberIDType )
{
   Fire_OnModelChanged();
}

void CModel::OnMembersCleared( )
{
   Fire_OnModelChanged();
}

void CModel::OnJointLoadChanged(IFem2dJointLoad*, LoadCaseIDType loadingID)
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnJointLoadAdded(LoadIDType loadID, LoadCaseIDType loadingID)
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnJointLoadRemoved(LoadIDType loadID, LoadCaseIDType loadingID )
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnJointLoadsCleared(LoadCaseIDType loadingID )
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnJointDeflectionChanged(IFem2dJointDeflection*, LoadCaseIDType loadingID)
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnJointDeflectionAdded(LoadIDType loadID, LoadCaseIDType loadingID)
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnJointDeflectionRemoved(LoadIDType loadID, LoadCaseIDType loadingID )
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnJointDeflectionsCleared(LoadCaseIDType loadingID )
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnPointLoadChanged(IFem2dPointLoad*, LoadCaseIDType loadingID)
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnPointLoadAdded(LoadIDType loadID, LoadCaseIDType loadingID)
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnPointLoadRemoved(LoadIDType loadID, LoadCaseIDType loadingID )
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnPointLoadsCleared(LoadCaseIDType loadingID )
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnDistributedLoadChanged(IFem2dDistributedLoad*, LoadCaseIDType loadingID)
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnDistributedLoadAdded(LoadIDType loadID, LoadCaseIDType loadingID)
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnDistributedLoadRemoved(LoadIDType loadID, LoadCaseIDType loadingID )
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnDistributedLoadsCleared(LoadCaseIDType loadingID )
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnMemberStrainChanged(IFem2dMemberStrain*, LoadCaseIDType loadingID)
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnMemberStrainAdded(LoadIDType loadID, LoadCaseIDType loadingID)
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnMemberStrainRemoved(LoadIDType loadID, LoadCaseIDType loadingID )
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnMemberStrainsCleared(LoadCaseIDType loadingID )
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnLoadingAdded(LoadCaseIDType loadingID)
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnLoadingRemoved(LoadCaseIDType loadingID )
{
   Fire_OnLoadingChanged(loadingID);
}

void CModel::OnLoadingsCleared()
{
   Fire_OnModelChanged();
}

void CModel::OnPOIChanged(IFem2dPOI*)
{
   // POIs carry no analysis behavior of their own (location markers,
   // consulted on demand) - no stiffness/results impact, matches legacy's
   // "new pois take care of themselves" comment on OnPOIAdded
}

void CModel::OnPOIAdded(PoiIDType)
{
}

void CModel::OnPOIRemoved(PoiIDType)
{
}

void CModel::OnPOIsCleared()
{
}
