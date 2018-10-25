// LBAMViewerDoc.cpp : implementation of the CLBAMViewerDoc class
//

#include "stdafx.h"
#include "LBAMViewer.h"

#include "LBAMViewerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLBAMViewerDoc

IMPLEMENT_DYNCREATE(CLBAMViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CLBAMViewerDoc, CDocument)
	//{{AFX_MSG_MAP(CLBAMViewerDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLBAMViewerDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CLBAMViewerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
   DISP_FUNCTION(CLBAMViewerDoc,"OnModelChanged",OnModelChanged,VT_I4,VTS_UNKNOWN VTS_I2)

END_DISPATCH_MAP()

// Note: we add support for IID_ILBAMViewer to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {66FA1CB3-2031-49DA-B8BC-A316342E33DC}
static const IID IID_ILBAMViewer =
{ 0x66fa1cb3, 0x2031, 0x49da, { 0xb8, 0xbc, 0xa3, 0x16, 0x34, 0x2e, 0x33, 0xdc } };

BEGIN_INTERFACE_MAP(CLBAMViewerDoc, CDocument)
	INTERFACE_PART(CLBAMViewerDoc, IID_ILBAMViewer, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLBAMViewerDoc construction/destruction

CLBAMViewerDoc::CLBAMViewerDoc():
m_ResponseType(rtMz),
m_Cumulative(FALSE),
m_ShowGrid(FALSE),
m_ShowInternalPois(TRUE),
m_LoadGroupCookie(1),
m_LiveLoadCookie(2),
m_LoadCombinationCookie(3)
{
	EnableAutomation();

	AfxOleLockApp();
}

CLBAMViewerDoc::~CLBAMViewerDoc()
{
	AfxOleUnlockApp();
}

BOOL CLBAMViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

   CreateDocument();

	return TRUE;
}

LPUNKNOWN CLBAMViewerDoc::GetInterfaceHook(const void* piid)
{
   if ( ::IsEqualIID(__uuidof(ILBAMModelEvents), *(IID*)piid) )
      return GetInterface(&IID_IUnknown);
   else
      return NULL;
}


void CLBAMViewerDoc::CreateDocument()
{
   HRESULT hr;

   if (m_pModel)
      BlastDocument();

   // create an empty model
   m_pModel.CoCreateInstance(CLSID_LBAMModel);
   IUnknown* pUnk = GetInterface(&IID_IUnknown);
//   BOOL bst = AfxConnectionAdvise(m_pModel, IID_ILBAMModelEvents,pUnk,TRUE,&m_dwCookie);
//   ATLASSERT(bst==0);

   // set up analysis engines
   hr = m_pLBAMAnalysisEngine.CoCreateInstance(CLSID_LBAMAnalysisEngine);
   ATLASSERT(SUCCEEDED(hr));

//   hr = m_pLBAMAnalysisEngine->Initialize(m_pModel, atForce);
//   ATLASSERT(SUCCEEDED(hr));
   CComPtr<IEnvelopedVehicularResponse> envelopedVehicularResponse;
#if defined _USE_ORIGINAL_LIVELOADER
   envelopedVehicularResponse.CoCreateInstance(CLSID_BruteForceVehicularResponse);
#else
   envelopedVehicularResponse.CoCreateInstance(CLSID_BruteForceVehicularResponse2);
#endif

   // initialize the engine with default values (NULL), except for the vehicular response enveloper
   m_pLBAMAnalysisEngine->InitializeEx(m_pModel,atForce,
                                       NULL, // load group response
                                       NULL, // influence line response
                                       NULL, // analysis pois
                                       NULL, // basic vehicular response
                                       NULL, // live load model response
                                       envelopedVehicularResponse,
                                       NULL, // load case response
                                       NULL, // load combination response
                                       NULL, // concurrent load combination response
                                       NULL, // live load negative moment response
                                       NULL); // contraflexure response

   // create and wire up progress monitoring window
   hr = m_pProgressMonitorWindow.CoCreateInstance(CLSID_ProgressMonitorWindow);
   ATLASSERT(SUCCEEDED(hr));

   CComQIPtr<IProgressMonitor> ipm(m_pProgressMonitorWindow);

   // engine has its own interface for wiring up progress monitoring 
   CComQIPtr<ISupportProgressMonitorForEngine> ispme(m_pLBAMAnalysisEngine);
   hr = ispme->InitializeProgressMonitor4E(ipm, m_LoadGroupCookie, m_LiveLoadCookie, m_LoadCombinationCookie);
   ATLASSERT(SUCCEEDED(hr));
}

