///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
// Copyright © 1999-2019  Washington State Department of Transportation
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

#if !defined(AFX_SYSAGENT_H__99C34AA5_2BE4_11D2_8EB3_006097DF3C68__INCLUDED_)
#define AFX_SYSAGENT_H__99C34AA5_2BE4_11D2_8EB3_006097DF3C68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SysAgent.h : header file
//

#include "ProgressThread.h"


#include <vector>
#include <iostream>
#include <fstream>

#include <memory>

/////////////////////////////////////////////////////////////////////////////
// CSysAgent command target
class ATL_NO_VTABLE CSysAgent : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSysAgent, &CLSID_SysAgent>,
   public IAgentEx,
   public IProgress,
   public ILogFile
{
public:
	CSysAgent();
	virtual ~CSysAgent();

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_SYSAGENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSysAgent)
	COM_INTERFACE_ENTRY(IAgent)
	COM_INTERFACE_ENTRY(IAgentEx)
	COM_INTERFACE_ENTRY(IProgress)
	COM_INTERFACE_ENTRY(ILogFile)
END_COM_MAP()

// IAgentEx
public:
	STDMETHOD(SetBroker)(/*[in]*/ IBroker* pBroker) override;
   STDMETHOD(RegInterfaces)() override;
	STDMETHOD(Init)() override;
	STDMETHOD(Init2)() override;
	STDMETHOD(Reset)() override;
	STDMETHOD(ShutDown)() override;
   STDMETHOD(GetClassID)(CLSID* pCLSID) override;

// IProgress
public:
   STDMETHOD(CreateProgressWindow)(/*[in]*/ DWORD dwMask,/*[in]*/ UINT nDelay) override;
	STDMETHOD(Init)(/*[in]*/ short begin, /*[in]*/ short end, /*[in]*/ short inc) override;
	STDMETHOD(Increment)() override;
	STDMETHOD(UpdateMessage)(/*[in]*/ LPCTSTR msg) override;
	STDMETHOD(Continue)() override;
	STDMETHOD(DestroyProgressWindow)() override;

// ILogFile
public:
   STDMETHOD(Open)(/*[in]*/ LPCTSTR name,/*[out]*/ DWORD* pdwCookie) override;
   STDMETHOD(put_EndLines)(/*[in]*/ BOOL bEndLines) override;
   STDMETHOD(get_EndLines)(/*[out,retval]*/ BOOL* pbEndLines) override;
   STDMETHOD(LogMessage)(/*[in]*/ DWORD dwCookie,/*[in]*/ LPCTSTR msg) override;
   STDMETHOD(Close)(/*[in]*/ DWORD dwCookie) override;

private:
   IBroker* m_pBroker; // weak reference
   CProgressThread* m_pThread;
   Int16 m_cProgressRef; // progress thread ref count
                                            // a progress window instance begins

   HRESULT ValidateThread();

   std::vector<std::_tstring> m_MessageStack;
   std::_tstring m_LastMessage; // most recent message

   BOOL m_bEndLines;
   std::vector<std::shared_ptr<std::_tofstream> > m_LogFiles;
};

OBJECT_ENTRY_AUTO(CLSID_SysAgent,CSysAgent)

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSAGENT_H__99C34AA5_2BE4_11D2_8EB3_006097DF3C68__INCLUDED_)
