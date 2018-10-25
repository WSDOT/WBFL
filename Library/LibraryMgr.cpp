///////////////////////////////////////////////////////////////////////
// Library - Framework for libraries
// Copyright © 1999-2011  Washington State Department of Transportation
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

// LibraryMgr.cpp : Implementation of CLibraryMgr
#include "stdafx.h"
#include "WBFLLibrary.h"
#include "LibraryMgr.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class PredLibrary
{
public:
   PredLibrary(BSTR bstrTarget) : m_bstrTarget(bstrTarget) {}
   PredLibrary() {}

   bool operator()(std::pair<unsigned long,CAdapt<CComPtr<ILibrary>>>& item)
   {
      CComPtr<ILibrary> entry(item.second.m_T);

      CComBSTR bstrName;
      entry->get_Name(&bstrName);

      return m_bstrTarget == bstrName;
   };

   bool operator()(std::pair<unsigned long,CAdapt<CComPtr<ILibrary>>>& item1,std::pair<unsigned long,CAdapt<CComPtr<ILibrary>>>& item2) const
   {
      CComPtr<ILibrary> entry1(item1.second.m_T);
      CComPtr<ILibrary> entry2(item2.second.m_T);

      CComBSTR bstrName1;
      entry1->get_Name(&bstrName1);

      CComBSTR bstrName2;
      entry2->get_Name(&bstrName2);

      return bstrName1 < bstrName2;
   }

private:
   CComBSTR m_bstrTarget;
};

/////////////////////////////////////////////////////////////////////////////
// CLibraryMgr

STDMETHODIMP CLibraryMgr::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILibraryMgr
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


HRESULT CLibraryMgr::OnBeforeAdd( StoredType* pVal)
{
   CComPtr<ILibrary> entry(pVal->second.m_T);

   // Setup a connection point on the entry
   DWORD dwCookie;
   HRESULT hr = AtlAdvise(entry,GetUnknown(),IID_ILibraryEvents,&dwCookie);
   ATLASSERT( SUCCEEDED(hr) );
   if ( FAILED(hr) )
      dwCookie = -1;

   pVal->first = dwCookie;


   return S_OK;
}

HRESULT CLibraryMgr::OnAfterAdd(StoredType* pVal, CollectionIndexType idx)
{
   // Give the entry a reference to the transaction server if it supports undo
   CComQIPtr<ISupportTransactions> supportTxns(pVal->second.m_T);
   if ( supportTxns )
   {
      supportTxns->putref_TransactionMgr(m_TxnMgr);
   }

   // GIet the entry a reference to the unit system
   CComQIPtr<ISupportDocUnitSystem> supportDocUnits(pVal->second.m_T);
   if ( supportDocUnits )
   {
      supportDocUnits->putref_UnitSystem(m_UnitSystem);
   }

   // Sort the collection
   std::sort(m_coll.begin(),m_coll.end(),PredLibrary());

   return S_OK;
}

HRESULT CLibraryMgr::OnBeforeRemove( StoredType* pVal, CollectionIndexType idx)
{
   CComPtr<ILibrary> entry(pVal->second.m_T);

   // Setup a connection point on the entry
   DWORD dwCookie = pVal->first;
   if ( 0 <= dwCookie )
   {
      HRESULT hr = AtlUnadvise(GetUnknown(),IID_ILibraryEvents,dwCookie);
      ATLASSERT( SUCCEEDED(hr) );
   }

   return S_OK;
}

HRESULT CLibraryMgr::OnAfterRemove( CollectionIndexType idx)
{

   // Event?
   return S_OK;
}

STDMETHODIMP CLibraryMgr::get_Name(BSTR *pVal)
{
	// TODO: Add your implementation code here
   *pVal = m_bstrName.Copy();

	return S_OK;
}

STDMETHODIMP CLibraryMgr::put_Name(BSTR newVal)
{
	// TODO: Add your implementation code here
   CComBSTR bstrOldName = m_bstrName.Copy();
   m_bstrName = newVal;

   Fire_OnNameChanged(bstrOldName,newVal);

	return S_OK;
}

//STDMETHODIMP CLibraryMgr::AddLibrary(ILibrary *newLibrary)
//{
//   CHECK_IN(newLibrary);
//
//   // Setup connection point
//   DWORD dwCookie;
//   HRESULT hr = AtlAdvise(newLibrary,GetUnknown(),DIID_DLibraryEvents,&dwCookie );
//   ATLASSERT(SUCCEEDED(hr)); 
//   if ( FAILED(hr) )
//      dwCookie = -1;
//
//   // Add library to the collection
//   m_coll.push_back(ItemType(dwCookie,newLibrary));
//
//   // Sort the collection
//   std::sort(m_coll.begin(),m_coll.end(),PredLibrary());
//
//   // Fire event
//   Fire_OnChanged(this);
//
//   return S_OK;
//}
//
//STDMETHODIMP CLibraryMgr::RemoveLibrary(BSTR name)
//{
//   // Search for the library
//   std::vector<ItemType>::iterator found = std::find_if(m_coll.begin(), m_coll.end(),PredLibrary(name));
//   if ( found == m_coll.end() )
//      return E_INVALIDARG; // Library not found
//
//   // Disconnect connection point
//   DWORD dwCookie = (*found).first;
//   CComQIPtr<ILibrary> lib((*found).second.m_T);
//
//   if ( 0 <= dwCookie )
//   {
//      AtlUnadvise(lib,DIID_DLibraryEvents,dwCookie);
//   }
//
//   // Remove library from collection
//   m_coll.erase(found);
//
//   // Fire event
//   Fire_OnChanged(this);
//
//	return S_OK;
//}
//
//STDMETHODIMP CLibraryMgr::get_Count(long *pVal)
//{
//	// TODO: Add your implementation code here
//
//	return S_OK;
//}
//

