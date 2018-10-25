///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2012  Washington State Department of Transportation
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

// ErrorLog.h : Declaration of the CErrorLog

#ifndef __ERRORLOG_H_
#define __ERRORLOG_H_

#include "resource.h"       // main symbols
#include <vector>
#include <fstream>
#include <boost\shared_ptr.hpp>

/////////////////////////////////////////////////////////////////////////////
// CErrorLog
class ATL_NO_VTABLE CErrorLog : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CErrorLog, &CLSID_WBFLErrorLog>,
   public IObjectSafetyImpl<CErrorLog,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IWBFLErrorLog
{
public:
	CErrorLog()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ERRORLOG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CErrorLog)
	COM_INTERFACE_ENTRY(IWBFLErrorLog)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()


// IWBFLErrorLog
public:
   STDMETHOD(Open)(/*[in]*/ BSTR fileName,/*[out,retval]*/ DWORD* dwCookie);
   STDMETHOD(LogMessage)(/*[in]*/DWORD dwCookie,/*[in]*/ BSTR msg);
   STDMETHOD(Close)(/*[in]*/ DWORD dwCookie);

private:
   std::vector<boost::shared_ptr<std::_tofstream> > m_LogFiles;
};

#endif //__ERRORLOG_H_
