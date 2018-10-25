///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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
#include <map>


/////////////////////////////////////////////////////////////////////////////
// CMaterial
class ATL_NO_VTABLE CMaterial : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CMaterial,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CMaterial, &CLSID_Material>,
	public ISupportErrorInfo,
	public IMaterial,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CMaterial,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CMaterial()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_MATERIAL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMaterial)
	COM_INTERFACE_ENTRY(IMaterial)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   std::map<StageIndexType,Float64> m_E;
   std::map<StageIndexType,Float64> m_Density;

   // ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IConcrete
public:
   STDMETHOD(get_E)(StageIndexType stageIdx,Float64* E) override;
	STDMETHOD(put_E)(StageIndexType stageIdx,Float64 E) override;
	STDMETHOD(get_Density)(StageIndexType stageIdx,Float64* w) override;
	STDMETHOD(put_Density)(StageIndexType stageIdx,Float64 w) override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};

#endif //__MATERIAL_H_
