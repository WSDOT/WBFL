// EventTest.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "EventTest.h"

#include "mfcdual.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEventTest

IMPLEMENT_DYNCREATE(CEventTest, CCmdTarget)

CEventTest::CEventTest()
{
	EnableAutomation();
}

CEventTest::~CEventTest()
{
}


void CEventTest::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CEventTest, CCmdTarget)
	//{{AFX_MSG_MAP(CEventTest)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CEventTest, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CEventTest)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IEventTest to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {39DEBAA1-F13F-11D4-8B90-006097C68A9C}
static const IID IID_IEventTest =
{ 0x39debaa1, 0xf13f, 0x11d4, { 0x8b, 0x90, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c } };

BEGIN_INTERFACE_MAP(CEventTest, CCmdTarget)
	INTERFACE_PART(CEventTest, IID_IDisplayObjectEvents, DisplayObjectEvents)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CEventTest,DisplayObjectEvents)

/////////////////////////////////////////////////////////////////////////////
// CEventTest message handlers
STDMETHODIMP CEventTest::XDisplayObjectEvents::OnLButtonDown(IDisplayObject* dispObj,UINT nFlags,long x,long y)
{
   METHOD_PROLOGUE(CEventTest,DisplayObjectEvents);

   AfxMessageBox("Event Received");
   return S_OK;
}

STDMETHODIMP CEventTest::XDisplayObjectEvents::OnLButtonDblClk(IDisplayObject* dispObj,UINT nFlags,long x,long y)
{
   METHOD_PROLOGUE(CEventTest,DisplayObjectEvents);

   AfxMessageBox("Event Received");
   return S_OK;
}
