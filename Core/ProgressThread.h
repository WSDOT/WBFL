#pragma once

#include "ProgressDlg.h"

// CProgressThread

class CProgressThread : public CWinThread
{
	DECLARE_DYNCREATE(CProgressThread)

protected:
	CProgressThread();           // protected constructor used by dynamic creation
	virtual ~CProgressThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

   virtual BOOL OnIdle(LONG lCount);

   void EndThread();

   HRESULT CreateProgressWindow(DWORD dwMask,UINT nDelay);

   void Init(short begin, short end, short inc);
   void Increment();
   void UpdateMessage( LPCTSTR msg);
   BOOL EnableCancel();
   void EnableCancel(BOOL bEnable);
   BOOL Continue();
   void DestroyProgressWindow();

protected:
   CProgressDlg m_ProgressDlg;
   BOOL m_bCancelEnabled;
   BOOL m_bTerminate;

	DECLARE_MESSAGE_MAP()
};


