// FEA2DDoc.h : interface of the CFEA2DDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FEA2DDOC_H__BCB8A0EF_E659_11D4_8B81_006097C68A9C__INCLUDED_)
#define AFX_FEA2DDOC_H__BCB8A0EF_E659_11D4_8B81_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFEA2DDoc : public CDocument
{
protected: // create from serialization only
	CFEA2DDoc();
	DECLARE_DYNCREATE(CFEA2DDoc)


// Attributes
public:
   CComPtr<IFem2dModel> m_Model;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFEA2DDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFEA2DDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
   DWORD m_dwCookie;

// Generated message map functions
protected:
	//{{AFX_MSG(CFEA2DDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
   LPUNKNOWN GetInterfaceHook(const void*);

   DECLARE_DISPATCH_MAP()
   BOOL OnModelChanged();
   BOOL OnLoadingChanged(long loadingID);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FEA2DDOC_H__BCB8A0EF_E659_11D4_8B81_006097C68A9C__INCLUDED_)
