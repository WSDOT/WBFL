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
   std::unique_ptr<WBFL::FEA2D::Model> m_Model;

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

// Generated message map functions
protected:
	//{{AFX_MSG(CFEA2DDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
   // WBFL::FEA2D::Model doesn't fire change notifications itself (unlike
   // the old IFem2dModelEvents connection point) - callers that mutate the
   // model call these directly afterward. OnModelChanged() is for
   // structural changes (joints/members/loadings added or removed);
   // OnLoadingChanged() is for changes confined to one loading's loads.
   void OnModelChanged();
   void OnLoadingChanged(LoadCaseIDType loadingID);
   afx_msg void OnViewModelProperties();
   afx_msg void OnGTStrudl();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

