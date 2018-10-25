#if !defined(AFX_EAFREPORTVIEW_H__AA94BED5_010C_407C_9FE3_B3DB15B55D37__INCLUDED_)
#define AFX_EAFREPORTVIEW_H__AA94BED5_010C_407C_9FE3_B3DB15B55D37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// eafreportview.h : header file
//
#include <EAF\EAFExp.h>
#include <boost\shared_ptr.hpp>

class CReportSpecification;
class CReportSpecificationBuilder;
class CReportBrowser;

/////////////////////////////////////////////////////////////////////////////
// CEAFReportView view

class EAFCLASS CEAFReportView : public CView
{
protected:
	CEAFReportView();           // protected constructor used by dynamic creation
	DECLARE_DYNAMIC(CEAFReportView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFReportView)
   public:
   virtual void OnInitialUpdate();
   virtual void OnUpdate(CView* pSender,LPARAM lHint,CObject* pHint);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL
	virtual void OnDrawNoBrowser(CDC* pDC);      // overridden to draw this view

// Implementation
protected:
	virtual ~CEAFReportView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   virtual boost::shared_ptr<CReportSpecification> CreateReportSpecification() = 0;

   // If you aren't using CEAFBrokerDocument and the Agent/Broker framework
   // override this method with a different implementation
   virtual boost::shared_ptr<CReportBrowser> CreateReportBrowser();

   virtual void RefreshReport();

   virtual CSize GetBrowserSize(UINT nType, int cx, int cy);

	// Generated message map functions
protected:
	//{{AFX_MSG(CEAFReportView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnFilePrint();
   afx_msg void OnUpdateFilePrint(CCmdUI* pUpdate);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
   bool m_bInitialUpdate;

   boost::shared_ptr<CReportBrowser> m_pReportBrowser;
   boost::shared_ptr<CReportSpecification> m_pReportSpec;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EAFREPORTVIEW_H__AA94BED5_010C_407C_9FE3_B3DB15B55D37__INCLUDED_)
