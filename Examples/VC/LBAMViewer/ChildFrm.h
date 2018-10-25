// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////
#include <map>

#if !defined(AFX_CHILDFRM_H__1C0C4772_4920_445B_B485_FAB7D6F2637F__INCLUDED_)
#define AFX_CHILDFRM_H__1C0C4772_4920_445B_B485_FAB7D6F2637F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class iDataSetBuilder;

class CChildFrame : 
public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:
   CSplitterWnd m_Splitter;

// Operations
public:
   void ClearDataSetBuilders(bool doUpdate);
   void AddDataSetBuilder(long key, iDataSetBuilder* bldr, bool doUpdate);
   void RemoveDataSetBuilder(long key, bool doUpdate);
   long GetNumDataSetBuilders();
   iDataSetBuilder* GetDataSetBuilder(long idx);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

   DECLARE_INTERFACE_MAP()

   BEGIN_INTERFACE_PART(LiveLoadEvents,ILiveLoadConfigurationEvents)
      STDMETHOD_(HRESULT,OnLiveLoadConfigurationChanged)(ILiveLoadConfiguration* placement);
   END_INTERFACE_PART(LiveLoadEvents)


// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
   afx_msg void OnMDIActivate( BOOL, CWnd*, CWnd* );

	DECLARE_MESSAGE_MAP()

   // set up dispatch interface so we can listen to IDispatch-based connection points
//   LPUNKNOWN GetInterfaceHook(const void*);

   DECLARE_DISPATCH_MAP()

    // Generated OLE dispatch map functions
    //{{AFX_DISPATCH(AClassWithAutomation)
    //}}AFX_DISPATCH
 
private:
   typedef std::map<long,iDataSetBuilder*>     DataSetBuilderContainer;
   typedef DataSetBuilderContainer::iterator   DataSetBuilderIterator;
   typedef DataSetBuilderContainer::value_type DataSetBuilderValueType;
   DataSetBuilderContainer  m_DataSetBuilders;

   std::map<long,long> m_PlacementCookies;

   bool m_EventBlocker;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__1C0C4772_4920_445B_B485_FAB7D6F2637F__INCLUDED_)
