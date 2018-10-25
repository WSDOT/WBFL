// ArpNoticeDoc.h : interface of the CArpNoticeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARPNOTICEDOC_H__790C0062_8D43_11D3_89DC_006097C68A9C__INCLUDED_)
#define AFX_ARPNOTICEDOC_H__790C0062_8D43_11D3_89DC_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CArpNoticeDoc : public CDocument
{
protected: // create from serialization only
	CArpNoticeDoc();
	DECLARE_DYNCREATE(CArpNoticeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArpNoticeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CArpNoticeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CArpNoticeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARPNOTICEDOC_H__790C0062_8D43_11D3_89DC_006097C68A9C__INCLUDED_)
