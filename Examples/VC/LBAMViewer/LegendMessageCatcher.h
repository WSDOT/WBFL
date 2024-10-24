#pragma once


#define MC_MSG_BASE 100
#define MC_MSG_MAX    200

interface iMessageListener
{
	virtual void OnCaughtMessage(int msg) = 0;
};


/////////////////////////////////////////////////////////////////////////////
// CLegendMessageCatcher window
// This class is not a viewable window. It's sole purpose is to catch messages from menus
// created in the DManipTools dll.
class CLegendMessageCatcher : public CWnd
{
	// Construction
public:
	CLegendMessageCatcher(iMessageListener* plistener);

	// Attributes
public:

	// Operations
public:

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CLegendMessageCatcher)
		//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CLegendMessageCatcher();

	// Generated message map functions
	void OnMessageCaught(UINT id);

protected:
	//{{AFX_MSG(CLegendMessageCatcher)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	CLegendMessageCatcher();

	iMessageListener* m_pListener;
};