STDMETHODIMP CLibraryMgr::get_Item(BSTR name, ILibrary **pVal)
{
   CHECK_RETOBJ(pVal);

   std::vector<StoredType>::iterator found = std::find_if(m_coll.begin(), m_coll.end(),PredLibrary(name));
   if ( found == m_coll.end() )
      return E_INVALIDARG;

   CComPtr<ILibrary> lib = (*found).second.m_T;

   *pVal = lib;
   (*pVal)->AddRef();

	return S_OK;
}

//STDMETHODIMP CLibraryMgr::Clear()
//{
//   // Disconnect from all connection points
//   std::vector<StoredType>::iterator begin = m_coll.begin();
//   std::vector<StoredType>::iterator end   = m_coll.end();
//   while ( begin != end )
//   {
//      ItemType& item = *begin++;
//      DWORD dwCookie = item.first;
//      CComQIPtr<ILibrary> lib( item.second.m_T );
//
//      if ( 0 <= dwCookie )
//      {
//         AtlUnadvise(lib,DIID_DLibraryEvents,dwCookie);
//      }
//   }
//
//   // Clear the collection
//   m_coll.clear();
//
//   // Fire an event
//   Fire_OnChanged(this);
//
//	return S_OK;
//}
//
//STDMETHODIMP CLibraryMgr::get__NewEnum(IUnknown **ppenum)
//{
//   typedef _CopyVariantFromInterfacePair<ItemType> _CopyPolicy; // Copy interface (second parameter in ItemType pair) to VARIANT
//   typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, _CopyPolicy, std::vector<ItemType> > Enum;
//   CComObject<Enum>* pEnum;
//   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
//   if ( FAILED(hr) )
//      return hr;
//
//   hr = pEnum->Init( NULL, m_coll );
//   if ( FAILED(hr) )
//      return hr;
//
//   pEnum->QueryInterface( ppenum );
//
//   return S_OK;
//}
//   
STDMETHODIMP CLibraryMgr::get__Enum(IEnumLibrary** ppenum)
{
   return get__EnumElements(ppenum);
//   typedef _CopyInterfacePair<ILibrary,ItemType> _CopyPolicy; // Copy the second parameter in ItemType, which is an ILibrary pointer to an ILibrary pointer
//   typedef CComEnumOnSTL<IEnumLibrary,&IID_IEnumLibrary, ILibrary*, _CopyPolicy, std::vector<ItemType> > Enum;
//   CComObject<Enum>* pEnum;
//   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
//   if ( FAILED(hr) )
//      return hr;
//
//   hr = pEnum->Init( NULL, m_coll );
//   if ( FAILED(hr) )
//      return hr;
//
//   pEnum->QueryInterface( ppenum );
//
//   return S_OK;
}

//////////////////////////////////////////////
// ILibraryEvents
STDMETHODIMP CLibraryMgr::OnNameChanged( BSTR oldName, BSTR newName)
{
   Fire_OnLibraryNameChanged(oldName,newName);
   return S_OK;
}

STDMETHODIMP CLibraryMgr::OnLibraryChanged(ILibrary* lib)
{
   Fire_OnLibraryChanged(lib);
   return S_OK;
}

STDMETHODIMP CLibraryMgr::OnEntryNameChanged(ILibrary* lib,BSTR oldName,BSTR newName)
{
   Fire_OnEntryNameChanged(lib,oldName,newName);
   return S_OK;
}

STDMETHODIMP CLibraryMgr::OnEntryChanged(ILibrary* lib,ILibraryEntry* entry)
{
   Fire_OnEntryChanged(lib,entry);
   return S_OK;
}

///////////////////////////////////////////////////////////
// ISupportDocUnitSystem
STDMETHODIMP CLibraryMgr::putref_UnitSystem(IDocUnitSystem* unitSystem)
{
   // Extend default implementation by assigning the unit system to
   // all entries currently in the library

   HRESULT hr = ISupportDocUnitSystemImpl<&LIBID_WBFLLibrary>::putref_UnitSystem(unitSystem);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IEnumLibrary> enumLib;
   get__Enum(&enumLib);

   CComPtr<ILibrary> lib;
   while ( enumLib->Next(1,&lib,NULL) != S_FALSE )
   {
      CComQIPtr<ISupportDocUnitSystem> supportUnitSystem(lib);
      if ( supportUnitSystem )
      {
         supportUnitSystem->putref_UnitSystem(m_UnitSystem);
      }

      lib.Release();
   }

   return hr;
}

///////////////////////////////////////////////////////////
// ISupportTransactions
STDMETHODIMP CLibraryMgr::putref_TransactionMgr(ITransactionMgr* txnMgr)
{
   // Extend the base class implementation
   HRESULT hr = ISupportTransactionsImpl::putref_TransactionMgr(txnMgr);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IEnumLibrary> enumLib;
   get__Enum(&enumLib);

   CComPtr<ILibrary> lib;
   while ( enumLib->Next(1,&lib,NULL) != S_FALSE )
   {
      CComQIPtr<ISupportTransactions> supportTxns(lib);
      if ( supportTxns )
      {
         supportTxns->putref_TransactionMgr(m_TxnMgr);
      }

      lib.Release();
   }

   return hr;
}
