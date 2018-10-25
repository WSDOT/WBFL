// FileNewPage.cpp : implementation file
//

#include "stdafx.h"
#include "filenewdlg.h"
#include "FileNewPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileNewPage property page

IMPLEMENT_DYNCREATE(CFileNewPage, CPropertyPage)

CFileNewPage::CFileNewPage() : CPropertyPage(CFileNewPage::IDD),
m_DirectoryName("."),
m_Suffix("tmp")
{
	//{{AFX_DATA_INIT(CFileNewPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CFileNewPage::~CFileNewPage()
{
}

void CFileNewPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileNewPage)
	DDX_Control(pDX, IDC_FILE_LIST, m_FileListBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileNewPage, CPropertyPage)
	//{{AFX_MSG_MAP(CFileNewPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileNewPage message handlers
void CFileNewPage::SetDirectoryAndSuffix(const CString& directoryName, const CString& suffix)
{
   ASSERT(!directoryName.IsEmpty());
   ASSERT(!suffix.IsEmpty());
   m_DirectoryName = directoryName;
   m_Suffix = suffix;
}

CString CFileNewPage::GetSuffix() const
{
   return m_Suffix;
}

CString CFileNewPage::GetDirectoryName() const
{
   return m_DirectoryName;
}

BOOL CFileNewPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

   // nothing selected
   m_SelectedFile.Empty();

   // fill list box with file names
   CString filespec = m_DirectoryName + CString("\\*.") + m_Suffix;
   CFileFind finder;
   BOOL is_file;
   is_file = finder.FindFirst(filspec);
   while(is_file)
   {
      is_file = finder.FindNext();
      if (is_file)
      {

      }
   }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
