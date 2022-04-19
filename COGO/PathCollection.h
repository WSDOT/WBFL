///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// PathCollection.h : Declaration of the CPathCollection

#ifndef __PATHCOLLECTION_H_
#define __PATHCOLLECTION_H_
#pragma once

#include "resource.h"       // main symbols
#include "Collections.h"

class CPathCollection;
typedef PersistentIDCollection<CPathCollection,IPathCollection,&IID_IPathCollection,CogoObjectID,IPath> PathCollectionImpl;

/////////////////////////////////////////////////////////////////////////////
// CPathCollection
class ATL_NO_VTABLE CPathCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CPathCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPathCollection, &CLSID_PathCollection>,
   public PathCollectionImpl
{
public:
   CPathCollection() :
      m_bstrCollectionName("Paths"),
      m_bstrItemName("Path")
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_PATHCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPathCollection)
   COM_INTERFACE_ENTRY(IPathCollection)
   COM_INTERFACE_ENTRY_CHAIN(PathCollectionImpl)
END_COM_MAP()

   void SetCollectionName(BSTR bstrCollectionName) { m_bstrCollectionName = bstrCollectionName; }
   void SetItemName(BSTR bstrItemName) { m_bstrItemName = bstrItemName; }
   CComBSTR GetCollectionName() { return m_bstrCollectionName; }
   CComBSTR GetItemName() { return m_bstrItemName; }

// IPathCollection
public:
//   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
   STDMETHOD(Clone)(/*[out,retval]*/ IPathCollection* *clone) override;
   STDMETHOD(get__EnumPaths)(/*[out,retval]*/ IEnumPaths** ppenum) override;
	STDMETHOD(get_Factory)(/*[out,retval]*/IPathFactory** factory) override;
	STDMETHOD(putref_Factory)(/*[in]*/IPathFactory* factory) override;
//   STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval) override;  
   STDMETHOD(get_Item)(/*[in]*/ CogoObjectID id, /*[out, retval]*/ IPath* *pVal) override;
   STDMETHOD(putref_Item)(/*[in]*/ CogoObjectID id, /*[in]*/ IPath* pVal) override;
   STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
   STDMETHOD(AddEx)(/*[in]*/ CogoObjectID id,/*[in]*/ IPath* newVal) override;
   STDMETHOD(Add)(/*[in]*/ CogoObjectID id,/*[out,retval]*/ IPath* *Path) override;
   STDMETHOD(Remove)(/*[in]*/ CogoObjectID id) override;
   STDMETHOD(Clear)() override;
   STDMETHOD(FindID)(/*[in]*/ IPath* Path,/*[out,retval]*/CogoObjectID* ID) override;
   STDMETHOD(get__EnumIDs)(/*[out,retval]*/ IEnumIDs** ppenum) override;
//	STDMETHOD(get_Factory)(/*[out,retval]*/IPoint2dFactory** factory) override;
//	STDMETHOD(put_Factory)(/*[in]*/IPoint2dFactory* factory) override;
   STDMETHOD(ID)(/*[in]*/ CollectionIndexType index,/*[out,retval]*/ CogoObjectID* ID) override;

private:
   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);
   HRESULT PathNotFound(CogoObjectID id);
   HRESULT PathAlreadyDefined(CogoObjectID id);
   HRESULT PathIDError(CogoObjectID id,UINT nHelpString,HRESULT hRes);

   CComPtr<IPathFactory> m_Factory;

   CComBSTR m_bstrCollectionName;
   CComBSTR m_bstrItemName;
};

#endif //__PATHCOLLECTION_H_
