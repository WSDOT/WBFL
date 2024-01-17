///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
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

// ProgressMonitorWindow.cpp : Implementation of CProgressMonitorWindow
#include "stdafx.h"
#include "WBFLTools.h"
#include "ProgressMonitorWindow.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressMonitorWindow

STDMETHODIMP CProgressMonitorWindow::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IProgressMonitorWindow
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CProgressMonitorWindow::CProgressMonitorWindow():
m_IsFileOpen(false)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
   AfxOleLockApp();
}

CProgressMonitorWindow::~CProgressMonitorWindow()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
   AfxOleUnlockApp();
}

HRESULT CProgressMonitorWindow::FinalConstruct()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

   // dialog must be created in the current context, or problems
   m_pDlg = std::make_unique<CProgressMonitorDlg>();

   if (m_pDlg.get() != nullptr)
      return S_OK;
   else
      return E_POINTER;
}

void CProgressMonitorWindow::FinalRelease()
{
   if ( m_pDlg->GetSafeHwnd() )
   {
      Hide();
   }
}

STDMETHODIMP CProgressMonitorWindow::put_GaugeValue(/*[in]*/long cookie, /*[in]*/ long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

   m_pDlg->SetProgressValue(newVal);

   if (m_IsFileOpen)
   {
      m_FileStream << "("<<cookie<<")>>Gauge value set to "<< newVal<<std::endl;
   }

   m_pDlg->PumpMessage();

   return S_OK;
}
STDMETHODIMP CProgressMonitorWindow::put_Message(/*[in]*/long cookie, /*[in]*/BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
   m_pDlg->SetMessage(newVal);

   if (m_IsFileOpen)
   {
      CString msg(newVal);
      m_FileStream << "("<<cookie<<")>>Msg: "<<(LPCTSTR)msg<<std::endl;
   }

   m_pDlg->PumpMessage();

   return S_OK;
}

STDMETHODIMP CProgressMonitorWindow::get_WasCancelled(/*[out, retval]*/ VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

   // pump the message que every chance we get so our dialog is more responsive.
   m_pDlg->PumpMessage();

   *pVal = m_pDlg->m_WasCancelled;

   if (m_IsFileOpen)
   {
      m_FileStream << ">>Cancel Queried - value was "<<(*pVal==VARIANT_FALSE?"False":"True")<<std::endl;
   }

   return S_OK;
}

STDMETHODIMP CProgressMonitorWindow::Show(BSTR msg,HWND hParent)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if ( hParent )
      m_wndParent.Attach(hParent);

   // create and show our modeless dialog
   CString cmsg(msg);
   m_pDlg->Create( IDD_PROGRESSMONITORDLG, &m_wndParent );
   m_pDlg->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
   m_pDlg->m_MessageCtl.SetWindowText(cmsg);

   if (m_IsFileOpen)
   {
      m_FileStream << ">>Show called: HasCancel="<<(m_pDlg->m_HasCancel==VARIANT_FALSE?"false":"true")<<", HasGauge="<<(m_pDlg->m_HasGauge==VARIANT_FALSE?"false":"true")<<std::endl;
   }

	return S_OK;
}

STDMETHODIMP CProgressMonitorWindow::Hide()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_pDlg->DestroyWindow();

   if (m_IsFileOpen)
   {
      m_FileStream << ">>Hide called"<<std::endl;
   }

   if ( m_wndParent.GetSafeHwnd() )
   {
      m_wndParent.SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
   }

   m_wndParent.Detach();

	return S_OK;
}

STDMETHODIMP CProgressMonitorWindow::Close()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_pDlg->Close();

   VARIANT_BOOL bClosed = VARIANT_FALSE;

   // wait until the dialog is closed
   while ( bClosed == VARIANT_FALSE )
   {
      m_pDlg->PumpMessage();
      bClosed = m_pDlg->m_WasCancelled;
   }

   m_pDlg->DestroyWindow();

   if (m_IsFileOpen)
   {
      m_FileStream << ">>Close called"<<std::endl;
   }

   if ( m_wndParent.GetSafeHwnd() )
   {
      m_wndParent.SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
   }

   m_wndParent.Detach();

	return S_OK;
}

STDMETHODIMP CProgressMonitorWindow::get_HasCancel(VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   *pVal = m_pDlg->m_HasCancel;
   return S_OK;
}

STDMETHODIMP CProgressMonitorWindow::put_HasCancel(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   m_pDlg->m_HasCancel = newVal;
   return S_OK;
}


STDMETHODIMP CProgressMonitorWindow::get_HasGauge(VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   *pVal = m_pDlg->m_HasGauge;
	return S_OK;
}

STDMETHODIMP CProgressMonitorWindow::put_HasGauge(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   m_pDlg->m_HasGauge = newVal;
	return S_OK;
}

// ILogProgressToFile
STDMETHODIMP CProgressMonitorWindow::OpenLogFile(BSTR fileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

   try
   {
      if (m_FileStream.is_open())
      {
         m_FileStream.close();
      }

      CString file_name(fileName);
      if (file_name.GetLength()==0)
      {
         return E_INVALIDARG;
      }

      m_FileStream.open((LPCTSTR)file_name);
      if (m_FileStream.is_open())
      {
         m_IsFileOpen = true;
      }
      else
      {
         return E_FAIL;
      }
   }
   catch(...)
   {
      ATLASSERT(false);
      return E_FAIL;
   }

   return S_OK;
}

STDMETHODIMP CProgressMonitorWindow::CloseLogFile()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

   try
   {
      if (m_FileStream.is_open())
      {
         m_FileStream.close();
         m_IsFileOpen = false;
      }
      else
      {
         ATLASSERT(false); // trying to close a file that was never opened?
      }
   }
   catch(...)
   {
      ATLASSERT(false);
      return E_FAIL;
   }

   return S_OK;
}