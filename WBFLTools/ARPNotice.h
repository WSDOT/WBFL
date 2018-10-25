///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2017  Washington State Department of Transportation
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

// ARPNotice.h : Declaration of the CARPNotice

#ifndef __ARPNOTICE_H_
#define __ARPNOTICE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CARPNotice
class ATL_NO_VTABLE CARPNotice : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CARPNotice, &CLSID_ARPNotice>,
   public IObjectSafetyImpl<CARPNotice,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IARPNotice
{
public:
	CARPNotice()
	{
      m_bShowAgain = VARIANT_FALSE;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ARPNOTICE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CARPNotice)
	COM_INTERFACE_ENTRY(IARPNotice)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   VARIANT_BOOL m_bShowAgain;

// IARPNotice
public:
	STDMETHOD(get_ShowAgain)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(put_ShowAgain)(/*[in]*/ VARIANT_BOOL newVal) override;
	STDMETHOD(Show)(/*[in]*/ VARIANT_BOOL bGiveChoice,/*[in]*/ LicenseType lt,/*[out,retval]*/ AcceptanceType* accept) override;
};

#endif //__ARPNOTICE_H_
