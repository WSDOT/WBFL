///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

// Pier.h : Declaration of the CPier

#ifndef __PIER_H_
#define __PIER_H_

#include "resource.h"       // main symbols
#include <vector>

class CSpan;

/////////////////////////////////////////////////////////////////////////////
// CPier
// This can be any kind of pier object... pier, bent, temporary support, etc
class ATL_NO_VTABLE CPier : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CPier,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPier, &CLSID_Pier>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPier,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IPier,
   public IStructuredStorage2
{
public:
   CPier()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void Init(IGenericBridge* pBridge,IPierLine* pPierLine);

   static HRESULT ValidateOrientation(BSTR bstrOrientation);
   void SetLongitudinalPierDescription(ILongitudinalPierDescription* cloneLPD); // replaces the default LPD with a clone
   void SetTransversePierDescription(ITransversePierDescription* cloneTPD); // replaces the default TPD with a clone

DECLARE_REGISTRY_RESOURCEID(IDR_PIER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPier)
	COM_INTERFACE_ENTRY(IPier)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   IPierLine* m_pPierLine; // weak reference
   IGenericBridge* m_pBridge; // weak reference to parent

   CComPtr<ILongitudinalPierDescription> m_LongPierDesc;
   CComPtr<ITransversePierDescription> m_TransPierDesc;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPier
public:
   STDMETHOD(get_Station)(/*[out,retval]*/IStation* *station);
	STDMETHOD(get_LongitudinalPierDescription)(/*[out, retval]*/ ILongitudinalPierDescription* *pVal);
   STDMETHOD(get_Direction)(/*[out,retval]*/ IDirection* *direction);
   STDMETHOD(get_SkewAngle)(/*[out,retval]*/ IAngle* *skewAngle);
	STDMETHOD(CreateTransversePierDescription)();
	STDMETHOD(get_TransversePierDescription)(/*[out, retval]*/ ITransversePierDescription* *pVal);
   STDMETHOD(get_Index)(/*[out,retval]*/PierIndexType* pIndex);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);
};

#endif //__PIER_H_
