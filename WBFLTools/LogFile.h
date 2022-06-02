///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2022  Washington State Department of Transportation
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

// LogFile.h : Declaration of the CLogFile

#pragma once

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CLogFile
class ATL_NO_VTABLE CLogFile : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLogFile, &CLSID_LogFile>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CLogFile,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ILogFile
{
public:
   CLogFile()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LOGFILE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLogFile)
	COM_INTERFACE_ENTRY(ILogFile)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

   // ILogFile
public:
   STDMETHOD(Open)(/*[in]*/ LPCTSTR name,/*[out]*/ DWORD* pdwCookie) override;
   STDMETHOD(put_EndLines)(/*[in]*/ BOOL bEndLines) override;
   STDMETHOD(get_EndLines)(/*[out,retval]*/ BOOL* pbEndLines) override;
   STDMETHOD(LogMessage)(/*[in]*/ DWORD dwCookie,/*[in]*/ LPCTSTR msg) override;
   STDMETHOD(Close)(/*[in]*/ DWORD dwCookie) override;

private:
   BOOL m_bEndLines;
   std::vector<std::shared_ptr<std::_tofstream> > m_LogFiles;
};
