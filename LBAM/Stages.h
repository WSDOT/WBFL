///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright (C) 2009  Washington State Department of Transportation
//                     Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// Stages.h : Declaration of the CStages

#ifndef __STAGES_H_
#define __STAGES_H_

#include "resource.h"       // main symbols
#include "WbflComCollections.h"
#include "StageCP.h"
#include "LBAMUtils.h"

class CStages;
typedef CComSegmentCollection< IStages, IStage, IEnumStage, &IID_IEnumStage,StageIndexType> StageCollImpl;
typedef CPersistentCollection<CStages, StageCollImpl,StageIndexType> PersistentStageCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CStages
class ATL_NO_VTABLE CStages : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CStages,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CStages, &CLSID_Stages>,
	public ISupportErrorInfo,
   public PersistentStageCollImpl,
	public IConnectionPointContainerImpl<CStages>,
	public CProxyDStagesEvents< CStages >,
   public IObjectSafetyImpl<CStages,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStageEvents
{
public:
	CStages()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STAGES)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStages)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PersistentStageCollImpl)
   COM_INTERFACE_ENTRY(IStageEvents)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CStages)
CONNECTION_POINT_ENTRY(IID_IStagesEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISpanEvents
   STDMETHOD(OnStageChanged)(/*[in]*/IStage* Stage, ChangeType change);

public:
// IStages
	STDMETHOD(Clone)(/*[out, retval]*/ IStages** clone);
	STDMETHOD(Add)(/*[in]*/ IStage* stage);
	STDMETHOD(Insert)(/*[in]*/ StageIndexType relpos, /*[in]*/ IStage* stage);
	STDMETHOD(RemoveByIndex)(/*[in]*/ StageIndexType relpos);
	STDMETHOD(RemoveByName)(/*[in]*/ BSTR name);
	STDMETHOD(FindIndex)(/*[in]*/ BSTR name, /*[out,retval]*/StageIndexType* index);

private:
   IStage* Find(const CComBSTR& name);

private:
   // implementations of virtual functions for collection
   virtual HRESULT OnBeforeAdd( StoredType* pVal)
   {
      CHECK_IN(pVal);
      try
      {
         // set up connection point
         HRESULT hr;
         hr = CrAdvise(pVal->second.m_T, this, IID_IStageEvents, &(pVal->first));
         if (FAILED(hr))
            return hr;
      }
      catch(...)
      {
         ATLASSERT(0);
         return E_FAIL;
      }
      return S_OK;
   }

   virtual HRESULT OnAfterAdd( StoredType* pVal, StageIndexType idx)
   {
      Fire_OnStagesAdded(pVal->second.m_T, idx);
      return S_OK;
   }

   virtual HRESULT OnBeforeRemove( StoredType* pVal, StageIndexType idx)
   {
      try
      {
         // release connection point
         HRESULT hr;
         hr = CrUnadvise(pVal->second.m_T, this, IID_IStageEvents, pVal->first);
         if (FAILED(hr))
            return hr;
      }
      catch(...)
      {
         ATLASSERT(0);
         return E_FAIL;
      }

      Fire_OnStagesBeforeRemove(pVal->second.m_T, idx);

      return S_OK;
   }

   virtual HRESULT OnAfterRemove( StageIndexType idx)
   {
      return S_OK; 
   }

   virtual HRESULT OnAfterMoveTo( StageIndexType from, StageIndexType to)
   {
      Fire_OnStagesMoveTo(from, to);
      return S_OK;
   }

   virtual HRESULT OnAfterCopyTo( StageIndexType from, StageIndexType to)
   {
      Fire_OnStagesCopyTo(from, to);
      return S_OK;
   }

   virtual HRESULT OnAfterReverse()
   {
      Fire_OnStagesReverse();
      return S_OK;
   }

public:
   virtual void FinalRelease()
   {
      // free up all of our connectionpoints on destruct
      StageIndexType cnt=0;
      for (iterator it= begin(); it != end(); it++)
      {
         OnBeforeRemove(*it, cnt++);
      }
   }

};

#endif //__STAGES_H_
