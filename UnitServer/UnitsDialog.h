///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
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

// UnitsDialog.h : Declaration of the CUnitsDialog

#ifndef __UNITSDIALOG_H_
#define __UNITSDIALOG_H_

#include "resource.h"       // main symbols
#include <atlwin.h>
#include <HtmlHelp.h>

/////////////////////////////////////////////////////////////////////////////
// CUnitsDialog
class CUnitsDialog : 
	public CDialogImpl<CUnitsDialog>
{
public:

	CUnitsDialog()
	{
      m_UnitMode = umSI;
      m_bHelp = false;
	}

	~CUnitsDialog()
	{
	}

   void SetUnitMode(UnitModeType um)
   {
      m_UnitMode = um;
   }

   UnitModeType GetUnitMode()
   {
      return m_UnitMode;
   }

   void EnableHelp(LPCTSTR pszFile,long nID)
   {
      m_bHelp = true;
      m_nHelpID = nID;
      m_bstrHelpFile = pszFile;
   }

	enum { IDD = IDD_UNITSDIALOG };

private:
   UnitModeType m_UnitMode;
   bool m_bHelp;
   CComBSTR m_bstrHelpFile;
   long m_nHelpID;

BEGIN_MSG_MAP(CUnitsDialog)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	COMMAND_HANDLER(IDHELP, BN_CLICKED, OnHelp)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
      CheckRadioButton(IDC_SI,IDC_US,m_UnitMode == umSI ? IDC_SI :IDC_US);

      if ( !m_bHelp )
      {
         CWindow wnd(GetDlgItem(IDHELP));
         wnd.ShowWindow( SW_HIDE );
      }
      
		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
      m_UnitMode = IsDlgButtonChecked(IDC_SI) == BST_CHECKED ? umSI : umUS;
		return 0;
	}
	LRESULT OnHelp(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
      USES_CONVERSION;
      HtmlHelp(m_hWnd,OLE2T(m_bstrHelpFile),HH_HELP_CONTEXT,m_nHelpID);
		return 0;
	}
};

#endif //__UNITSDIALOG_H_
