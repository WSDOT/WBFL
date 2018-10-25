#ifndef INCLUDED_EAFSTATUSBAR_H_
#define INCLUDED_EAFSTATUSBAR_H_

#pragma once


// CEAFStatusBar

#include <EAF\EAFExp.h>

class EAFCLASS CEAFStatusBar : public CStatusBar
{
	DECLARE_DYNAMIC(CEAFStatusBar)

public:
	CEAFStatusBar();
	virtual ~CEAFStatusBar();

   /// Enables/disables the "Modified" flag on the status bar
   virtual void EnableModifiedFlag(BOOL bEnable);

protected:
	DECLARE_MESSAGE_MAP()

   /// Returns the pane index for the "Modified" flag
   virtual int GetModifiedPane();

public:
   virtual BOOL Create(CWnd* pParentWnd, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, UINT nID = AFX_IDW_STATUS_BAR);
};


#endif // INCLUDED_EAFSTATUSBAR_H_