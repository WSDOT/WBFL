///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

// SuperstructureMemberCollection.h : Declaration of the CSuperstructureMemberCollection

#ifndef __SUPERSTRUCTUREMEMBERCOLLECTION_H_
#define __SUPERSTRUCTUREMEMBERCOLLECTION_H_

#include "resource.h"       // main symbols
#include <WBFLComCollections.h>
#include "SuperstructureMember.h"
#include "GenericBridgeCP.h"
#include "FilteredSuperstructureMemberCollection.h"

class CSuperstructureMemberCollection;
typedef CComSegmentCollection< ISuperstructureMemberCollection, ISuperstructureMember, IEnumSuperstructureMember, &IID_IEnumSuperstructureMember, CollectionIndexType > SuperstructureMemberCollImpl;
typedef CPersistentCollection<CSuperstructureMemberCollection, SuperstructureMemberCollImpl, CollectionIndexType> PersistentSuperstructureMemberCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CSuperstructureMemberCollection
class ATL_NO_VTABLE CSuperstructureMemberCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSuperstructureMemberCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSuperstructureMemberCollection, &CLSID_SuperstructureMemberCollection>,
	public ISupportErrorInfo,
   public PersistentSuperstructureMemberCollImpl,
	public IConnectionPointContainerImpl<CSuperstructureMemberCollection>,
	public CProxyDSuperstructureMemberCollectionEvents< CSuperstructureMemberCollection >,
   public IObjectSafetyImpl<CSuperstructureMemberCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISuperstructureMemberEvents
{
public:
   CSuperstructureMemberCollection()
	{
      m_bSym  = VARIANT_FALSE;
      m_pBridge = NULL;
      m_ID = 0; // not assigned
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetBridge(IGenericBridge* pBridge);

   void RenameStageReferences(BSTR bstrOldName,BSTR bstrNewName);
   void AddDataForStage(BSTR bstrName);
   void RemoveDataForStage(BSTR bstrName);

   void SetID(long id);
   void SetPoints(IPoint2d* pLeftEnd,IPoint2d* pLeftRef,IPoint2d* pRightEnd,IPoint2d* pRightRef);


DECLARE_REGISTRY_RESOURCEID(IDR_SUPERSTRUCTUREMEMBERCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSuperstructureMemberCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PersistentSuperstructureMemberCollImpl)

   COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

	COM_INTERFACE_ENTRY(ISuperstructureMemberEvents)

   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSuperstructureMemberCollection)
   CONNECTION_POINT_ENTRY(IID_ISuperstructureMemberCollectionEvents)
END_CONNECTION_POINT_MAP()

private:
   IGenericBridge* m_pBridge; // Weak reference

protected:
   CComBSTR GetCollectionName() { return CComBSTR("SuperstructureMembers"); }
   CComBSTR GetStoredName()     { return CComBSTR("SuperstructureMember");  }
   virtual HRESULT DoSaveItem(IStructuredSave2* save,ISuperstructureMember* item);
   virtual HRESULT DoLoadItem(IStructuredLoad2* load,ISuperstructureMember* *ppItem);
   virtual HRESULT SaveAdditionalProperties(IStructuredSave2 *save);
   virtual HRESULT LoadAdditionalProperties(IStructuredLoad2 *load);

// ISuperstructureMemberEvents
public:
	STDMETHOD(OnSuperstructureMemberChanged)(ISuperstructureMember * ssm)
	{
      Fire_OnSuperstructureMemberCollectionChanged(this);
		return S_OK;
	}

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISuperstructureMemberCollection
public:
	STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType position, /*[out, retval]*/ ISuperstructureMember* *pVal);
   STDMETHOD(get_Count)(/*[out,retval]*/ CollectionIndexType* pVal);
   STDMETHOD(get_ID)(/*[out,retval]*/long* id);
	STDMETHOD(Add)();
   STDMETHOD(Insert)(/*[in]*/CollectionIndexType relPosition);
	STDMETHOD(MoveTo)(/*[in]*/ CollectionIndexType fromPosition, /*[in]*/ CollectionIndexType toPosition);
	STDMETHOD(CopyTo)(/*[in]*/CollectionIndexType fromPosition, /*[in]*/CollectionIndexType toPosition);
   STDMETHOD(Remove)(/*[in]*/CollectionIndexType position);
   STDMETHOD(Reverse)();
   STDMETHOD(Clear)();
	STDMETHOD(get_MemberLength)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(Clone)(/*[out, retval]*/ ISuperstructureMemberCollection** clone);
   STDMETHOD(get_Symmetrical)(/*[out,retval]*/ VARIANT_BOOL* bSym);
   STDMETHOD(put_Symmetrical)(/*[in]*/ VARIANT_BOOL bSym);
