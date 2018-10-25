///////////////////////////////////////////////////////////////////////
// Library - Framework for libraries
// Copyright © 1999-2014  Washington State Department of Transportation
//                        Bridge and Structures Office
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

// LibraryMgr.h : Declaration of the CLibraryMgr

#ifndef __LIBRARYMGR_H_
#define __LIBRARYMGR_H_

#include "resource.h"       // main symbols
#include <vector>
#include "WBFLLibrary.h"
#include "LibraryCP.h"
#include <TxnMgrImpl.h>
#include <SupportDisplayUnitsImpl.h>

#include <WBFLComCollections.h> // For copy policy

class CLibraryMgr;
typedef CComVectorCollection<ILibraryMgr,ILibrary,IEnumLibrary,&IID_IEnumLibrary,CollectionIndexType> VectorImpl;
typedef CPersistentCollection<CLibraryMgr,VectorImpl,CollectionIndexType> PersistentCollection;

/////////////////////////////////////////////////////////////////////////////
// CLibraryMgr
class ATL_NO_VTABLE CLibraryMgr : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLibraryMgr, &CLSID_LibraryMgr>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CLibraryMgr>,
   public PersistentCollection,
   public ILibraryEvents,
   public CProxyDLibraryMgrEvents< CLibraryMgr >,
   public ISupportTransactionsImpl,
   public ISupportDocUnitSystemImpl<&LIBID_WBFLLibrary>
{
public:
   CLibraryMgr() :
      m_bstrName("Unnamed")
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LIBRARYMGR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

//DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CLibraryMgr)
	COM_INTERFACE_ENTRY(ILibraryMgr)
	COM_INTERFACE_ENTRY(ILibraryEvents)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ISupportDocUnitSystem)
   COM_INTERFACE_ENTRY(ISupportTransactions)
   COM_INTERFACE_ENTRY_CHAIN(PersistentCollection)
END_COM_MAP()

BEGIN_CATEGORY_MAP(CLibraryMgr)
   IMPLEMENTED_CATEGORY(CATID_WBFLLibraryMgr)
END_CATEGORY_MAP()

BEGIN_CONNECTION_POINT_MAP(CLibraryMgr)
CONNECTION_POINT_ENTRY(IID_ILibraryMgrEvents)
END_CONNECTION_POINT_MAP()

   virtual CComBSTR GetCollectionName() { return CComBSTR("LibraryManager"); }
   virtual CComBSTR GetStoredName() { return CComBSTR("Library"); }

   virtual HRESULT OnBeforeAdd( StoredType* pVal);
   virtual HRESULT OnAfterAdd(StoredType* pVal, CollectionIndexType idx);
   virtual HRESULT OnBeforeRemove( StoredType* pVal, CollectionIndexType idx);
   virtual HRESULT OnAfterRemove( CollectionIndexType idx);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILibraryMgr
public:
   STDMETHOD(get__Enum)(/*[out,retval]*/ IEnumLibrary** ppenum);
//	STDMETHOD(Clear)();
	STDMETHOD(get_Item)(/*[in]*/ BSTR name, /*[out, retval]*/ ILibrary* *pVal);
//	STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown* *pVal);
//	STDMETHOD(get_Count)(/*[out, retval]*/ Uint32 *pVal);
//	STDMETHOD(RemoveLibrary)(/*[in]*/ BSTR name);
//	STDMETHOD(AddLibrary)(/*[in]*/ ILibrary* newLibrary);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);

// ILibraryEvents
public:
   STDMETHOD(OnNameChanged)(/*[in]*/ BSTR oldName,/*[in]*/ BSTR newName);
   STDMETHOD(OnLibraryChanged)(/*[in]*/ ILibrary* lib);
   STDMETHOD(OnEntryNameChanged)(/*[in]*/ ILibrary* lib,/*[in]*/ BSTR oldName,/*[in]*/ BSTR newName);
   STDMETHOD(OnEntryChanged)(/*[in]*/ ILibrary* lib,/*[in]*/ ILibraryEntry* entry);


// ISupportDocUnitSystem
public:
   STDMETHOD(putref_UnitSystem)(IDocUnitSystem* unitSystem);

// ISupportTransactions
public:
   STDMETHOD(putref_TransactionMgr)(/*[in]*/ITransactionMgr* txnMgr);

private:
   CComBSTR m_bstrName;
};

#endif //__LIBRARYMGR_H_
