///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2018  Washington State Department of Transportation
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
// Model.h : Declaration of the CModel

#ifndef __Model_H_
#define __Model_H_
#pragma once

#include "resource.h"       // main symbols

#include "JointCollection.h"
#include "MemberCollection.h"
#include "LoadingCollection.h"
#include "POICollection.h"
#include "result.h"
#include "SymBandedMatrix.h"
#include "ModelEvents.h"

#if defined _DEBUG
#include <fstream>
#endif
#include "Fem2dCP.h"

/////////////////////////////////////////////////////////////////////////////
// CModel
class ATL_NO_VTABLE CModel : 
 	public CComObjectRootEx<CComSingleThreadModel>,
   //public CComRefCountTracer<CModel,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CModel, &CLSID_Fem2dModel>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CModel>,
   public IObjectSafetyImpl<CModel,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dModel,
	public IStructuredStorage2,
	public IFem2dModelResultsForScriptingClients,
	public IFem2dModelResults,
	public IFem2dModelResultsEx,
	public CProxyIFem2dModelEvents< CModel >,
   public ModelEvents
{
public:
	CModel();
	virtual ~CModel();

DECLARE_REGISTRY_RESOURCEID(IDR_MODEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CModel)
	COM_INTERFACE_ENTRY(IFem2dModel)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IFem2dModelResults)
	COM_INTERFACE_ENTRY(IFem2dModelResultsEx)
	COM_INTERFACE_ENTRY(IFem2dModelResultsForScriptingClients)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CModel)
