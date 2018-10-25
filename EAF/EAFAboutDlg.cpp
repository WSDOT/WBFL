// EAFAboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFAboutDlg.h>
#include <EAF\EAFApp.h>
#include <MFCTools\VersionInfo.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CEAFAboutDlg dialog

IMPLEMENT_DYNAMIC(CEAFAboutDlg, CDialog)

CEAFAboutDlg::CEAFAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ABOUTBOX, pParent)
{

}

CEAFAboutDlg::~CEAFAboutDlg()
{
}

void CEAFAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

   DDX_Control(pDX,IDC_PLUGINS,m_PluginList);
}


BEGIN_MESSAGE_MAP(CEAFAboutDlg, CDialog)
   ON_NOTIFY(LVN_ITEMACTIVATE,IDC_PLUGINS,&CEAFAboutDlg::OnSomething)
END_MESSAGE_MAP()


// CEAFAboutDlg message handlers

BOOL CEAFAboutDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   // put the icon in the dialog
   CStatic* pIcon = (CStatic*)GetDlgItem(IDC_APPICON);
   HICON hIcon = GetIconHandle();
   pIcon->SetIcon( hIcon );

   // Get the version information and update the version # and copyright
   SetWindowText( AfxGetAppName() );

   CString strExe = AfxGetApp()->m_pszAppName;
   strExe += ".exe";

   CVersionInfo verInfo;
   verInfo.Load(strExe);
   CString strVersion = verInfo.GetFileVersionAsString();
   CString strCopyright = verInfo.GetLegalCopyright();

   CString str;
   str.Format("Version %s",strVersion);
   GetDlgItem(IDC_VERSION)->SetWindowText(str);
   GetDlgItem(IDC_COPYRIGHT)->SetWindowText(strCopyright);

   // Fill the list control with plugin names
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   CEAFPluginManager* pPluginMgr = pApp->GetPluginManager();
   UINT nPlugins = pPluginMgr->GetPluginCount();
   
   m_ImageList.Create(16,16,ILC_COLOR32,0,nPlugins);
   m_PluginList.SetImageList(&m_ImageList,LVSIL_SMALL);

   DWORD style = m_PluginList.GetExtendedStyle();
   m_PluginList.SetExtendedStyle( style | LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT | LVS_EX_LABELTIP);

   // set up the columns
   CRect rect;
   m_PluginList.GetClientRect(&rect);
   m_PluginList.InsertColumn(0,"Components");
   m_PluginList.SetColumnWidth(0,rect.Width());
   
   //pImageList->Add(hIcon); // for each plugin
   for ( UINT idx = 0; idx < nPlugins; idx++ )
   {
      CComPtr<IEAFAppPlugin> plugin;
      pPluginMgr->GetPlugin(idx,&plugin);
      m_ImageList.Add( plugin->GetIcon() );
      m_PluginList.InsertItem(idx,plugin->GetComponentName(),idx);
   }

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CEAFAboutDlg::OnSomething(NMHDR* pNotifyStruct,LRESULT* pResult)
{
   LPNMITEMACTIVATE pItemActivate = (LPNMITEMACTIVATE)(pNotifyStruct);

   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   CEAFPluginManager* pPluginMgr = pApp->GetPluginManager();

   CComPtr<IEAFAppPlugin> plugin;
   pPluginMgr->GetPlugin( pItemActivate->iItem, &plugin );
   plugin->OnAbout();
}