void CLBAMViewerDoc::BlastDocument()
{
   if (m_pModel)
   {
      IUnknown* pUnk = GetInterface(&IID_IUnknown);
//      BOOL bst = AfxConnectionUnadvise(m_pModel, IID_ILBAMModelEvents, pUnk,TRUE,m_dwCookie);
//      ATLASSERT(bst==0);
      m_pModel = NULL;
      m_pLBAMAnalysisEngine=NULL;
   }
}


/////////////////////////////////////////////////////////////////////////////
// CLBAMViewerDoc serialization

void CLBAMViewerDoc::Serialize(CArchive& ar)
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
// CLBAMViewerDoc diagnostics

#ifdef _DEBUG
void CLBAMViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLBAMViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLBAMViewerDoc commands


BOOL CLBAMViewerDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
   HRESULT hr;
//	if (!CDocument::OnOpenDocument(lpszPathName))
//		return FALSE;
   CreateDocument();
	
   CComPtr<IStructuredLoad2> pLoad;
   pLoad.CoCreateInstance(CLSID_StructuredLoad2);

   CComPtr<IStructuredStorage2> pSS;
   m_pModel->QueryInterface(&pSS);

   hr = pLoad->Open(CComBSTR(lpszPathName));
   if (FAILED(hr))
   {
      AfxMessageBox("Error Opening File - Probably doesn't exist", MB_OK||MB_ICONEXCLAMATION);
      return FALSE;
   }

   pSS->Load(pLoad);

   pLoad->Close();
	
   // no stages are selected yet - select first one
   CComPtr<IStages> stages;
   hr = m_pModel->get_Stages(&stages);
   StageIndexType stgcnt;
   hr = stages->get_Count(&stgcnt);
   if (stgcnt >0)
   {
      CComPtr<IStage> stage;
      hr = stages->get_Item(0,&stage);
      CComBSTR name;
      hr = stage->get_Name(&name);
      m_CurrentStage = CString(name);
   }
   else
   {
      // MessageBox("No Stages exist for LBAM. There must be at least one","Error", MB_OK||MB_ICONEXCLAMATION);
      return FALSE;
   }

   m_ResponseType = rtMz;
   m_Cumulative = FALSE;

	return TRUE;
}

BOOL CLBAMViewerDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
   CComPtr<IStructuredSave2> pSave;
   pSave.CoCreateInstance(CLSID_StructuredSave2);
   pSave->Open(_bstr_t(lpszPathName));

   CComPtr<IStructuredStorage2> pSS;
   m_pModel->QueryInterface(&pSS);
   pSS->Save(pSave);

   pSave->Close();

   SetModifiedFlag(FALSE);

   return TRUE;
}

HRESULT CLBAMViewerDoc::OnModelChanged(ILBAMModel * me,  ChangeType change)
{
   // let any change cause a redraw for now
   SetModifiedFlag(TRUE);
   UpdateAllViews(0,1,0);
   return S_OK;
}

void CLBAMViewerDoc::OnCloseDocument() 
{
   BlastDocument();
	
	CDocument::OnCloseDocument();
}

void CLBAMViewerDoc::SetStage(CString& stage)
{
   if (stage != m_CurrentStage)
   {
      m_CurrentStage = stage;

      this->UpdateAllViews(0, HINT_STAGE_CHG, 0);
   }
}

CString CLBAMViewerDoc::GetStage()
{
   return m_CurrentStage;
}

CLBAMViewerDoc::ResponseType CLBAMViewerDoc::GetResponseType()
{
   return m_ResponseType;
}

void CLBAMViewerDoc::SetResponseType(ResponseType type)
{
   if (type != m_ResponseType)
   {
      m_ResponseType = type;

      this->UpdateAllViews(0, LOAD_SELECTED_HINT, 0);
   }
}

BOOL CLBAMViewerDoc::GetAccumulateResults()
{
   return m_Cumulative;
}

void CLBAMViewerDoc::SetAccumulateResults(BOOL doAccumulate)
{
   if (doAccumulate != m_Cumulative)
   {
      m_Cumulative = doAccumulate;

      this->UpdateAllViews(0, LOAD_SELECTED_HINT, 0);
   }
}

BOOL CLBAMViewerDoc::GetShowGrid()
{
   return m_ShowGrid;
}

void CLBAMViewerDoc::SetShowGrid(BOOL doShowGrid)
{
   if (doShowGrid != m_ShowGrid)
   {
      m_ShowGrid = doShowGrid;

      this->UpdateAllViews(0, GRAPH_SETTING_HINT, 0);
   }
}

BOOL CLBAMViewerDoc::GetShowInternalPOIs()
{
   return m_ShowInternalPois;
}

void CLBAMViewerDoc::SetShowInternalPOIs(BOOL doShowInternalPOIs)
{
   if (doShowInternalPOIs != m_ShowInternalPois)
   {
      m_ShowInternalPois = doShowInternalPOIs;

      this->UpdateAllViews(0, 0, 0);
   }
}



