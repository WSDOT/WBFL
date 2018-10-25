///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

// Material.h : Declaration of the CMaterial

#ifndef __MATERIAL_H_
#define __MATERIAL_H_

#include "resource.h"       // main symbols
#include "GenericBridgeCP.h"


/////////////////////////////////////////////////////////////////////////////
// CMaterial
class ATL_NO_VTABLE CMaterial : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CMaterial,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CMaterial, &CLSID_Material>,
	public ISupportErrorInfo,
	public IMaterial,
   public IStructuredStorage2,
   public CProxyDMaterialEvents< CMaterial >,
   public IConnectionPointContainerImpl<CMaterial>,
   public IObjectSafetyImpl<CMaterial,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CMaterial()
	{
      m_E = 4000;
      m_Density = 0;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_MATERIAL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMaterial)
	COM_INTERFACE_ENTRY(IMaterial)

	COM_INTERFACE_ENTRY(IStructuredStorage2)

	COM_INTERFACE_ENTRY(ISupportErrorInfo)

   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CMaterial)
	CONNECTION_POINT_ENTRY(IID_IMaterialEvents)
END_CONNECTION_POINT_MAP()

private:
   Float64 m_E;
   Float64 m_Density;

   // ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IConcrete
public:
   STDMETHOD(get_E)(/*[out,retval]*/Float64* E);
	STDMETHOD(put_E)(/*[in]*/Float64 E);
	STDMETHOD(get_Density)(/*[out,retval]*/Float64* w);
	STDMETHOD(put_Density)(/*[in]*/Float64 w);
	STDMETHOD(Clone)(/*[out,retval]*/IMaterial** clone);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);
};

#endif //__MATERIAL_H_
