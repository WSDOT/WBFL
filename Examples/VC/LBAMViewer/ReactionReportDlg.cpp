// ReactionReportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lbamviewer.h"
#include "ReactionReportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static DWORD CALLBACK StreamInCtrl(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb )
{
   CString* pstr = (CString*)dwCookie;

   long leng = pstr->GetLength();
   if ( leng < cb )
   {
      *pcb = leng;
      memcpy( pbBuff, (LPCSTR)*pstr, *pcb );
      pstr->Empty();
   }
   else
   {
      *pcb = cb;
      memcpy( pbBuff, (LPCSTR)*pstr, *pcb );
      *pstr = pstr->Right( leng - cb );
   }

   return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CReactionReportDlg dialog


CReactionReportDlg::CReactionReportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReactionReportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReactionReportDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CReactionReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReactionReportDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReactionReportDlg, CDialog)
	//{{AFX_MSG_MAP(CReactionReportDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReactionReportDlg message handlers

BOOL CReactionReportDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();


   CRichEditCtrl* pLabel = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT1);
   ASSERT( pLabel );
   
   CString str(m_Stream.str().c_str());
   EDITSTREAM es;
   es.dwCookie = (DWORD)(&str);
   es.dwError = 0;
   es.pfnCallback = StreamInCtrl;
   long nc = pLabel->StreamIn( SF_RTF, es );

   pLabel->SetBackgroundColor(FALSE, GetSysColor(COLOR_3DFACE) );
   pLabel->SetReadOnly(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
