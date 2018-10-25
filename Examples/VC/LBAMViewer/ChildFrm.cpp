// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "LBAMViewer.h"
#include "LBAMViewerView.h"

#include "LoadSelectTreeView.h"

#include "ChildFrm.h"
#include "MainFrm.h"
#include "DataSetBuilder.h"
#include "mfcdual.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
   ON_WM_MDIACTIVATE( )
END_MESSAGE_MAP()


// This goes in the source code file
 // Note: ClassWizard looks for these comments:
 BEGIN_DISPATCH_MAP(CChildFrame, CCmdTarget)
     //{{AFX_DISPATCH_MAP(AClassWithAutomation)
        // NOTE - the ClassWizard will add and remove mapping macros here.
     //}}AFX_DISPATCH_MAP
 END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CChildFrame,CMDIChildWnd)
   INTERFACE_PART(CChildFrame,IID_ILiveLoadConfigurationEvents,LiveLoadEvents)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CChildFrame,LiveLoadEvents);

/*
LPUNKNOWN CChildFrame::GetInterfaceHook(const void* piid)
{
   if ( ::IsEqualIID(IID_ILiveLoadConfigurationEvents, *(IID*)piid) )
      return GetInterface(&IID_ILiveLoadConfigurationEvents);
   else
      return NULL;
}
*/

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame():
m_EventBlocker(true)
{
   EnableAutomation ();
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers
void CChildFrame::OnMDIActivate( BOOL st, CWnd* pActivateWnd, CWnd* pDeActivateWnd)
{
   if (st)
   {
      // tell mainframe it has to update it's document dependent stuff
      CMainFrame* pmf = dynamic_cast<CMainFrame*>( ::AfxGetMainWnd() );
      ATLASSERT(pmf);

      pmf->UpdateToolBar();
   }
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{

	   if (!m_Splitter.CreateStatic(this,1,2) ||
          !m_Splitter.CreateView(0, 0, RUNTIME_CLASS(CLoadSelectTreeView), CSize(lpcs->cx/5,lpcs->cy), pContext) ||
          !m_Splitter.CreateView(0, 1, RUNTIME_CLASS(CLBAMViewerView), CSize(0,0), pContext))
          return FALSE;

      return TRUE;


	return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}

void CChildFrame::ClearDataSetBuilders(bool doUpdate)
{
   m_DataSetBuilders.clear();
   
   if (doUpdate)
   {
      CLBAMViewerView* vw = (CLBAMViewerView*)m_Splitter.GetPane(0,1);
      vw->OnUpdate(NULL, 0, 0);
   }
}

void CChildFrame::AddDataSetBuilder(IndexType key, iDataSetBuilder* bldr, bool doUpdate)
{
   m_DataSetBuilders.insert(DataSetBuilderValueType(key,bldr));

   // listen to vehicle placement if we have one
   if (bldr->HasTruckPlacement())
   {
      LiveLoadModelType model_type;
      VehicleIndexType vehicle_index;
      CComPtr<ILiveLoadConfiguration> placement;
      bldr->GetTruckInfo(&model_type, &vehicle_index, &placement);

      DWORD cookie;
      IDispatch* pid = GetIDispatch(FALSE);
      if (!AfxConnectionAdvise (placement,
           IID_ILiveLoadConfigurationEvents, pid, FALSE,
           &cookie))
      {
         ATLASSERT(0);
      }

      m_PlacementCookies.insert(std::map<IndexType,DWORD>::value_type(key,cookie));
   }

   if (doUpdate)
   {
      SimpleMutex mutex(m_EventBlocker); // prevent events from firing while update
      CLBAMViewerView* vw = (CLBAMViewerView*)m_Splitter.GetPane(0,1);
      vw->OnUpdate(NULL,0,0);
   }
}

void CChildFrame::RemoveDataSetBuilder(IndexType key, bool doUpdate)
{
   try
   {
      iDataSetBuilder* pbld = m_DataSetBuilders[key];

      // disconnect from placement
      if (pbld->HasTruckPlacement())
      {
         DWORD cookie = m_PlacementCookies[key];

         LiveLoadModelType model_type;
         VehicleIndexType vehicle_index;
         CComPtr<ILiveLoadConfiguration> placement;
         pbld->GetTruckInfo(&model_type, &vehicle_index, &placement);

         IDispatch* pid = GetIDispatch(FALSE);
         AfxConnectionUnadvise (placement, IID_ILiveLoadConfigurationEvents,
                                pid, FALSE, 
                                cookie);

         m_PlacementCookies.erase(key);
      }

      m_DataSetBuilders.erase(key);

      if (doUpdate)
      {
         SimpleMutex mutex(m_EventBlocker); // prevent events from firing while update
         CLBAMViewerView* vw = (CLBAMViewerView*)m_Splitter.GetPane(0,1);
         vw->OnUpdate(NULL,0,0);
      }
   }
   catch(...)
   {
      ATLASSERT(0);
   }
}

IndexType CChildFrame::GetNumDataSetBuilders()
{
   return m_DataSetBuilders.size();
}

iDataSetBuilder* CChildFrame::GetDataSetBuilder(IndexType idx)
{
   ATLASSERT(idx>=0 && idx<GetNumDataSetBuilders());

   DataSetBuilderIterator it =  m_DataSetBuilders.begin();
   for (IndexType i=0; i<idx; i++)
      it++;

   ATLASSERT(it!=m_DataSetBuilders.end());
   return it->second;
}

// connection point implementation
HRESULT CChildFrame::XLiveLoadEvents::OnLiveLoadConfigurationChanged(ILiveLoadConfiguration* placement)
{
   METHOD_PROLOGUE(CChildFrame,LiveLoadEvents);

   if (pThis->m_EventBlocker)
   {
      SimpleMutex mutex(pThis->m_EventBlocker); // prevent events from firing while update
      CLBAMViewerView* vw = (CLBAMViewerView*)(pThis->m_Splitter).GetPane(0,1);
      vw->OnUpdate(NULL,TRUCK_POSITION_CHANGED_HINT,0);
   }

   return S_OK;
}
