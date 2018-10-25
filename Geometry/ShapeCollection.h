///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2014  Washington State Department of Transportation
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

// ShapeCollection.h : Declaration of the CShapeCollection

#ifndef __SHAPECOLLECTION_H_
#define __SHAPECOLLECTION_H_

#include "resource.h"       // main symbols
#include "WBFLComCollections.h"

class CShapeCollection;
typedef CComVectorCollection<IShapeCollection,IShape,IEnumShape,&IID_IEnumShape,CollectionIndexType> ShapeVectorImpl;
typedef CPersistentCollection<CShapeCollection,ShapeVectorImpl,CollectionIndexType> PersistentShapeCollection;

/////////////////////////////////////////////////////////////////////////////
// CShapeCollection
class ATL_NO_VTABLE CShapeCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CShapeCollection, &CLSID_ShapeCollection>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CShapeCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public PersistentShapeCollection
{
public:
	CShapeCollection()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SHAPECOLLECTION)

BEGIN_COM_MAP(CShapeCollection)
	COM_INTERFACE_ENTRY(IShapeCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY_CHAIN(PersistentShapeCollection)
END_COM_MAP()

protected:
   CComBSTR GetCollectionName()
   {
      return CComBSTR("ShapeCollection"); // This is the "Unit Name" stored in the persistance stream
   }

public:

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IShapeCollection
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
   STDMETHOD(get__Enum)(/*[out,retval]*/ IEnumShape** ppenum);
//   STDMETHOD(Clear)();
//	STDMETHOD(Remove)(/*[in]*/ CollectionIndexType Index);
//	STDMETHOD(Add)(/*[in]*/ IShape* pPoint);
//	STDMETHOD(get_Item)(CollectionIndexType Index, IShape** pPoint);
////	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
////	STDMETHOD(get__NewEnum)(IUnknown** retval);
   STDMETHOD(get_ShapeProperties)(/*[out,retval]*/IShapeProperties** props);
};

#endif //__SHAPECOLLECTION_H_
