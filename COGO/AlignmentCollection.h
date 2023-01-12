///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// AlignmentCollection.h : Declaration of the CAlignmentCollection

#ifndef __AlignmentCollection_H_
#define __AlignmentCollection_H_
#pragma once

#include "resource.h"       // main symbols
#include "Collections.h"
#include "COGOCP.h"

class CAlignmentCollection;
typedef PersistentIDCollection<CAlignmentCollection,IAlignmentCollection,&IID_IAlignmentCollection,CogoObjectID,IAlignment> AlignmentCollectionImpl;

/////////////////////////////////////////////////////////////////////////////
// CAlignmentCollection
class ATL_NO_VTABLE CAlignmentCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CAlignmentCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CAlignmentCollection, &CLSID_AlignmentCollection>,
	public IConnectionPointContainerImpl<CAlignmentCollection>,
   public AlignmentCollectionImpl,
   public IAlignmentEvents,
	public CProxyDAlignmentCollectionEvents< CAlignmentCollection >
{
public:
   CAlignmentCollection() :
      m_bstrCollectionName("Alignments"),
      m_bstrItemName("Alignment")
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_ALIGNMENTCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAlignmentCollection)
	COM_INTERFACE_ENTRY(IAlignmentEvents)

	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY_CHAIN(AlignmentCollectionImpl)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CAlignmentCollection)
CONNECTION_POINT_ENTRY(IID_IAlignmentCollectionEvents)
END_CONNECTION_POINT_MAP()

   void SetCollectionName(BSTR bstrCollectionName) { m_bstrCollectionName = bstrCollectionName; }
   void SetItemName(BSTR bstrItemName) { m_bstrItemName = bstrItemName; }
   CComBSTR GetCollectionName()  { return m_bstrCollectionName; }
   CComBSTR GetItemName() { return m_bstrItemName; }

// IAlignmentCollection
public:
//   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
   STDMETHOD(Clone)(/*[out,retval]*/ IAlignmentCollection* *clone) override;
   STDMETHOD(get__EnumAlignments)(/*[out,retval]*/ IEnumAlignments** ppenum) override;
	STDMETHOD(get_Factory)(/*[out,retval]*/IAlignmentFactory** factory) override;
	STDMETHOD(putref_Factory)(/*[in]*/IAlignmentFactory* factory) override;
//   STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval) override;  
   STDMETHOD(get_Item)(/*[in]*/ CogoObjectID id, /*[out, retval]*/ IAlignment* *pVal) override;
   STDMETHOD(putref_Item)(/*[in]*/ CogoObjectID id, /*[in]*/ IAlignment* pVal) override;
   STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
   STDMETHOD(AddEx)(/*[in]*/ CogoObjectID id,/*[in]*/ IAlignment* newVal) override;
   STDMETHOD(Add)(/*[in]*/ CogoObjectID id,/*[out,retval]*/ IAlignment* *Path) override;
   STDMETHOD(Remove)(/*[in]*/ CogoObjectID id) override;
   STDMETHOD(Clear)() override;
   STDMETHOD(FindID)(/*[in]*/ IAlignment* pAlignment,/*[out,retval]*/CogoObjectID* ID) override;
   STDMETHOD(get__EnumIDs)(/*[out,retval]*/ IEnumIDs** ppenum) override;
//	STDMETHOD(get_Factory)(/*[out,retval]*/IPoint2dFactory** factory) override;
//	STDMETHOD(putref_Factory)(/*[in]*/IPoint2dFactory* factory) override;
   STDMETHOD(ID)(/*[in]*/ CollectionIndexType index,/*[out,retval]*/ CogoObjectID* ID) override;

// IAlignmentEvents
	STDMETHOD(OnAlignmentChanged)(IAlignment* pAlignment) override
	{
      CogoObjectID id;
      FindID(pAlignment,&id);
      Fire_OnAlignmentChanged(this,id,pAlignment);
		return S_OK;
	}

	STDMETHOD(OnProfileChanged)(IProfile* pProfile) override
	{
      Fire_OnProfileChanged(this,pProfile);
		return S_OK;
	}

   STDMETHOD(OnStationEquationsChanged)(IStationEquationCollection* equations) override
   {
      Fire_OnStationEquationsChanged(this,equations);
      return S_OK;
   }


private:
   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);
   HRESULT AlignmentNotFound(CogoObjectID id);
   HRESULT AlignmentAlreadyDefined(CogoObjectID id);
   HRESULT AlignmentIDError(CogoObjectID id,UINT nHelpString,HRESULT hRes);

   void Advise(CogoObjectID id,IAlignment* pAlignment);
   void Unadvise(CogoObjectID id,IAlignment* pAlignment);
   void UnadviseAll();
   std::map<CogoObjectID,DWORD> m_Cookies;

   CComPtr<IAlignmentFactory> m_Factory;

   CComBSTR m_bstrCollectionName;
   CComBSTR m_bstrItemName;
};

#endif //__AlignmentCollection_H_
