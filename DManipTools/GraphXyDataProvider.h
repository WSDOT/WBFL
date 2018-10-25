///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2015  Washington State Department of Transportation
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

// GraphXyDataProvider.h : Declaration of the CGraphXyDataProvider

#ifndef __GraphXyDataProvider_H_
#define __GraphXyDataProvider_H_
#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGraphXyDataProvider
class ATL_NO_VTABLE CGraphXyDataProvider:
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGraphXyDataProvider, &CLSID_GraphXyDataProvider>,
	public ISupportErrorInfo,
   public iGraphXyDataProvider
{
public:
	CGraphXyDataProvider();

DECLARE_REGISTRY_RESOURCEID(IDR_GRAPHXYDATAPROVIDER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGraphXyDataProvider)
   COM_INTERFACE_ENTRY(iGraphXyDataProvider)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

HRESULT FinalConstruct();

// iGraphXyDataProvider
public:
   STDMETHOD_(void,put_DataSet)(iDataSet2d* dataSet);
   STDMETHOD_(void,get_DataSet)(iDataSet2d** dataSet);

   STDMETHOD_(void,put_DataPointFactory)(iDataPointFactory* factory);
   STDMETHOD_(void,get_DataPointFactory)(iDataPointFactory** factory);

private:
   CComPtr<iDataSet2d>          m_DataSet;
   CComPtr<iDataPointFactory>   m_Factory;

};

#endif //__GraphXyDataProvider_H_
