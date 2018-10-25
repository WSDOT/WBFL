#if !defined(AFX_EVENTTEST_H__39DEBAA2_F13F_11D4_8B90_006097C68A9C__INCLUDED_)
#define AFX_EVENTTEST_H__39DEBAA2_F13F_11D4_8B90_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EventTest.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CEventTest command target

class CEventTest : public CCmdTarget
{
	DECLARE_DYNCREATE(CEventTest)

	CEventTest();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventTest)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CEventTest();

	// Generated message map functions
	//{{AFX_MSG(CEventTest)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CEventTest)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

   BEGIN_INTERFACE_PART(DisplayObjectEvents,IDisplayObjectEvents)
      STDMETHOD(OnLButtonDown)(IDisplayObject* dispObj,UINT nFlags,long x,long y);
      STDMETHOD(OnLButtonDblClk)(IDisplayObject* dispObj,UINT nFlags,long x,long y);
   END_INTERFACE_PART(DisplayObjectEvents)
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVENTTEST_H__39DEBAA2_F13F_11D4_8B90_006097C68A9C__INCLUDED_)