//   STDMETHOD(get_Fractional)(/*[out,retval]*/ VARIANT_BOOL* bFrac);
//   STDMETHOD(put_Fractional)(/*[in]*/ VARIANT_BOOL bFrac);
//	STDMETHOD(GetSegmentForSpanLocation)(/*[in]*/ long spanIdx,/*[in]*/ Float64 location,  /*[out]*/ Float64* dist,/*[out]*/ ISegment** segment);
//	STDMETHOD(GetSegmentForLocation)(/*[in]*/ Float64 location, /*[out]*/ Float64* dist,/*[out]*/ ISegment** segment);
////   STDMETHOD(GetSegmentPoint)(/*[in]*/ Float64 location,/*[out]*/ long* ssmbrIdx,/*[out]*/ long* segmentIdx,/*[out]*/ Float64* dist);
//   STDMETHOD(GetMemberForLocation)(/*[in]*/ Float64 location, /*[out,retval]*/ ISuperstructureMember* *mbr);
	STDMETHOD(GetSuperstructureMembers)(/*[out,retval]*/ IFilteredSuperstructureMemberCollection** mbrs);
   STDMETHOD(GetReferencePoint)(/*[in]*/ EndType endType,/*[out,retval]*/IPoint2d** ppPoint);
	STDMETHOD(GetEndPoint)(/*[in]*/ EndType endType,/*[out,retval]*/IPoint2d** ppPoint);

private:
	HRESULT FillNonSymmetrical(Float64 gdrLineLength,CFilteredSuperstructureMemberCollection* pColl);
	HRESULT FillSymmetrical(Float64 gdrLineLength,CFilteredSuperstructureMemberCollection* pColl);

//   HRESULT SpanLocationToAbsolute(long spanIdx,Float64 loc,Float64* dist);
   
   HRESULT AdviseSuperstructureMember(ISuperstructureMember* ssm,DWORD *pdwCookie);
   HRESULT UnadviseSuperstructureMember(ISuperstructureMember* ssm,DWORD dwCookie);

   // implementations of virtual functions for collection
   virtual HRESULT OnBeforeAdd( StoredType* pVal)
   {
      try
      {
         // set up connection point
         HRESULT hr;
         hr = AdviseSuperstructureMember(pVal->second.m_T, &(pVal->first));
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

   virtual HRESULT OnAfterAdd( StoredType* pVal, long id)
   {
      CSuperstructureMember* pMbr = dynamic_cast<CSuperstructureMember*>(pVal->second.m_T.p);
      pMbr->SetBridge(m_pBridge);

      Fire_OnSuperstructureMemberAdded(id);
      return S_OK;
   }

   virtual HRESULT OnBeforeRemove( StoredType* pVal, long id)
   {
      try
      {
         // release connection point
         HRESULT hr;
         hr = UnadviseSuperstructureMember(pVal->second.m_T, pVal->first);
         if (FAILED(hr))
            return hr;
      }
      catch(...)
      {
         ATLASSERT(0);
         return E_FAIL;
      }

      CComPtr<ISuperstructureMember> mbr = pVal->second.m_T;
      CSuperstructureMember* pMbr = dynamic_cast<CSuperstructureMember*>(mbr.p);
      pMbr->SetBridge(NULL);

      return S_OK;
   }

   virtual HRESULT OnAfterRemove( long id)
   {
      Fire_OnSuperstructureMemberRemoved(id);
      return S_OK; 
   }

   virtual HRESULT OnAfterMoveTo( long from, long to)
   {
      Fire_OnSuperstructureMemberMoved(from,to);
      return S_OK;
   }
//   virtual HRESULT OnAfterCopyTo( long from, long to)
//   {
//       NOTE: The implementation of CopyTo has been changed...
//              This method will never be called
//              Events fire in OnAfterRemove and OnAfterAdd
//              when the old item is removed from the collection and
//              the copy is inserted
//
//      Fire_OnSuperstructureMemberCollectionChanged(this);
//      return S_OK;
//   }
   virtual HRESULT OnAfterReverse()
   {
      Fire_OnSuperstructureMemberCollectionChanged(this);
      return S_OK;
   }


protected:
   CComPtr<IPoint2d> m_EndPoint[2]; // points at the end of the superstructure member collection
   CComPtr<IPoint2d> m_RefPoint[2]; // the points used to define the superstructure member collection
   long m_ID;
   VARIANT_BOOL m_bSym;
//   VARIANT_BOOL m_bFrac; // superstructure members are a fraction of the girder line length
//   long m_GdrLineIdx;
};

#endif //__SUPERSTRUCTUREMEMBERCOLLECTION_H_
