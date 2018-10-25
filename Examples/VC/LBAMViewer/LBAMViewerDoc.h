// LBAMViewerDoc.h : interface of the CLBAMViewerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LBAMVIEWERDOC_H__F8C27425_F157_4AB0_B6CB_170D2BFF1E0F__INCLUDED_)
#define AFX_LBAMVIEWERDOC_H__F8C27425_F157_4AB0_B6CB_170D2BFF1E0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Hints.h"

class CLBAMViewerDoc : public CDocument
{
protected: // create from serialization only
	CLBAMViewerDoc();
	DECLARE_DYNCREATE(CLBAMViewerDoc)

// Attributes
public:
// Attributes
public:
   CComPtr<ILBAMModel>                    m_pModel;
   CComPtr<ILBAMAnalysisEngine>           m_pLBAMAnalysisEngine;

   CComPtr<IProgressMonitorWindow>           m_pProgressMonitorWindow;
   long                                      m_LoadGroupCookie;
   long                                      m_LiveLoadCookie;
   long                                      m_LoadCombinationCookie;

   enum ResponseType {rtFx, rtFy, rtMz, rtDx, rtDy, rtRz, rtStress};
protected:
	CString m_CurrentStage;

   ResponseType m_ResponseType;
   BOOL m_Cumulative;
   BOOL m_ShowGrid;
   BOOL m_ShowInternalPois;

protected:
   DWORD m_dwCookie;

// Operations
public:
   void SetStage(CString& stage);
   CString GetStage();

   ResponseType GetResponseType();
   void SetResponseType(ResponseType type);

   BOOL GetAccumulateResults();
   void SetAccumulateResults(BOOL doAccumulate);

   BOOL GetShowGrid();
   void SetShowGrid(BOOL doShow);

   BOOL GetShowInternalPOIs();
   void SetShowInternalPOIs(BOOL doShow);



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLBAMViewerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLBAMViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
   void CreateDocument();
   void BlastDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CLBAMViewerDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CLBAMViewerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
   LPUNKNOWN GetInterfaceHook(const void*);

   DECLARE_DISPATCH_MAP()
   HRESULT OnModelChanged(ILBAMModel * me, ChangeType change);


	DECLARE_INTERFACE_MAP()


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LBAMVIEWERDOC_H__F8C27425_F157_4AB0_B6CB_170D2BFF1E0F__INCLUDED_)