CONNECTION_POINT_ENTRY(IID_IFem2dModelEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

public:
   // Implementation of ModelEvents. Events fired from parts of the model
   virtual void OnJointChanged(IFem2dJoint*) override;
   virtual void OnJointAdded(JointIDType) override;
   virtual void OnJointRemoved(JointIDType) override;
   virtual void OnJointsCleared() override;
   virtual void OnMemberChanged(IFem2dMember*) override;
   virtual void OnMemberAdded(MemberIDType) override;
   virtual void OnMemberRemoved(MemberIDType) override;
   virtual void OnMembersCleared() override;
   virtual void OnJointLoadChanged(IFem2dJointLoad*, LoadCaseIDType loadingID) override;
   virtual void OnJointLoadAdded(LoadIDType loadID, LoadCaseIDType loadingID) override;
   virtual void OnJointLoadRemoved(LoadIDType loadID, LoadCaseIDType loadingID ) override;
   virtual void OnJointLoadsCleared(LoadCaseIDType loadingID ) override;
   virtual void OnJointDeflectionChanged(IFem2dJointDeflection*, LoadCaseIDType loadingID) override;
   virtual void OnJointDeflectionAdded(LoadIDType loadID, LoadCaseIDType loadingID) override;
   virtual void OnJointDeflectionRemoved(LoadIDType loadID, LoadCaseIDType loadingID ) override;
   virtual void OnJointDeflectionsCleared(LoadCaseIDType loadingID ) override;
   virtual void OnPointLoadChanged(IFem2dPointLoad*, LoadCaseIDType loadingID) override;
   virtual void OnPointLoadAdded(LoadIDType loadID, LoadCaseIDType loadingID) override;
   virtual void OnPointLoadRemoved(LoadIDType loadID, LoadCaseIDType loadingID ) override;
   virtual void OnPointLoadsCleared(LoadCaseIDType loadingID ) override;
   virtual void OnDistributedLoadChanged(IFem2dDistributedLoad*, LoadCaseIDType loadingID) override;
   virtual void OnDistributedLoadAdded(LoadIDType loadID, LoadCaseIDType loadingID) override;
   virtual void OnDistributedLoadRemoved(LoadIDType loadID, LoadCaseIDType loadingID ) override;
   virtual void OnDistributedLoadsCleared(LoadCaseIDType loadingID ) override;
   virtual void OnMemberStrainChanged(IFem2dMemberStrain*, LoadCaseIDType loadingID) override;
   virtual void OnMemberStrainAdded(LoadIDType loadID, LoadCaseIDType loadingID) override;
   virtual void OnMemberStrainRemoved(LoadIDType loadID, LoadCaseIDType loadingID ) override;
   virtual void OnMemberStrainsCleared(LoadCaseIDType loadingID ) override;
   virtual void OnLoadingAdded(LoadCaseIDType loadingID) override;
   virtual void OnLoadingRemoved(LoadCaseIDType loadingID ) override;
   virtual void OnLoadingsCleared() override;
   virtual void OnPOIChanged(IFem2dPOI*) override;
   virtual void OnPOIAdded(PoiIDType ID) override;
   virtual void OnPOIRemoved(PoiIDType ID) override;
   virtual void OnPOIsCleared() override;

   HRESULT CModel::FinalConstruct();

private:
   // data to support change management
   bool m_ModelDirty;                // something affecting the stiffness changed
   typedef std::set<LoadCaseIDType> DirtyLoadings;
   typedef DirtyLoadings::iterator  DirtyLoadingsIterator;
   DirtyLoadings                    m_DirtyLoadings;   // dirty loadings

   // data to support IFem2dModel
   typedef CComObject<CJointCollection> Joints;
   typedef Joints::iterator             JointIterator;
   typedef CComObject<CMemberCollection> Members;
   typedef Members::iterator             MemberIterator;
   typedef CComObject<CLoadingCollection> Loadings;
   typedef Loadings::iterator             LoadingIterator;
   typedef CComObject<CPOICollection>     POIs;
   typedef POIs::iterator                 POIIterator;

   CComPtr<Joints>   m_pJoints;
   CComPtr<Members>  m_pMembers;
   CComPtr<Loadings> m_pLoadings;
   CComPtr<POIs>     m_pPOIs;

   Float64 m_ForceEquilibriumTolerance, m_MomentEquilibriumTolerance;

   CComBSTR m_Name;


public:
// IFem2dModel
   STDMETHOD(put_Name)(BSTR name) override;
   STDMETHOD(get_Name)(BSTR* name) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(get_POIs)(/*[out, retval]*/ IFem2dPOICollection* *pVal) override;
	STDMETHOD(get_Loadings)(/*[out, retval]*/ IFem2dLoadingCollection* *pVal) override;
	STDMETHOD(get_Members)(/*[out, retval]*/ IFem2dMemberCollection* *pVal) override;
	STDMETHOD(get_Joints)(/*[out, retval]*/ IFem2dJointCollection* *pVal) override;
	STDMETHOD(get_Results)(/*[out, retval]*/ IFem2dModelResultsForScriptingClients* *pVal) override;
	STDMETHOD(get_StructuredStorage)(/*[out, retval]*/ IStructuredStorage2* *pVal) override;
   STDMETHOD(put_ForceEquilibriumTolerance)(/*[in]*/Float64 tol);
   STDMETHOD(get_ForceEquilibriumTolerance)(/*[out, retval]*/Float64* tol);
   STDMETHOD(put_MomentEquilibriumTolerance)(/*[in]*/Float64 tol);
   STDMETHOD(get_MomentEquilibriumTolerance)(/*[out, retval]*/Float64* tol);

// IFem2dModelResultsForScriptingClients
   STDMETHOD(ComputeJointDeflections)(/*[in]*/LoadCaseIDType loadingID, /*[in]*/JointIDType jointID, /*[in]*/ Fem2dJointDOF dof,/*[out,retval]*/Float64* pVal) override;
   STDMETHOD(ComputeMemberDeflections)(/*[in]*/LoadCaseIDType loadingID, /*[in]*/MemberIDType memberID, /*[in]*/ Fem2dMbrDOF dof,/*[out,retval]*/Float64* pVal) override;
   STDMETHOD(ComputePOIDeflections)(/*[in]*/LoadCaseIDType loadingID, /*[in]*/PoiIDType poiID, /*[in]*/Fem2dLoadOrientation orientation, /*[in]*/ Fem2dJointDOF dof,/*[out,retval]*/Float64* pVal) override;
   STDMETHOD(ComputeReactions)(/*[in]*/LoadCaseIDType loadingID, /*[in]*/JointIDType jointID, /*[in]*/ Fem2dJointDOF dof,/*[out,retval]*/Float64* pVal) override;
   STDMETHOD(ComputeMemberForces)(/*[in]*/LoadCaseIDType loadingID, /*[in]*/MemberIDType memberID, /*[in]*/ Fem2dMbrDOF dof,/*[out,retval]*/Float64* pVal) override;
   STDMETHOD(ComputePOIForces)(/*[in]*/LoadCaseIDType loadingID, /*[in]*/PoiIDType poiID, /*[in]*/Fem2dMbrFaceType face, /*[in]*/Fem2dLoadOrientation orientation, /*[in]*/ Fem2dJointDOF dof,/*[out,retval]*/Float64* pVal) override;

// IFem2dModelResults
	STDMETHOD(ComputePOIForces)(/*[in]*/LoadCaseIDType loadingID, /*[in]*/PoiIDType poiID, /*[in]*/Fem2dMbrFaceType face, /*[in]*/Fem2dLoadOrientation orientation, /*[out]*/Float64* Fx, /*[out]*/Float64* Fy, /*[out]*/Float64* Mz) override;
	STDMETHOD(ComputeMemberForces)(/*[in]*/LoadCaseIDType loadingID, /*[in]*/MemberIDType memberID, /*[out]*/Float64* startFx, /*[out]*/Float64* startFy, /*[out]*/Float64* startMz, /*[out]*/Float64* endFx, /*[out]*/Float64* endFy, /*[out]*/Float64* endMz) override;
	STDMETHOD(ComputeReactions)(/*[in]*/LoadCaseIDType loadingID, /*[in]*/JointIDType jointID, /*[out]*/Float64* Fx, /*[out]*/Float64* Fy, /*[out]*/Float64* Mz) override;
	STDMETHOD(ComputePOIDeflections)(/*[in]*/LoadCaseIDType loadingID, /*[in]*/PoiIDType poiID, /*[in]*/Fem2dLoadOrientation orientation, /*[out]*/Float64* Dx, /*[out]*/Float64* Dy, /*[out]*/Float64* Rz) override;
	STDMETHOD(ComputeMemberDeflections)(/*[in]*/LoadCaseIDType loadingID, /*[in]*/MemberIDType memberID, /*[out]*/Float64* startDx, /*[out]*/Float64* startDy, /*[out]*/Float64* startRz, /*[out]*/Float64* endDx, /*[out]*/Float64* endDy, /*[out]*/Float64* endRz) override;
	STDMETHOD(ComputeJointDeflections)(/*[in]*/LoadCaseIDType loadingID, /*[in]*/JointIDType jointID, /*[out]*/Float64* Dx, /*[out]*/Float64* Dy, /*[out]*/Float64* Rz) override;

// IFem2dModelResultsEx
	STDMETHOD(ComputeMemberForcesEx)(/*[in]*/LoadCaseIDType loadingID, /*[in]*/MemberIDType memberID, /*[in]*/Fem2dLoadOrientation orientation, /*[out]*/Float64* startFx, /*[out]*/Float64* startFy, /*[out]*/Float64* startMz, /*[out]*/Float64* endFx, /*[out]*/Float64* endFy, /*[out]*/Float64* endMz) override;

// IStructuredStorage2
public:
   STDMETHOD(Load)(/*[in]*/ IStructuredLoad2 *load) override;
   STDMETHOD(Save)(/*[in]*/ IStructuredSave2 *save) override;

// Data members for Results storage and FEM solution
private:
   typedef Result<NUM_DOF,NUM_DOF>             JntResult;
   typedef ResultArray<JntResult>              JntResultArray;
   typedef std::map<JointIDType,JntResultArray*>       JntResultContainer;
   typedef JntResultContainer::iterator        JntResultIterator;
   typedef JntResultContainer::const_iterator  ConstJntResultIterator;

   typedef std::map<MemberIDType,CMember::MbrResultArray*>       MbrResultContainer;
   typedef MbrResultContainer::iterator        MbrResultIterator;
   typedef MbrResultContainer::const_iterator  ConstMbrResultIterator;

   typedef Result<NUM_DOF*2,NUM_DOF>           PoiResult;
   typedef ResultArray<PoiResult>              PoiResultArray;
   typedef std::map<PoiIDType,PoiResultArray*>      PoiResultContainer;
   typedef PoiResultContainer::iterator        PoiResultIterator;
   typedef PoiResultContainer::const_iterator  ConstPoiResultIterator;

   JntResultContainer     m_JntResults;
   MbrResultContainer     m_MbrResults;
   PoiResultContainer     m_PoiResults;

   // A simple cache for negative load case POI results - typically these results are asked for
   // sequentially
#pragma Reminder("The following will cause problems if this class becomes multithreaded")
   struct SimplePOIResultCache
   {
      SimplePOIResultCache():
      poiID(-MAX_ID), loadCase(-MAX_ID), poiResult(-MAX_ID)
      {;}

      bool IsHit(PoiIDType poiid, LoadCaseIDType lcase)
      {
         if (lcase<0) // only cache negative load cases
            return poiid==this->poiID && lcase==this->loadCase;
         else
            return false;
      }

      void ClearCache()
      {
          poiID = -MAX_ID;
          loadCase = -MAX_ID;
      }

      void Update(PoiIDType poiid, LoadCaseIDType lcase, const PoiResult& poiresult)
      {
         poiID = poiid;
         loadCase = lcase;
         poiResult = poiresult;
      }

      PoiResult poiResult;

   private:
      PoiIDType poiID;
      LoadCaseIDType loadCase;

   } m_SimplePOIResultCache;

   LONG m_BandWidth;
   LONG m_NumGlobalDOF;
   LONG m_NumCondensedDOF;
   SymBandedMatrix m_K; // Global stiffness matrix
   Float64 *m_pF;  // Global Force Vector

#if defined _DEBUG
   SymBandedMatrix m_Korig;
   Float64 *m_pForig;
#endif

#if defined ENABLE_LOGGING
   std::_tofstream logfile;
#endif

// public methods for C++ clients in this server
public:
   CJointCollection* GetJoints();
   CMemberCollection* GetMembers();

// Methods for results storage and FEM solution
private:
   // Processing Functions
   void StiffnessAnalysis();

   // Misc Functions
   void SetForceEquilibriumCheckTolerance(Float64 tol) { m_ForceEquilibriumTolerance = tol; }
   Float64 GetForceEquilibriumCheckTolerance() const { return m_ForceEquilibriumTolerance; }
   void SetMomentEquilibriumCheckTolerance(Float64 tol) { m_MomentEquilibriumTolerance = tol; }
   Float64 GetMomentEquilibriumCheckTolerance() const { return m_MomentEquilibriumTolerance; }

   void ClearAnalysis();
   void InitModel();
   void CheckModel();
   void ClearLoads();
   void Compute();
   void ComputeLoadings();
   void FemAnalysis();
   LONG ComputeBandWidth();
   void BandSolve(LONG mode,LONG neq,LONG band,Float64 **KBand,Float64 *FBand);
   void AllocateKGlobal();
   void AllocateFGlobal();
   void FreeFGlobal();
   void AssembleGlobalStiffnessMatrix();
   void AssembleGlobalForceVector();
   void AssembleJointLoads();
   void AssembleElementLoads();
   void ApplyJntDeflections();
   void ComputeMemberResults();
   void ComputeReactions();
   void CheckEquilibrium();
   void SolveDeflectionsClassical();

   void StoreJntResults(LoadCaseIDType lcase);
   void StoreMbrResults(LoadCaseIDType lcase);
   //void StorePoiResults(LoadCaseIDType lcase);
   const PoiResult* StorePoiResults(LoadCaseIDType lcase, PoiIDType poiid);
   void RemoveAllResults();
   void RemoveResults(LoadCaseIDType lcase);
   void RemoveAllPoiResults();
   void RemovePoiResults(PoiIDType poi);

   void GetJointFromDof(LONG dof, JointIDType* joint, LONG* jdof);
   HRESULT DealWithExceptions();

#if defined _DEBUG
   void CheckSolution();
   Float64 GetKij(LONG I,LONG J);
#endif
};

#endif //__Model_H_
