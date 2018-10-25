// FileNewDlgDoc.h : interface of the CFileNewDlgDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILENEWDLGDOC_H__BD01DE7F_5A3D_11D2_9D69_00609710E6CE__INCLUDED_)
#define AFX_FILENEWDLGDOC_H__BD01DE7F_5A3D_11D2_9D69_00609710E6CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CFileNewDlgDoc : public CDocument
{
protected: // create from serialization only
	CFileNewDlgDoc();
	DECLARE_DYNCREATE(CFileNewDlgDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileNewDlgDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFileNewDlgDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFileNewDlgDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILENEWDLGDOC_H__BD01DE7F_5A3D_11D2_9D69_00609710E6CE__INCLUDED_)
