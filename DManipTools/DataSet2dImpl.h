///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2012  Washington State Department of Transportation
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

// DataSet2d.h : Declaration of the CDataSet2dImpl

#ifndef __DATASET2D_H_
#define __DATASET2D_H_
#pragma once

#include "resource.h"       // main symbols
#include <DManipTools\DataSet2d.h>

/////////////////////////////////////////////////////////////////////////////
// CDataSet2dImpl
class ATL_NO_VTABLE CDataSet2dImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDataSet2dImpl, &CLSID_DataSet2d>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CDataSet2dImpl>,
   public iDataSet2d
{
public:
   CDataSet2dImpl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DATASET2D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDataSet2dImpl)
	COM_INTERFACE_ENTRY(iDataSet2d)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDataSet2dImpl)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IDataSet2d
public:
   STDMETHOD_(HRESULT,get_Item)(CollectionIndexType idx, IPoint2d** pVal);
   STDMETHOD_(void,get_Count)(CollectionIndexType *pVal);
   STDMETHOD_(void,Add)(IPoint2d *pVal);
   STDMETHOD_(HRESULT,Insert)(CollectionIndexType index, IPoint2d *pVal);
   STDMETHOD_(HRESULT,Remove)(CollectionIndexType index);
   STDMETHOD_(void,Clear)();
	STDMETHOD(Clone)(/*[out, retval]*/ iDataSet2d** clone);

protected:
   typedef CAdapt<CComPtr<IPoint2d> > ContainerItem;
   typedef std::vector<ContainerItem> ContainerType;
   typedef ContainerType::iterator    ContainerIterator;
   ContainerType m_Container;

};

#endif //__DataSet2d_H_
