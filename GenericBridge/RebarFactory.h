///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2020  Washington State Department of Transportation
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

// RebarFactory.h : Declaration of the CRebarFactory

#ifndef __RebarFactory_H_
#define __RebarFactory_H_

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CRebarFactory
class ATL_NO_VTABLE CRebarFactory : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CRebarFactory,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CRebarFactory, &CLSID_RebarFactory>,
	public ISupportErrorInfo,
	public IRebarFactory,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CRebarFactory,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CRebarFactory()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_REBARFACTORY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRebarFactory)
	COM_INTERFACE_ENTRY(IRebarFactory)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IRebarFactory
public:
   STDMETHOD(CreateRebar)(/*[in]*/ MaterialSpec spec, /*[in]*/ RebarGrade grade, /*[in]*/ BarSize size, /*[in]*/ IUnitConvert* convert,/*[in]*/ StageIndexType stageIdx,/*[out,retval]*/ IRebar** rebar) override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};

#endif //__RebarFactory_H_
