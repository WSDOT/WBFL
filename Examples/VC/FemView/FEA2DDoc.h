// FEA2DDoc.h : interface of the CFEA2DDoc class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

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
public:
   afx_msg void OnViewModelProperties();
   afx_msg void OnGTStrudl();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

