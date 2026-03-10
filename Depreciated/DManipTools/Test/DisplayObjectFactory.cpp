// DisplayObjectFactory.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "DisplayObjectFactory.h"
#include "TestDoc.h"

#include "mfcdual.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayObjectFactory

CDisplayObjectFactory::CDisplayObjectFactory(CTestDoc* pDoc)
{
   m_pDoc = pDoc;
   ::CoCreateInstance(CLSID_DisplayObjectFactory,NULL,CLSCTX_ALL,IID_iDisplayObjectFactory,(void**)&m_Factory);
}


CDisplayObjectFactory::~CDisplayObjectFactory()
{
}




BEGIN_INTERFACE_MAP(CDisplayObjectFactory,CCmdTarget)
   INTERFACE_PART(CDisplayObjectFactory,IID_iDisplayObjectFactory,Factory)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CDisplayObjectFactory,Factory);


/////////////////////////////////////////////////////////////////////////////
// CDisplayObjectFactory message handlers
STDMETHODIMP_(void) CDisplayObjectFactory::XFactory::Create(CLIPFORMAT cfFormat,COleDataObject* pDataObject,iDisplayObject** dispObj)
{
   METHOD_PROLOGUE(CDisplayObjectFactory,Factory);

   pThis->m_Factory->Create(cfFormat,pDataObject,dispObj);
}
