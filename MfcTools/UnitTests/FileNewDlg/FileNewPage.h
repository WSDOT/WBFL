#if !defined(AFX_FILENEWPAGE_H__BD01DE8A_5A3D_11D2_9D69_00609710E6CE__INCLUDED_)
#define AFX_FILENEWPAGE_H__BD01DE8A_5A3D_11D2_9D69_00609710E6CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FileNewPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileNewPage dialog

class CFileNewPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFileNewPage)

// Construction
public:
	CFileNewPage();
	~CFileNewPage();

// Dialog Data
   void SetDirectoryAndSuffix(const CString& directoryName, const CString& suffix);
   CString GetDirectoryName() const;
   CString GetSuffix() const;
	//{{AFX_DATA(CFileNewPage)
	enum { IDD = IDD_TEMPLATE_FILE_NEW };
	CListBox	m_FileListBox;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFileNewPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFileNewPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
   CString m_DirectoryName;
   CString m_Suffix;
   CString m_SelectedFile;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILENEWPAGE_H__BD01DE8A_5A3D_11D2_9D69_00609710E6CE__INCLUDED_)
