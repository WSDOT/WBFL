///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2024  Washington State Department of Transportation
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

// LoadingCollection.h : Declaration of the CLoadingCollection

#ifndef __LoadingCollection_H_
#define __LoadingCollection_H_
#pragma once

#include "resource.h"       // main symbols

#include "Fem2dCollections.h"
#include "CircularChild.h"
#include "Loading.h"

using LoadingCollImpl = CModelCollection<IFem2dLoadingCollection, IFem2dLoading, CLoading, IFem2dEnumLoading, &IID_IFem2dEnumLoading,LoadCaseIDType>;

/////////////////////////////////////////////////////////////////////////////
// CLoadingCollection
class ATL_NO_VTABLE CLoadingCollection : 
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
   // public CComRefCountTracer<CLoadingCollection,CCircularChild<IFem2dModel, CComSingleThreadModel> >,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CLoadingCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public LoadingCollImpl
{
public:
   CLoadingCollection()
   {}

   virtual ~CLoadingCollection()
   {}

   // IMPORTANT!!!
   // OnCreate must be called once and only once by creator
   void OnCreate(IFem2dModel* pModel, ModelEvents* pEvents);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadingCollection)
	COM_INTERFACE_ENTRY(IFem2dLoadingCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IFem2dLoadingCollection
public:
	STDMETHOD(Create)(/*[in]*/LoadCaseIDType ID,/*[out,retval]*/IFem2dLoading* *ppLoading) override;
	STDMETHOD(Remove)(/*[in]*/IndexType IDorIndex, /*[in]*/Fem2dAccessType AccessMethod,/*[out,retval]*/LoadCaseIDType* pid) override;
	STDMETHOD(RemoveIDLessThan)(/*[in]*/LoadCaseIDType id) override;
	STDMETHOD(Clear)() override;
};

#endif //__LoadingCollection_H_
