// EAFStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include <EAF\EAFStatusBar.h>

#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CEAFStatusBar

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
   ID_INDICATOR_MODIFIED,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

IMPLEMENT_DYNAMIC(CEAFStatusBar, CStatusBar)

CEAFStatusBar::CEAFStatusBar()
{

}

CEAFStatusBar::~CEAFStatusBar()
{
}


BEGIN_MESSAGE_MAP(CEAFStatusBar, CStatusBar)
END_MESSAGE_MAP()



// CEAFStatusBar message handlers



BOOL CEAFStatusBar::Create(CWnd* pParentWnd, DWORD dwStyle , UINT nID)
{
   BOOL bResult = CStatusBar::Create(pParentWnd, dwStyle, nID);
   if ( !bResult )
      return bResult;

   bResult = SetIndicators(indicators,sizeof(indicators)/sizeof(UINT));
   return bResult;
}

void CEAFStatusBar::EnableModifiedFlag(BOOL bEnable)
{
   SetPaneStyle(GetModifiedPane(), bEnable ? SBPS_NORMAL : SBPS_DISABLED );
}

int CEAFStatusBar::GetModifiedPane()
{
   return 1;
}
