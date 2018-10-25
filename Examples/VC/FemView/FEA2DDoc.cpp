// FEA2DDoc.cpp : implementation of the CFEA2DDoc class
//

#include "stdafx.h"
#include "FEA2D.h"

#include "FEA2DDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFEA2DDoc

IMPLEMENT_DYNCREATE(CFEA2DDoc, CDocument)

BEGIN_MESSAGE_MAP(CFEA2DDoc, CDocument)
	//{{AFX_MSG_MAP(CFEA2DDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFEA2DDoc,CDocument)
   DISP_FUNCTION(CFEA2DDoc,"OnModelChanged",OnModelChanged,VT_EMPTY,VTS_NONE)
   DISP_FUNCTION(CFEA2DDoc,"OnLoadingChanged",OnModelChanged,VT_EMPTY,VTS_I4)
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFEA2DDoc construction/destruction
LPUNKNOWN CFEA2DDoc::GetInterfaceHook(const void* piid)
{
   if ( ::IsEqualIID(__uuidof(IFem2dModelEvents), *(IID*)piid) )
      return GetInterface(&IID_IUnknown);
   else
      return NULL;
}

CFEA2DDoc::CFEA2DDoc()
{
   EnableAutomation();
   m_Model.CoCreateInstance(CLSID_Fem2dModel);
   IUnknown* pUnk = GetInterface(&IID_IUnknown);
   AfxConnectionAdvise(m_Model,__uuidof(IFem2dModelEvents),pUnk,TRUE,&m_dwCookie);
}

CFEA2DDoc::~CFEA2DDoc()
{
   IUnknown* pUnk = GetInterface(&IID_IUnknown);
   AfxConnectionUnadvise(m_Model,__uuidof(IFem2dModelEvents),pUnk,TRUE,m_dwCookie);
}

BOOL CFEA2DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFEA2DDoc serialization

void CFEA2DDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFEA2DDoc diagnostics

#ifdef _DEBUG
void CFEA2DDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFEA2DDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFEA2DDoc commands

BOOL CFEA2DDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
//	if (!CDocument::OnOpenDocument(lpszPathName))
//		return FALSE;
	
	// TODO: Add your specialized creation code here
   CComPtr<IStructuredLoad2> pLoad;
   pLoad.CoCreateInstance(CLSID_StructuredLoad2);

   CComQIPtr<IStructuredStorage2> pSS(m_Model);

   pLoad->Open(CComBSTR(lpszPathName));

   pSS->Load(pLoad);

   pLoad->Close();
	
	return TRUE;
}

BOOL CFEA2DDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
   CComPtr<IStructuredSave2> pSave;
   pSave.CoCreateInstance(CLSID_StructuredSave2);
   pSave->Open(CComBSTR(lpszPathName));

   CComQIPtr<IStructuredStorage2> pSS(m_Model);
   pSS->Save(pSave);

   pSave->Close();

   SetModifiedFlag(FALSE);

   return TRUE;
//	return CDocument::OnSaveDocument(lpszPathName);
}

//STDMETHODIMP CFEA2DDoc::XModelEvents::OnModelChanged()
//{
//   return raw_OnModelChanged();
//}
//
//STDMETHODIMP CFEA2DDoc::XModelEvents::OnLoadingChanged(long id)
//{
//   return raw_OnLoadingChanged(id);
//}
//
//STDMETHODIMP CFEA2DDoc::XModelEvents::raw_OnModelChanged()
//{
//   METHOD_PROLOGUE(CFEA2DDoc,ModelEvents);
//   pThis->SetModifiedFlag(TRUE);
//   pThis->UpdateAllViews(0,1,0);
//   return S_OK;
//}
//
//STDMETHODIMP CFEA2DDoc::XModelEvents::raw_OnLoadingChanged(long id)
//{
//   METHOD_PROLOGUE(CFEA2DDoc,ModelEvents);
//    pThis->SetModifiedFlag(TRUE);
//  pThis->UpdateAllViews(0,2,0);
//   return S_OK;
//}

BOOL CFEA2DDoc::OnModelChanged()
{
   SetModifiedFlag(TRUE);
   UpdateAllViews(0,1,0);
   return S_OK;
}

BOOL CFEA2DDoc::OnLoadingChanged(long id)
{
   SetModifiedFlag(TRUE);
   UpdateAllViews(0,2,0);
   return S_OK;
}
