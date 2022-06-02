///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
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

// UnitsDialog.h : Declaration of the CUnitsDialog

#ifndef __UNITSDIALOG_H_
#define __UNITSDIALOG_H_

#include "resource.h"       // main symbols
#include <atlwin.h>

/////////////////////////////////////////////////////////////////////////////
// CUnitsDialog
class CUnitsDialog : 
	public CDialogImpl<CUnitsDialog>
{
public:

	CUnitsDialog()
	{
      m_UnitMode = umSI;
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

	enum { IDD = IDD_UNITSDIALOG };

private:
   UnitModeType m_UnitMode;

BEGIN_MSG_MAP(CUnitsDialog)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	virtual LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
      CheckRadioButton(IDC_SI,IDC_US,m_UnitMode == umSI ? IDC_SI :IDC_US);
      
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
};

#endif //__UNITSDIALOG_H_
